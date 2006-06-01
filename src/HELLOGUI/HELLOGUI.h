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
//  HELLOGUI : HELLO component GUI implemetation 
//

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

  void    initialize( CAM_Application* );
  QString engineIOR() const;
  void    windows( QMap<int, int>& ) const;

  static HELLO_ORB::HELLO_Gen_ptr InitHELLOGen( SalomeApp_Application* );

public slots:
  bool    deactivateModule( SUIT_Study* );
  bool    activateModule( SUIT_Study* );

protected slots:
  void            OnMyNewItem();
  void            OnGetBanner();
};

#endif
