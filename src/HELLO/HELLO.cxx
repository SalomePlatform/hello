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
using namespace std;
#include "HELLO.hxx"
#include "utilities.h"

#include <string>


//=============================================================================
/*!
 *  standard constructor
 */
//=============================================================================

HELLO::HELLO(CORBA::ORB_ptr orb,
	PortableServer::POA_ptr poa,
	PortableServer::ObjectId * contId, 
	const char *instanceName, 
	const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName)
{
  MESSAGE("activate object");
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
}

HELLO::~HELLO()
{
}


char* HELLO::makeBanner(const char* name)
{
    string banner="Hello, ";
    banner+=name;
    return CORBA::string_dup(banner.c_str());
}



extern "C"
{
  PortableServer::ObjectId * HELLOEngine_factory(
			       CORBA::ORB_ptr orb,
			       PortableServer::POA_ptr poa, 
			       PortableServer::ObjectId * contId,
			       const char *instanceName, 
		       	       const char *interfaceName)
  {
    MESSAGE("PortableServer::ObjectId * HELLOEngine_factory()");
    SCRUTE(interfaceName);
    HELLO * myHELLO 
      = new HELLO(orb, poa, contId, instanceName, interfaceName);
    return myHELLO->getId() ;
  }
}
