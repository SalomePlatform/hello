using namespace std;
#include "HELLOGUI.h"

// SALOME Includes
#include "Utils_ORB_INIT.hxx"
#include "Utils_SINGLETON.hxx"
#include "utilities.h"

#include "SALOME_Selection.h"
#include "SALOME_InteractiveObject.hxx"
#include "SALOMEGUI_QtCatchCorbaException.hxx"

#include "QAD_MessageBox.h"
//#include "QAD_Tools.h"
//#include "QAD_FileDlg.h"

//#include "SMESH_TypeFilter.hxx"

// QT Includes
#include <qinputdialog.h>
#include <qmessagebox.h>


HELLO_ORB::HELLO_Gen_ptr HELLOGUI::InitHELLOGen(QAD_Desktop* parent)
{
    Engines::Component_var comp =
	parent->getEngine("FactoryServer", "HELLO");
    HELLO_ORB::HELLO_Gen_ptr clr = HELLO_ORB::HELLO_Gen::_narrow(comp);
    ASSERT(!CORBA::is_nil(clr));
    return clr;
    //return clr._retn();
}


bool HELLOGUI::OnGUIEvent (int theCommandID, QAD_Desktop* parent)
{
  MESSAGE("HELLOGUI::OnGUIEvent");
  
  QAD_Study* myActiveStudy   = parent->getActiveStudy();

  QString file;

  switch (theCommandID)
    {
    case 941:
      {
	MESSAGE("command " << theCommandID << " activated");

	QString myStudyName = myActiveStudy->getTitle();
	int myStudyId = myActiveStudy->getStudyId();
	
	bool ok=FALSE;

	QString meshName;
	//meshName = QInputDialog::getText( "Saisie du Prénom", "Please, Enter your name", 
	meshName = QInputDialog::getText( tr("QUE_HELLO_LABEL"), tr("QUE_HELLO_NAME"), 
		QLineEdit::Normal,
		QString::null, &ok);

	if ( ! meshName.isEmpty())
	{
	    HELLO_ORB::HELLO_Gen_ptr hellogen = HELLOGUI::InitHELLOGen(parent);
	    QString banner = hellogen->makeBanner(meshName);
	    QMessageBox::about( parent, tr("INF_HELLO_BANNER"), banner);

	//    QAD_MessageBox::warn1 ((QWidget*)QAD_Application::getDesktop(),
	//	    Object::tr("WRN_WARNING"), 
	//	    QObject::tr("WRN_STUDY_LOCKED"),
	//	    QObject::tr("BUT_OK"));
	}
	else
	{
	    MESSAGE("CANCEL");
	}

      }
      break;
    }
  return true;
}


bool HELLOGUI::SetSettings (QAD_Desktop* parent)
{
  MESSAGE("HELLOGUI::SetSettings");
  return true;
}


bool HELLOGUI::CustomPopup ( QAD_Desktop* parent,
			   QPopupMenu* popup,
			   const QString & theContext,
			   const QString & theParent,
			   const QString & theObject )
{
  MESSAGE("HELLOGUI::CustomPopup");
  return true;
}

void HELLOGUI::ActiveStudyChanged( QAD_Desktop* parent )
{
  MESSAGE("HELLOGUI::ActiveStudyChanged");
}

void HELLOGUI::DefinePopup( QString & theContext, QString & theParent, QString & theObject )
{
  MESSAGE("HELLOGUI::DefinePopup");
  //theObject = "";
  //theContext = "";
}




extern "C"
{
  bool OnGUIEvent(int theCommandID, QAD_Desktop* parent)
  {
    return HELLOGUI::OnGUIEvent(theCommandID, parent);
  }


  bool SetSettings ( QAD_Desktop* parent )
  {
    return HELLOGUI::SetSettings( parent );
  }

  bool customPopup ( QAD_Desktop* parent,
		     QPopupMenu* popup,
		     const QString & theContext,
		     const QString & theParent,
		     const QString & theObject )
  {
    return HELLOGUI::CustomPopup( parent, popup, theContext,
				theParent, theObject );
  }

  void definePopup ( QString & theContext, QString & theParent, QString & theObject )
  {
    HELLOGUI::DefinePopup( theContext, theParent, theObject );
  }
  
  bool activeStudyChanged ( QAD_Desktop* parent )
  {
    HELLOGUI::ActiveStudyChanged( parent );
  }
}
