#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "matrix.h"
#include "colvec.h"
#include "rowvec.h"
#include "helper.h"

using namespace v8;
using namespace std;

// element-wise functions:

Handle<Value> Exp(const Arguments& args){
	HandleScope scope;
	if (args[0]->IsObject()){
		if(colvecWrap::HasInstance(args[0]) == true) {
			arma::colvec A = UnwrapColvec(args[0]);
			arma::colvec B = arma::exp(A);
			return scope.Close(colvecWrap::NewInstance(B));
		} else if (matWrap::HasInstance(args[0]) == true){
			arma::mat A = UnwrapMatrix(args[0]);
			arma::mat B = arma::exp(A);
			return scope.Close(matWrap::NewInstance(B));
		}
	}

	return scope.Close(ThrowException(Exception::TypeError(
		 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Exp2(const Arguments& args){
	HandleScope scope;
		if (args[0]->IsObject()){
			if(colvecWrap::HasInstance(args[0]) == true) {
				arma::colvec A = UnwrapColvec(args[0]);
				arma::colvec B = arma::exp2(A);
				return scope.Close(colvecWrap::NewInstance(B));
			} else if (matWrap::HasInstance(args[0]) == true){
				arma::mat A = UnwrapMatrix(args[0]);
				arma::mat B = arma::exp2(A);
				return scope.Close(matWrap::NewInstance(B));
			}
		}

		return scope.Close(ThrowException(Exception::TypeError(
			 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Exp10(const Arguments& args){
	HandleScope scope;
		if (args[0]->IsObject()){
			if(colvecWrap::HasInstance(args[0]) == true) {
				arma::colvec A = UnwrapColvec(args[0]);
				arma::colvec B = arma::exp10(A);
				return scope.Close(colvecWrap::NewInstance(B));
			} else if (matWrap::HasInstance(args[0]) == true){
				arma::mat A = UnwrapMatrix(args[0]);
				arma::mat B = arma::exp10(A);
				return scope.Close(matWrap::NewInstance(B));
			}
		}

		return scope.Close(ThrowException(Exception::TypeError(
			 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Trunc_exp(const Arguments& args){
	HandleScope scope;
		if (args[0]->IsObject()){
			if(colvecWrap::HasInstance(args[0]) == true) {
				arma::colvec A = UnwrapColvec(args[0]);
				arma::colvec B = arma::trunc_exp(A);
				return scope.Close(colvecWrap::NewInstance(B));
			} else if (matWrap::HasInstance(args[0]) == true){
				arma::mat A = UnwrapMatrix(args[0]);
				arma::mat B = arma::trunc_exp(A);
				return scope.Close(matWrap::NewInstance(B));
			}
		}

		return scope.Close(ThrowException(Exception::TypeError(
			 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Log(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::log(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::log(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Log2(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::log2(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::log2(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Log10(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::log10(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::log10(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Trunc_log(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::trunc_log(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::trunc_log(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Pow(const Arguments& args){
	HandleScope scope;
	if (args[0]->IsObject() && args[1]->IsNumber()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::pow(A, args[1]->NumberValue());
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::pow(A, args[1]->NumberValue());
					return scope.Close(matWrap::NewInstance(B));
				}
			}
	return scope.Close(ThrowException(Exception::TypeError(
					 String::New("Expects matrix, vector or field as its first argument, and a numeric data type as its second."))));
}

Handle<Value> Sqrt(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::sqrt(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::sqrt(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Square(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::square(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::square(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Floor(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::floor(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::floor(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Ceil(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::ceil(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::ceil(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Round(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::round(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::round(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

Handle<Value> Sign(const Arguments& args){
	HandleScope scope;
			if (args[0]->IsObject()){
				if(colvecWrap::HasInstance(args[0]) == true) {
					arma::colvec A = UnwrapColvec(args[0]);
					arma::colvec B = arma::sign(A);
					return scope.Close(colvecWrap::NewInstance(B));
				} else if (matWrap::HasInstance(args[0]) == true){
					arma::mat A = UnwrapMatrix(args[0]);
					arma::mat B = arma::sign(A);
					return scope.Close(matWrap::NewInstance(B));
				}
			}

			return scope.Close(ThrowException(Exception::TypeError(
				 String::New("Function expects a matrix, vector or field as its sole argument."))));
}

// Scalar Valued Functions of Vectors/Matrices/Cubes

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

Handle<Value> Det(const Arguments& args){
	HandleScope scope;

	if(matWrap::HasInstance(args[0]) != true){
		return ThrowException(Exception::TypeError(
		String::New("det() expects a (square) matrix as its first argument")));
	}

	double ret;
	arma::mat A = UnwrapMatrix(args[0]);

	if(args[1]->IsString()){
		v8::String::Utf8Value param1(args[1]->ToString());
		const char *method = *param1;
		ret = arma::det(A, method);
	} else {
		ret = arma::det(A);
	}

	return scope.Close(Number::New(ret));

}

Handle<Value> Dot(const Arguments& args){
	HandleScope scope;
	if (args[0]->IsObject() && args[1]->IsObject()){
		if(matWrap::HasInstance(args[0]) == true){
			arma::mat A = UnwrapMatrix(args[0]);

			if(matWrap::HasInstance(args[1]) == true){

					arma::mat B = UnwrapMatrix(args[1]);
					double ret = arma::dot(A,B);
					return scope.Close(Number::New(ret));

					} else if (colvecWrap::HasInstance(args[1]) == true){

						arma::colvec B = UnwrapColvec(args[1]);
						double ret = arma::dot(A,B);
						return scope.Close(Number::New(ret));
					}

		} else if (colvecWrap::HasInstance(args[0]) == true){
			arma::colvec A = UnwrapColvec(args[0]);

			if(matWrap::HasInstance(args[1]) == true){

					arma::mat B = UnwrapMatrix(args[1]);
					double ret = arma::dot(A,B);
					return scope.Close(Number::New(ret));

					} else if (colvecWrap::HasInstance(args[1]) == true){

						arma::colvec B = UnwrapColvec(args[1]);
						double ret = arma::dot(A,B);
						return scope.Close(Number::New(ret));
					}
		}
	}
	else {
		return ThrowException(Exception::TypeError(
		String::New("dot() expects two vectors with the same number of elements as its arguments.")));
		}
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

  if(matWrap::HasInstance(args[0]) != true) {
	  return ThrowException(Exception::TypeError(
		  String::New("Function expects a (square) matrix as its sole argument")));
  }

  arma::mat A = UnwrapMatrix(args[0]);
  double tr = arma::trace(A);
  return scope.Close(Number::New(tr));
}

// Scalar/Vector Valued Functions of Vectors/Matrices

Handle<Value> All(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
		arma::colvec X = UnwrapColvec(args[0]);
		bool status = arma::all(X);
		return scope.Close(Boolean::New(status));
	} else if(matWrap::HasInstance(args[0]) == true){

	}

}

Handle<Value> Diagvec(const Arguments& args){
	HandleScope scope;

	if(matWrap::HasInstance(args[0])==false){
	 return ThrowException(Exception::TypeError(
	 				String::New("Function expects a matrix as its first argument")));
	}

	arma::colvec ret;
	arma::mat X = UnwrapMatrix(args[0]);

	if(args[1]->IsNumber() == true){
		ret = arma::diagvec(X, args[1]->NumberValue());
	} else {
		ret = arma::diagvec(X);
	}

	return scope.Close(colvecWrap::NewInstance(ret));
}

Handle<Value> Min(const Arguments& args){
	HandleScope scope;
		if(colvecWrap::HasInstance(args[0]) == true) {
				double ret;
				arma::colvec X = UnwrapColvec(args[0]);
				ret = arma::min(X);
				return scope.Close(Number::New(ret));
			}

		if(matWrap::HasInstance(args[0]) == true && matWrap::HasInstance(args[1]) == true){
			arma::mat X = UnwrapMatrix(args[0]);
			arma::mat Y = UnwrapMatrix(args[1]);
			arma::mat ret = arma::min(X,Y);
			return scope.Close(matWrap::NewInstance(ret));
		}

		if(matWrap::HasInstance(args[0]) == true) {
			arma::mat X = UnwrapMatrix(args[0]);
			if(args[1]->IsNumber() && args[1]->NumberValue() == 1){
			  arma::colvec ret = arma::min(X, args[1]->NumberValue());
			  return scope.Close(colvecWrap::NewInstance(ret));
			} else {
			  arma::rowvec ret = arma::min(X);
			  return scope.Close(rowvecWrap::NewInstance(ret));
			}
		}
		return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));
}

Handle<Value> Max(const Arguments& args){
	HandleScope scope;
		if(colvecWrap::HasInstance(args[0]) == true) {
				double ret;
				arma::colvec X = UnwrapColvec(args[0]);
				ret = arma::max(X);
				return scope.Close(Number::New(ret));
			}

		if(matWrap::HasInstance(args[0]) == true && matWrap::HasInstance(args[1]) == true){
				arma::mat X = UnwrapMatrix(args[0]);
				arma::mat Y = UnwrapMatrix(args[1]);
				arma::mat ret = arma::max(X,Y);
				return scope.Close(matWrap::NewInstance(ret));
			}

		if(matWrap::HasInstance(args[0]) == true) {
			arma::mat X = UnwrapMatrix(args[0]);
			if(args[1]->IsNumber() && args[1]->NumberValue() == 1){
			  arma::colvec ret = arma::max(X, args[1]->NumberValue());
			  return scope.Close(colvecWrap::NewInstance(ret));
			} else {
			  arma::rowvec ret = arma::max(X);
			  return scope.Close(rowvecWrap::NewInstance(ret));
			}
		}

		return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));
}

Handle<Value> Prod(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
			double ret;
			arma::colvec X = UnwrapColvec(args[0]);
			ret = arma::prod(X);
			return scope.Close(Number::New(ret));
		}
		if(matWrap::HasInstance(args[0]) == true) {
			arma::mat X = UnwrapMatrix(args[0]);
			if(args[1]->IsNumber() && args[1]->NumberValue() == 1){
			  arma::colvec ret = arma::prod(X, args[1]->NumberValue());
			  return scope.Close(colvecWrap::NewInstance(ret));
			} else {
			  arma::rowvec ret = arma::prod(X);
			  return scope.Close(rowvecWrap::NewInstance(ret));
			}
		}
		return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));
}

Handle<Value> Sum(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
		double ret;
		arma::colvec X = UnwrapColvec(args[0]);
		ret = arma::sum(X);
		return scope.Close(Number::New(ret));
	}
	if(matWrap::HasInstance(args[0]) == true) {
		arma::mat X = UnwrapMatrix(args[0]);
		if(args[1]->IsNumber() && args[1]->NumberValue() == 1){
		  arma::colvec ret = arma::sum(X,args[1]->NumberValue());
		  return scope.Close(colvecWrap::NewInstance(ret));
		} else {
		  arma::rowvec ret = arma::sum(X);
		  return scope.Close(rowvecWrap::NewInstance(ret));
		}
	}

	return ThrowException(Exception::TypeError(
		String::New("Function expects a matrix or vector as its first argument")));
}

Handle<Value> Mean(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
		arma::colvec X = UnwrapColvec(args[0]);
		return scope.Close(Number::New(arma::mean(X)));
	} else if(matWrap::HasInstance(args[0]) == true){

	}

	return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));

}

Handle<Value> Median(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
		arma::colvec X = UnwrapColvec(args[0]);
		return scope.Close(Number::New(arma::median(X)));
	} else if(matWrap::HasInstance(args[0]) == true){

	}

	return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));

}

Handle<Value> Stddev(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
		arma::colvec X = UnwrapColvec(args[0]);
		return scope.Close(Number::New(arma::stddev(X)));
	} else if(matWrap::HasInstance(args[0]) == true){

	}

	return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));

}

Handle<Value> Var(const Arguments& args){
	HandleScope scope;
	if(colvecWrap::HasInstance(args[0]) == true) {
		arma::colvec X = UnwrapColvec(args[0]);
		return scope.Close(Number::New(arma::var(X)));
	} else if(matWrap::HasInstance(args[0]) == true){

	}

	return ThrowException(Exception::TypeError(
			String::New("Function expects a matrix or vector as its first argument")));

}


// Vector/Matrix/Cube Valued Functions of Vectors/Matrices/Cubes


Handle<Value> Diagmat(const Arguments& args){
	HandleScope scope;

	if (matWrap::HasInstance(args[0])){
	arma::mat X = UnwrapMatrix(args[0]);
	arma::mat R = arma::diagmat(X);
	return scope.Close(matWrap::NewInstance(R));
	} else if (colvecWrap::HasInstance(args[0])){
	 arma::colvec x = UnwrapColvec(args[0]);
	 arma::mat R = arma::diagmat(x);
	 return scope.Close(matWrap::NewInstance(R));
	}

	return ThrowException(Exception::TypeError(
		String::New("Function expects a matrix or vector as its sole argument")));
}

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
  // initialize armadillo classes
  matWrap::Initialize(target);
  colvecWrap::Initialize(target);
  rowvecWrap::Initialize(target);

  // module functions
  target->Set(String::NewSymbol("accu"),
         FunctionTemplate::New(Accu)->GetFunction());

  target->Set(String::NewSymbol("cond"),
         FunctionTemplate::New(Cond)->GetFunction());

  target->Set(String::NewSymbol("det"),
         FunctionTemplate::New(Det)->GetFunction());

  target->Set(String::NewSymbol("dot"),
         FunctionTemplate::New(Dot)->GetFunction());

  target->Set(String::NewSymbol("rank"),
         FunctionTemplate::New(Rank)->GetFunction());

  target->Set(String::NewSymbol("trace"),
       FunctionTemplate::New(Trace)->GetFunction());

  // element-wise functions:

  target->Set(String::NewSymbol("exp"),
       FunctionTemplate::New(Exp)->GetFunction());

  target->Set(String::NewSymbol("exp2"),
       FunctionTemplate::New(Exp2)->GetFunction());

  target->Set(String::NewSymbol("exp10"),
       FunctionTemplate::New(Exp10)->GetFunction());

  target->Set(String::NewSymbol("trunc_exp"),
       FunctionTemplate::New(Trunc_exp)->GetFunction());

  target->Set(String::NewSymbol("log"),
       FunctionTemplate::New(Log)->GetFunction());

  target->Set(String::NewSymbol("log2"),
       FunctionTemplate::New(Log2)->GetFunction());

  target->Set(String::NewSymbol("log10"),
       FunctionTemplate::New(Log10)->GetFunction());

  target->Set(String::NewSymbol("trunc_log"),
       FunctionTemplate::New(Trunc_log)->GetFunction());

  target->Set(String::NewSymbol("pow"),
       FunctionTemplate::New(Pow)->GetFunction());

  target->Set(String::NewSymbol("sqrt"),
       FunctionTemplate::New(Sqrt)->GetFunction());

  target->Set(String::NewSymbol("square"),
       FunctionTemplate::New(Square)->GetFunction());

  target->Set(String::NewSymbol("floor"),
       FunctionTemplate::New(Floor)->GetFunction());

  target->Set(String::NewSymbol("ceil"),
       FunctionTemplate::New(Ceil)->GetFunction());

  target->Set(String::NewSymbol("round"),
       FunctionTemplate::New(Round)->GetFunction());

  target->Set(String::NewSymbol("sign"),
       FunctionTemplate::New(Sign)->GetFunction());

  // Scalar/Vector Valued Functions of Vectors/Matrices

  target->Set(String::NewSymbol("all"),
       FunctionTemplate::New(All)->GetFunction());

  target->Set(String::NewSymbol("diagvec"),
       FunctionTemplate::New(Diagvec)->GetFunction());

  target->Set(String::NewSymbol("min"),
       FunctionTemplate::New(Min)->GetFunction());

  target->Set(String::NewSymbol("max"),
       FunctionTemplate::New(Max)->GetFunction());

  target->Set(String::NewSymbol("prod"),
       FunctionTemplate::New(Prod)->GetFunction());

  target->Set(String::NewSymbol("sum"),
       FunctionTemplate::New(Sum)->GetFunction());

  target->Set(String::NewSymbol("mean"),
       FunctionTemplate::New(Mean)->GetFunction());

  target->Set(String::NewSymbol("median"),
       FunctionTemplate::New(Median)->GetFunction());

  target->Set(String::NewSymbol("stddev"),
       FunctionTemplate::New(Stddev)->GetFunction());

  target->Set(String::NewSymbol("var"),
       FunctionTemplate::New(Var)->GetFunction());

  // Vector/Matrix/Cube Valued Functions of Vectors/Matrices/Cubes

  target->Set(String::NewSymbol("diagmat"),
       FunctionTemplate::New(Diagmat)->GetFunction());

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
