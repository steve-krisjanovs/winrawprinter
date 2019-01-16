#include "rawprinter.h"
#include <windows.h>
#include <tchar.h>
//#include <vector>
//#include <locale>
//#include <codecvt>
//#include <cstring>
//#include <string>
//#include <iostream>

// 
//  RawDataToPrinter - sends binary data directly to a printer 
//          optionally with an XPSDrv Printer Driver 
//  
// szPrinterName: NULL-terminated string specifying printer name 
// lpData:        Pointer to raw data bytes 
// dwCount        Length of lpData in bytes 
//  
// Returns: TRUE for success, FALSE for failure. 
//  
BOOL rawprinter::RawDataToPrinter (LPTSTR szPrinterName, LPBYTE lpData, DWORD dwCount)
{
    BOOL     bStatus = FALSE;
    HANDLE     hPrinter = NULL;
    DOC_INFO_1       DocInfo;
    DWORD    dwPrtJob = 0L;
    DWORD    dwBytesWritten = 0L;

    // Open a handle to the printer. 
    bStatus = OpenPrinter (szPrinterName, &hPrinter, NULL);
    
    if (bStatus) {
        // Fill in the structure with info about this "document." 
        DocInfo.pDocName = (LPTSTR)_T("Raw print document");
        DocInfo.pOutputFile = NULL;

        // Enter the datatype of this buffer.
        //  Use "XPS_PASS" when the data buffer should bypass the 
        //    print filter pipeline of the XPSDrv printer driver. 
        //    This datatype would be used to send the buffer directly 
        //    to the printer, such as when sending print head alignment 
        //    commands. Normally, a data buffer would be sent as the
        //    "RAW" datatype.
        //
        
        //default print mode to raw. if the printer is a type 4 (XPS) printer driver (windows >= 8), then use "XPS_PASS" for passthrough. 
        DocInfo.pDatatype = (LPTSTR)_T("RAW");
        if (IsV4Driver(szPrinterName))
            DocInfo.pDatatype = (LPTSTR)_T("XPS_PASS");

        dwPrtJob = StartDocPrinter (
                        hPrinter,
                        1,
                        (LPBYTE)&DocInfo);

        if (dwPrtJob > 0) {
                // Send the data to the printer. 
                bStatus = WritePrinter (
                hPrinter,
                lpData,
                dwCount,
                &dwBytesWritten);
        }
        
        EndDocPrinter (hPrinter);

        // Close the printer handle. 
        bStatus = ClosePrinter(hPrinter);
    }
    
    if (!bStatus || (dwCount != dwBytesWritten)) {
        bStatus = FALSE;
    } else {
        bStatus = TRUE;
    }

    return bStatus;
}

bool rawprinter::IsV4Driver(LPTSTR printerName)
{
    HANDLE handle;
    PRINTER_DEFAULTS defaults;

    defaults.DesiredAccess = PRINTER_ACCESS_USE;
    defaults.pDatatype = (LPTSTR)_T("RAW"); 
    defaults.pDevMode = NULL;

    if (::OpenPrinter(printerName, &handle, &defaults) == 0)
    {
        return false;
    }

    DWORD version = GetDriverVersion(handle);

    //::ClosePrinter(handle);

    return version == 4;
}

DWORD rawprinter::GetDriverVersion(HANDLE handle)
{
    DWORD needed;

    ::GetPrinterDriver(handle, NULL, 2, NULL, 0, &needed);
    if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        return -1;
    }

    std::vector<char> buffer(needed);
    if (::GetPrinterDriver(handle, NULL, 2, (LPBYTE) &buffer[0], needed, &needed) == 0)
    {
        return -1;
    }

    return ((DRIVER_INFO_2*) &buffer[0])->cVersion;
}

//////////////////////////////////////////////////////////////////
//NAPI endpoints start
//////////////////////////////////////////////////////////////////
// std::string rawprinter::hello(){
//   return "Hello World";
// }
// Napi::String rawprinter::HelloWrapped(const Napi::CallbackInfo& info) 
// {
//   Napi::Env env = info.Env();
//   Napi::String returnValue = Napi::String::New(env, rawprinter::hello());
//   return returnValue;
// }

Napi::Boolean rawprinter::PrintBufferToPrinter(const Napi::CallbackInfo& info) 
{
    //std::cout << "start rawprinter::PrintBufferToPrinter(...)\n";

    Napi::Env env = info.Env();   
    Napi::TypeError arg_err = Napi::TypeError::New(env, "Two parameters expected. param1 (string): file path, param2 (string) printer name");

    if (info.Length() != 2)
        arg_err.ThrowAsJavaScriptException();
    if (!info[1].IsString())
        arg_err.ThrowAsJavaScriptException();
    if (!info[0].IsBuffer())
        arg_err.ThrowAsJavaScriptException();

    //params are good. send it off to the printer

    Napi::Buffer<char> buff = info[0].As<Napi::Buffer<char>>();
    std::string s = (info[1].As<Napi::String>()).Utf8Value();
    LPTSTR prt = new TCHAR[s.size() + 1]; 
    strcpy(prt, s.c_str());
    LPBYTE data = LPBYTE(buff.Data());

    //std::cout << "before RawDataToPrinter(...)\n";
    //std::cout << "buffer bytelength:" << buff.ByteLength() << "\n";
    //std::cout << "printername: " << s << "\n";

    BOOL result = FALSE;
    try 
    {
        result = rawprinter::RawDataToPrinter(prt, data, buff.ByteLength());
    }
    catch(const std::exception& e) 
    {
        Napi::Error ptr_err = Napi::Error::New(env, e.what());
        ptr_err.ThrowAsJavaScriptException();
    }

    Napi::Boolean nresult = Napi::Boolean::New(env, (result == TRUE) ? true : false);
    return nresult;

    //std::cout << "after RawDataToPrinter(...)\n";
}

Napi::Object rawprinter::Init(Napi::Env env, Napi::Object exports) 
{
    exports.Set(
        "PrintBufferToPrinter",
        Napi::Function::New(env, rawprinter::PrintBufferToPrinter)
    );
    // exports.Set(
    //     "hello", 
    //     Napi::Function::New(env, rawprinter::HelloWrapped)
    // );
    return exports;
}
//////////////////////////////////////////////////////////////////
//NAPI endpoints end
//////////////////////////////////////////////////////////////////