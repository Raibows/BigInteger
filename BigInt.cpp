//
// Created by Raibows on 2019/12/30.
//
#include "BigInt.h"
#include <iostream>
#include <algorithm>
#include <math.h>

bool BigInt::get_positive_sign() {
    return this->sign == 0 ? true : false;
}

int BigInt::get_real_length() {
    /*
     * not include the sign bit
     */
    vector<int>::iterator iter = this->value.end() - 1;
    this->real_length = 0;
    while (*iter == 0 && iter != this->value.begin() + 1) {
        this->value.erase(iter);
        --iter;
    }
    while (iter != this->value.begin()) {
        ++this->real_length;
        --iter;
    }
    return this->real_length;
}

void BigInt::set_sign(bool positive_sign) {
    this->sign = positive_sign ? 0 : 1;
    this->value[0] = this->sign;
}

void BigInt::set_number(string value, bool positive_sign) {
    this->value = vector<int>(value.size()+1, 0);
    this->sign = positive_sign ? 0 : 1;
    this->value[0] = sign;
    int i = 0;
	int j = value.size() - 1;
    for (; j >= 0; --j) {
        this->value[++i] = (value[j] - '0');
    }
    this->real_length = i;
}


BigInt::BigInt(string value_and_sign) {
    bool positive;
    if (value_and_sign[0] == '-')
    {
        positive = false;
        value_and_sign = value_and_sign.substr(1);
    } else if (value_and_sign[0] == '+') {
        positive = true;
        value_and_sign = value_and_sign.substr(1);
    } else {
        positive = true;
    }
	int i = 0;
	while (i < value_and_sign.size() - 1)
	{
		if (value_and_sign[i] != '0') {
			break;
		}
		++i;
	}
	value_and_sign = value_and_sign.substr(i);
	if (value_and_sign == "0") {
		positive = true;
	}
//    printf("structor %s \n", value_and_sign.c_str());
    this->set_number(value_and_sign, positive);
}

BigInt::BigInt(long long int value) {
    this->sign = value >= 0 ? 0 : 1;
    this->value = vector<int>(1);
    this->value[0] = this->sign;
    value = abs(value);
    if (value == 0)
    {
        this->value.push_back(0);
    }
    while (value > 0) {
        this->value.push_back(value % 10);
        value /= 10;
    }
    this->real_length = this->value.size() - 1;
}

BigInt::BigInt(int length, int init_value, bool positive_sign) {
    if (init_value <= 0 || init_value > 9) {
        throw runtime_error("ERROR init value must > 0 and < 10!");
    }
    this->sign = positive_sign ? 0 : 1;
    this->value = vector<int>(length+1, init_value);
    this->value[0] = this->sign;
    this->real_length = length;
}

string BigInt::to_string() {
    string temp;
    if (this->sign == 1) {
        temp.push_back('-');
    }
    vector<int>::iterator iter = this->value.end() - 1;
    while(*iter == 0 && iter != this->value.begin() + 1) {
        --iter;
    }
    for (; iter != this->value.begin(); --iter) {
        temp.push_back(('0' + *iter));
    }
    return temp;
}

void BigInt::operator=(BigInt b) {
    bool positive = b.sign == 0 ? true : false;
    string value = b.to_string();
    if (positive == false)
    {
        value = value.substr(1);
    }
    this->set_number(value, positive);
}

bool BigInt::operator==(BigInt b) {
    return (this->to_string() == b.to_string());
}

bool BigInt::operator!=(BigInt b) {
    return !(this->to_string() == b.to_string());
}

bool BigInt::operator>(BigInt b) {
    return this->greater(b);
}

bool BigInt::operator<=(BigInt b) {
    return !(*this > b);
}

bool BigInt::operator<(BigInt b) {
    if (this->to_string() == b.to_string())
    {
        return false;
    }
    return !this->greater(b);
}

bool BigInt::operator>=(BigInt b) {
    return !(*this < b);
}

bool BigInt::greater(BigInt b) {
    if (this->sign != b.sign){
        return this->sign == 0 ? true : false;
    }
    if (this->get_real_length() != b.get_real_length()){
        return this->real_length > b.real_length;
    }
    vector<int>::iterator iter1 = this->value.end()-1;
    vector<int>::iterator iter2 = b.value.end()-1;
    while (iter1 >= this->value.begin() && iter2 >= b.value.begin()){
        if (*iter1 != *iter2)
        {
            return *iter1 > *iter2;
        }
        --iter1;
        --iter2;
    }
    return false;
}

BigInt BigInt::absolute() {
    BigInt temp = *this;
    bool sign = true;
    temp.set_sign(sign);
    return temp;
}

