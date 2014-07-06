#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "helper.h"

using namespace v8;
using namespace std;

template<typename T>
Persistent<FunctionTemplate> cubeWrap<T>::constructor;

template <typename T>
cubeWrap<T>::cubeWrap(const Arguments& args) : q_(NULL) {
};

template <typename T>
cubeWrap<T>::~cubeWrap() {
  delete q_;
};

template <typename T>
void cubeWrap<T>::Initialize(Handle<Object> target) {

};

template<> inline void cubeWrap<double>::Initialize(Handle<Object> target) {

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Cube"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(String::NewSymbol("Cube"), constructor->GetFunction());

};

template<> inline void cubeWrap<float>::Initialize(Handle<Object> target) {

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("FCube"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(String::NewSymbol("FCube"), constructor->GetFunction());

};

template<> inline void cubeWrap<arma::cx_double>::Initialize(Handle<Object> target) {

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("CX_Cube"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(String::NewSymbol("CX_Cube"), constructor->GetFunction());

};

template<> inline void cubeWrap<arma::cx_float>::Initialize(Handle<Object> target) {

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("CX_FCube"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(String::NewSymbol("CX_FCube"), constructor->GetFunction());

};

template<> inline void cubeWrap<arma::uword>::Initialize(Handle<Object> target) {

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("UCube"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(String::NewSymbol("UCube"), constructor->GetFunction());

};

template<> inline void cubeWrap<arma::sword>::Initialize(Handle<Object> target) {

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("ICube"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(String::NewSymbol("ICube"), constructor->GetFunction());

};

template <typename T>
Handle<Value> cubeWrap<T>::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
	  cubeWrap<T>* w = new cubeWrap<T>(args);
	  w->Wrap(args.This());
	  return args.This();
  } else {
	  return ThrowException(Exception::Error(
	   String::New("Error: Function is a constructor, has to be invoked with new.")));

  }
}
