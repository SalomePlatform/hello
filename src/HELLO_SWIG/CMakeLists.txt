# Copyright (C) 2012-2021  CEA/DEN, EDF R&D, OPEN CASCADE
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

include(${SWIG_USE_FILE})

include_directories(
  ${KERNEL_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}/idl
  ${PROJECT_SOURCE_DIR}/src/HELLO
)

SET(_bin_SCRIPTS
  HELLO_SalomeSessionless.py
  ${CMAKE_CURRENT_BINARY_DIR}/HelloHelper.py
)

# additional preprocessor / compiler flags
ADD_DEFINITIONS(${OMNIORB_DEFINITIONS}  )

# SWIG wrapping
SET(HelloHelper_HEADERS HelloHelper.h HelloHelper.i)
SET(HelloHelper_SOURCES HelloHelper.cxx ${HelloHelper_HEADERS})
SET_SOURCE_FILES_PROPERTIES(HelloHelper.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(HelloHelper.i PROPERTIES SWIG_FLAGS "-py3")
SET_SOURCE_FILES_PROPERTIES(HelloHelper_wrap.cpp PROPERTIES COMPILE_FLAGS "-DHAVE_CONFIG_H")
#SET(_swig_SCRIPTS ${CMAKE_CURRENT_BINARY_DIR}/HelloHelper.py )
IF(${CMAKE_VERSION} VERSION_LESS "3.8.0") 
  SWIG_ADD_MODULE(HelloHelper python ${HelloHelper_SOURCES})
ELSE()
  SWIG_ADD_LIBRARY(HelloHelper LANGUAGE python SOURCES ${HelloHelper_SOURCES})
ENDIF()
SWIG_LINK_LIBRARIES(HelloHelper ${PYTHON_LIBRARIES} ${PLATFORM_LIBS} HELLOEngine ${KERNEL_SalomeKernelHelpers} ${KERNEL_SalomeDS} )
SWIG_CHECK_GENERATION(HelloHelper)
IF(WIN32)
  SET_TARGET_PROPERTIES(_HelloHelper PROPERTIES DEBUG_OUTPUT_NAME _HelloHelper_d)
ENDIF(WIN32)
install(TARGETS _HelloHelper DESTINATION ${SALOME_INSTALL_LIBS})
install(FILES ${HelloHelper_HEADERS} DESTINATION ${SALOME_INSTALL_HEADERS})
SALOME_INSTALL_SCRIPTS("${_swig_SCRIPTS}"  ${SALOME_INSTALL_BINS} EXTRA_DPYS "${SWIG_MODULE_HelloHelper_REAL_NAME}")

SALOME_INSTALL_SCRIPTS("${_bin_SCRIPTS}" ${SALOME_INSTALL_PYTHON} DEF_PERMS)
