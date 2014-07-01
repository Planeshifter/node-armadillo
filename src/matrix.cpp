#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm> 

#include "matrix.h"
#include "helper.h"

using namespace v8;
using namespace std;

Persistent<FunctionTemplate> matWrap::constructor;

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
  
  else if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()) {
  q_ = new arma::mat(args[0]->NumberValue(), args[1]->NumberValue());
  }
  
  else if (args.Length() == 3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsString() )
  {
    
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
      FunctionTemplate::New(zeros)->GetFunction());    
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("fill"),
      FunctionTemplate::New(fill)->GetFunction());  
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("n_cols"),
      FunctionTemplate::New(n_cols)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("n_rows"),
      FunctionTemplate::New(n_rows)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("n_elem"),
      FunctionTemplate::New(n_elem)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("print"),
      FunctionTemplate::New(print)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("t"),
      FunctionTemplate::New(t)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("reset"),
      FunctionTemplate::New(reset)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_empty"),
      FunctionTemplate::New(is_empty)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_finite"),
      FunctionTemplate::New(is_finite)->GetFunction());
  
  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_square"),
      FunctionTemplate::New(is_square)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_vec"),
      FunctionTemplate::New(is_vec)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_colvec"),
      FunctionTemplate::New(is_colvec)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("is_rowvec"),
      FunctionTemplate::New(is_rowvec)->GetFunction());


  tpl->PrototypeTemplate()->Set(String::NewSymbol("eye"),
      FunctionTemplate::New(eye)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("resize"),
      FunctionTemplate::New(resize)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("i"),
      FunctionTemplate::New(i)->GetFunction());
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("at"),
      FunctionTemplate::New(at)->GetFunction());
  
  tpl->PrototypeTemplate()->Set(String::NewSymbol("randu"),
      FunctionTemplate::New(randu)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("randn"),
      FunctionTemplate::New(randn)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("set_size"),
       FunctionTemplate::New(set_size)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_row"),
       FunctionTemplate::New(shed_row)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_rows"),
       FunctionTemplate::New(shed_rows)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_col"),
       FunctionTemplate::New(shed_col)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("shed_cols"),
       FunctionTemplate::New(shed_cols)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("swap_rows"),
      FunctionTemplate::New(swap_rows)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("swap_cols"),
      FunctionTemplate::New(swap_cols)->GetFunction());


  // Submatrix views

  tpl->PrototypeTemplate()->Set(String::NewSymbol("col"),
		  FunctionTemplate::New(col)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("row"),
		  FunctionTemplate::New(row)->GetFunction());

  // Operators
  tpl->PrototypeTemplate()->Set(String::NewSymbol("add"),
      FunctionTemplate::New(add)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("subtract"),
      FunctionTemplate::New(subtract)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("elementMultiply"),
        FunctionTemplate::New(elementMultiply)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("elementDivide"),
        FunctionTemplate::New(elementDivide)->GetFunction());

    // Object properties

   tpl->InstanceTemplate()->SetAccessor(String::New("n_rows"), GetNrow);

   tpl->InstanceTemplate()->SetAccessor(String::New("n_cols"), GetNcol);

   tpl->InstanceTemplate()->SetAccessor(String::New("n_elem"), GetNelem);


  constructor = Persistent<FunctionTemplate>::New(tpl);
  target->Set(String::NewSymbol("mat"), constructor->GetFunction());
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
  *q = q->fill(args[0]->NumberValue());
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
  
  Local<Object> instance = constructor->GetFunction()->NewInstance(0, NULL);
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

Handle<Value> matWrap::n_elem(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Number::New(q->n_elem));
}


Handle<Value> matWrap::print(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  q->print();
  return scope.Close(Undefined());
}



Handle<Value> matWrap::reset(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  q->reset();

  return scope.Close(Undefined());
}


Handle<Value> matWrap::is_empty(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_empty()));
}

Handle<Value> matWrap::is_finite(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_finite()));
}

Handle<Value> matWrap::is_square(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_square()));
}

Handle<Value> matWrap::is_vec(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_vec()));
}

Handle<Value> matWrap::is_colvec(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_colvec()));
}

Handle<Value> matWrap::is_rowvec(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->is_rowvec()));
}

