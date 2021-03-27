//
// https://dbj.org/license_dbj
//
#define WIN32_LEAN_AND_MEAN 
// Windows Header Files
#include <windows.h>

#ifndef _UNICODE
#error Make sure your interop dll's are unicode and using wchar_t only. This one is not.
#endif  // _UNICODE

// https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-disablethreadlibrarycalls
// must not use static runtime, reason is:
// using DisableThreadLibraryCalls(hModule);
#include <crtdbg.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// functions exported start here

/*
 Just an Arbitrary but real example.

 mmsystem requires windows be included before it
  */
#include <mmsystem.h>
  /*
   This is to show using win32 structure from C# code.
   C# has to contain and use C# equivalent:

		 [StructLayout(LayoutKind.Sequential, Pack = 1)]
		  public struct WAVEFORMATEX
		  {
			  public ushort wFormatTag;
			  public ushort nChannels;
			  public uint nSamplesPerSec;
			  public uint nAvgBytesPerSec;
			  public ushort nBlockAlign;
			  public ushort wBitsPerSample;
			  public ushort cbSize;
		  }

		  And this is the mandatory C# declaration of the C function
		  implemented bellow. Of course this dll is best places in the
		  same directory as exe using it

		  [DllImport(@"valstat_dll.dll", EntryPoint = "waveformat")]
		  static extern int myFun(out WAVEFORMATEX wfx);

		  usage from C# :

			  public static void test_dll_call()
		 {
			 WAVEFORMATEX wfx;
			 try
			 {
				 int result = waveformat(out wfx);
				 Console.WriteLine(result);
				 Console.WriteLine(wfx.cbSize);
				 Console.WriteLine(wfx.nAvgBytesPerSec);
				 Console.WriteLine(wfx.nBlockAlign);
				 Console.WriteLine(wfx.nChannels);
				 Console.WriteLine(wfx.nSamplesPerSec);
				 Console.WriteLine(wfx.wBitsPerSample);
				 Console.WriteLine(wfx.wFormatTag);
			 }
			 catch (System.DllNotFoundException x)
			 {
				 Log(x);
			 }
		 }


  */
__declspec(dllexport)
int waveformat(void* const pWaveFormatex)
{
	WAVEFORMATEX wfx = {
	.cbSize = 1,
	.nAvgBytesPerSec = 2,
	.nBlockAlign = 3,
	.nChannels = 4,
	.nSamplesPerSec = 5,
	.wBitsPerSample = 6,
	.wFormatTag = 7
	};

#ifdef _DEBUG
	// to observe from debugger
	WAVEFORMATEX* wfxp_ = (WAVEFORMATEX*)pWaveFormatex;
	(void)wfxp_;
#endif
	memcpy(pWaveFormatex, &wfx, sizeof(wfx));
	return 42;
}

