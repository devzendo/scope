dnl @synopsis TYPE_SIZED_INTS
dnl
dnl Check for sized-int types like u_int16_t and int32_t, typically
dnl defined in sys/types.h.  If these are not defined, you will have
dnl to define your own versions.
dnl
dnl @version 1.2a, 2002/09/06
dnl @author Warren Young <warren@etr-usa.com>
AC_DEFUN([TYPE_SIZED_INTS],
[AC_CACHE_CHECK([for sized int types], ac_cv_type_sized_ints,
[
  AC_TRY_COMPILE(
  [
  	#include <sys/types.h>
  ],
  [
  	u_int8_t u8;
  	u_int16_t u16;
  	u_int32_t u32;
  	int8_t i8;
  	int16_t i16;
  	int32_t i32;
  ],
  ac_cv_type_sized_ints=yes,
  ac_cv_type_sized_ints=no)
])

  if test x"$ac_cv_type_sized_ints" = "xyes"
  then
    AC_DEFINE(HAVE_SIZED_INT_TYPES, 1,
			[ define if you have sized integer types like int16_t in sys/types.h ])
  else
	AC_MSG_ERROR([Cannot find header for sized int types like int16_t!])
  fi
])