BigInt BigInt::add(BigInt b) {
    BigInt temp(max(this->get_real_length(), b.get_real_length()), 1, true);
    vector<int>::iterator iter1 = this->value.begin() + 1;
    vector<int>::iterator iter2 = b.value.begin() + 1;
    vector<int>::iterator iter = temp.value.begin() + 1;
    int value1 = 0;
    int value2 = 0;
    int carry = 0;
    int sum = 0;
    if (this->get_positive_sign() == b.get_positive_sign()) //the same sign
    {
        temp.set_sign(this->get_positive_sign());
        while (true) {
            if (iter1 == this->value.end() && iter2 == b.value.end() && carry == 0)
            {
                break;
            }
            if (iter1 != this->value.end()) {
                value1 = *iter1;
                ++iter1;
            } else {
                value1 = 0;
            }
            if (iter2 != b.value.end()) {
                value2 = *iter2;
                ++iter2;
            } else {
                value2 = 0;
            }
            sum = carry + value1 + value2;
            carry = sum / 10;
            if (iter == temp.value.end())
            {
                temp.value.push_back(sum % 10);
            } else {
                *iter = sum % 10;
                ++iter;
            }
        }
    } else { // not the same sign
        BigInt absolute_a = this->absolute();
        BigInt absolute_b = b.absolute();
        bool a_abs_greater_b = false;
        if (absolute_a == absolute_b) {
            return BigInt(0);
        }
        if (this->get_positive_sign()) {
            if (*this > absolute_b)
            {
                a_abs_greater_b = true;
                temp.set_sign(true);
            } else {
                a_abs_greater_b = false;
                temp.set_sign(false);
            }
        } else {
            if (b > absolute_a){
                a_abs_greater_b = false;
                temp.set_sign(true);
            } else {
                a_abs_greater_b = true;
                temp.set_sign(false);
            }
        }
        if (a_abs_greater_b) { // abs(a) > abs(b)
            while (true) {
                if (iter1 == this->value.end() && iter2 == b.value.end()) {
                    break;
                }
                if (iter1 != this->value.end()){
                    value1 = *iter1;
                    ++iter1;
                } else {
                    value1 = 0;
                }
                if (iter2 != b.value.end()) {
                    value2 = *iter2;
                    ++iter2;
                } else {
                    value2 = 0;
                }
                sum = carry + value1 - value2;
                carry = 0;
                if (sum < 0) {
                    sum = 10 + sum;
                    carry = -1;
                }
                if (iter != temp.value.end()) {
                    *iter = sum;
                    ++iter;
                } else {
                    temp.value.push_back(sum);
                }
            }
        } else { // abs_a < abs_b
            while (true) {
                if (iter1 == this->value.end() && iter2 == b.value.end()) {
                    break;
                }
                if (iter1 != this->value.end()){
                    value1 = *iter1;
                    ++iter1;
                } else {
                    value1 = 0;
                }
                if (iter2 != b.value.end()) {
                    value2 = *iter2;
                    ++iter2;
                } else {
                    value2 = 0;
                }
                sum = carry - value1 + value2;
                carry = 0;
                if (sum < 0) {
                    sum = 10 + sum;
                    carry = -1;
                }
                if (iter != temp.value.end()) {
                    *iter = sum;
                    ++iter;
                } else {
                    temp.value.push_back(sum);
                }
            }
        }
    }
    temp.get_real_length();
    return temp;
}

BigInt BigInt::sub_value(int start, int end) {
    //return sub of self, if x = 123456, return x[start=1: end=3) = 12
    int real_length = this->get_real_length();
    if (end == -1) {
        end = real_length;
    }
	if (start > real_length || start < 1 || end < 1 || end > real_length) {
	    throw runtime_error("ERROR sub_value start, end is wrong!");
	}
    BigInt temp(end - start, 1, this->get_positive_sign());
	int i = 1;
	while (start != end) {
	    temp.value[i] = this->value[start];
	    ++start;
	    ++i;
	}
    return temp;
}

BigInt BigInt::get_zero() {
    int i = 0;
    this->get_real_length();
    BigInt temp = *this;
    temp.set_sign(true);
    for (; i < temp.value.size(); ++i) {
        temp.value[i] = 0;
    }
    return temp;
}

BigInt BigInt::karatsuba(BigInt a, BigInt b) {
    if (a < 10 || b < 10) {
        return a * b;
    }
    int len_a = a.get_real_length();
    int len_b = b.get_real_length();
    int half = max(len_a, len_b) / 2;
    BigInt aa = a.sub_value(1, len_a-half);
    BigInt bb = a.sub_value(len_a-half, -1);
    BigInt cc = b.sub_value(1, len_b-half);
    BigInt dd = b.sub_value(len_b-half, -1);

    BigInt z2 = this->karatsuba(aa, cc);
    BigInt z0 = this->karatsuba(bb, dd);
    BigInt z1 = this->karatsuba((aa+bb), (cc+dd)) - z0 - z2;

    return z2 * pow(10, 2*half) + z1 * pow(10, half) + z0;
}

BigInt BigInt::multiply(BigInt b) {
    return this->karatsuba(*this, b);
}

BigInt BigInt::operator+(BigInt b) {
    return this->add(b);
}

BigInt BigInt::operator-(BigInt b) {
    BigInt temp = b;
    temp.set_sign(!b.get_positive_sign());
    return this->add(temp);
}

BigInt BigInt::operator*(BigInt b) {
    if (*this == 0 || b == 0) {
        return BigInt(0);
    }
    int len_a = this->get_real_length();
    int len_b = b.get_real_length();
    vector<int> temp (len_a+len_b, 0);
    bool positive = this->get_positive_sign() == b.get_positive_sign() ? this->get_positive_sign() : false;
    int carry = 0;
    int i, j;
    for (i=1; i<= len_a; ++i) { //not carry first
        for (j=1; j<=len_b; ++j) {
            temp[i+j-1] += this->value[i] * b.value[j];
        }
    }
    i = 1;
    j = 0;
    while (i < (len_a+len_b) || carry != 0) { // calculate carry
        if (i >= temp.size()) {
            temp.push_back(0);
        }
        j = temp[i] + carry;
        temp[i] = j % 10;
        carry = j / 10;
        ++i;
    }
    BigInt ans("0");
    ans.set_sign(positive);
    ans.value = temp;
    ans.get_real_length();
    return ans;
}

