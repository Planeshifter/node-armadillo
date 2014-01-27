#define BUILDING_NODE_EXTENSION
#include <node.h>

#include "matrix.h"

using namespace v8;

void Initialize(Handle<Object> target) {
  matWrap::Initialize(target);
}

NODE_MODULE(GrumpyGolem, Initialize)