#ifndef complex_h
#define complex_h
#include <vector>
#include <ostream>

class complex{

 public:

  complex();
  
  complex(double a, double b, bool polar=false);

  void SetPol(bool p);

  void SetImg(double b);

  void SetRe(double a);

  void SetMod(double r);

  void SetArg(double t);
  
  void SetZ(double a, double b, bool polar=false);

  complex operator+(const complex &other);

  complex operator-(const complex &other);

  complex Scalar_Product(double Scl);

  complex operator*(const complex &other);

  complex operator/(const complex &other);
  
  bool operator==(const complex &other);

  bool operator!=(const complex &other);

  complex operator+=(const complex &other);

  complex operator-=(const complex &other);

  complex operator*=(const complex &other);

  complex operator/=(const complex &other);

  void Conjugate(void);

  double GetRe(void) const;

  double GetImg(void) const;

  double GetMod(void) const;

  double GetArg(void) const;

  double CalRe(void);

  double CalImg(void);

  double CalMod(void);

  double CalArg(void);

  bool GetPol(void) const;

  std::vector<double> z=std::vector<double>(2);

  std::vector<double> zp=std::vector<double>(2);

  bool Polar=false;
  
};


std::ostream& operator<<(std::ostream &out, const complex &c);

std::istream& operator>>(std::istream &in, complex &c);

double Mod(complex z);

double Re(complex z);

double Img(complex z);

double Arg(complex z);

bool polar(complex z);

complex Conj(complex z);

complex Pow(complex z);

complex Sin(complex z);

complex Cos(complex z);

complex Tan(complex z);

complex Csc(complex z);

complex Sec(complex z);

complex Cot(complex z);

complex Sinh(complex z);

complex Cosh(complex z);

complex Tanh(complex z);

complex Csch(complex z);

complex Sech(complex z);

complex Coth(complex z);

complex Exp(complex z);

complex Log(complex z);

template <typename fun>
complex PartX(fun f, complex z);

template <typename fun>
complex PartY(fun f, complex z);

template <typename fun>
complex Derivate(fun f, complex z);

#endif
