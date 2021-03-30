//
// https://dbj.org/license_dbj
// 
// Big Note: this peoject is all C  code
// and there is no public header that would be normaly distrbuted 
// for callers to use
// thus there is no extern "C" {  ... }
//
#include "compiler_string.h"
#include "waveformat.h"
#include "safe_division.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	handle_store(hModule);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		/*BOOL failed =*/ DisableThreadLibraryCalls(hModule);
		/*_ASSERTE(failed);*/
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
		// in case you have not noticed in decades before
		// that above is the only break in here
		// so all the above "falls through" to it
	}
	return TRUE;
}


