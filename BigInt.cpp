//
// Created by Raibows on 2019/12/30.
//
#include "BigInt.h"
#include <string>
#include <vector>
#include <iostream>

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
    for (string::iterator iter = value.end()-1; iter >= value.begin(); --iter) {
        this->value[++i] = (*iter - '0');
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
    printf("structor %s \n", value_and_sign.c_str());
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

BigInt BigInt::sub(BigInt b) {

}

BigInt BigInt::operator+(BigInt b) {
    return this->add(b);
}