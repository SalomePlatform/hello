//  HELLOGUI : HELLO component GUI implemetation 
//

#ifndef _HELLOGUI_H_
#define _HELLOGUI_H_

#include "SALOMEGUI.h"
#include "QAD_Desktop.h"

#include <SALOMEconfig.h>
#include CORBA_CLIENT_HEADER(HELLO_Gen)



class HELLOGUI: public SALOMEGUI
{
  Q_OBJECT

public:
  HELLOGUI( const QString& name = "", QObject* parent = 0 );

  virtual bool OnGUIEvent (int theCommandID, QAD_Desktop* parent);

  virtual bool SetSettings (QAD_Desktop* parent);

  virtual bool CustomPopup ( QAD_Desktop* parent,
			    QPopupMenu* popup,
			    const QString & theContext,
			    const QString & theParent,
			    const QString & theObject);

  virtual void DefinePopup(QString & theContext, QString & theParent, QString & theObject);

  virtual bool ActiveStudyChanged ( QAD_Desktop* parent );

  static HELLO_ORB::HELLO_Gen_ptr InitHELLOGen(QAD_Desktop* parent);

protected:

private:

};

#endif
