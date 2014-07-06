#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "matrix.h"
#include "colvec.h"
#include "rowvec.h"


using namespace v8;
using namespace std;

arma::mat UnwrapMatrix(Handle<Value> inputMat){
	Handle<Object> obj = Handle<Object>::Cast(inputMat);
	matWrap* u = node::ObjectWrap::Unwrap<matWrap>(obj);
	arma::mat* r = u->GetWrapped();
	return *r;
}

arma::Col<double> UnwrapColvec(Handle<Value> inputVec){
	Handle<Object> obj = Handle<Object>::Cast(inputVec);
	colvecWrap<double>* u = node::ObjectWrap::Unwrap<colvecWrap<double> >(obj);
	arma::colvec* r = u->GetWrapped();
	return *r;
}

arma::rowvec UnwrapRowvec(Handle<Value> inputVec){
	Handle<Object> obj = Handle<Object>::Cast(inputVec);
	rowvecWrap* u = node::ObjectWrap::Unwrap<rowvecWrap>(obj);
	arma::rowvec* r = u->GetWrapped();
	return *r;
}
