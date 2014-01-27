
#ifndef MATRIX_H
#define MATRIX_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm> 

class matWrap : public node::ObjectWrap {
  
  public:  
    static void Initialize(v8::Handle<v8::Object> target);
    arma::mat* GetWrapped() const { return q_; };
    void SetWrapped(arma::mat q) {
      if (q_) delete q_;
      q_ = new arma::mat(q);
      };
  
  static v8::Handle<v8::Value> NewInstance(arma::mat q);
    
  private:
     matWrap(const v8::Arguments& args);
    ~matWrap();
    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
   static v8::Handle<v8::Value> ones(const v8::Arguments& args);
   static v8::Handle<v8::Value> zeros(const v8::Arguments& args);
   static v8::Handle<v8::Value> fill(const v8::Arguments& args);
   static v8::Handle<v8::Value> t(const v8::Arguments& args);
   static v8::Handle<v8::Value> n_cols(const v8::Arguments& args);
   static v8::Handle<v8::Value> n_rows(const v8::Arguments& args);
   static v8::Handle<v8::Value> print(const v8::Arguments& args);
   
  // Wrapped object
     arma::mat* q_;
};

#endif