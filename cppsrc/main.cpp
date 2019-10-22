#include <napi.h>
#include "Samples/functionexample.h"
#include "Samples/classexample.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  // return exports;
  // return functionexample::Init(env, exports);
  functionexample::Init(env, exports);
  return ClassExample::Init(env, exports);
}

NODE_API_MODULE(testaddon, InitAll)
