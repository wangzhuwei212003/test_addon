#include "functionexample.h"

std::string functionexample::hello()
{
  return "He";
}

Napi::String functionexample::HelloWrapped(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::String returnValue = Napi::String::New(env, functionexample::hello());
  return returnValue;
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
    "hello", Napi::Function::New(env, functionexample::HelloWrapped)
  );
  return exports;
}

// For every function in C++ we want to export 
// we will basically create a NAPI wrapped function (HelloWrapped in this example) 
// and add it to the exports object using Init.