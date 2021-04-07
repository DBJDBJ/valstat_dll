#pragma once
#include "common.h"

static enum { icp_data_count = 255 };

// this is the valstat structure
// for communicating to the "other"
// languages calling in here
typedef struct {
	int* val;
	char data[icp_data_count];
} int_charr_pair;
/*
Above struct in C#9 is declared as:

[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
struct int_charr_pair
{
	public int val;
	[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 255)]
	public string data;
}

NOTE: .NET default interop char is ANSI
*/

// if data is null valstat data will be an empty string
// that means it will be made of one char and that char is '\0'
inline void int_charr_pair_set_data(int_charr_pair* icp_, const  char* new_data_)
{
	ASSERT(icp_);
#ifdef _DEBUG
	memset(icp_->data, '\0', icp_data_count);
#endif

	if (new_data_) {
		int rez = sprintf_s(icp_->data, icp_data_count, "%s", new_data_);
		ASSERT(rez > 1);
	}
	else {
		icp_->data[0] = '\0';
	}
}

// this is an feeble attempt to send the address from the DLL stack space
// so that DLL caller can use it
inline void* last_result_address(int new_result)
{
	static int last_result_ = 0;
	last_result_ = new_result;
	return &last_result_;
}

// C#9 declaration
//  [DllImport(valstat_dll_location)]
//  static extern void safe_division(out int_charr_pair vst_ptr, int numerator, int denominator);
//
// using valstat protocol to send back full info
// through the pointer to the valstat struct
// sent from the caller
// CAVEAT EMPTOR: in case of MT we would need to enter the critical section here at the entrance
__declspec(dllexport) void safe_division(int_charr_pair* vst_ptr, int numerator, int denominator)
{
	ASSERT(vst_ptr);

	if (numerator > MAXINT32) {
		int_charr_pair_set_data(vst_ptr, "Error: numerator > uint32 max");
		vst_ptr->val = NULL;
		return;
	}

	if (numerator < 0) {
		int_charr_pair_set_data(vst_ptr, "Error: numerator < 0");
		vst_ptr->val = NULL;
		return;
	}

	if (denominator > MAXINT32) {
		int_charr_pair_set_data(vst_ptr, "Error: divisor > uint32 max");
		vst_ptr->val = NULL;
		return;
	}

	if (denominator < 0) {
		int_charr_pair_set_data(vst_ptr, "Error: divisor < 0");
		vst_ptr->val = NULL;
		return;
	}

	if (denominator == 0) {
		int_charr_pair_set_data(vst_ptr, "Error: divisor is 0");
		vst_ptr->val = NULL;
		return;
	}
	// if using heap we would need to use CoTaskMemAlloc
	// and C# Marshall will need to use CoTaskMemFree
	// thus we will
	// allocate result on dll global stack and use its address
	vst_ptr->val = last_result_address(numerator / denominator);
	int_charr_pair_set_data(vst_ptr, NULL);
	return;
}

/// <summary>
///  using callbacks seems more maleable as a C# interop mechanism
/// </summary>
typedef void (*safe_division_fp)(int_charr_pair*);

// CAVEAT EMPTOR: in case of MT we would need to enter the critical section here at the entrance
//                since there is a callback call, that call will hold this all locked until
//                callback finishes
//                thus the callers must "finish quickly"
__declspec(dllexport) void safe_division_cb(safe_division_fp callback_, int numerator, int denominator)
{
	ASSERT(callback_); // never fails

	int_charr_pair icp = { /*&fty2*/ NULL, {0} };

	int_charr_pair* vst_ptr = &icp;
	ASSERT(vst_ptr);

	if (numerator > MAXINT32) {
		int_charr_pair_set_data(vst_ptr, "Error: numerator > uint32 max");
		vst_ptr->val = NULL;
	}
	else if (numerator < 0) {
		int_charr_pair_set_data(vst_ptr, "Error: numerator < 0");
		vst_ptr->val = NULL;
	}
	else if (denominator > MAXINT32) {
		int_charr_pair_set_data(vst_ptr, "Error: divisor > uint32 max");
		vst_ptr->val = NULL;
	}
	else if (denominator < 0) {
		int_charr_pair_set_data(vst_ptr, "Error: divisor < 0");
		vst_ptr->val = NULL;
	}
	else if (denominator == 0) {
		int_charr_pair_set_data(vst_ptr, "Error: divisor is 0");
		vst_ptr->val = NULL;
	}
	else {
		// if using heap we would need to use CoTaskMemAlloc
		// and C# Marshall will need to use CoTaskMemFree
		// thus we will
		// allocate result on dll global stack and use its address
		vst_ptr->val = last_result_address(numerator / denominator);
		int_charr_pair_set_data(vst_ptr, NULL);
	}

	// 1.  we are using the address of the local variable, dangerous but ok for playground
	// 2. program flow will return here befroe leaving the dll
	callback_(vst_ptr);
}

