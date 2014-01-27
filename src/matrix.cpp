
#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm> 

#include "matrix.h"

using namespace v8;
using namespace std;

Persistent<Function> matWrap::constructor;

// Supported implementations:
// mat ( )

matWrap::matWrap(const Arguments& args) : q_(NULL) {
  
  if (args.Length() == 0) {
    // mat ( )
    q_ = new arma::mat();
  }
  else if (args.Length() == 1 && args[0]->IsString()) { 
  v8::String::Utf8Value param1(args[0]->ToString());
  std::string matrix_input = std::string(*param1);
  q_ = new arma::mat(matrix_input);
  }
  
  else if (args[0]->IsNumber() && args[1]->IsNumber()) {
  q_ = new arma::mat(args[0]->NumberValue(), args[1]->NumberValue());
  }
  
}

matWrap::~matWrap() {
  delete q_;
}


void matWrap::Initialize(Handle<Object> target) {
   // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("mat"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1); 
  
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("ones"),
      FunctionTemplate::New(ones)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("zeros"),
      FunctionTemplate::New(ones)->GetFunction());    
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("fill"),
      FunctionTemplate::New(ones)->GetFunction());  
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("n_cols"),
      FunctionTemplate::New(n_cols)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("n_rows"),
      FunctionTemplate::New(n_rows)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("print"),
      FunctionTemplate::New(print)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("t"),
      FunctionTemplate::New(t)->GetFunction());
  
  
  
  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("mat"), constructor);
}


Handle<Value> matWrap::New(const Arguments& args) {
  HandleScope scope;

  matWrap* w = new matWrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> matWrap::ones(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  if (args.Length() == 0) 
    {
    q->ones();
    };
  if (args.Length() == 2) 
    {
    q->ones(args[0]->NumberValue(), args[1]->NumberValue());
    };
  return scope.Close(Undefined());
}

Handle<Value> matWrap::zeros(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  if (args.Length() == 0) 
    {
    q->zeros();
    };
  if (args.Length() == 2) 
    {
    q->zeros(args[0]->NumberValue(), args[1]->NumberValue());
    };
  return scope.Close(Undefined());
}

Handle<Value> matWrap::fill(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  *q = q->fill(3.2);
  return scope.Close(Undefined());
}

Handle<Value> matWrap::t(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  return scope.Close(NewInstance(q->t()));
}

Handle<Value> matWrap::NewInstance(arma::mat q) {
  HandleScope scope;
  
  Local<Object> instance = constructor->NewInstance(0, NULL);
  matWrap* w = node::ObjectWrap::Unwrap<matWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}


Handle<Value> matWrap::n_cols(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Number::New(q->n_cols));
}

Handle<Value> matWrap::n_rows(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Number::New(q->n_rows));
}

Handle<Value> matWrap::print(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  q->print();
  return scope.Close(Undefined());
}


