// Copyright (C) 2007-2012  CEA/DEN, EDF R&D, OPEN CASCADE
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
//

#ifndef _HELLO_HXX_
#define _HELLO_HXX_

#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(HELLO_Gen)
#include <SALOME_Component_i.hxx>

class HELLO:
  public POA_HELLO_ORB::HELLO_Gen,
  public Engines_Component_i 
{
public:
  HELLO( CORBA::ORB_ptr orb,
	 PortableServer::POA_ptr poa,
	 PortableServer::ObjectId* contId, 
	 const char* instanceName, 
	 const char* interfaceName );
  virtual ~HELLO();

  HELLO_ORB::status hello  ( SALOMEDS::Study_ptr study, const char* name );
  HELLO_ORB::status goodbye( SALOMEDS::Study_ptr study, const char* name );
  void              copyOrMove( const HELLO_ORB::object_list& what,
				SALOMEDS::SObject_ptr where,
				CORBA::Long row, CORBA::Boolean isCopy );
  virtual char*     getVersion();
};

extern "C"
PortableServer::ObjectId* HELLOEngine_factory( CORBA::ORB_ptr orb,
					       PortableServer::POA_ptr poa,
					       PortableServer::ObjectId* contId,
					       const char* instanceName,
					       const char* interfaceName );

#endif