Handle<Value> matWrap::eye(const Arguments& args) {
  HandleScope scope;
  
    matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
    arma::mat* q = w->GetWrapped();
    arma::mat A = *q;
    
  if (args.Length() == 0)
    {
    A.eye();
    }
  else if(args.Length() == 2)
    {
    A.eye(args[0]->NumberValue(), args[1]->NumberValue());
    }
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> matWrap::resize(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  q->resize(args[0]->NumberValue(), args[1]->NumberValue());

  return scope.Close(Undefined());
}

Handle<Value> matWrap::i(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();  
  return scope.Close(NewInstance(q->i()));
}

Handle<Value> matWrap::at(const Arguments& args) {
  HandleScope scope;
  Local<Value> ret;
  
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();  
  
  if(args.Length() == 1 && args[0]->IsNumber())
    {
    ret = Number::New(q->at(args[0]->NumberValue()));
    }
  else if(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber())
    {
    ret = Number::New(q->at(args[0]->NumberValue(), args[1]->NumberValue()));
    }
  return scope.Close(ret);
}

Handle<Value> matWrap::randu(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat A = *q;

  if (args.Length() == 0)
  	  {
	  A.randu();
  	  }
  else if (args.Length() == 2)
	  {
		  A.randu(args[0]->NumberValue(), args[1]->NumberValue());
	  }
  *q = A;
  return scope.Close(Undefined());
}


Handle<Value> matWrap::randn(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat A = *q;

  if (args.Length() == 0)
  	  {
	  A.randn();
  	  }
  else if (args.Length() == 2)
	  {
		  A.randn(args[0]->NumberValue(), args[1]->NumberValue());
	  }
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> matWrap::set_size(const Arguments& args){
	HandleScope scope;
	if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){

		  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
		  arma::mat* q = w->GetWrapped();
		  arma::mat A = *q;

		  A.set_size(args[0]->NumberValue(),args[1]->NumberValue());
		  *q = A;

	} else {
		return ThrowException(Exception::TypeError(
			  String::New("Functions expects two numeric arguments (n_rows, n_cols).")));
		}
	return scope.Close(Undefined());
}

Handle<Value> matWrap::shed_row(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat A = *q;

  A.shed_row(args[0]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> matWrap::shed_rows(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat A = *q;

  A.shed_rows(args[0]->NumberValue(), args[1]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}

Handle<Value> matWrap::shed_col(const Arguments& args) {
  HandleScope scope;

  if(args.Length() == 1 && args[0]->IsNumber())
  {
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat A = *q;

  A.shed_col(args[0]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
  }
  else
	  {
	  return ThrowException(Exception::TypeError(
			  String::New("shed_col function has only one (numeric) argument: column_number")));
	  }
}

Handle<Value> matWrap::shed_cols(const Arguments& args) {
  HandleScope scope;

  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat A = *q;

  A.shed_cols(args[0]->NumberValue(), args[1]->NumberValue());
  *q = A;
  return scope.Close(Undefined());
}



Handle<Value> matWrap::swap_rows(const Arguments& args) {
  HandleScope scope;

  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
	  arma::mat* q = w->GetWrapped();
	  arma::mat A = *q;

	  A.swap_rows(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
  } else {
	 	  return ThrowException(Exception::TypeError(
	 			  String::New("Function expects two numeric arguments: row1, row2.")));
  }
}

Handle<Value> matWrap::swap_cols(const Arguments& args) {
  HandleScope scope;
  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber()){
	  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
	  arma::mat* q = w->GetWrapped();
	  arma::mat A = *q;

	  A.swap_cols(args[0]->NumberValue(), args[1]->NumberValue());
	  *q = A;
	  return scope.Close(Undefined());
	  } else {
		  return ThrowException(Exception::TypeError(
		 	 			  String::New("Function expects two numeric arguments: col1, col2.")));
	  }
}

// Submatrix views

Handle<Value> matWrap::col(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args.This());
	arma::mat A_col = A.col(args[0]->NumberValue());

	return scope.Close(NewInstance(A_col));
}

Handle<Value> matWrap::row(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args.This());

	arma::mat A_row = A.row(args[0]->NumberValue());

	return scope.Close(NewInstance(A_row));
}

// Operators

Handle<Value> matWrap::add(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat a = *q;
  arma::mat c;

  if (args[0]->IsObject())
  {
  Handle<Object> obj = Handle<Object>::Cast(args[0]);
  matWrap* u = ObjectWrap::Unwrap<matWrap>(obj);
  arma::mat* r = u->GetWrapped();
  arma::mat b = *r;
  c = a + b;
  }
  else if (args[0]->IsNumber())
  {
  double b = args[0]->NumberValue();
  c = a + b;
  }
  return scope.Close(NewInstance(c));
}

Handle<Value> matWrap::subtract(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat a = *q;
  arma::mat c;

  if (args[0]->IsObject())
  {
  Handle<Object> obj = Handle<Object>::Cast(args[0]);
  matWrap* u = ObjectWrap::Unwrap<matWrap>(obj);
  arma::mat* r = u->GetWrapped();
  arma::mat b = *r;
  c = a - b;
  }
  else if (args[0]->IsNumber())
  {
  double b = args[0]->NumberValue();
  c = a - b;
  }
  return scope.Close(NewInstance(c));
}

Handle<Value> matWrap::elementMultiply(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat a = *q;

  Handle<Object> obj = Handle<Object>::Cast(args[0]);
  matWrap* u = ObjectWrap::Unwrap<matWrap>(obj);
  arma::mat* r = u->GetWrapped();
  arma::mat b = *r;

  arma::mat c = a % b;
  return scope.Close(NewInstance(c));
}

Handle<Value> matWrap::elementDivide(const Arguments& args) {
  HandleScope scope;
  matWrap* w = ObjectWrap::Unwrap<matWrap>(args.This());
  arma::mat* q = w->GetWrapped();
  arma::mat a = *q;

  Handle<Object> obj = Handle<Object>::Cast(args[0]);
  matWrap* u = ObjectWrap::Unwrap<matWrap>(obj);
  arma::mat* r = u->GetWrapped();
  arma::mat b = *r;

  arma::mat c = a / b;
  return scope.Close(NewInstance(c));
}

// Object properties

 Handle<Value> matWrap::GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  HandleScope scope;
  matWrap* w = node::ObjectWrap::Unwrap<matWrap>(info.Holder());
  arma::mat* q = w->GetWrapped();
  return scope.Close(Number::New(q->n_rows));
}

 Handle<Value> matWrap::GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   matWrap* w = node::ObjectWrap::Unwrap<matWrap>(info.Holder());
   arma::mat* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_cols));
 }


 Handle<Value> matWrap::GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
   HandleScope scope;
   matWrap* w = node::ObjectWrap::Unwrap<matWrap>(info.Holder());
   arma::mat* q = w->GetWrapped();
   return scope.Close(Number::New(q->n_elem));
 }

