#pragma once
#include "common.h"
/*

in case of C# declared as:

[DllImport(valstat_dll_location, EntryPoint = "safe_division", CharSet = CharSet.Unicode, ExactSpelling = true)]
static extern void safe_division([Out] (int?, string?) valstat, decimal numerator, decimal denominator);
*/

typedef struct {

	int val;
	char* stat;
	int stat_len;

} int_string_valstat;

__declspec(dllexport)  void __stdcall safe_division(int_string_valstat* vst_ptr, int numerator, int denominator)
{
	const char* const message_ = "Jupi!";
	const size_t const message_len_ = strlen(message_);

	ASSERT(vst_ptr);
	vst_ptr->val = 42;
	vst_ptr->stat_len = 1 + (message_len_ < vst_ptr->stat_len ? message_len_ : vst_ptr->stat_len);

	int rez = sprintf_s(vst_ptr->stat, vst_ptr->stat_len, "%s", message_);

	ASSERT(rez > 1);
}

/* C#
unsafe struct int_charr_pair
{
	public int val;

	// NOTE! .NET Marshall defaul char is CharSet.Ansi
	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 255)]
	public char[] data;
}
*/

static enum { icp_data_count = 255 };

typedef struct {
	int val;
	char data[icp_data_count];
} int_charr_pair;

__declspec(dllexport) void safe_division_2(int_charr_pair* vst_ptr, int numerator, int denominator)
{
	ASSERT(vst_ptr);

	static const char  message_[] = { "HELLO FROM DLL" };
	const size_t const message_len_ = strlen(message_);

	vst_ptr->val = 42;

	int rez = sprintf_s(vst_ptr->data, icp_data_count, "%s", message_);

	ASSERT(rez > 1);
}

/// <summary>
///  using callbacks seems more maleable as a C# interop mechanism
/// </summary>
typedef void (*safe_division_fp)(int_charr_pair*);

__declspec(dllexport) void safe_division_cb(safe_division_fp callback_, int numerator, int denominator)
{
	ASSERT(callback_); // never fails

	static const char  message_[] = { "HELLO FROM DLL" };
	const size_t const message_len_ = strlen(message_);

	int_charr_pair icp = { 42 ,{0} };

	int rez = sprintf_s(icp.data, icp_data_count, "%s", message_);

	// dangerous but ok for playground
	callback_(&icp);
}

