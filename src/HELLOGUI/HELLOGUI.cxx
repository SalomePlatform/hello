// Copyright (C) 2005  CEA/DEN, EDF R&D
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License.
//
// This library is distributed in the hope that it will be useful
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//
#include "HELLOGUI.h"

#include <SUIT_MessageBox.h>
#include <SUIT_ResourceMgr.h>
#include <SUIT_Desktop.h>
#include <SalomeApp_Application.h>

#include <SALOME_LifeCycleCORBA.hxx>

// QT Includes
#include <QInputDialog>
#include <QIcon>

using namespace std;

// Constructor
HELLOGUI::HELLOGUI() :
  SalomeApp_Module( "HELLO" ) // default name
{
}

// Gets an reference to the module's engine
HELLO_ORB::HELLO_Gen_ptr HELLOGUI::InitHELLOGen( SalomeApp_Application* app )
{
  Engines::Component_var comp = app->lcc()->FindOrLoad_Component( "FactoryServer","HELLO" );
  HELLO_ORB::HELLO_Gen_ptr clr = HELLO_ORB::HELLO_Gen::_narrow(comp);
  ASSERT(!CORBA::is_nil(clr));
  return clr;
}

// Module's initialization
void HELLOGUI::initialize( CAM_Application* app )
{

  SalomeApp_Module::initialize( app );

  InitHELLOGen( dynamic_cast<SalomeApp_Application*>( app ) );

  QWidget* aParent = application()->desktop();
  SUIT_ResourceMgr* aResourceMgr = app->resourceMgr();

  // create actions
  createAction( 190, tr( "TLT_MY_NEW_ITEM" ), QIcon(), tr( "MEN_MY_NEW_ITEM" ), tr( "STS_MY_NEW_ITEM" ), 0, aParent, false,
		this, SLOT( OnMyNewItem() ) );
  QPixmap aPixmap = aResourceMgr->loadPixmap( "HELLO",tr( "ICON_GET_BANNER" ) );
  createAction( 901, tr( "TLT_GET_BANNER" ), QIcon( aPixmap ), tr( "MEN_GET_BANNER" ), tr( "STS_GET_BANNER" ), 0, aParent, false,
		this, SLOT( OnGetBanner() ) );

  // create menus
  int aMenuId;
  aMenuId = createMenu( tr( "MEN_FILE" ), -1, -1 );
  createMenu( separator(), aMenuId, -1, 10 );
  aMenuId = createMenu( tr( "MEN_FILE_HELLO" ), aMenuId, -1, 10 );
  createMenu( 190, aMenuId );

  aMenuId = createMenu( tr( "MEN_HELLO" ), -1, -1, 30 );
  createMenu( 901, aMenuId, 10 );

  // create toolbars
  int aToolId = createTool ( tr( "TOOL_HELLO" ) );
  createTool( 901, aToolId );
}

// Module's engine IOR
QString HELLOGUI::engineIOR() const
{
  CORBA::String_var anIOR = getApp()->orb()->object_to_string( InitHELLOGen( getApp() ) );
  return QString( anIOR.in() );
}

// Module's activation
bool HELLOGUI::activateModule( SUIT_Study* theStudy )
{
  bool bOk = SalomeApp_Module::activateModule( theStudy );

  setMenuShown( true );
  setToolShown( true );

  return bOk;
}

// Module's deactivation
bool HELLOGUI::deactivateModule( SUIT_Study* theStudy )
{
  setMenuShown( false );
  setToolShown( false );

  return SalomeApp_Module::deactivateModule( theStudy );
}

// Default windows
void HELLOGUI::windows( QMap<int, int>& theMap ) const
{
  theMap.clear();
  theMap.insert( SalomeApp_Application::WT_ObjectBrowser, Qt::LeftDockWidgetArea );
  theMap.insert( SalomeApp_Application::WT_PyConsole,     Qt::BottomDockWidgetArea );
}

// Action slot
void HELLOGUI::OnMyNewItem()
{
  SUIT_MessageBox::warning( getApp()->desktop(),tr( "INF_HELLO_BANNER" ), tr( "INF_HELLO_MENU" ) );
}

// Action slot
void HELLOGUI::OnGetBanner()
{
  // Dialog to get the Name
  bool ok = FALSE;
  QString myName = QInputDialog::getText( getApp()->desktop(), tr( "QUE_HELLO_LABEL" ), tr( "QUE_HELLO_NAME" ),
					  QLineEdit::Normal, QString::null, &ok );

  if ( ok && !myName.isEmpty()) // if we got a name, get a HELLO component and ask for makeBanner
  {
    HELLO_ORB::HELLO_Gen_ptr hellogen = HELLOGUI::InitHELLOGen( getApp() );
    QString banner = hellogen->makeBanner( (const char*)myName.toLatin1() );
    SUIT_MessageBox::information( getApp()->desktop(), tr( "INF_HELLO_BANNER" ), banner, tr( "BUT_OK" ) );
  }
}

// Export the module
extern "C" {
  CAM_Module* createModule()
  {
    return new HELLOGUI();
  }
}
