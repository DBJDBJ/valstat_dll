
# valstat dll

## The Purpose

> [valstat](https://github.com/DBJDBJ/valstat) is language agnostic call/response protocol

The purpose of this dll is to show valstat interop with various projects and languages who can run on Windows and load and use this DLL.

Thus it does not contains "snazzy, whiz-bang" code. It shows the valstat usage and maleability.

(Roadmap: that is not stopping me to plan and use the fastest possible Fibonaci generator, valstat enabled)

## Operational Environment

- The "dll" suffix means this is Windows only project
- The Visual Studio project use is [very advisable](https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/debugger/how-to-debug-native-dlls?view=vs-2015&redirectedfrom=MSDN) if one needs to debug the dll
- As per Windows lore no static CRT is linked in
  - that means 
    - [`DisableThreadLibraryCalls`](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-disablethreadlibrarycalls) function 
    - Actual `DllMain` code provided
- This  dll is coded in C
  - that makes possible the simplest, fastest and smallest windows dll 
  - valstat C implementation is perfectly simple, light and usable
- this is a separate repo but best used as submodule in repos using it

** &copy; by dbj@dbj.org  https://dbj.org/license_dbj **