#ifndef ROWVEC_H
#define ROWVEC_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

using namespace v8;

class rowvecWrap : public node::ObjectWrap {

public:
    static void Initialize(v8::Handle<v8::Object> target);
    arma::rowvec* GetWrapped() const { return q_; };
    void SetWrapped(arma::rowvec q) {
      if (q_) delete q_;
      q_ = new arma::rowvec(q);
      };

    static v8::Handle<v8::Value> NewInstance(arma::rowvec q);

    // check whether something is an instance of the rowvec class
     static bool HasInstance(v8::Handle<v8::Value> value) {
 		 if (!value->IsObject()) return false;
 		 v8::Local<Object> obj = value->ToObject();
 		 return constructor->HasInstance(obj);
 		 }

  private:
     rowvecWrap(const v8::Arguments& args);
    ~rowvecWrap();
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);

    // Methods

    static v8::Handle<v8::Value> at(const v8::Arguments& args);

    static v8::Handle<v8::Value> fill(const v8::Arguments& args);

    static v8::Handle<v8::Value> is_empty(const v8::Arguments& args);
    static v8::Handle<v8::Value> is_finite(const v8::Arguments& args);

    static v8::Handle<v8::Value> print(const v8::Arguments& args);

    static v8::Handle<v8::Value> randu(const v8::Arguments& args);
    static v8::Handle<v8::Value> randn(const v8::Arguments& args);
    static v8::Handle<v8::Value> reset(const v8::Arguments& args);
    static v8::Handle<v8::Value> resize(const v8::Arguments& args);


    static v8::Handle<v8::Value> set_size(const v8::Arguments& args);
    static v8::Handle<v8::Value> shed_col(const v8::Arguments& args);
    static v8::Handle<v8::Value> shed_cols(const v8::Arguments& args);
    static v8::Handle<v8::Value> swap_rows(const v8::Arguments& args);
    static v8::Handle<v8::Value> swap_cols(const v8::Arguments& args);

    static v8::Handle<v8::Value> zeros(const v8::Arguments& args);

    // Accesors
    static v8::Handle<v8::Value> GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static v8::Handle<v8::Value> GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static v8::Handle<v8::Value> GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info);

	// Wrapped object
    arma::rowvec* q_;
};

#endif
