//  Copyright (C) 2007-2010  CEA/DEN, EDF R&D, OPEN CASCADE
//
//  Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
//  See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
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

/*!
  \brief Constructor
  
  Creates an instance of the HELLO GUI module.

  \note Since SalomeApp_Module uses virtual inheritance 
  from LightApp_Module class, it's necessary to call both
  base classes constructors, even though HELLOGUI class
  inherits directly only SalomeApp_Module.
*/
HELLOGUI::HELLOGUI() :
  SalomeApp_Module( "HELLO" ), // module name
  LightApp_Module( "HELLO" )   // module name
{
}

/*!
  \brief Destructor
  
  Destroys any allocated resources.
*/  
HELLOGUI::~HELLOGUI()
{
  // nothing to do
}

/*!
  \brief Gets an reference to the HELLO module CORBA engine

  Returns the reference to the HELLO engine, loading it to the C++ container
  (FactoryServer by default) if necessary.

  \param app pointer to the current application instance
  \return reference to the module engine
*/
HELLO_ORB::HELLO_Gen_ptr HELLOGUI::InitHELLOGen( SalomeApp_Application* app )
{
  Engines::Component_var comp = app->lcc()->FindOrLoad_Component( "FactoryServer","HELLO" );
  HELLO_ORB::HELLO_Gen_ptr clr = HELLO_ORB::HELLO_Gen::_narrow(comp);
  ASSERT(!CORBA::is_nil(clr));
  return clr;
}

