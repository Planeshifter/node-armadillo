#ifndef HELPER_H
#define HELPER_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

#include "colvec.h"

using namespace v8;

arma::mat UnwrapMatrix(Handle<Value> inputMat);
arma::colvec UnwrapColvec(Handle<Value> inputVec);
colvecWrap ColvecApply(Handle<Value> inputVec, Handle<Function> FUN);

#endif
