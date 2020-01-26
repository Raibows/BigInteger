//
// Created by Raibows on 2019/12/30.
//

#ifndef BigInteger_BIGINT_H
#define BigInteger_BIGINT_H


#include <algorithm>
#include <iterator>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;


class BigInt {
    /*
     * real_length recorded the real length of the value, not included the sign bit
     * sign, 0 means positive number, 1 means negative number
     */

    friend std::ostream& operator<<(std::ostream& os, BigInt& x);
    friend std::ostream& operator<<(std::ostream& os, BigInt&& x);

  private:
    vector<int> value;
    int real_length;
    int sign;
    void set_number(string value, bool positive_sign);
    bool greater(BigInt& b);
    BigInt add(BigInt& b);
    BigInt sub_value(int start, int end);
    BigInt karatsuba(BigInt& a, BigInt& b);
    BigInt simple_multiply(BigInt& b);
    BigInt multiply(BigInt& b);
    vector<BigInt> div_and_mod(BigInt& b);
    BigInt multi_ten(int n);
    void set_sign(bool positive_sign);
    BigInt quick_pow(int power);

  public:
    BigInt(string value_and_sign);
    BigInt(long long int value);
    BigInt(int length, int init_value, bool positive_sign);
    string to_string();
    BigInt absolute();
    BigInt negative();
    BigInt power(int power);
    bool get_positive_sign();
    int get_real_length();
    void operator=(BigInt b);

    bool operator==(BigInt& b);
    bool operator==(BigInt&& b);

    bool operator!=(BigInt& b);
    bool operator!=(BigInt&& b);

    bool operator>(BigInt& b);
    bool operator>(BigInt&& b);

    bool operator>=(BigInt& b);
    bool operator>=(BigInt&& b);

    bool operator<(BigInt& b);
    bool operator<(BigInt&& b);

    bool operator<=(BigInt& b);
    bool operator<=(BigInt&& b);

    BigInt operator+(BigInt& b);
    BigInt operator+(BigInt&& b);

    BigInt operator-(BigInt& b);
    BigInt operator-(BigInt&& b);

    BigInt operator*(BigInt& b);
    BigInt operator*(BigInt&& b);

    BigInt operator/(BigInt& b);
    BigInt operator/(BigInt&& b);

    BigInt operator%(BigInt& b);
    BigInt operator%(BigInt&& b);

    BigInt& operator++();
    BigInt operator++(int); //postfix


    BigInt& operator--();
    BigInt operator--(int); //postfix

    BigInt& operator+=(BigInt& b);
    BigInt& operator+=(BigInt&& b);

    BigInt& operator-=(BigInt& b);
    BigInt& operator-=(BigInt&& b);

    BigInt& operator*=(BigInt& b);
    BigInt& operator*=(BigInt&& b);

    BigInt& operator/=(BigInt& b);
    BigInt& operator/=(BigInt&& b);

    BigInt& operator%=(BigInt& b);
    BigInt& operator%=(BigInt&& b);
};

#endif // TEST_BIGINT_H
