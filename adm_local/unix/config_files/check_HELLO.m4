#  Check availability of HELLO module binary distribution
#
#  Author : Marc Tajchman (CEA, 2002)
#------------------------------------------------------------

AC_DEFUN([CHECK_HELLO],[

AC_CHECKING(for Hello)

Hello_ok=no

AC_ARG_WITH(hello,
	    --with-hello=DIR root directory path of HELLO installation,
	    HELLO_DIR="$withval",HELLO_DIR="")

if test "x$HELLO_DIR" = "x" ; then

# no --with-gui-dir option used

  if test "x$HELLO1_ROOT_DIR" != "x" ; then

    # HELLO1_ROOT_DIR environment variable defined
    HELLO_DIR=$HELLO1_ROOT_DIR

  else

    # search hello binaries in PATH variable
    AC_PATH_PROG(TEMP, libHELLO.so)
    if test "x$TEMP" != "x" ; then
      HELLO_BIN_DIR=`dirname $TEMP`
      HELLO_DIR=`dirname $HELLO_BIN_DIR`
    fi

  fi
#
fi

if test -f ${HELLO_DIR}/lib/salome/libHELLO.so  ; then
  Hello_ok=yes
  AC_MSG_RESULT(Using HELLO distribution in ${HELLO_DIR})

  if test "x$HELLO1_ROOT_DIR" == "x" ; then
    HELLO1_ROOT_DIR=${HELLO_DIR}
  fi
  AC_SUBST(HELLO1_ROOT_DIR)
else
  AC_MSG_WARN("Cannot find compiled HELLO distribution")
fi
  
AC_MSG_RESULT(for HELLO: $Hello_ok)
 
])dnl
 
