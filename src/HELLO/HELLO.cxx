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
