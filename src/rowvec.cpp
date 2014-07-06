#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "helper.h"

using namespace v8;
using namespace std;

template<typename T>
Persistent<FunctionTemplate> rowvecWrap<T>::constructor;

template<typename T>
rowvecWrap<T>::rowvecWrap(const Arguments& args) : q_(NULL) {

	if (args.Length() == 0) {
	    // rowvec ( )
	    q_ = new arma::Row<T>();
	  } else if (args.Length() == 1 && args[0]->IsNumber()){
		q_ = new arma::Row<T>(args[0]->NumberValue());
	  }
}

template<typename T>
rowvecWrap<T>::~rowvecWrap() {
  delete q_;
}

template<typename T>
void rowvecWrap<T>::Initialize(Handle<Object> target) {

};

template<> inline void rowvecWrap<double>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("Rowvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("Rowvec"), constructor->GetFunction());

};

template<> inline void rowvecWrap<float>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("FRowvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("FRowvec"), constructor->GetFunction());

};

template<typename T>
void rowvecWrap<T>::registerMethods(Local<FunctionTemplate> tpl){

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

};

template<typename T>
Handle<Value> rowvecWrap<T>::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
  rowvecWrap<T>* w = new rowvecWrap(args);
  w->Wrap(args.This());

  return args.This();
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));

  }
}

template<typename T>
Handle<Value> rowvecWrap<T>::NewInstance(arma::Row<T> q) {
  HandleScope scope;

  Local<Object> instance = constructor->GetFunction()->NewInstance(0, NULL);
  rowvecWrap<T>* w = node::ObjectWrap::Unwrap<rowvecWrap<T> >(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

template<typename T>
Handle<Value> rowvecWrap<T>::at(const Arguments& args) {
  HandleScope scope;
  Local<Value> ret;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();

  if(args.Length() == 1 && args[0]->IsNumber()){
	  ret = Number::New(q->at(args[0]->NumberValue()));
  }

  return scope.Close(ret);
}

template<typename T>
Handle<Value> rowvecWrap<T>::fill(const Arguments& args){
	HandleScope scope;
	rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
	arma::Row<T>* q = w->GetWrapped();
	*q = q->fill(args[0]->NumberValue());
	return scope.Close(Undefined());

}

template<typename T>
Handle<Value> rowvecWrap<T>::is_empty(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_empty()));
}

template<typename T>
Handle<Value> rowvecWrap<T>::is_finite(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_finite()));
}

template<typename T>
Handle<Value> rowvecWrap<T>::print(const Arguments& args) {
  HandleScope scope;
  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();
  q->print();
  return scope.Close(Undefined());
}

template<typename T>
Handle<Value> rowvecWrap<T>::randu(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();
  arma::Row<T> A = *q;

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

template<typename T>
Handle<Value> rowvecWrap<T>::randn(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();
  arma::Row<T> A = *q;

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

template<typename T>
Handle<Value> rowvecWrap<T>::reset(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();
  q->reset();

  return scope.Close(Undefined());
}

template<typename T>
Handle<Value> rowvecWrap<T>::resize(const Arguments& args) {
  HandleScope scope;

  if (args[0]->IsNumber()){
	  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
	  arma::Row<T>* q = w->GetWrapped();
	  q->resize(args[0]->NumberValue());

	  return scope.Close(Undefined());
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));
  }

}

template<typename T>
Handle<Value> rowvecWrap<T>::set_size(const Arguments& args){
	HandleScope scope;
	if (args.Length() == 1 && args[0]->IsNumber()){

		rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
		arma::Row<T>* q = w->GetWrapped();
		arma::Row<T> A = *q;

		A.set_size(args[0]->NumberValue());
		*q = A;

	} else {
		return ThrowException(Exception::TypeError(
			  String::New("Function expects numeric argument (n_elem).")));
		}
	return scope.Close(Undefined());
}

template<typename T>
Handle<Value> rowvecWrap<T>::shed_col(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();
  arma::Row<T> A = *q;

  A.shed_col(args[0]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

template<typename T>
Handle<Value> rowvecWrap<T>::shed_cols(const Arguments& args) {
  HandleScope scope;

  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
  arma::Row<T>* q = w->GetWrapped();
  arma::Row<T> A = *q;

  A.shed_cols(args[0]->NumberValue(), args[1]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

template<typename T>
Handle<Value> rowvecWrap<T>::swap_rows(const Arguments& args) {
  HandleScope scope;

  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
	  arma::Row<T>* q = w->GetWrapped();
	  arma::Row<T> A = *q;

	  A.swap_rows(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
  } else {
	 	  return ThrowException(Exception::TypeError(
	 			  String::New("swap_rows expects two numeric arguments: row1, row2.")));
  }
}

template<typename T>
Handle<Value> rowvecWrap<T>::swap_cols(const Arguments& args) {
  HandleScope scope;
  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  rowvecWrap<T>* w = ObjectWrap::Unwrap<rowvecWrap<T> >(args.This());
	  arma::Row<T>* q = w->GetWrapped();
	  arma::Row<T> A = *q;

	  A.swap_cols(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
	  } else {
		  return ThrowException(Exception::TypeError(
		 	 			  String::New("swap_cols expects two numeric arguments: col1, col2.")));
	  }
}

// Object properties

template<typename T>
Handle<Value> rowvecWrap<T>::GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  HandleScope scope;
  rowvecWrap<T>* w = node::ObjectWrap::Unwrap<rowvecWrap<T> >(info.Holder());
  arma::Row<T>* q = w->GetWrapped();
  return scope.Close(Number::New(q->n_rows));
}

template<typename T>
Handle<Value> rowvecWrap<T>::GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   rowvecWrap<T>* w = node::ObjectWrap::Unwrap<rowvecWrap<T> >(info.Holder());
   arma::Row<T>* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_cols));
 }

template<typename T>
Handle<Value> rowvecWrap<T>::GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   rowvecWrap<T>* w = node::ObjectWrap::Unwrap<rowvecWrap<T> >(info.Holder());
   arma::Row<T>* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_elem));
 }
