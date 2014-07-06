#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "rowvec.h"
#include "helper.h"

using namespace v8;
using namespace std;

Persistent<FunctionTemplate> rowvecWrap::constructor;

rowvecWrap::rowvecWrap(const Arguments& args) : q_(NULL) {

	if (args.Length() == 0) {
	    // rowvec ( )
	    q_ = new arma::rowvec();
	  } else if (args.Length() == 1 && args[0]->IsNumber()){
		q_ = new arma::rowvec(args[0]->NumberValue());
	  }
}

rowvecWrap::~rowvecWrap() {
  delete q_;
}

void rowvecWrap::Initialize(Handle<Object> target) {
   // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Rowvec"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype

  tpl->PrototypeTemplate()->Set(String::NewSymbol("at"),
       FunctionTemplate::New(at)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("fill"),
       FunctionTemplate::New(fill)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_empty"),
      FunctionTemplate::New(is_empty)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_finite"),
      FunctionTemplate::New(is_finite)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("print"),
       FunctionTemplate::New(print)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("randu"),
          FunctionTemplate::New(randu)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("randn"),
          FunctionTemplate::New(randn)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("reset"),
        FunctionTemplate::New(reset)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("resize"),
        FunctionTemplate::New(resize)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("set_size"),
          FunctionTemplate::New(set_size)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_col"),
          FunctionTemplate::New(shed_col)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_cols"),
          FunctionTemplate::New(shed_cols)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("swap_rows"),
          FunctionTemplate::New(swap_rows)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("swap_cols"),
          FunctionTemplate::New(swap_cols)->GetFunction());

  // Object properties
  tpl->InstanceTemplate()->SetAccessor(String::New("n_rows"), GetNrow);

  tpl->InstanceTemplate()->SetAccessor(String::New("n_cols"), GetNcol);

  tpl->InstanceTemplate()->SetAccessor(String::New("n_elem"), GetNelem);

  constructor = Persistent<FunctionTemplate>::New(tpl);
  target->Set(String::NewSymbol("Rowvec"), constructor->GetFunction());
}

Handle<Value> rowvecWrap::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
  rowvecWrap* w = new rowvecWrap(args);
  w->Wrap(args.This());

  return args.This();
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));

  }
}

Handle<Value> rowvecWrap::NewInstance(arma::rowvec q) {
  HandleScope scope;

  Local<Object> instance = constructor->GetFunction()->NewInstance(0, NULL);
  rowvecWrap* w = node::ObjectWrap::Unwrap<rowvecWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

Handle<Value> rowvecWrap::at(const Arguments& args) {
  HandleScope scope;
  Local<Value> ret;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();

  if(args.Length() == 1 && args[0]->IsNumber()){
	  ret = Number::New(q->at(args[0]->NumberValue()));
  }

  return scope.Close(ret);
}

Handle<Value> rowvecWrap::fill(const Arguments& args){
	HandleScope scope;
	rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
	arma::rowvec* q = w->GetWrapped();
	*q = q->fill(args[0]->NumberValue());
	return scope.Close(Undefined());

}

Handle<Value> rowvecWrap::is_empty(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_empty()));
}

Handle<Value> rowvecWrap::is_finite(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_finite()));
}


Handle<Value> rowvecWrap::print(const Arguments& args) {
  HandleScope scope;
  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();
  q->print();
  return scope.Close(Undefined());
}

Handle<Value> rowvecWrap::randu(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();
  arma::rowvec A = *q;

  if (args.Length() == 0)
  	  {
	  A.randu();
  	  }
  else if (args.Length() == 1)
	  {
		  A.randu(args[0]->NumberValue());
	  }
  *q = A;
  return scope.Close(Undefined());
}


Handle<Value> rowvecWrap::randn(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();
  arma::rowvec A = *q;

  if (args.Length() == 0)
  	  {
	  A.randn();
  	  }
  else if (args.Length() == 1)
	  {
		  A.randn(args[0]->NumberValue());
	  }
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> rowvecWrap::reset(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();
  q->reset();

  return scope.Close(Undefined());
}

Handle<Value> rowvecWrap::resize(const Arguments& args) {
  HandleScope scope;

  if (args[0]->IsNumber()){
	  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
	  arma::rowvec* q = w->GetWrapped();
	  q->resize(args[0]->NumberValue());

	  return scope.Close(Undefined());
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));
  }

}

Handle<Value> rowvecWrap::set_size(const Arguments& args){
	HandleScope scope;
	if (args.Length() == 1 && args[0]->IsNumber()){

		rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
		arma::rowvec* q = w->GetWrapped();
		arma::rowvec A = *q;

		A.set_size(args[0]->NumberValue());
		*q = A;

	} else {
		return ThrowException(Exception::TypeError(
			  String::New("Function expects numeric argument (n_elem).")));
		}
	return scope.Close(Undefined());
}


Handle<Value> rowvecWrap::shed_col(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();
  arma::rowvec A = *q;

  A.shed_col(args[0]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> rowvecWrap::shed_cols(const Arguments& args) {
  HandleScope scope;

  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
  arma::rowvec* q = w->GetWrapped();
  arma::rowvec A = *q;

  A.shed_cols(args[0]->NumberValue(), args[1]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> rowvecWrap::swap_rows(const Arguments& args) {
  HandleScope scope;

  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
	  arma::rowvec* q = w->GetWrapped();
	  arma::rowvec A = *q;

	  A.swap_rows(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
  } else {
	 	  return ThrowException(Exception::TypeError(
	 			  String::New("swap_rows expects two numeric arguments: row1, row2.")));
  }
}

Handle<Value> rowvecWrap::swap_cols(const Arguments& args) {
  HandleScope scope;
  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  rowvecWrap* w = ObjectWrap::Unwrap<rowvecWrap>(args.This());
	  arma::rowvec* q = w->GetWrapped();
	  arma::rowvec A = *q;

	  A.swap_cols(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
	  } else {
		  return ThrowException(Exception::TypeError(
		 	 			  String::New("swap_cols expects two numeric arguments: col1, col2.")));
	  }
}

// Object properties

 Handle<Value> rowvecWrap::GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  HandleScope scope;
  rowvecWrap* w = node::ObjectWrap::Unwrap<rowvecWrap>(info.Holder());
  arma::rowvec* q = w->GetWrapped();
  return scope.Close(Number::New(q->n_rows));
}

 Handle<Value> rowvecWrap::GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   rowvecWrap* w = node::ObjectWrap::Unwrap<rowvecWrap>(info.Holder());
   arma::rowvec* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_cols));
 }

 Handle<Value> rowvecWrap::GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   rowvecWrap* w = node::ObjectWrap::Unwrap<rowvecWrap>(info.Holder());
   arma::rowvec* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_elem));
 }
