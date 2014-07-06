#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace v8;
using namespace std;

template<typename T>
Persistent<FunctionTemplate> colvecWrap<T>::constructor;

template<typename T>
colvecWrap<T>::colvecWrap(const Arguments& args) : q_(NULL) {

	if (args.Length() == 0) {
	    // colvec ( )
	    q_ = new arma::Col<T>();
	  } else if (args.Length() == 1 && args[0]->IsNumber()){
		q_ = new arma::Col<T>(args[0]->NumberValue());
	  }
};


template<typename T>
colvecWrap<T>::~colvecWrap() {
  delete q_;
};


template<typename T>
void colvecWrap<T>::Initialize(Handle<Object> target) {

};

template<> inline void colvecWrap<double>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("Colvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("Colvec"), constructor->GetFunction());

};

template<> inline void colvecWrap<float>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("FColvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("FColvec"), constructor->GetFunction());

};

/*
template<> inline void colvecWrap<arma::cx_double>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("CX_Colvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("CX_Colvec"), constructor->GetFunction());

};

template<> inline void colvecWrap<arma::cx_float>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("CX_FColvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("CX_FColvec"), constructor->GetFunction());

};

*/

template<> inline void colvecWrap<arma::uword>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("UColvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("UColvec"), constructor->GetFunction());

};

template<> inline void colvecWrap<arma::sword>::Initialize(Handle<Object> target) {

	 // Prepare constructor template
	  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	  tpl->SetClassName(String::NewSymbol("IColvec"));
	  tpl->InstanceTemplate()->SetInternalFieldCount(1);
	  registerMethods(tpl);
	  constructor = Persistent<FunctionTemplate>::New(tpl);
	  target->Set(String::NewSymbol("IColvec"), constructor->GetFunction());

};

template<typename T>
void colvecWrap<T>::registerMethods(Local<FunctionTemplate> tpl){

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

};


template<typename T>
Handle<Value> colvecWrap<T>::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
  colvecWrap<T>* w = new colvecWrap(args);
  w->Wrap(args.This());

  return args.This();
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));

  }
};

template<typename T>
Handle<Value> colvecWrap<T>::NewInstance(arma::Col<T> q) {
  HandleScope scope;

  Local<Object> instance = constructor->GetFunction()->NewInstance(0, NULL);
  colvecWrap<T>* w = node::ObjectWrap::Unwrap<colvecWrap<T> >(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
};

template<typename T>
Handle<Value> colvecWrap<T>::at(const Arguments& args) {
  HandleScope scope;
  Local<Value> ret;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();

  if(args.Length() == 1 && args[0]->IsNumber()){
	  ret = Number::New(q->at(args[0]->NumberValue()));
  }

  return scope.Close(ret);
};

template<typename T>
Handle<Value> colvecWrap<T>::fill(const Arguments& args){
	HandleScope scope;
	colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
	arma::Col<T>* q = w->GetWrapped();
	*q = q->fill(args[0]->NumberValue());
	return scope.Close(Undefined());

};

template<typename T>
Handle<Value> colvecWrap<T>::is_empty(const Arguments& args) {
  HandleScope scope;
  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_empty()));
};

template<typename T>
Handle<Value> colvecWrap<T>::is_finite(const Arguments& args) {
  HandleScope scope;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_finite()));
};

template<typename T>
Handle<Value> colvecWrap<T>::print(const Arguments& args) {
  HandleScope scope;
  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();
  q->print();
  return scope.Close(Undefined());
};

template<typename T>
Handle<Value> colvecWrap<T>::randu(const Arguments& args) {
  HandleScope scope;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();
  arma::Col<T> A = *q;

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
};

template<typename T>
Handle<Value> colvecWrap<T>::randn(const Arguments& args) {
  HandleScope scope;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();
  arma::Col<T> A = *q;

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
};

template<typename T>
Handle<Value> colvecWrap<T>::reset(const Arguments& args) {
  HandleScope scope;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();
  q->reset();

  return scope.Close(Undefined());
};

template<typename T>
Handle<Value> colvecWrap<T>::resize(const Arguments& args) {
  HandleScope scope;

  if (args[0]->IsNumber()){
	  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
	  arma::Col<T>* q = w->GetWrapped();
	  q->resize(args[0]->NumberValue());

	  return scope.Close(Undefined());
  } else {
	  return ThrowException(Exception::Error(
	 			  String::New("Error: Function is a constructor, has to be invoked with new.")));
  }

};

template<typename T>
Handle<Value> colvecWrap<T>::set_size(const Arguments& args){
	HandleScope scope;
	if (args.Length() == 1 && args[0]->IsNumber()){

		colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
		arma::Col<T>* q = w->GetWrapped();
		arma::Col<T> A = *q;

		A.set_size(args[0]->NumberValue());
		*q = A;

	} else {
		return ThrowException(Exception::TypeError(
			  String::New("Function expects numeric argument (n_elem).")));
		}
	return scope.Close(Undefined());
};

template<typename T>
Handle<Value> colvecWrap<T>::shed_row(const Arguments& args) {
  HandleScope scope;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();
  arma::Col<T> A = *q;

  A.shed_row(args[0]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
};

template<typename T>
Handle<Value> colvecWrap<T>::shed_rows(const Arguments& args) {
  HandleScope scope;

  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
  arma::Col<T>* q = w->GetWrapped();
  arma::Col<T> A = *q;

  A.shed_rows(args[0]->NumberValue(), args[1]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
};

template<typename T>
Handle<Value> colvecWrap<T>::swap_rows(const Arguments& args) {
  HandleScope scope;

  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
	  arma::Col<T>* q = w->GetWrapped();
	  arma::Col<T> A = *q;

	  A.swap_rows(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
  } else {
	 	  return ThrowException(Exception::TypeError(
	 			  String::New("swap_rows expects two numeric arguments: row1, row2.")));
  }
};

template<typename T>
Handle<Value> colvecWrap<T>::swap_cols(const Arguments& args) {
  HandleScope scope;
  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  colvecWrap<T>* w = ObjectWrap::Unwrap<colvecWrap<T> >(args.This());
	  arma::Col<T>* q = w->GetWrapped();
	  arma::Col<T> A = *q;

	  A.swap_cols(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
	  } else {
		  return ThrowException(Exception::TypeError(
		 	 			  String::New("swap_cols expects two numeric arguments: col1, col2.")));
	  }
};

// Object properties

template<typename T>
 Handle<Value> colvecWrap<T>::GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  HandleScope scope;
  colvecWrap<T>* w = node::ObjectWrap::Unwrap<colvecWrap<T> >(info.Holder());
  arma::Col<T>* q = w->GetWrapped();
  return scope.Close(Number::New(q->n_rows));
};

 template<typename T>
 Handle<Value> colvecWrap<T>::GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   colvecWrap<T>* w = node::ObjectWrap::Unwrap<colvecWrap<T> >(info.Holder());
   arma::Col<T>* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_cols));
 };

 template<typename T>
 Handle<Value> colvecWrap<T>::GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   colvecWrap<T>* w = node::ObjectWrap::Unwrap<colvecWrap<T> >(info.Holder());
   arma::Col<T>* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_elem));
 };
