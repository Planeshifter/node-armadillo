#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <armadillo>
#include <iostream>
#include <vector>
#include <algorithm>

#include "matrix.h"

using namespace v8;
using namespace std;


void Initialize(Handle<Object> target) {
  matWrap::Initialize(target);
}

NODE_MODULE(armadillo, Initialize)
