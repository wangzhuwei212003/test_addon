#include "classexample.h"

Napi::FunctionReference ClassExample::constructor;

Napi::Object ClassExample::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "ClassExample", {
                                                             InstanceMethod("add", &ClassExample::Add),
                                                             InstanceMethod("getValue", &ClassExample::GetValue),
                                                         });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("ClassExample", func);
  return exports;
}

ClassExample::ClassExample(const Napi::CallbackInfo &info) : Napi::ObjectWrap<ClassExample>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1 || !info[0].IsNumber())
  {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number value = info[0].As<Napi::Number>();
  _actualClass = new ActualClass(value.DoubleValue());
}

Napi::Value ClassExample::GetValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  // double num = _actualClass.getValue(); 
  // member reference type 'ActualClass *' is a pointer; did you mean to use '->'?
  double num = _actualClass->getValue();
  return Napi::Number::New(env, num);
}

Napi::Value ClassExample::Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (  info.Length() != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number toAdd = info[0].As<Napi::Number>(); 
  double answer = _actualClass->add(toAdd.DoubleValue());

  return Napi::Number::New(info.Env(), answer);
}

