# Copyright (C) 2007-2013  CEA/DEN, EDF R&D, OPEN CASCADE
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License.
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

# -* Makefile *- 
# Author : 
# Modified by : Alexander BORODIN (OCN) - autotools usage
# Module : GHS3DPLUGIN
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	HELLOGUI.h

# Libraries targets
lib_LTLIBRARIES = libHELLO.la

dist_libHELLO_la_SOURCES = \
	HELLOGUI.cxx

# MOC pre-processing
MOC_FILES = \
	HELLOGUI_moc.cxx

nodist_libHELLO_la_SOURCES = $(MOC_FILES)

libHELLO_la_CPPFLAGS = \
	$(QT_INCLUDES) \
	$(CAS_CPPFLAGS) \
	$(PYTHON_INCLUDES) \
	$(BOOST_CPPFLAGS) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	$(GUI_CXXFLAGS) \
	-I$(srcdir)/../HELLO \
	-I$(top_builddir)/idl \
	-I$(top_builddir)

libHELLO_la_LDFLAGS  = \
	../../idl/libSalomeIDLHELLO.la \
	../HELLO/libHELLOEngine.la \
	$(KERNEL_LDFLAGS) -lSalomeLifeCycleCORBA \
	$(GUI_LDFLAGS) \
	-lSalomeApp

# resources files
nodist_salomeres_DATA = \
	HELLO_msg_en.qm \
	HELLO_msg_fr.qm \
	HELLO_icons.qm
