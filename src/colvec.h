#ifndef COLVEC_H
#define COLVEC_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

using namespace v8;

class colvecWrap : public node::ObjectWrap {

public:
    static void Initialize(v8::Handle<v8::Object> target);
    arma::colvec* GetWrapped() const { return q_; };
    void SetWrapped(arma::colvec q) {
      if (q_) delete q_;
      q_ = new arma::colvec(q);
      };

    static v8::Handle<v8::Value> NewInstance(arma::colvec q);

    // check whether something is an instance of the colvec class
     static bool HasInstance(v8::Handle<v8::Value> value) {
 		 if (!value->IsObject()) return false;
 		 v8::Local<Object> obj = value->ToObject();
 		 return constructor->HasInstance(obj);
 		 }

  private:
     colvecWrap(const v8::Arguments& args);
    ~colvecWrap();
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);

    static v8::Handle<v8::Value> at(const v8::Arguments& args);


	// Wrapped object
    arma::colvec* q_;
};

#endif
