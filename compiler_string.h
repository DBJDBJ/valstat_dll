#pragma once
#include "common.h"
/*
full compiler descriptor

string_p_ must be pre-allocated memory block of length string_len_
*/
__declspec(dllexport) int compiler_string(wchar_t* const cs_string_p_, int string_len_)
{

	ASSERT(cs_string_p_ != NULL); // remember: this is C code, not C++ hence the 'NULL'
	ASSERT(string_len_ > 1);

	static const wchar_t* const compiler_string_ =
		L"MSVC " WSTRNGFY(_MSC_FULL_VER) L"-" WSTRNGFY(_MSC_BUILD)
		;
	const size_t compiler_string_len_ = wcslen(compiler_string_);
	ASSERT(compiler_string_len_ < string_len_);
	/*
	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l?view=msvc-160
	*/

	// (w)sprintf_s guarantees that the buffer will be null-terminated unless the buffer size is zero.
	// at this point string_len_ > compiler_string_len_
	// that matters because L'\0' will have to be appended to the cs_str_
	int rezult = swprintf_s(cs_string_p_, string_len_, L"%s", compiler_string_);

	return rezult > 0; // used as true or false by the callers
}

/*
In C# this function is declared as:

[DllImport(@"<full path>\valstat_dll.dll"
			, EntryPoint = "this_name",
			CharSet = CharSet.Unicode,
			ExactSpelling = true,
			SetLastError = true)]
static extern bool this_name([Out] char[] string_, Int32 string_length_);

thus we can use windows SetLastError() to signal the error to the caller
not as rich as valstat but works

*/
__declspec(dllexport) int this_name(wchar_t* const cs_string_p_, int string_len_)
{

	ASSERT(cs_string_p_ != NULL); // remember: this is C code, not C++ hence the 'NULL'
	ASSERT(string_len_ > 1);

	wchar_t const this_name_[1024] = { L'\0' };

	if (0 == GetModuleFileNameW(handle_store(NULL), this_name_, 1024))
	{
		SetLastError(GetLastError()); // signal to the "managed" caller
		return FALSE;
	}
	const size_t this_name_len_ = wcslen(this_name_);
	ASSERT(this_name_len_ < string_len_);

	int rezult = swprintf_s(cs_string_p_, string_len_, L"%s", this_name_);

	return rezult > 0; // used as true or false by the callers
}
