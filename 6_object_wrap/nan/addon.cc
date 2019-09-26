#include <nan.h>
#include "myobject.h"
#include "one.h"

using namespace v8;

void InitAll(Local<Object> exports) {
  printf("InitAll\n");
  MyObject::Init(exports);
  One::Init(exports);
}

NODE_MODULE(addon, InitAll)
