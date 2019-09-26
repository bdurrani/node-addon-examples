#ifndef ONE_H
#define ONE_H

#include <v8.h>
#include <nan.h>
#include "primitive.h"

using namespace v8;

class One : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

  // void New(const Nan::FunctionCallbackInfo<Value> &info) {
  //   printf("IS CONSTRUCT CALL %d\n", info.IsConstructCall());
  //   info.GetReturnValue().Set(info.This());
  // }

  explicit One(::Primitive* value );

  static v8::Local<v8::Value> NewInstance(::Primitive * one); 
  static void Doit(const Nan::FunctionCallbackInfo<v8::Value> &); 
  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info); 
  static Nan::Persistent<v8::Function> constructor;
  double value_;
 private:
  ~One();
  ::Primitive* m_data;
};

#endif
