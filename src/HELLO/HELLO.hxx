#ifndef _HELLO_HXX_
#define _HELLO_HXX_

#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(HELLO_Gen)
#include "SALOME_Component_i.hxx"

class HELLO:
  public POA_HELLO_ORB::HELLO_Gen,
  public Engines_Component_i 
{

public:
    HELLO(CORBA::ORB_ptr orb,
	    PortableServer::POA_ptr poa,
	    PortableServer::ObjectId * contId, 
	    const char *instanceName, 
	    const char *interfaceName);
    virtual ~HELLO();

    //

    char* makeBanner(const char* name);

};

extern "C"
    PortableServer::ObjectId * HELLOEngine_factory(
	    CORBA::ORB_ptr orb,
	    PortableServer::POA_ptr poa,
	    PortableServer::ObjectId * contId,
	    const char *instanceName,
	    const char *interfaceName);


#endif
