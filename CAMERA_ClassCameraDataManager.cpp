///
/// \file CAMERA_ClassCameraDataManager.cpp
/// \brief Classe CLASS_CAMERA_DATA_MANAGER
/// \author Florian Roussel
/// \date 2018-06-06
///
/// CLASS_CAMERA_DATA_MANAGER functions
///

// C++ Standard
// Qt librairies
#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QStringBuilder>
// Modules
#include "CAMERA_ClassCameraDataManager.h"
// App
#include "CAMERA_ClassCameraProtocolDecode.h"

/******************************** DEFINITIONS ********************************/

/*----------------------------- Public types -----------------------------*/
/*--------------------------- Public constants --------------------------*/
/*--------------------------- Public variables ---------------------------*/
/*------------------------------- Private types ------------------------------*/
/*---------------------------- Private constants ---------------------------*/
/*---------------------------- Private variables ----------------------------*/

/**************************** DEFINITIONS ENDING ****************************/

/******************************************************************************
 *                             Private functions                              *
 *****************************************************************************/

/******************************************************************************
 *                          Constructor / Destructor                          *
 *****************************************************************************/

///
/// \fn CLASS_CAMERA_DATA_MANAGER(QObject *parent)
/// \brief CLASS_CAMERA_DATA_MANAGER constructor
///
/// \param[in] udpLocalPort : UDP local port to receive image packets
/// \param[in] parent : Objet parent
///
CLASS_CAMERA_DATA_MANAGER::CLASS_CAMERA_DATA_MANAGER(const Word udpLocalPort, QObject *parent):
   QObject(parent),
   f_Udp(QHostAddress::LocalHost, udpLocalPort, this),
   f_ImageFileExtension(QLatin1String(".raw")),
   f_CurrentImage()
{

}

///
/// \fn ~CLASS_CAMERA_DATA_MANAGER()
/// \brief CLASS_CAMERA_DATA_MANAGER destructor
///
CLASS_CAMERA_DATA_MANAGER::~CLASS_CAMERA_DATA_MANAGER()
{
   // Remove image(s) class in the container
   for (CLASS_CAMERA_IMAGE* Image : f_CurrentImage.values())
      delete Image;

   f_CurrentImage.clear();
}

/******************************************************************************
 *                                 Getter                                     *
 *****************************************************************************/

/******************************************************************************
 *                                  Setter                                    *
 *****************************************************************************/

/******************************************************************************
 *                             Public methods                                 *
 *****************************************************************************/

///
/// \fn Start
/// \brief Start class initialisation
///
void CLASS_CAMERA_DATA_MANAGER::Start(void)
{
   // Open UDP communication
   if (f_Udp.Open() == false)
   {
      qDebug() << "Cannot open UDP communication, abort CameraImagesBackUpByUDP launch!";
      return;
   }

   // If we have open the UDP, we connect new data signal reception
   QObject::connect(&f_Udp, &CLASS_UDP::SIGNAL_NewDataAvailable, this, &CLASS_CAMERA_DATA_MANAGER::SLOT_NewDataReceived, Qt::QueuedConnection);

   qDebug() << "CameraImagesBackUpByUDP - Ready to receive image packets";
}

/******************************************************************************
 *                               Public slots                                 *
 *****************************************************************************/

///
/// \fn SLOT_NewDataReceived
/// \brief Receive new raw data from communication
/// \param[in] rawData : Raw data
///
void CLASS_CAMERA_DATA_MANAGER::SLOT_NewDataReceived(const QByteArray& rawData)
{
   // Contains decoded data from raw data received
   CLASS_CAMERA_PROTOCOL_DATA ProtocolDataDecoded;

   // Status of decoding data
   Bool DecodeDataStatus(CLASS_CAMERA_PROTOCOL_DECODE::Decode(rawData, &ProtocolDataDecoded));

   // If decoding status is true, we append/create image data
   if (DecodeDataStatus == true)
   {
      // Get image ID
      const Word ImageId(ProtocolDataDecoded.GetImageID());

      // If we haven't this image, we create it
      if (f_CurrentImage.contains(ImageId) == false)
         f_CurrentImage.insert(ImageId, new CLASS_CAMERA_IMAGE(ImageId, ProtocolDataDecoded.GetVerticalResolution(), ProtocolDataDecoded.GetHorizontalResolution()));

      // Get current image object
      CLASS_CAMERA_IMAGE* CurrentImage(f_CurrentImage.value(ImageId));

      if (CurrentImage != nullptr)
      {
         // Append pixels data
         CurrentImage->AppendPixelsData(ProtocolDataDecoded.GetLineNumber(), ProtocolDataDecoded.GetPixels());

         // If image is complete, we export image in file
         if (CurrentImage->ImageIsReadyToExport() == true)
         {
            // Create file if does not exist, otherwise erased the old
            QFile Image(QStandardPaths::displayName(QStandardPaths::TempLocation) % QString::number(CurrentImage->GetImageID()) % f_ImageFileExtension);

            if (Image.exists() == true)
            {
               if (Image.remove() == false)
               {
                  qDebug() << "Cannot erased previous image with image identifier: " % QString::number(ImageId) % ", abort writing and remove image data!";
                  // Remove image entry
                  f_CurrentImage.remove(ImageId);

                  return;
               }
            }

            // If the relevant file does not already exist, this function will try to create a new file before opening it
            if (Image.open(QIODevice::WriteOnly) == true)
            {
               QByteArray PixelsDataConcatened;

               // In QMap, values are sorted by key
               for (const QByteArray& PixelsDataPerLine : CurrentImage->GetPixels().values())
                  PixelsDataConcatened.append(PixelsDataPerLine);

               // Write Data in file
               Image.write(PixelsDataConcatened);

               // Close file
               Image.close();

               // Remove image entry
               f_CurrentImage.remove(ImageId);
            }
            else
            {
               qDebug() << "Cannot create image file with image identifier: " % QString::number(ImageId) % ", abort writing!";
            }
         }
      }
      else
      {
         qDebug() << "Cannot get image object for image identifier: " % QString::number(ImageId);
      }
   }
   else
   {
      qDebug() << "Error decoding data frame: " % rawData;
   }
}

/******************************************************************************
 *                              Private methods                               *
 *****************************************************************************/
