//  HELLOGUI : HELLO component GUI implemetation 
//

#ifndef _HELLOGUI_H_
#define _HELLOGUI_H_

#include "QAD_Desktop.h"

#include <SALOMEconfig.h>
#include CORBA_CLIENT_HEADER(HELLO_Gen)



class HELLOGUI: public QObject
{
  Q_OBJECT

public:

  static bool OnGUIEvent (int theCommandID, QAD_Desktop* parent);

  static bool SetSettings (QAD_Desktop* parent);

  static bool CustomPopup ( QAD_Desktop* parent,
			    QPopupMenu* popup,
			    const QString & theContext,
			    const QString & theParent,
			    const QString & theObject);

  static void DefinePopup(QString & theContext, QString & theParent, QString & theObject);

  static void ActiveStudyChanged ( QAD_Desktop* parent );

  static HELLO_ORB::HELLO_Gen_ptr InitHELLOGen(QAD_Desktop* parent);

protected:

private:

};

#endif
