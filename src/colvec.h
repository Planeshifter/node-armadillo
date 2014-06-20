#ifndef COLVEC_H
#define COLVEC_H

#include <node.h>
#include <armadillo>  // Armadillo: Linear Algebra package
#include <iostream>
#include <vector>
#include <algorithm>

class colvecWrap : public node::ObjectWrap {

public:
    static void Initialize(v8::Handle<v8::Object> target);
    arma::mat* GetWrapped() const { return q_; };
    void SetWrapped(arma::colvec q) {
      if (q_) delete q_;
      q_ = new arma::colvec(q);
      };

    static v8::Handle<v8::Value> NewInstance(arma::colvec q);

  private:
     matWrap(const v8::Arguments& args);
    ~matWrap();
    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);

	// Wrapped object
    arma::colvec* q_;
};

#endif
