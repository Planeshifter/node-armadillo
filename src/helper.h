#ifndef HELPER_H
#define HELPER_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

#include "colvec.h"
#include "rowvec.h"

using namespace v8;

arma::Mat<double> UnwrapMatrix(Handle<Value> inputMat);

arma::Col<double> UnwrapColvec(Handle<Value> inputVec);

arma::Row<double> UnwrapRowvec(Handle<Value> inputVec);

#endif
