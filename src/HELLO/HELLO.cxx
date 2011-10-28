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

using namespace std;

#include "HELLO.hxx"

#include "Utils_CorbaException.hxx"
#include "OpUtil.hxx"
#include "Utils_ExceptHandlers.hxx"
#include "utilities.h"

#include CORBA_CLIENT_HEADER(SALOMEDS_Attributes)

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

void HELLO::createObject(SALOMEDS::Study_ptr theStudy,
                         const char* theName) throw (SALOME::SALOME_Exception)
{
  Unexpect aCatch(SALOME_SalomeException);

  SALOMEDS::SObject_var aResultSO;
  if (theStudy->_is_nil()) return;

  SALOMEDS::GenericAttribute_var anAttr;
  SALOMEDS::StudyBuilder_var     aStudyBuilder = theStudy->NewBuilder();
  // BEGIN: add to UseCaseTree (this must be done on KERNEL level automatically?)
  SALOMEDS::UseCaseBuilder_var   aUseCaseBuilder = theStudy->GetUseCaseBuilder();
  // END: add to UseCaseTree (this must be done on KERNEL level automatically?)

  SALOMEDS::SComponent_var aFather = theStudy->FindComponent("HELLO");
  if (aFather->_is_nil()) {
    aFather = aStudyBuilder->NewComponent("HELLO");
    anAttr = aStudyBuilder->FindOrCreateAttribute(aFather, "AttributeName");
    SALOMEDS::AttributeName_var aName = SALOMEDS::AttributeName::_narrow(anAttr);
    aName->SetValue("Hellos");
    aName->UnRegister();

    //anAttr = aStudyBuilder->FindOrCreateAttribute(aFather, "AttributePixMap");
    //SALOMEDS::AttributePixMap_var aPixMap=SALOMEDS::AttributePixMap::_narrow(anAttr);
    //aPixMap->SetPixMap("ICON_GET_BANNER");
    //aPixMap->UnRegister();
    aStudyBuilder->DefineComponentInstance(aFather, (HELLO_ORB::HELLO_Gen_var)HELLO_Gen::_this());

    // BEGIN: add to UseCaseTree (this must be done on KERNEL level automatically?)
    //aUseCaseBuilder->SetRootCurrent();
    //SALOMEDS::SObject_var aRootObj = aUseCaseBuilder->GetCurrentObject();
    //if (!aUseCaseBuilder->HasChildren(aRootObj)) {
    if (!aUseCaseBuilder->IsUseCaseNode(aFather)) {
      aUseCaseBuilder->SetRootCurrent();
      aUseCaseBuilder->Append(aFather);
    }
    // END: add to UseCaseTree (this must be done on KERNEL level automatically?)
  }
  if (aFather->_is_nil()) return;

  aResultSO = aStudyBuilder->NewObject(aFather);
  aResultSO->SetAttrString("AttributeName", theName);

  // BEGIN: add to UseCaseTree (this must be done on KERNEL level automatically?)
  aUseCaseBuilder->AppendTo(aFather, aResultSO);
  // END: add to UseCaseTree (this must be done on KERNEL level automatically?)

  aFather->UnRegister();
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
    return myHELLO->getId();
  }
}
