#include <complex>
#include <vector>
#include <array>

using std::pair;
using std::vector;
using std::complex;
using std::array;

namespace Equations {

    template <class T>
    pair <bool, vector<complex<T> > > quadratic (array<complex<T>, 3> coef) {
        if (coef[0] == T() && coef[1] == T() && coef[2] == T()) {
            return {false, {}};
        }
        if (coef[1] == T() && coef[2] == T()) {
            return {true, {}};
        }
        vector <complex<T> > x;
        if (coef[2] == T()) {
            x.push_back(-(coef[0] / coef[1]));
            return {true, x};
        }
        const complex<T> DIV = T(1) / (T(2) * coef[2]);
        const T FOUR = T(4);
        const complex <T> D = sqrt (coef[1] * coef[1] - FOUR * coef[0] * coef[2]);
        x.push_back((-coef[1] + D) * DIV);
        x.push_back((-coef[1] - D) * DIV);
        return {true, x};
    }
}
