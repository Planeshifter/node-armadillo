#ifndef CUBE_H
#define CUBE_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

using namespace v8;

template <typename T>
class cubeWrap : public node::ObjectWrap {

public:
	 static void Initialize(v8::Handle<v8::Object> target);
private:
   cubeWrap(const v8::Arguments& args);
  ~cubeWrap();
  static v8::Persistent<v8::FunctionTemplate> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped object
  arma::Cube<T>* q_;
};


#include "cube.cpp"

#endif
