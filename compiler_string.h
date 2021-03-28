#pragma once
#include "common.h"
/*
full compiler descriptor

string_p_ must be pre-allocated memory block of length string_len_
*/
__declspec(dllexport) int compiler_string(wchar_t* const cs_string_p_, int string_len_)
{

	ASSERT(cs_string_p_ != NULL); // remember: this is C code, not C++
	ASSERT(string_len_ > 1);

	static const wchar_t* const compiler_string_ =
		L"MSVC " WSTRNGFY(_MSC_FULL_VER) L"-" WSTRNGFY(_MSC_BUILD)
		;
	const size_t compiler_string_len_ = wcslen(compiler_string_);
	ASSERT(compiler_string_len_ < string_len_);
	/*
	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l?view=msvc-160

	int swprintf_s(
	   wchar_t *buffer,
	   size_t sizeOfBuffer,
	   const wchar_t *format,
	   ...
	);

	*/

	// (w)sprintf_s guarantees that the buffer will be null-terminated unless the buffer size is zero.
	// at this point string_len_ > compiler_string_len_
	// that matters because L'\0' will have to be appended to the cs_str_
	int rezult = swprintf_s(cs_string_p_, string_len_, L"%s", compiler_string_);

	return rezult > 0; // used as true or false by the callers
}
