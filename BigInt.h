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
private:
    vector<int> value;
    int real_length;
    int sign;
    void set_number(string value, bool positive_sign);
    bool greater(BigInt b);
public:
    BigInt(int length);
    BigInt(string value_and_sign);
    BigInt(long long int value);
    string to_string();
    BigInt absolute();
    bool get_positive_sign();
    int get_real_length();
    void operator = (BigInt b);
    bool operator == (BigInt b);
    bool operator != (BigInt b);
    bool operator > (BigInt b);
    bool operator >= (BigInt b);
    bool operator < (BigInt b);
    bool operator <= (BigInt b);
};

#endif //TEST_BIGINT_H
