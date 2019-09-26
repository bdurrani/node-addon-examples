#include "one.h"

Nan::Persistent<v8::Function> One::constructor;

One::~One() {}
One::One(::Primitive* value) : m_data(value) {} 

void One::Doit(const Nan::FunctionCallbackInfo<v8::Value> &info){
    printf("One::Just do it\n");
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    One* obj = ObjectWrap::Unwrap<One>(info.Holder());
    printf("One:: calling Primitve.Doit()\n");
    obj->m_data->Doit();
}

Local<v8::Value> One::NewInstance(::Primitive * one)
{ 
    Nan::EscapableHandleScope scope; 
    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { Nan::New<v8::External>(one) };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    MaybeLocal<Object> instance = Nan::NewInstance(cons, argc, argv);
    Local<Object> self;

    if(instance.IsEmpty()){
        printf("instance is empty\n");
    }

    if(instance.ToLocal(&self)){
        printf("self is not null\n");   
        return scope.Escape(self);
    }
    return Nan::Null();
}

void One::New(const Nan::FunctionCallbackInfo<v8::Value>& info)
{ 
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.IsConstructCall()) {
        printf( "Invoked as constructor: `new MyObject(...)\n`");
        // auto obj = new One(0.0);
        // obj->Wrap(info.This());
        // info.GetReturnValue().Set(info.This());
        ::Primitive* obj = static_cast<::Primitive*>(info[0].As<External>()->Value()); 
        printf("casting a Primitive %p\n", obj);
        auto tree = new One(obj);
        printf("made a One\n");
        tree->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        printf("Invoked as function constructor\n");
        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = {info[0]};
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        info.GetReturnValue().Set(
            cons->NewInstance(context, argc, argv).ToLocalChecked());
    }
}

void One::Init(v8::Local<v8::Object> exports) {

    v8::Local<v8::Context> context = exports->CreationContext();
    Nan::HandleScope scope;
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    Local<String> class_name = Nan::New("One").ToLocalChecked();
    tpl->SetClassName(class_name); 

    Nan::SetPrototypeMethod(tpl, "doIt", Doit);

    Local<Function> ctor = Nan::GetFunction(tpl).ToLocalChecked();

    // constructor.Reset(ctor);
    constructor.Reset(tpl->GetFunction(context).ToLocalChecked());
    Nan::Set(exports, class_name, ctor);
}