/*!
  \brief Module initialization.

  Overloaded from CAM_Module class.
  
  Perform general module initialization (like creation of actions,
  menus, toolbars, etc).

  \note This function is invoked only once per study, when the module
  is first time activated by the user.
  The study associated with the application might not exist
  (created or opened) when this function is invoked, so it is not
  recommended to perform any study-dependant actions here.

  \param app pointer to the current application instance
*/
void HELLOGUI::initialize( CAM_Application* app )
{
  // call the parent implementation
  SalomeApp_Module::initialize( app );

  // load HELLO module engine, if necessary
  HELLO_ORB::HELLO_Gen_var engine = InitHELLOGen( dynamic_cast<SalomeApp_Application*>( app ) );

  // get reference to the desktop and resources manager
  QWidget* aDesktop = application()->desktop();
  SUIT_ResourceMgr* aResourceMgr = app->resourceMgr();

  // create actions
  createAction( 190, tr( "TLT_MY_NEW_ITEM" ), QIcon(), tr( "MEN_MY_NEW_ITEM" ), tr( "STS_MY_NEW_ITEM" ), 0, aDesktop, false,
		this, SLOT( OnMyNewItem() ) );
  QPixmap aPixmap = aResourceMgr->loadPixmap( "HELLO",tr( "ICON_GET_BANNER" ) );
  createAction( 901, tr( "TLT_GET_BANNER" ), QIcon( aPixmap ), tr( "MEN_GET_BANNER" ), tr( "STS_GET_BANNER" ), 0, aDesktop, false,
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

/*!
  \brief Get module engine IOR

  Overloaded from SalomeApp_Module class.

  Returns the reference to the module engine, loading it if necessary.
 
  \return string containing module engine IOR
*/
QString HELLOGUI::engineIOR() const
{
  CORBA::String_var anIOR = getApp()->orb()->object_to_string( InitHELLOGen( getApp() ) );
  return QString( anIOR.in() );
}

/*!
  \brief Get module icon.

  Overloaded from CAM_Module class.

  Load and return the module icon pixmap. This icon is shown, for example,
  in the Object browser.

  Default implementation uses iconName() function to retrieve the name
  of the image file to be used as the module icon and tries to load this
  file and create pixmap from it.
  Returns valid QPixmap instance if image is loaded correctly.

  \return module icon pixmap
  \sa iconName()
*/
QPixmap HELLOGUI::moduleIcon() const
{
  // nothing to do, in this example just call the parent implementation
  return SalomeApp_Module::moduleIcon();
}

/*!
  \brief Get module icon's name.

  Overloaded from CAM_Module class.

  This function is used to get module icon image file name.
  Default implementation tries to retrieve the name of the
  icon file from the application using moduleIcon() function, which
  in its turn retrieves the information about the module icon
  from the configuration file (e.g. SalomeApp.xml, LightApp.xml).

  \return module icon file name
  \sa moduleIcon()
*/
QString HELLOGUI::iconName() const
{
  // nothing to do, in this example just call the parent implementation
  return SalomeApp_Module::iconName();
}

/*!
  \brief Get compatible dockable windows.

  Overloaded from LightApp_Module class.

  Fills and returns the list of dockable windows which should be
  available when the module is active. It is a map of integer values
  where \c key is an enumerator from LightApp_Application::WindowTypes
  enumeration, specifying window type, and \c value is an enumerator
  from Qt::DockWidgetArea, specifying the window's default position
  in the main window layout.

  Empty map means no dockable windows available when the module is active.

  \param theMap this map should be filled to specify the list of
                required dockable windows withe their default positions
*/
void HELLOGUI::windows( QMap<int, int>& theMap ) const
{
  theMap.clear();
  theMap.insert( SalomeApp_Application::WT_ObjectBrowser, Qt::LeftDockWidgetArea );
  theMap.insert( SalomeApp_Application::WT_PyConsole,     Qt::BottomDockWidgetArea );
}

/*!
  \brief Get compatible view windows types.

  Overloaded from LightApp_Module class.

  Fills and returns the list of 3D/2D view windows types compatible
  with this module. The views of the specified types will be automatically
  activated (raised to the top of view stack) or created (if necessary)
  each time when the module is activated by the user.
  Empty list means no compatible view windows for the module.

  Example:
  \code
  theList.append( OCCViewer_Viewer::Type() );
  theList.append( SVTK_Viewer::Type() );
  \endcode

  \param theList this list should be filled to specify the list of
                 compatible view window types
*/
void HELLOGUI::viewManagers( QStringList& /*theList*/ ) const
{
  // no compatible view managers, nothing to do here
}

/*!
  \brief Create popup selection handler.

  Overloaded from LightApp_Module class.

  This function can be used to create custom popup menu handler.
  The application takes ownership over the returned pointer, 
  so you should not destroy it.
  
  This function is part of the context popup menu management mechanism.
  Selection object (instance of LightApp_Selection class or its successor)
  analizes the currently selected items and defines selection-dependant
  variables which are processed by the popup manager (QtxPopupMgr class).
  
  These variables can be included into the lexical constructions, named
  "rules", which are associated with the popup menu actions (refer to the
  QtxPopupMgr class for more details).

  Exampe:
  \code
  // obtain popup manager
  QtxPopupMgr* mgr = popupMgr();
  // create new action, with ID = 100
  createAction( 100, "Action", QIcon(), "Action", "My action", 0, application()->desktop(),
                false, this, SLOT( OnMyAction() ) );
  // define popup rule for action
  QString rule = "client='ObjectBrowser' and $type in {'MyType1' 'MyType2'} and selcount=1";
  // set visibility rule for action
  mgr->setRule( 100, rule, QtxPopupMgr::VisibleRule );
  \endcode

  In the above code, \a selcount variable is automatically defined 
  by LightApp_Selection class, but \a type variable should be set by
  the successor class. Note, that LightApp_Selection class implements
  several useful variables which can be used in the lexical rules.
  
  \return new selection object
  \sa contextMenuPopup()
*/
LightApp_Selection* HELLOGUI::createSelection() const
{
  // nothing to do, in this example just call the parent implementation
  return SalomeApp_Module::createSelection();
}

/*!
  \brief Create displayer object.

  Overloaded from LightApp_Module class.

  This function can be used to create and return custom displayer object.
  The application does not take the ownership over the returned value.

  Displayer is a part of the presentations management system.
  If can be used to implement visualization operations, like create, show
  or hide presentation in the viewer of specific type, etc.

  \return pointer to the module displayer
 */
LightApp_Displayer* HELLOGUI::displayer()
{
  // nothing to do, in this example just call the parent implementation
  return SalomeApp_Module::displayer();
}

/*!
  \brief Create context popup menu.

  Overloaded from CAM_Module class.

  This function can be used to customize context popup menu management.
  The module should fill \a menu with the items (e.g. by inserting own
  QAction items). The menu contents can be context-depending, the parameter
  \a type can be used to test the context of the popup menu invocation
  (e.g. "ObjectBrowser").
  Parameter \a title can be used to return the string value to be used
  popup menu title if required.

  Default implementation from LightApp_Module class calls createSelection()
  function to create popup selection handler and initialized the popup menu
  using popup manager.
    
  \param type popup menu context
  \param menu pointer to the popup menu
  \param title custom popup menu title can be returned here
  \sa createSelection()
*/
void HELLOGUI::contextMenuPopup( const QString& type, QMenu* menu, QString& title )
{
  // nothing to do, in this example just call the parent implementation
  return SalomeApp_Module::contextMenuPopup( type, menu, title );
}

/*!
  \brief Export module preferences.

  Overloaded from LightApp_Module class.

  This function is invoked only once when the common "Preferences"
  dialog box is first time activated by the user (via the "File/Preferences"
  menu command) or when module is first time activated.

  This function should be used to export module preferences to the 
  common "Preferences" dialog box and associate them with the corresponding
  widgets. The preferences items are arranged to the tree-like structure, where
  top-level items represent just a containers for the underlying items.
  Each low-level preferences item is linked to the resources item (via "section"
  and "parameter" attributes). See QtxResourceMgr class for more details about
  resources management.

  Example:
  \code
  // create top-level preferences tab page
  int settingsId = addPreference( "Settings" );
  // create general settings group box
  int generalId = addPreference( tr( "General" ), settingsId );
  // set group box property - number of columns - to 2
  setPreferenceProperty( generalId, "columns", 2 );
  // create shading color preferences item (color button)
  addPreference( "Shading color", generalId, LightApp_Preferences::Color,
                 "HELLO", "shading_color" );
  // create precision preferences item (spin box)
  int precisionId = addPreference( tr( "GEOM_PREF_length_precision" ), generalId,
                 LightApp_Preferences::IntSpin, "HELLO", "precision" );
  // set precision preferences item properties
  setPreferenceProperty( precisionId, "min", 0 );
  setPreferenceProperty( precisionId, "max", 10 );
  \endcode

  \sa preferencesChanged()
*/
void HELLOGUI::createPreferences()
{
  // no module preferences, nothing to do here
}

/*!
  \brief Process preference item change event.

  Overloaded from LightApp_Module class.

  This function is called every time when the preference item
  owned by this module is changed by the user (usually this occurs when
  the user presses "OK" or "Apply" button in the "Preferences" dialog box).

  The module can perform any specific actions if necessary to response
  to the preferences changes.

  \param section resources item section name
  \param parameter resources item parameter name

  \sa createPreferences()
*/
void HELLOGUI::preferencesChanged( const QString& section, const QString& parameter )
{
  // nothing to do, in this example just call the parent implementation
  SalomeApp_Module::preferencesChanged( section, parameter );
}

/*!
  \brief Store visual state.

  Overloaded from SalomeApp_Module class.
  
  This method is called just before the study document is saved,
  so the module has a possibility to store any visual parameters
  in the AttributeParameter study attribute (if required).

  \param savePoint save point unique identifier
*/
void HELLOGUI::storeVisualParameters( int /*savePoint*/ )
{
  // no specific visual state, nothing to do here
}

/*!
  \brief Restore visual state.

  Overloaded from SalomeApp_Module class.
  
  This method is called after the study document is opened,
  so the module has a possibility to restore the visual parameters
  from the AttributeParameter study attribute (if required).

  \param savePoint save point unique identifier
*/
void HELLOGUI::restoreVisualParameters( int /*savePoint*/ )
{
  // no specific visual state, nothing to do here
}

/*!
  \brief Handle active study changing action.

  Overloaded from LightApp_Module class.
  
  This function is called each time when the active study is changed
  (usually this happens when users switches between different studies'
  desktops).

  Can be used to perform any relevant actions.
*/
void HELLOGUI::studyActivated()
{
  // no any specific action required, nothing to do here
}

/*!
  \brief Check if the module can perform "copy" operation.

  Overloaded from LightApp_Module class.
  
  This function is a part of the general copy/paste mechanism.

  Can be re-implemented to customize the copy/paste handling 
  in the module. Default implementation returns \c false.

  \return \c true if the module can perform "copy" operation or \c false otherwise
  \sa canPaste(), copy(), paste()
*/
bool HELLOGUI::canCopy() const
{
  // copy/paste is not supported, in this example just call the parent implementation
  return SalomeApp_Module::canCopy();
}

/*!
  \brief Check if the module can perform "paste" operation.

  Overloaded from LightApp_Module class.
  
  This function is a part of the general copy/paste mechanism.

  Can be re-implemented to customize the copy/paste handling 
  in the module. Default implementation returns \c false.

  \return \c true if the module can perform "paste" operation or \c false otherwise
  \sa canCopy(), copy(), paste()
*/
bool HELLOGUI::canPaste() const
{
  // copy/paste is not supported, in this example just call the parent implementation
  return SalomeApp_Module::canPaste();
}

/*!
  \brief Perform "copy" operation.

  Overloaded from LightApp_Module class.
  
  This function is a part of the general copy/paste mechanism.

  Can be re-implemented to customize the copy/paste handling 
  in the module. Default implementation does nothing.

  \sa canCopy(), canPaste(), paste()
*/
void HELLOGUI::copy()
{
  // copy/paste is not supported, nothing to do here
}

/*!
  \brief Perform "paste" operation.

  Overloaded from LightApp_Module class.
  
  This function is a part of the general copy/paste mechanism.

  Can be re-implemented to customize the copy/paste handling 
  in the module. Default implementation does nothing.

  \sa canCopy(), canPaste(), copy()
*/
void HELLOGUI::paste()
{
  // copy/paste is not supported, nothing to do here
}

/*!
  \brief Module activation.
  
  Overloaded from CAM_Module class.
  
  This function is called each time the module is activated
  by the user. It is usually used to perform any relevant actions,
  like displaying menus and toolbars, etc.
  
  \param theStudy current study object
  \return \c true if activation is completed correctly or \c false
          if module activation fails
  
  \sa deactivateModule()
*/
bool HELLOGUI::activateModule( SUIT_Study* theStudy )
{
  // call parent implementation
  bool bOk = SalomeApp_Module::activateModule( theStudy );

  // show own menus
  setMenuShown( true );
  // show own toolbars
  setToolShown( true );

  // return the activation status
  return bOk;
}

/*!
  \brief Module deactivation.
  
  Overloaded from CAM_Module class.
  
  This function is called each time the module is deactivated
  by the user. It is usually used to perform any relevant actions,
  like hiding menus and toolbars, etc.
  
  \param theStudy current study object
  \return \c true if deactivation is completed correctly or \c false
          if module deactivation fails

  \sa activateModule()
*/
bool HELLOGUI::deactivateModule( SUIT_Study* theStudy )
{
  // hide own menus
  setMenuShown( false );
  // hide own toolbars
  setToolShown( false );

  // call parent implementation and return the activation status
  return SalomeApp_Module::deactivateModule( theStudy );
}

/*!
  \brief Create specific operation object.
  
  Overloaded from LightApp_Module class.
  
  This function is a part of operation management mechanism.
  It can be used to create module specific operations, if module
  implements transaction handling basing on the GUI operations instances.

  This function is automatically called from startOperation() function.
  After operation is created, it can be started/stopped/paused/resumed etc.
  Compatibility between diferent simultaneously running operations is also
  checked by invoking of the corresponding methods of the LightApp_Operation
  class.

  The application takes ownership over the returned pointer, 
  so you should not destroy it.

  Default implementation in LightApp_Module class processes common Show/Hide
  operations.

  \param id unique operation identifier
  \return new operation object
*/
LightApp_Operation* HELLOGUI::createOperation( const int id ) const
{
  // no specific operations, in this example just call the parent implementation
  return SalomeApp_Module::createOperation( id );
}

/*!
  \brief Sample menu item action slot
*/
void HELLOGUI::OnMyNewItem()
{
  SUIT_MessageBox::warning( getApp()->desktop(),tr( "INF_HELLO_BANNER" ), tr( "INF_HELLO_MENU" ) );
}

/*!
  \brief "Show banner" menu item action slot
*/
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
