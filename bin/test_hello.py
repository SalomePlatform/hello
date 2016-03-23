# Copyright (C) 2007-2016  CEA/DEN, EDF R&D, OPEN CASCADE
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#
# See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
#

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
