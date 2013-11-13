#include <cmath>
#include <cstdio>
#include <iomanip>
#include "ComplexNumber.h"
#include "ComplexNumber_io.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

istream& operator >>(istream &in, ComplexNumber &num) {
    double real, image;
    in >> real >> image;
    num.setValue(real, image);
    return in;
}

ostream& operator <<(ostream &out, const ComplexNumber &num) {
    out << num.real();
    if (fabs(num.image()) > ZMAT_EPS) {
        if (num.image() <= 0.0) {
            out << " - ";
        } else {
            out << " + ";
        }
        out << num.image() << " i";
    }
    return out;
}

ZMAT_END_NAMESPACE
