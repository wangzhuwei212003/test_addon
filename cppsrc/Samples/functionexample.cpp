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

int functionexample::add(int a, int b)
{
  return a + b;
}
Napi::Number functionexample::AddWrapped(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
  {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number first = info[0].As<Napi::Number>();
  Napi::Number second = info[1].As<Napi::Number>();

  int returnValue = functionexample::add(first.Int32Value(), second.Int32Value());
  return Napi::Number::New(env, returnValue);
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("hello", Napi::Function::New(env, functionexample::HelloWrapped));
  exports.Set("add", Napi::Function::New(env, functionexample::AddWrapped));
  return exports;
}

// For every function in C++ we want to export
// we will basically create a NAPI wrapped function (HelloWrapped in this example)
// and add it to the exports object using Init.