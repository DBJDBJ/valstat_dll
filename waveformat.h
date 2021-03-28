#pragma once
#include "common.h"

/*
 Just an Arbitrary but real example.

 mmsystem requires windows included before it
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
__declspec(dllexport) int waveformat(void* const pWaveFormatex)
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
	return OK_VAL;
}

