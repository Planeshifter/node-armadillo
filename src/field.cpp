#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "helper.h"

using namespace v8;
using namespace std;

template<typename T>
Persistent<FunctionTemplate> fieldWrap<T>::constructor;

template <typename T>
fieldWrap<T>::fieldWrap(const Arguments& args) : q_(NULL) {
};

template <typename T>
fieldWrap<T>::~fieldWrap() {
  delete q_;
};

template <typename T>
void fieldWrap<T>::Initialize(Handle<Object> target) {

};

template <typename T>
Handle<Value> fieldWrap<T>::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
	  fieldWrap<T>* w = new fieldWrap<T>(args);
	  w->Wrap(args.This());
	  return args.This();
  } else {
	  return ThrowException(Exception::Error(
	   String::New("Error: Function is a constructor, has to be invoked with new.")));

  }
}
