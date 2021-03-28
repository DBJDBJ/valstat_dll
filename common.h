#pragma once
#define WIN32_LEAN_AND_MEAN 
#define STRICT 1
#include <windows.h>

#ifndef _UNICODE
#error Make sure your interop dll's are unicode and using wchar_t only. This one is not.
#endif  // _UNICODE

// https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-disablethreadlibrarycalls
// must not use static runtime, reason is:
// using DisableThreadLibraryCalls(hModule);
#include <crtdbg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h> // otherwise linker will not find wide versions

#define ASSERT _ASSERTE

#define ARRAY_LENGTH(array) __countof(array)
#define ARRAY_END(array) (&array[ARRAY_LENGTH(array)])

// vcruntime.h contains all the necessary macros
// do not re-invent them
// 
// remember: must be 100% wchar_t compatible
// this is  planet WIN32
#define WSTRNGFY(X_) _CRT_WIDE( _CRT_STRINGIZE(X_)  ) 
// 

#ifndef STATIC_ASSERT_MSG
#   if defined(static_assert)
#       define STATIC_ASSERT_MSG(expr, msg) static_assert(expr, msg)
#   elif defined(_STATIC_ASSERT)
#       define STATIC_ASSERT_MSG(expr, msg) _STATIC_ASSERT(expr)
#   elif defined(_MSC_VER)
#       include <crtdbg.h>
#       define STATIC_ASSERT_MSG(expr, msg) _STATIC_ASSERT(expr)
#   elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) \
          || __has_feature(c_static_assert)
#       define STATIC_ASSERT_MSG(expr, msg) _Static_assert(expr, msg)
#   else
#       define STATIC_ASSERT_MSG(expr, msg) switch (0) {case 0:case (expr):;}
#   endif
#endif /* STATIC_ASSERT */

#ifndef STATIC_ASSERT
#   define STATIC_ASSERT(expr) STATIC_ASSERT_MSG(expr, #expr)
#endif

#define OK_VAL 42
