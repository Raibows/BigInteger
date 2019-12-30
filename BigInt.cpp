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
    return this->real_length;
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

BigInt::BigInt(int length) {
    this->value = vector<int>(length+1, 0);
    this->real_length = 0;
    this->sign = 0;
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
    this->value[0] = sign;
    int i = 0;
    while (value > 0) {
        this->value[++i] = (value % 10);
        value /= 10;
    }
    this->real_length = i;
}

string BigInt::to_string() {
    string temp;
    if (this->sign == 1) {
        temp.push_back('-');
    }
    vector<int>::iterator iter = this->value.end() - 1;
    while(*iter == 0) {
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
    if (this->real_length != b.real_length){
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