#include "../lib/complex.h"
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>

complex::complex(){
}

complex::complex(double a, double b, bool polar=false){
  if(polar){
    this->SetRe(a);
    this->SetImg(b);
    this->SetMod(this->CalMod());
    this->SetArg(this->CalArg());
  }else{
    this->SetMod(a);
    this->SetArg(b);
    this->SetRe(this->CalRe());
    this->SetImg(this->CalImg());
  }
}

complex comolex::operator+(complex &other){
  if(this->polar
}

complex comolex::operator

complex comolex::operator

complex comolex::operator

complex comolex::operator

complex comolex::operator
