/*
 * File:   bigint.h
 * Author: dibyendu
 *
 * Created on February 19, 2011
 */

#ifndef BIGINT_H
    #define	BIGINT_H

    #include <string>
    #include <iostream>

using namespace std;

class BigInt {
public:
    BigInt();
    BigInt(const BigInt&);
    BigInt(int);
    BigInt(long long);
    BigInt(long);
    BigInt(string);
    virtual ~BigInt();
    BigInt operator +(const BigInt&);
    BigInt operator -(const BigInt&);
    BigInt operator *(const BigInt&);
    BigInt operator /(const BigInt&);
    BigInt operator %(const BigInt&);
    BigInt operator ^(BigInt&);
    void operator +=(const BigInt&);
    void operator -=(const BigInt&);
    void operator *=(const BigInt&);
    void operator /=(const BigInt&);
    void operator %=(const BigInt&);
    BigInt & operator ++();
    BigInt operator ++(int);
    BigInt & operator --();
    BigInt operator --(int);
    void operator =(const BigInt&);
    bool operator ==(const BigInt&);
    bool operator !=(const BigInt&);
    bool operator<(const BigInt&);
    bool operator <=(const BigInt&);
    bool operator>(const BigInt&);
    bool operator >=(const BigInt&);
    friend ostream & operator <<(ostream&, const BigInt&);
    static BigInt factorial(const BigInt&);
    static BigInt mod(const BigInt&);
    static bool isPalindrome(const BigInt&);
    static bool isPrime(const BigInt&);
    static bool isEven(const BigInt&);
    static BigInt reverseNumber(const BigInt&);
    static long sumOfDigit(const BigInt&);
    static int numberOfDigit(const BigInt&);
private:
    char *number;

    enum SIGN {
        negative = -1,
        zero,
        positive
    };
    SIGN sign;
};

#endif        /* BIGINT_H */
