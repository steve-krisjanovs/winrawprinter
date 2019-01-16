/* cppsrc/main.cpp */
#include <napi.h>
#include "rawprinter.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return rawprinter::Init(env, exports);
}

NODE_API_MODULE(winrawprinter, InitAll)


