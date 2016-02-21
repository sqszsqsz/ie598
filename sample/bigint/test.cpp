/*
 * File:   test.cpp
 * Author: dibyendu
 *
 * Created on February 20, 2011
 */

#include <iostream>
#include "bigint.h"

using namespace std;

int
main(int argc, char** argv) {
    BigInt a("-88"), b(7), c, zero(0);
    c = a * b;
    cout << endl << a << " * " << b << " = " << c << endl;
    c = a % b;
    cout << endl << a << " % " << b << " = " << c << endl;
    string s = "1000";
    c = BigInt::factorial(s);
    cout << endl << s << " !" << " = " << c << endl;
    cout << BigInt::numberOfDigit(c) << endl;
    cout << BigInt::sumOfDigit(c) << endl;
    BigInt d = BigInt::reverseNumber(c);
    cout << d << endl;
    cout << BigInt::sumOfDigit(d) << endl;
}