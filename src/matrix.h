#ifndef MATRIX_H
#define MATRIX_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace v8;

class matWrap : public node::ObjectWrap {
  
  public:  
    static void Initialize(v8::Handle<v8::Object> target);
    arma::mat* GetWrapped() const { return q_; };
    void SetWrapped(arma::mat q) {
      if (q_) delete q_;
      q_ = new arma::mat(q);
      };
  
    static v8::Handle<v8::Value> NewInstance(arma::mat q);
    
    // check whether something is an instance of the matrix class
     static bool HasInstance(v8::Handle<v8::Value> value) {
 		 if (!value->IsObject()) return false;
 		 v8::Local<Object> obj = value->ToObject();
 		 return constructor->HasInstance(obj);
 		 }

  private:
     matWrap(const v8::Arguments& args);
    ~matWrap();

    static v8::Persistent<v8::FunctionTemplate> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
   static v8::Handle<v8::Value> at(const v8::Arguments& args);

   static v8::Handle<v8::Value> eye(const v8::Arguments& args);

   static v8::Handle<v8::Value> fill(const v8::Arguments& args);

   static v8::Handle<v8::Value> i(const v8::Arguments& args);
   static v8::Handle<v8::Value> is_empty(const v8::Arguments& args);
   static v8::Handle<v8::Value> is_finite(const v8::Arguments& args);   
   static v8::Handle<v8::Value> is_square(const v8::Arguments& args);
   static v8::Handle<v8::Value> is_vec(const v8::Arguments& args);
   static v8::Handle<v8::Value> is_colvec(const v8::Arguments& args);
   static v8::Handle<v8::Value> is_rowvec(const v8::Arguments& args);
   
   static v8::Handle<v8::Value> n_cols(const v8::Arguments& args);
   static v8::Handle<v8::Value> n_rows(const v8::Arguments& args);
   static v8::Handle<v8::Value> n_elem(const v8::Arguments& args);
   
   static v8::Handle<v8::Value> ones(const v8::Arguments& args);
   
   static v8::Handle<v8::Value> print(const v8::Arguments& args);
   
   static v8::Handle<v8::Value> randu(const v8::Arguments& args);
   static v8::Handle<v8::Value> randn(const v8::Arguments& args);
   static v8::Handle<v8::Value> reset(const v8::Arguments& args);
   static v8::Handle<v8::Value> resize(const v8::Arguments& args);

   static v8::Handle<v8::Value> set_size(const v8::Arguments& args);
   static v8::Handle<v8::Value> shed_row(const v8::Arguments& args);
   static v8::Handle<v8::Value> shed_rows(const v8::Arguments& args);
   static v8::Handle<v8::Value> shed_col(const v8::Arguments& args);
   static v8::Handle<v8::Value> shed_cols(const v8::Arguments& args);
   static v8::Handle<v8::Value> swap_rows(const v8::Arguments& args);
   static v8::Handle<v8::Value> swap_cols(const v8::Arguments& args);

   static v8::Handle<v8::Value> t(const v8::Arguments& args);

   static v8::Handle<v8::Value> zeros(const v8::Arguments& args);

   // Submatrix Views

   static v8::Handle<v8::Value> col(const v8::Arguments& args);
   static v8::Handle<v8::Value> row(const v8::Arguments& args);

   // Operators
   static v8::Handle<v8::Value> add(const v8::Arguments& args);
   static v8::Handle<v8::Value> subtract(const v8::Arguments& args);
   static v8::Handle<v8::Value> elementMultiply(const v8::Arguments& args);
   static v8::Handle<v8::Value> elementDivide(const v8::Arguments& args);

   // Accesors
   static v8::Handle<v8::Value> GetNrow(v8::Local<v8::String> property, const v8::AccessorInfo& info);
   static v8::Handle<v8::Value> GetNcol(v8::Local<v8::String> property, const v8::AccessorInfo& info);
   static v8::Handle<v8::Value> GetNelem(v8::Local<v8::String> property, const v8::AccessorInfo& info);

   // Wrapped object
   arma::mat* q_;
};

#endif
