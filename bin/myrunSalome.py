#!/usr/bin/env python

def test(clt):
   """
        Test function that creates an instance of HELLO component
        usage : hello=test(clt)
   """
   # create an LifeCycleCORBA instance
   import LifeCycleCORBA
   lcc = LifeCycleCORBA.LifeCycleCORBA(clt.orb)
   import HELLO_ORB
   hello = lcc.FindOrLoadComponent("FactoryServer", "HELLO")
   return hello

#

if __name__ == "__main__":
   import user
   from runSalome import *
   clt,args = main()
   
   #
   #  Impression arborescence Naming Service
   #
   
   if clt != None:
     print
     print " --- registered objects tree in Naming Service ---"
     clt.showNS()
     session=clt.waitNS("/Kernel/Session")
     catalog=clt.waitNS("/Kernel/ModulCatalog")
     import socket
     container =  clt.waitNS("/Containers/" + socket.gethostname().split('.')[0] + "/FactoryServer")
