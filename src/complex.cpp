#include "../lib/complex.h"
#include <cmath>
#include <vector>
#include <ostream>
#include <cstdlib>
#include <iostream>

#define Pi (double)std::acos(-1)

complex::complex(){
}

complex::complex(double a, double b, bool polar){
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
  bool md=((int)(t/Pi)%2==0);
  if(md){
    t=std::fmod(t,Pi);
  }else{
    t=std::fmod(t,Pi)-Pi;
  }
  zp[1]=t;
}

void complex::SetZ(double a, double b, bool polar){
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

complex complex::operator+(const complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe() + other.GetRe(),this->GetImg() + other.GetImg());
  z.SetPol(zPol);
  return z;
}

complex complex::operator-(const complex &other){
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
  complex z=complex(this->GetRe()*Scl,this->GetImg()*Scl);
  z.SetPol(zPol);
  return z;
}

complex complex::operator*(const complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe()* other.GetRe()-this->GetImg()* other.GetImg(),this->GetRe()* other.GetImg()+this->GetImg()* other.GetRe());
  z.SetPol(zPol);
  return z;
}

complex complex::operator/(const complex &other){
  bool zPol=false;
  if(this->GetPol() && this->GetPol()){
    zPol=true;
  }
  complex z=complex(this->GetRe()* other.GetRe()+this->GetImg()* other.GetImg(),-this->GetRe()* other.GetImg()+this->GetImg()* other.GetRe());
  z= z.Scalar_Product(1/(other.GetMod()*other.GetMod()));
  z.SetPol(zPol);
  return z;
}

bool complex::operator==(const complex &other){
  if(this->GetRe()==other.GetRe() && this->GetImg()==other.GetImg()){
    return true;
  }else{
    return false;
  }
}

bool complex::operator!=(const complex &other){
  if(this->GetRe()!=other.GetRe() || this->GetImg()!=other.GetImg()){
    return true;
  }else{
    return false;
  }
}

complex complex::operator+=(const complex &other){
  *this=*this+other;
  return *this;
}

complex complex::operator-=(const complex &other){
  *this=*this-other;
  return *this;
}

complex complex::operator*=(const complex &other){
  *this=*this*other;
  return *this;
}

complex complex::operator/=(const complex &other){
  *this=*this/other;
  return *this;
}

void complex::Conjugate(void){
  if(!(this->GetPol())){
    this->z[1]=-this->z[1];
  }else{
    this->zp[1]=-this->zp[1];
  }
}

double complex::GetRe(void) const{
  return z[0];
}

double complex::GetImg(void) const{
  return z[1];
}

double complex::GetMod(void) const{
  return zp[0];
}

double complex::GetArg(void) const{
  return zp[1];
}

double complex::CalRe(void){
  return zp[0]*std::cos(zp[1]);
}

double complex::CalImg(void){
  return zp[0]*std::sin(zp[1]);
}

double complex::CalMod(void){
  return std::pow(z[0]*z[0]+z[1]*z[1],0.5);
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

bool complex::GetPol(void) const{
  return this->Polar;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//


std::ostream& operator<<(std::ostream &out, const complex &c){
  if(!(c.GetPol())){
    out<<c.GetRe()<<" + "<<c.GetImg()<<"i\n";
  }else{
    out<<c.GetMod()<<" * exp["<<c.GetArg()<<"i]\n";
  }
  return out;
}

std::istream& operator>>(std::istream &in, complex &c){
  bool p=false;
  while(true){
      int b=0;
      char a;
      std::cout<<"Polar form? [y/n]: ";
      std::cin>>a;
      b=(int)a;
      if(b==110 || b==78){
        std::cout<<"Real part: ";
        in>>c.z[0];
        std::cout<<"Imaginary part: ";
        in>>c.z[1];
        c.zp[0]=c.CalMod();
        c.zp[1]=c.CalArg();
        c.Polar=p;
        return in;
      }else if(b==121 || b==89){
        std::cout<<"Module: ";
        in>>c.zp[0];
        std::cout<<"Argument: ";
        in>>c.zp[1];
        c.SetArg(c.zp[1]);
        c.z[0]=c.CalRe();
        c.z[1]=c.CalImg();
        c.Polar=! p;
        return in;               
      }else{
        std::cout<<"introduce a valid key\n";
      }
    }     
}

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
  z.Conjugate();
  return z;
}

complex Pow(complex z, double n){
  complex w= complex(std::pow(z.GetMod(),n),n*z.GetArg(),true);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Sin(complex z){
  complex w= complex(std::sin(z.GetRe())*std::cosh(z.GetImg()),std::cos(z.GetRe())*std::sinh(z.GetImg()));
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Cos(complex z){
  complex w= complex(std::cos(z.GetRe())*std::cosh(z.GetImg()),-std::sin(z.GetRe())*std::sinh(z.GetImg()));
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Tan(complex z){
  complex w= Sin(z)/Cos(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }
}

complex Csc(complex z){
  complex w= complex(1,0)/Sin(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Sec(complex z){
  complex w= complex(1,0)/Cos(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Cot(complex z){
  complex w= complex(1,0)/Tan(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }
}

complex Sinh(complex z){
  complex w= complex(std::sinh(z.GetRe())*std::cos(z.GetImg()),std::cosh(z.GetRe())*std::sin(z.GetImg()));
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Cosh(complex z){
  complex w= complex(std::cosh(z.GetRe())*std::cos(z.GetImg()),std::sinh(z.GetRe())*std::sin(z.GetImg()));
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Tanh(complex z){
  complex w= Sinh(z)/Cosh(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }
}

complex Csch(complex z){
  complex w= complex(1,0)/Sinh(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Sech(complex z){
  complex w= complex(1,0)/Cosh(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }  
}

complex Coth(complex z){
  complex w= complex(1,0)/Tanh(z);
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }
}

complex Exp(complex z){
  complex w= complex(std::exp(z.GetRe())*std::cos(z.GetImg()),std::exp(z.GetRe())*std::sin(z.GetImg()));
  if(!(z.GetPol())){
    w.SetPol(false);
    return w;
  }else{
    w.SetPol(true);
    return w;
  }
  }


