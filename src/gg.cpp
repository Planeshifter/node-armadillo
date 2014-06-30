#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "matrix.h"
#include "helper.h"

using namespace v8;
using namespace std;

Handle<Value> Accu(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);

	double x = accu(A);
	return scope.Close(Number::New(x));
}

Handle<Value> Cond(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);

	double c = cond(A);
	return scope.Close(Number::New(c));

}

Handle<Value> Rank(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);
	int ret;

	if (args.Length() == 2){
	double tolerance = args[1]->NumberValue();
		ret = arma::rank(A, tolerance);
	}
	else {
		ret = arma::rank(A);
	}

	return scope.Close(Number::New(ret));
}

Handle<Value> Trace(const Arguments& args) {
  HandleScope scope;

  arma::mat A = UnwrapMatrix(args[0]);

  double tr = arma::trace(A);

  return scope.Close(Number::New(tr));
}

// element-wise functions:

// Vector/Matrix/Cube Valued Functions of Vectors/Matrices/Cubes

Handle<Value> Kron(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);
	arma::mat B = UnwrapMatrix(args[1]);

	arma::mat K = arma::kron(A,B);

	return scope.Close(matWrap::NewInstance(K));
}

Handle<Value> Trans(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);
	arma::mat B = arma::trans(A);

	return scope.Close(matWrap::NewInstance(B));
}

Handle<Value> Trimatu(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);
	arma::mat U = arma::trimatu(A);

	return scope.Close(matWrap::NewInstance(U));
}

Handle<Value> Trimatl(const Arguments& args){
	HandleScope scope;

	arma::mat A = UnwrapMatrix(args[0]);
	arma::mat L = arma::trimatl(A);

	return scope.Close(matWrap::NewInstance(L));
}

// Decompositions, Factorisations, Inverses and Equation Solvers:

Handle<Value> Chol(const Arguments& args){
	HandleScope scope;

	arma::mat X = UnwrapMatrix(args[0]);
	arma::mat R = chol(X);

	return scope.Close(matWrap::NewInstance(R));
}

Handle<Value> Inv(const Arguments &args){
	HandleScope scope;

	arma::mat X = UnwrapMatrix(args[0]);
	arma::mat X_inv = inv(X);

	return scope.Close(matWrap::NewInstance(X_inv));
}

Handle<Value> Pinv(const Arguments &args){
	HandleScope scope;

	if(args[0]->IsObject() && args[1]->IsObject()){

		Handle<Object> B = Handle<Object>::Cast(args[0]);
		matWrap* B_wrap = node::ObjectWrap::Unwrap<matWrap>(B);
		arma::mat* B_pointer = B_wrap->GetWrapped();
		arma::mat B_res = *B_pointer;

		Handle<Object> A = Handle<Object>::Cast(args[1]);
		matWrap* A_wrap = node::ObjectWrap::Unwrap<matWrap>(A);
		arma::mat* A_pointer = A_wrap->GetWrapped();
		arma::mat A_res = *A_pointer;

		if (args[2]->IsNumber() && args[3]->IsString()){
			v8::String::Utf8Value param3(args[3]->ToString());
			const char *method = *param3;
			arma::pinv(B_res, A_res, args[2]->NumberValue(),method);
		} else if (args[2]->IsNumber()){
			arma::pinv(B_res, A_res, args[2]->NumberValue());
		} else {
			arma::pinv(B_res, A_res);
		}

		// assign decomposed matrices to input matrices
		*B_pointer = B_res;
		*A_pointer = A_res;

		return scope.Close(Undefined());
	}
	else {
		arma::mat A = UnwrapMatrix(args[0]);
		arma::mat retA;
		if (args[1]->IsNumber() && args[2]->IsString())
		{
			v8::String::Utf8Value param2(args[2]->ToString());
			const char *method = *param2;
			retA = arma::pinv(A, args[1]->NumberValue(), method);
		}
		else if (args[1]->IsNumber()){
			retA = arma::pinv(A, args[1]->NumberValue());
		}
		else {
			retA = arma::pinv(A);
		}
	return scope.Close(matWrap::NewInstance(retA));
	}
}

