#ifndef _BIGINT_H
#define _BIGINT_H

#include <iostream>
#include <string>

using namespace std;

class BigInt
{
    public:
        BigInt();
        BigInt(const string &);
    
        // Getter for myDigits field
        string getDigits() const;    
    private:
        string myDigits;
};

// Overloading I/O
ostream & operator << (ostream &, const BigInt &);
istream & operator >> (istream &, BigInt &);

// Overloading operation between two object
BigInt operator +(const BigInt & lhs, const BigInt & rhs);
BigInt operator -(const BigInt & lhs, const BigInt & rhs);
BigInt operator *(const BigInt & lhs, const BigInt & rhs);
BigInt operator /(const BigInt & lhs, const BigInt & rhs);

#endif // _BIGINT_H not defined
