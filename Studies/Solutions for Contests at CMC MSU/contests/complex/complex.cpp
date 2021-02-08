#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

namespace numbers {
    class complex {
    private:
        double Re = 0.0, Im = 0.0;
    public:
        complex (const double x = 0.0, const double y = 0.0): Re(x), Im(y) {}
        explicit complex (const std::string s)
        {
            unsigned i = 0;
            for (; i < s.length() && s[i] != ','; i++) {}
            Re = stod (s.substr(1, i - 1));
            Im = stod (s.substr(i + 1, s.length() - i - 1));
        }
        const double re () const
        {
            return this->Re;
        }
        const double im () const
        {
            return this->Im;
        }
        const double abs2 () const
        {
            return (Re * Re + Im * Im);
        }
        const double abs () const
        {
            return sqrt(this->abs2());
        }
        const std::string to_string () const {
            char x[40];
            snprintf(x, 38, "(%.10g,%.10g)", Re, Im);
            std::string s(x);
            return s;
        }
        complex &operator+=(const complex& rv) {
            this -> Re += rv.Re;
            this -> Im += rv.Im;
            return (*this);
        }
        complex &operator-=(const complex& rv) {
            this -> Re -= rv.Re;
            this -> Im -= rv.Im;
            return (*this);
        }
        complex &operator*=(const complex& rv) {
            double rea = this -> Re;
            double ima = this -> Im;
            this -> Re = (rea * rv.Re - ima * rv.Im);
            this -> Im = (rv.Re * ima + rea * rv.Im);
            return (*this);
        }
        complex &operator/=(const complex& rv) {
            double rea = this -> Re;
            double ima = this -> Im;
            this -> Re = (rea * rv.Re + ima * rv.Im) / rv.abs2();
            this -> Im = (- rea * rv.Im + rv.Re * ima) / rv.abs2();
            return (*this);
        }
        friend const complex operator-(const complex &a){
            return complex(-a.Re,-a.Im);
        }
        friend const complex operator~(const complex &a){
            return complex(a.Re,-a.Im);
        }
        friend complex operator+(complex a1, const complex& a2) {
            return a1 += a2;
        }
        friend complex operator-(complex a1, const complex& a2) {
            return a1 -= a2;
        }
        friend complex operator*(complex a1, const complex& a2) {
            return a1 *= a2;
        }
        friend complex operator/(complex a1, const complex& a2) {
            return a1 /= a2;
        }
    };
    
    class complex_stack {
    private:
        complex *values;
        size_t maxsize = 0;
        size_t sz = 0;
        complex_stack shorten (size_t newsize) const
        {
            if (newsize) {
                complex_stack cpy(*this);
                cpy.sz = sz - 1;
                return cpy;
            } else {
                complex_stack vain;
                return vain;
            }
        }
        complex_stack largen (size_t newsize) {
            if (newsize >= maxsize) {
                maxsize <<= 1;
                complex * newval = new complex[maxsize];
                for (size_t i = 0; i < sz; i++) {
                    newval[i] = values[i];
                }
                if (values) {
                    delete []values;
                }
                values = newval;
            }
            sz = newsize;
            return (*this);
        }
    public:
        complex_stack (size_t u_sz = 2) {
            maxsize = u_sz ? u_sz : 2;
            sz = 0;
            values = new complex[maxsize];
        }
        complex_stack (const complex_stack &x) {
            sz = x.sz;
            maxsize = x.maxsize;
            values = new complex[maxsize];
            for (size_t i = 0; i < sz; i++) {
                values[i] = x.values[i];
            }
        }
        ~complex_stack () {
            if (values) {
                delete []values;
            }
        }
        const complex_stack operator<<(const complex &a) const{
            complex_stack x (*this);
            x.largen(sz + 1);
            x.values[sz] = a;
            return x;
        }
        const complex operator+() const {
            return values[sz - 1];
        }
        const complex_stack& operator=(const complex_stack& x) {
            maxsize = x.maxsize;
            sz = x.sz;
            if (values) {
                delete []values;
            }
            values = new complex[maxsize];
            for (size_t i = 0; i < sz; i++) {
                values[i] = x.values[i];
            }
            return *this;
        }
        const complex operator[](const size_t i) const {
            return values[i];
        }
        const complex_stack operator~() const {
            return this->shorten(sz - 1);
        }
        size_t size () const {
            return sz;
        }
    };
    
    complex eval(const std::vector<std::string>&args, const complex &z) {
        complex_stack a;
        for (unsigned i = 0; i < args.size(); i++) {
            char x = args[i][0]; 
            switch (x) {
            case '+':
                complex v2 = +a;
                a = ~a;
                complex v1 = +a;
                a = ~a;
                a = a << (v1 + v2);
                break;
            case '-':
                complex v2 = +a;
                a = ~a;
                complex v1 = +a;
                a = ~a;
                a = a << (v1 - v2);
                break;
            case '*':
                complex v2 = +a;
                a = ~a;
                complex v1 = +a;
                a = ~a;
                a = a << (v1 * v2);
                break;
            case '/':
                complex v2 = +a;
                a = ~a;
                complex v1 = +a;
                a = ~a;
                a = a << (v1 / v2);
                break;
            case '!':
                a = a << (+a);
                break;
            case ';':
                a = ~a;
                break;
            case '~':
                complex v1 = +a;
                a = ~a;
                v1 = ~v1;
                a = a << v1;
                break;
            case '#':
                complex v1 = +a;
                a = ~a;
                v1 = -v1;
                a = a << v1;
                break;
            case 'z':
                a = a << z;
                break;
            default:
                complex v1(args[i]);
                a = a << v1;
            }
        }
        return +a;
    }
}

inline numbers::complex z (double k, int N, double R, numbers::complex C) {
    numbers::complex ret(R * cos (2 * M_PI * k / N), R * sin(2 * M_PI * k / N));
    return ret + C;
}

inline numbers::complex growth (int k, long N, double R, numbers::complex C) {
    return z(k + 1, N, R, C) - z(k, N, R, C);
}

numbers::complex add (int k, long N, double R, numbers::complex C, std::vector <std::string> args) {  
    return numbers::eval(args, z(k, N, R, C)) * growth(k, N, R, C);
}

int main (int argc, char *argv[]) 
{
    numbers::complex res;
    numbers::complex C(argv[1]);
    double R = strtod(argv[2], nullptr);
    long N = strtol(argv[3], nullptr, 10);
    std::vector <std::string> args;
    for (int i = 4; i < argc; i++) {
        args.push_back(argv[i]);
    }
    for (int i = 0; i < N; i++) {
        res += add(i, N, R, C, args);
    }
    std::cout<< res.to_string()<< std::endl;
}