Handle<Value> Qr(const Arguments& args){
	HandleScope scope;

	arma::mat X = UnwrapMatrix(args[2]);

	Handle<Object> Q_obj = Handle<Object>::Cast(args[0]);
	matWrap* Q_wrap = node::ObjectWrap::Unwrap<matWrap>(Q_obj);
	arma::mat* Q_pointer = Q_wrap->GetWrapped();
	arma::mat Q_res = *Q_pointer;

	Handle<Object> R_obj = Handle<Object>::Cast(args[1]);
	matWrap* R_wrap = node::ObjectWrap::Unwrap<matWrap>(R_obj);
	arma::mat* R_pointer = R_wrap->GetWrapped();
	arma::mat R_res = *R_pointer;

	arma::qr(Q_res, R_res, X);

	// assign decomposed matrices to input matrices
	*R_pointer = R_res;
	*Q_pointer = Q_res;

	return scope.Close(Undefined());
}

Handle<Value> Qr_econ(const Arguments& args){
	HandleScope scope;

	arma::mat X = UnwrapMatrix(args[2]);

	Handle<Object> Q_obj = Handle<Object>::Cast(args[0]);
	matWrap* Q_wrap = node::ObjectWrap::Unwrap<matWrap>(Q_obj);
	arma::mat* Q_pointer = Q_wrap->GetWrapped();
	arma::mat Q_res = *Q_pointer;

	Handle<Object> R_obj = Handle<Object>::Cast(args[1]);
	matWrap* R_wrap = node::ObjectWrap::Unwrap<matWrap>(R_obj);
	arma::mat* R_pointer = R_wrap->GetWrapped();
	arma::mat R_res = *R_pointer;

	arma::qr_econ(Q_res, R_res, X);

	// assign decomposed matrices to input matrices
	*R_pointer = R_res;
	*Q_pointer = Q_res;

	return scope.Close(Undefined());
}


void Initialize(Handle<Object> target) {
  matWrap::Initialize(target);

  target->Set(String::NewSymbol("accu"),
         FunctionTemplate::New(Accu)->GetFunction());

  target->Set(String::NewSymbol("cond"),
         FunctionTemplate::New(Cond)->GetFunction());

  target->Set(String::NewSymbol("rank"),
         FunctionTemplate::New(Rank)->GetFunction());

  target->Set(String::NewSymbol("trace"),
       FunctionTemplate::New(Trace)->GetFunction());

  // Vector/Matrix/Cube Valued Functions of Vectors/Matrices/Cubes

  target->Set(String::NewSymbol("kron"),
       FunctionTemplate::New(Kron)->GetFunction());

  target->Set(String::NewSymbol("trans"),
       FunctionTemplate::New(Trans)->GetFunction());

  target->Set(String::NewSymbol("trimatu"),
       FunctionTemplate::New(Trimatu)->GetFunction());

  target->Set(String::NewSymbol("trimatl"),
       FunctionTemplate::New(Trimatl)->GetFunction());

  // Decompositions, Factorisations, Inverses and Equation Solvers:

  target->Set(String::NewSymbol("chol"),
		  FunctionTemplate::New(Chol)->GetFunction());

  target->Set(String::NewSymbol("inv"),
		  FunctionTemplate::New(Inv)->GetFunction());

  target->Set(String::NewSymbol("pinv"),
 		  FunctionTemplate::New(Pinv)->GetFunction());

  target->Set(String::NewSymbol("qr"),
		  FunctionTemplate::New(Qr)->GetFunction());

  target->Set(String::NewSymbol("qr_econ"),
		  FunctionTemplate::New(Qr_econ)->GetFunction());

}

NODE_MODULE(armadillo, Initialize)
