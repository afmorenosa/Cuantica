#include "../lib/complex.h"
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>

#define Pi std::acos(-1)

complex::complex(){
}

complex::complex(double a, double b, bool polar=false){
  if(!(polar)){
    this->SetRe(a);
    this->SetImg(b);
    this->SetMod(this->CalMod());
    this->SetArg(this->CalArg());
  }else{
    this->SetMod(a);
    this->SetArg(b);
    this->SetPol(polar);
    this->SetRe(this->CalRe());
    this->SetImg(this->CalImg());
  }
}

void complex::SetPol(bool p){
  Polar= p;
}

void complex::SetImg(double b){
  z[1]=b;
}

void complex::SetRe(double a){
  z[0]=a;
}

void complex::SetMod(double r){
  zp[0]=r;
}

void complex::SetArg(double t){
  bool md;
  if(md%2==0){
    t=t%Pi;
  }else{
    t=t%Pi-Pi;
  }
  z[1]=t;
}

void complex::SetZ(double a, double b, bool polar=false){
  if(!(polar)){
    z[0]=a;
    z[1]=b;
    zp[0]=this->CalMod();
    zp[1]=this->CalArg();
  }else{
    zp[0]=a;
    zp[1]=b;
    z[0]=this->CalRe();
    z[1]=this->CalImg();
  }
}

complex complex::operator+(complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe() + other.GetRe(),this->GetImg() + other.GetImg());
  z.SetPol(zPol);
  return z;
}

complex complex::operator-(complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe() - other.GetRe(),this->GetImg() - other.GetImg());
  z.SetPol(zPol);
  return z;
}

complex complex::Scalar_Product(double Scl){
  bool zPol=false;
  if(this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe()*Scl,this->GetImg()Scl);
  z.SetPol(zPol);
  return z;
}

complex complex::operator*(complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe()* other.GetRe()-this->GetImg()* other.GetImg(),this->GetRe()* other.GetImg()+this->GetImg()* other.GetRe());
  z.SetPol(zPol);
  return z;
}

complex complex::operator/(complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe()* other.GetRe()+this->GetImg()* other.GetImg(),-this->GetRe()* other.GetImg()+this->GetImg()* other.GetRe());
z= z.Scalar_Product(1/other.GetMod());
  z.SetPol(zPol);
  return z;
}

bool complex::operator==(complex &other){
  if(this->GetRe()==other.GetRe() && this->GetImg()==other.GetImg()){
    return true;
  }else{
    return false;
  }
}

bool complex::operator!=(complex &other){
  if(this->GetRe()!=other.GetRe() || this->GetImg()!=other.GetImg()){
    return true;
  }else{
    return false;
  }
}

complex complex::operator+=(complex &other){
  *this=*this+other;
  return *this;
}

complex complex::operator-=(complex &other){
  *this=*this-other;
  return *this;
}

complex complex::operator*=(complex &other){
  *this=*this*other;
  return *this;
}

complex complex::operator/=(complex &other){
  *this=*this/other;
  return *this;
}

std::ostream& complex::operator<<(std::ostream &out, const complex &c){
  if(!(c.GetPol())){
    out<<c.GetRe()<<"+"<<GetImg()<<"i\n";
  }else{
    out<<c.GetMod()<<"exp["<<GetArg()<<"i]\n";
  }
  return out;
}

std::istream& complex::operator>>(std::istream &in, complex &c){
  bool p=false;
  while true{
      int b=(int)"n";
      char a;
      std::cout<<"Polar form? [y/n]: ";
      std::cin>>a;
      b=(int)a;
      if(b==(int)"n" || b==(int)"N"){
        std::cout<<"Real part: ";
        in>>c.z[0];
        std::cout<<"Imaginary part: ";
        in>>c.z[1];
        zp[0]=c.CalMod();
        zp[1]=c.CalArg();
        return in;
      }else if(b==(int)"y" || b==(int)"Y"){
        std::cout<<"Module: ";
        in>>c.zp[0];
        std::cout<<"Argument: ";
        in>>c.zp[1];
        zp[0]=c.CalMod();
        zp[1]=c.CalArg();
        return in;               
      }else{
        stc::cout<<"introduce a valid key\n";
      }
    }     
}

void complex::Conjugate(void){
  if(!(this->GetPol())){
    this->z[1]=-this->z[1];
  }else{
    this->zp[1]=-this->zp[1];
  }
}

double complex::GetRe(void){
  return z[0];
}

double complex::GetImg(void){
  return z[1];
}

double complex::GetMod(void){
  return zp[0];
}

double complex::GetArg(void){
  return zp[1];
}

double complex::CalRe(void);{
  return zp[0]*std::cos(zp[1]);
}

double complex::CalImg(void){
  return zp[0]*std::sin(zp[1]);
}

double complex::CalMod(void){
  return std::pow(zp[0]*zp[0]+zp[1]*zp[1],0.5);
}

double complex::CalArg(void){
  double x,y;
  x=this->GetRe();
  y=this->GetImg();
  if(x>0){
    return std::atan(y/x);
  }else if(x<0 && y>0){
    return Pi+std::atan(y/x);
  }else if(x<0 && y<0){
    return -Pi+std::atan(y/x);
  }else if(x==0){
    if(y>0){
      return Pi/2;
    }else if(y<0){
      return -Pi/2;
    }else if(y==0){
      return 0;
    }
  }else if(y==0){
    if(x>0){
      return 0;
    }else if(x<0){
      return -Pi;
    }else if(x==0){
      return 0;
    }
  }
}

bool complex::GetPol(void){
  return this->Polar;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//


double Mod(complex z){
  return z.GetMod();
}

double Re(complex z){
  return z.GetRe();
}

double Img(complex z){
  return z.GetImg();
}

double Arg(complex z){
  return z.GetArg();
}

bool polar(complex z){
  return z.GetPol();

}

complex Conj(complex z){
  return z.Conjugate();
}

complex Pow(complex z, double n){
  complex w= complex(std::pow(z.GetMod(),n),n*z.GetArg(),polar=true);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}
