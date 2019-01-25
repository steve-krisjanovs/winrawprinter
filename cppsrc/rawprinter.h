/* cppsrc/rawprinter.h */
#include <napi.h>
#include <windows.h>

namespace rawprinter {
  //internal functions used by rawprinter.cpp
  //-----------------------------------------
  bool IsV4Driver(LPTSTR printerName);
  DWORD GetDriverVersion(HANDLE handle);
  BOOL RawDataToPrinter (LPTSTR szPrinterName, LPBYTE lpData, DWORD dwCount);

  //////////////////////////////////////////////////////////////////
  //NAPI endpoints start
  //////////////////////////////////////////////////////////////////
  Napi::Boolean PrintBufferToPrinter(const Napi::CallbackInfo& info);
  void PrintBufferToPrinterAsync(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
  //////////////////////////////////////////////////////////////////
  //NAPI endpoints end
  //////////////////////////////////////////////////////////////////
}