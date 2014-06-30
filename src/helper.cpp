#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "matrix.h"
#include "helper.h"

using namespace v8;
using namespace std;

arma::mat UnwrapMatrix(Handle<Value> inputMat){
	Handle<Object> obj = Handle<Object>::Cast(inputMat);
	matWrap* u = node::ObjectWrap::Unwrap<matWrap>(obj);
	arma::mat* r = u->GetWrapped();
	return *r;
}

