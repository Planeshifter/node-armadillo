#ifndef COLVEC_H
#define COLVEC_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

using namespace v8;

template <typename T>
class colvecWrap : public node::ObjectWrap {

public:
    static void Initialize(v8::Handle<v8::Object> target);
    arma::Col<T>* GetWrapped() const { return q_; };
    void SetWrapped(arma::Col<T> q) {
      if (q_) delete q_;
      q_ = new arma::Col<T>(q);
      };

    static void registerMethods(Local<FunctionTemplate> tpl);
    static v8::Handle<v8::Value> NewInstance(arma::Col<T> q);

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
    static v8::Handle<v8::Value> shed_row(const v8::Arguments& args);
    static v8::Handle<v8::Value> shed_rows(const v8::Arguments& args);
    static v8::Handle<v8::Value> swap_rows(const v8::Arguments& args);
    static v8::Handle<v8::Value> swap_cols(const v8::Arguments& args);

    static v8::Handle<v8::Value> zeros(const v8::Arguments& args);

    // Accesors
    static v8::Handle<v8::Value> GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static v8::Handle<v8::Value> GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static v8::Handle<v8::Value> GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info);

	// Wrapped object
    arma::Col<T>* q_;
};

#include "colvec.cpp"

#endif
