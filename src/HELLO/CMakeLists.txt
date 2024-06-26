# Copyright (C) 2012-2024  CEA, EDF, OPEN CASCADE
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

# --- options ---
# additional include directories
INCLUDE_DIRECTORIES(
  ${KERNEL_INCLUDE_DIRS}
  ${OMNIORB_INCLUDE_DIR}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_BINARY_DIR}/idl
)

# --- definitions ---
ADD_DEFINITIONS(
  ${OMNIORB_DEFINITIONS}
)

# libraries to link to
SET(_link_LIBRARIES
  ${OMNIORB_LIBRARIES}
  ${KERNEL_SalomeIDLKernel}
  ${KERNEL_OpUtil}
  ${KERNEL_SalomeContainer}
  ${KERNEL_SalomeKernelHelpers}
  ${KERNEL_SalomeDS}
  SalomeIDLHELLO
)

# --- headers ---

# header files / no moc processing
SET(HELLO_HEADERS
  HELLO.hxx
)

# --- sources ---

# sources / static
SET(HELLO_SOURCES
  HELLO.cxx
)

# --- rules ---

ADD_LIBRARY(HELLOEngine ${HELLO_SOURCES})
TARGET_LINK_LIBRARIES(HELLOEngine ${_link_LIBRARIES} )
INSTALL(TARGETS HELLOEngine EXPORT ${PROJECT_NAME}TargetGroup DESTINATION ${SALOME_INSTALL_LIBS})

INSTALL(FILES ${HELLO_HEADERS} DESTINATION ${SALOME_INSTALL_HEADERS})