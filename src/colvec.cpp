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
  tpl->SetClassName(String::NewSymbol("Colvec"));
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

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_row"),
          FunctionTemplate::New(shed_row)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_rows"),
          FunctionTemplate::New(shed_rows)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("swap_rows"),
          FunctionTemplate::New(swap_rows)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("swap_cols"),
          FunctionTemplate::New(swap_cols)->GetFunction());

  // Object properties
  tpl->InstanceTemplate()->SetAccessor(String::New("n_rows"), GetNrow);

  tpl->InstanceTemplate()->SetAccessor(String::New("n_cols"), GetNcol);

  tpl->InstanceTemplate()->SetAccessor(String::New("n_elem"), GetNelem);

  constructor = Persistent<FunctionTemplate>::New(tpl);
  target->Set(String::NewSymbol("Colvec"), constructor->GetFunction());
}

Handle<Value> colvecWrap::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
  colvecWrap* w = new colvecWrap(args);
  w->Wrap(args.This());

  return args.This();
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));

  }
}

Handle<Value> colvecWrap::NewInstance(arma::colvec q) {
  HandleScope scope;

  Local<Object> instance = constructor->GetFunction()->NewInstance(0, NULL);
  colvecWrap* w = node::ObjectWrap::Unwrap<colvecWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
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

Handle<Value> colvecWrap::fill(const Arguments& args){
	HandleScope scope;
	colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
	arma::colvec* q = w->GetWrapped();
	*q = q->fill(args[0]->NumberValue());
	return scope.Close(Undefined());

}

Handle<Value> colvecWrap::is_empty(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_empty()));
}

Handle<Value> colvecWrap::is_finite(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_finite()));
}


Handle<Value> colvecWrap::print(const Arguments& args) {
  HandleScope scope;
  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();
  q->print();
  return scope.Close(Undefined());
}

Handle<Value> colvecWrap::randu(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();
  arma::colvec A = *q;

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


Handle<Value> colvecWrap::randn(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();
  arma::colvec A = *q;

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

Handle<Value> colvecWrap::reset(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();
  q->reset();

  return scope.Close(Undefined());
}

Handle<Value> colvecWrap::resize(const Arguments& args) {
  HandleScope scope;

  if (args[0]->IsNumber()){
	  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
	  arma::colvec* q = w->GetWrapped();
	  q->resize(args[0]->NumberValue());

	  return scope.Close(Undefined());
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));
  }

}

Handle<Value> colvecWrap::set_size(const Arguments& args){
	HandleScope scope;
	if (args.Length() == 1 && args[0]->IsNumber()){

		colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
		arma::colvec* q = w->GetWrapped();
		arma::colvec A = *q;

		A.set_size(args[0]->NumberValue());
		*q = A;

	} else {
		return ThrowException(Exception::TypeError(
			  String::New("Function expects numeric argument (n_elem).")));
		}
	return scope.Close(Undefined());
}


Handle<Value> colvecWrap::shed_row(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();
  arma::colvec A = *q;

  A.shed_row(args[0]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> colvecWrap::shed_rows(const Arguments& args) {
  HandleScope scope;

  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
  arma::colvec* q = w->GetWrapped();
  arma::colvec A = *q;

  A.shed_rows(args[0]->NumberValue(), args[1]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> colvecWrap::swap_rows(const Arguments& args) {
  HandleScope scope;

  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
	  arma::colvec* q = w->GetWrapped();
	  arma::colvec A = *q;

	  A.swap_rows(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
  } else {
	 	  return ThrowException(Exception::TypeError(
	 			  String::New("swap_rows expects two numeric arguments: row1, row2.")));
  }
}

Handle<Value> colvecWrap::swap_cols(const Arguments& args) {
  HandleScope scope;
  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  colvecWrap* w = ObjectWrap::Unwrap<colvecWrap>(args.This());
	  arma::colvec* q = w->GetWrapped();
	  arma::colvec A = *q;

	  A.swap_cols(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
	  } else {
		  return ThrowException(Exception::TypeError(
		 	 			  String::New("swap_cols expects two numeric arguments: col1, col2.")));
	  }
}

// Object properties

 Handle<Value> colvecWrap::GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  HandleScope scope;
  colvecWrap* w = node::ObjectWrap::Unwrap<colvecWrap>(info.Holder());
  arma::colvec* q = w->GetWrapped();
  return scope.Close(Number::New(q->n_rows));
}

 Handle<Value> colvecWrap::GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   colvecWrap* w = node::ObjectWrap::Unwrap<colvecWrap>(info.Holder());
   arma::colvec* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_cols));
 }

 Handle<Value> colvecWrap::GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   colvecWrap* w = node::ObjectWrap::Unwrap<colvecWrap>(info.Holder());
   arma::colvec* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_elem));
 }
