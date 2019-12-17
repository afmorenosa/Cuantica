#include <cmath>
#include <vector>

class complex{

 public:

  complex();
  
  complex(int a,int b);

  void SetImg(double b);

  void SetRe(double a);

  void SetMod(double r);

  void SetArg(double t);
  
  void SetC(double a, double b, bool polar=false);

  complex operator+(complex other);

  complex operator-(complex other);

  complex operator*(complex other);

  complex operator/(complex other);

  complex operator==(complex other);

  complex operator<(complex other);

  complex operator>(complex other);

  complex operator!=(complex other);

  complex operator+=(complex other);

  complex operator-=(complex other);

  complex operator*=(complex other);

  complex operator/=(complex other);

  complex operator<<(complex other);

  complex operator>>(complex other);

  double GetRe(void);

  double GetImg(void);

  double GetMod(void);

  double GetArg(void);

  bool GetPolar(void);
  
 private:

  std::vector<double> z(2);

  std::vector<double> zp(2);

  bool polar=false;
  
};

double Mod(complex z);

double Re(complex z);

double Img(complex z);

double Arg(complex z);

bool polar(complex z);

complex Conj(complex z);

complex Pow(complex z);
