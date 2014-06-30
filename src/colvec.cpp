#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "colvec.h"
#include "helper.h"

using namespace v8;
using namespace std;

Persistent<FunctionTemplate> colvecWrap::constructor;

colvecWrap::colvecWrap(const Arguments& args) : q_(NULL) {

	if (args.Length() == 0) {
	    // colvec ( )
	    q_ = new arma::colvec();
	  } else if (args.Length() == 1 && args[0]->IsNumber()){
		q_ = new arma::colvec(args[0]->NumberValue());
	  }
}

colvecWrap::~colvecWrap() {
  delete q_;
}

void colvecWrap::Initialize(Handle<Object> target) {
   // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("colvec"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("at"),
       FunctionTemplate::New(at)->GetFunction());

  constructor = Persistent<FunctionTemplate>::New(tpl);
  target->Set(String::NewSymbol("colvec"), constructor->GetFunction());
}

Handle<Value> colvecWrap::New(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = new colvecWrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> colvecWrap::at(const Arguments& args) {
  HandleScope scope;
  Local<Value> ret;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();

  if(args.Length() == 1 && args[0]->IsNumber()){
	  ret = Number::New(q->at(args[0]->NumberValue()));
  }

  return scope.Close(ret);
}
