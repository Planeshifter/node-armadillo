#ifndef FIELD_H
#define FIELD_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

using namespace v8;

template <typename T>
class fieldWrap : public node::ObjectWrap {

public:
	 static void Initialize(v8::Handle<v8::Object> target);
private:
   fieldWrap(const v8::Arguments& args);
  ~fieldWrap();
  static v8::Persistent<v8::FunctionTemplate> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped object
  arma::field<T>* q_;
};

#include "field.cpp"

#endif
