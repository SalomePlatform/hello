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

HELLOGUI::HELLOGUI( const QString& theName, QObject* theParent ) :
  SALOMEGUI( theName, theParent )
{}


// launch HELLO component and return a handle
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
    case 901: // call getBanner service
      {
	MESSAGE("command " << theCommandID << " activated");

	QString myStudyName = myActiveStudy->getTitle();
	int myStudyId = myActiveStudy->getStudyId();
	
	bool ok=FALSE;

	// Dialog to get the Name
	QString myName;
	myName = QInputDialog::getText( tr("QUE_HELLO_LABEL"), tr("QUE_HELLO_NAME"), 
		QLineEdit::Normal,
		QString::null, &ok);

	if ( ! myName.isEmpty()) // if we got a name, get a HELLO component and ask for makeBanner
	{
	    HELLO_ORB::HELLO_Gen_ptr hellogen = HELLOGUI::InitHELLOGen(parent);
	    QString banner = hellogen->makeBanner(myName);
	    QAD_MessageBox::info1( parent, tr("INF_HELLO_BANNER"), banner, tr("BUT_OK"));
	}
	else
	{
	    MESSAGE("CANCEL");
	}

      }
      break;
    case 190: // just a test in File Menu
      {
	    QAD_MessageBox::warn1 (parent,tr("INF_HELLO_BANNER"),tr("INF_HELLO_MENU"),tr("BUT_OK"));
      }
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

bool HELLOGUI::ActiveStudyChanged( QAD_Desktop* parent )
{
  MESSAGE("HELLOGUI::ActiveStudyChanged");
  return true;
}

void HELLOGUI::DefinePopup( QString & theContext, QString & theParent, QString & theObject )
{
  MESSAGE("HELLOGUI::DefinePopup");
  //theObject = "";
  //theContext = "";
}


static HELLOGUI aGUI("");
extern "C"
{
  Standard_EXPORT SALOMEGUI* GetComponentGUI() {
    return &aGUI;
  }
}
