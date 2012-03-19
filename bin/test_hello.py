##
# Test functionality of HELLO module
##

# initialize salome session
import salome
salome.salome_init()

# get reference to the HELLO engine
import HELLO_ORB
hello = salome.lcc.FindOrLoadComponent('FactoryServer', 'HELLO')

# test HELLO module
print "Say hello to John: should be OK"
if hello.hello(salome.myStudy, "John") != HELLO_ORB.OP_OK:
    print "ERROR: wrong operation code is returned"
else:
    print "OK"
print "Say hello to John: should answer 'already met'"
if hello.hello(salome.myStudy, "John") != HELLO_ORB.OP_ERR_ALREADY_MET:
    print "ERROR: wrong operation code is returned"
else:
    print "OK"
print "Say goodbye to Margaret: should answer 'did not meet yet'"
if hello.goodbye(salome.myStudy, "Margaret") != HELLO_ORB.OP_ERR_DID_NOT_MEET:
    print "ERROR: wrong operation code is returned"
else:
    print "OK"
print "Say hello to John: should be OK"
if hello.goodbye(salome.myStudy, "John") != HELLO_ORB.OP_OK:
    print "ERROR: wrong operation code is returned"
else:
    print "OK"
print "Say hello to John: should answer 'did not meet yet'"
if hello.goodbye(salome.myStudy, "John") != HELLO_ORB.OP_ERR_DID_NOT_MEET:
    print "ERROR: wrong operation code is returned"
else:
    print "OK"
