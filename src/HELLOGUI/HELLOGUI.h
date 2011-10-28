// Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
//
// Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com

//  HELLOGUI : HELLO component GUI implemetation

#ifndef _HELLOGUI_H_
#define _HELLOGUI_H_

#include <SalomeApp_Module.h>

#include <SALOMEconfig.h>
#include CORBA_CLIENT_HEADER(HELLO_Gen)

class SalomeApp_Application;

class HELLOGUI: public SalomeApp_Module
{
  Q_OBJECT

public:
  HELLOGUI();
  ~HELLOGUI();

  static HELLO_ORB::HELLO_Gen_ptr InitHELLOGen( SalomeApp_Application* app );

  virtual void                initialize( CAM_Application* app );
  virtual QString             engineIOR() const;

  virtual QPixmap             moduleIcon() const;
  virtual QString             iconName() const;

  virtual void                windows( QMap<int, int>& theMap ) const;
  virtual void                viewManagers( QStringList& theList ) const;

  virtual LightApp_Selection* createSelection() const;
  virtual LightApp_Displayer* displayer();

  virtual void                contextMenuPopup( const QString& type, QMenu* menu, QString& title );

  virtual void                createPreferences();
  virtual void                preferencesChanged( const QString& section, const QString& parameter );

  virtual void                storeVisualParameters( int savePoint );
  virtual void                restoreVisualParameters( int savePoint );

  virtual void                studyActivated();

  virtual bool                canCopy() const;
  virtual bool                canPaste() const;
  virtual bool                isDragable(const SUIT_DataObject* what) const;
  virtual bool                isDropAccepted(const SUIT_DataObject* where) const;
  virtual void                dropObjects(const DataObjectList& what, Qt::DropAction action,
                                          const SUIT_DataObject* parent, const int row);
  virtual void                copy();
  virtual void                paste();

public slots:
  virtual bool                activateModule( SUIT_Study* theStudy );
  virtual bool                deactivateModule( SUIT_Study* theStudy );

protected:
  virtual LightApp_Operation* createOperation( const int id ) const;

protected slots:
  void                        OnMyNewItem();
  void                        OnGetBanner();
};

#endif // _HELLOGUI_H_
