#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include "BigInt.h"

// Default constructor
BigInt::BigInt() {}

// Constructor for set myDigits
BigInt::BigInt(const string & s)
{
    myDigits = s;
}

// cout overloading
ostream & operator << (ostream & out, const BigInt & big)
{
    out << big.getDigits();
    return out;
}

// cin overloading
istream & operator >> (istream & in, BigInt & big)
{
    string s;
    in >> s;
    big = BigInt(s);
    return in;
}

// myDigits getter
string BigInt::getDigits() const
{
    return myDigits;
}

// Find smaller str between two string
bool isSmaller(string str1, string str2)
{
    // Calculate lengths of both string
    int n1 = (int) str1.length(), n2 = (int) str2.length();
    
    if (n1 < n2)
        return true;
    if (n2 > n1)
        return false;
    
    for (int i=0; i<n1; i++)
    {
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
    }
    return false;
}

// + operation
BigInt operator +(const BigInt & lhs, const BigInt & rhs)
{
    string str1 = lhs.getDigits();
    string str2 = rhs.getDigits();
    
    if (str1.length() > str2.length())
        swap(str1, str2);
    
    // Take an empty string for storing result
    string str = "";
    
    // Calculate lenght of both string
    int n1 = (int) str1.length(), n2 = (int) str2.length();
    int diff = n2 - n1;
    
    // Initialy carry take zero
    int carry = 0;
    
    // Traverse from end of both strings
    for (int i=n1-1; i>=0; i--)
    {
        // compute sum of current digits and carry
        int sum = ((str1[i]-'0') +
                   (str2[i+diff]-'0') +
                   carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    
    // Add remaining digits of str2[]
    for (int i=n2-n1-1; i>=0; i--)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    
    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');
    
    // reverse resultant string
    reverse(str.begin(), str.end());
    
    return str;
}

// - operation
BigInt operator -(const BigInt & lhs, const BigInt & rhs)
{
    string str1 = lhs.getDigits();
    string str2 = rhs.getDigits();
    
    // Before proceeding further, make sure str1
    // is not smaller
    if (isSmaller(str1, str2))
        swap(str1, str2);
    
    // Take an empty string for storing result
    string str = "";
    
    // Calculate lengths of both string
    int n1 = (int) str1.length(), n2 = (int) str2.length();
    int diff = n1 - n2;
    
    // Initially take carry zero
    int carry = 0;
    
    // Traverse from end of both strings
    for (int i=n2-1; i>=0; i--)
    {
        // compute difference of current digits and carry
        int sub = ((str1[i+diff]-'0') -
                   (str2[i]-'0') -
                   carry);
        if (sub < 0)
        {
            sub = sub+10;
            carry = 1;
        }
        else
            carry = 0;
        
        str.push_back(sub + '0');
    }
    
    // subtract remaining digits of str1[]
    for (int i=n1-n2-1; i>=0; i--)
    {
        if (str1[i]=='0' && carry)
        {
            str.push_back('9');
            continue;
        }
        int sub = ((str1[i]-'0') - carry);
        if (i>0 || sub>0) // remove preceding 0's
            str.push_back(sub+'0');
        carry = 0;
        
    }
    
    // reverse resultant string
    reverse(str.begin(), str.end());
    
    return str;
}

// * operation
BigInt operator *(const BigInt & lhs, const BigInt & rhs)
{
    string str1 = lhs.getDigits();
    string str2 = rhs.getDigits();
    string zero = "0";
    
    int n1 = str1.size();
    int n2 = str2.size();
    if (n1 == 0 || n2 == 0)
    {
        return zero;
    }
    
    // will keep the result number in vector
    // in reverse order
    vector<int> result(n1 + n2, 0);
    
    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;
    
    // Go from right to left in num1
    for (int i=n1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = str1[i] - '0';
        
        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;
        
        // Go from right to left in num2
        for (int j=n2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = str2[j] - '0';
            
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            
            // Carry for next iteration
            carry = sum/10;
            
            // Store result
            result[i_n1 + i_n2] = sum % 10;
            
            i_n2++;
        }
        
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
    
    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
        i--;
    
    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
    {
        return zero;
    }
    
    // generate the result string
    string s = "";
    while (i >= 0)
        s += to_string(result[i--]);
    
    return s;
}

BigInt operator /(const BigInt & lhs, const BigInt & rhs)
{
    string number = lhs.getDigits();
    string str2 = rhs.getDigits();
    string zero = "0";
    
    int divisor = stoi(str2);
    
    // As result can be very large store it in string
    string ans;
    
    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');
    
    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx)
    {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';
        
        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
    
    // If divisor is greater than number
    if (ans.length() == 0)
    {
        return zero;
    }
    
    // else return ans
    return ans;
}
