///
/// \file CAMERA_ClassCameraProtocolDecode.h
/// \brief CLASS_CAMERA_PROTOCOL_DECODE class
/// \author Florian Roussel
/// \date 2018-06-06
///

#ifndef CAMERA_CLASSCAMERAPROTOCOLDECODE_H
#define CAMERA_CLASSCAMERAPROTOCOLDECODE_H

// C++ Standard
// Qt librairies
#include <QObject>
// Modules
#include "COMMON_TypeDefs.h"
// App
#include "CAMERA_ClassCameraProtocolData.h"

///
/// \class CLASS_CAMERA_PROTOCOL_DECODE
/// \brief CLASS_CAMERA_PROTOCOL_DECODE class
///
class CLASS_CAMERA_PROTOCOL_DECODE : public QObject
{
      Q_OBJECT

   public:

      /*--------------------------- Public types ---------------------------*/

      /*------------------------- Public constants ------------------------*/

      /*---------------------- Constructor / Destructor ---------------------*/

      ///
      /// \fn CLASS_CAMERA_PROTOCOL_DECODE(QObject *parent)
      /// \brief CLASS_CAMERA_PROTOCOL_DECODE constructor
      ///
      /// \param[in] parent : Parent object
      ///
      CLASS_CAMERA_PROTOCOL_DECODE(QObject *parent = nullptr);

      ///
      /// \fn ~CLASS_CAMERA_PROTOCOL_DECODE()
      /// \brief CLASS_CAMERA_PROTOCOL_DECODE destructor
      ///
      ~CLASS_CAMERA_PROTOCOL_DECODE();

      /*------------------------------ Getter -----------------------------*/

      /*------------------------------ Setter ------------------------------*/

      /*-------------------------- Public methods  -------------------------*/

      ///
      /// \fn Decode
      /// \brief Decode raw data
      /// \param[in] rawData : Raw data from communication
      /// \param[in] protocolDataDecoded
      /// \return Bool \e If raw data has been decoded into protocolDataDecoded
      ///
      static Bool Decode(const QByteArray& rawData, CLASS_CAMERA_PROTOCOL_DATA *protocolDataDecoded);

      /*--------------------------- Public signals -------------------------*/

   signals:

      /*---------------------------- Public slots --------------------------*/

   public slots:

      /*----------------------------- Private types ----------------------------*/

      /*--------------------------- Private methods --------------------------*/

   protected:

   private:

      /*------------------------------ Variables ------------------------------*/

   protected:

   private:

};

#endif // CAMERA_CLASSCAMERAPROTOCOLDECODE_H
