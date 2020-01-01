//
// Created by Raibows on 2019/12/30.
//

#ifndef BigInteger_BIGINT_H
#define BigInteger_BIGINT_H


#include <vector>
#include <string>
using namespace std;



class BigInt {
    /*
     * real_length recorded the real length of the value, not included the sign bit
     * sign, 0 means positive number, 1 means negative number
     */

    friend std::ostream &operator<< (std::ostream& os, BigInt& x);
    friend std::ostream &operator<< (std::ostream& os, BigInt&& x);
private:
    vector<int> value;
    int real_length;
    int sign;
    void set_number(string value, bool positive_sign);
    bool greater(BigInt& b);
    BigInt add (BigInt& b);
    BigInt sub_value(int start, int end);
    BigInt karatsuba(BigInt& a, BigInt& b);
    BigInt simple_multiply(BigInt& b);
    BigInt multiply (BigInt& b);
    BigInt div(BigInt& b); // this / b
    BigInt multi_ten(int n);
public:
    BigInt(string value_and_sign);
    BigInt(long long int value);
    BigInt(int length, int init_value, bool positive_sign);
    string to_string();
    BigInt absolute();
    void set_sign(bool positive_sign);
    bool get_positive_sign();
    int get_real_length();
    void operator = (BigInt b);
    bool operator == (BigInt& b);
    bool operator == (BigInt&& b);
    bool operator != (BigInt&& b);
    bool operator != (BigInt& b);
    bool operator > (BigInt b);
    bool operator >= (BigInt b);
    bool operator < (BigInt b);
    bool operator <= (BigInt b);
    BigInt operator + (BigInt& b);
    BigInt operator + (BigInt&& b);
    BigInt operator - (BigInt& b);
    BigInt operator - (BigInt&& b);
    BigInt operator * (BigInt& b);
    BigInt operator * (BigInt&& b);
    BigInt operator / (BigInt& b);
};

#endif //TEST_BIGINT_H
