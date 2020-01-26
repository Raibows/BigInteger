//
// Created by Raibows on 2019/12/30.
//
#include "BigInt.h"

bool BigInt::get_positive_sign() {
    return this->sign == 0 ? true : false;
}

int BigInt::get_real_length() {
    /*
     * not include the sign bit
     */
    int i = this->value.size() - 1;
    int j = 0;
    this->real_length = 0;
    while (this->value[i] == 0 && i > 1) {
        --i;
        ++j;
    }
    this->value.erase(this->value.end() - j, this->value.end());
    while (i > 0) {
        ++this->real_length;
        --i;
    }
    return this->real_length;
}

void BigInt::set_sign(bool positive_sign) {
    this->sign = positive_sign ? 0 : 1;
    this->value[0] = this->sign;
}

void BigInt::set_number(string value, bool positive_sign) {
    this->value = vector<int>(value.size() + 1, 0);
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
    if (value_and_sign[0] == '-') {
        positive = false;
        value_and_sign = value_and_sign.substr(1);
    } else if (value_and_sign[0] == '+') {
        positive = true;
        value_and_sign = value_and_sign.substr(1);
    } else {
        positive = true;
    }
    int i = 0;
    while (i < value_and_sign.size() - 1) {
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
    if (value == 0) {
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
    this->value = vector<int>(length + 1, init_value);
    this->value[0] = this->sign;
    this->real_length = length;
}

string BigInt::to_string() {
    this->get_real_length();
    string temp;
    if (this->sign == 1) {
        temp.push_back('-');
    }
    this->get_real_length();
    for (int i = this->value.size() - 1; i > 0; --i) {
        temp.push_back('0' + this->value[i]);
    }
    return temp;
}

BigInt BigInt::multi_ten(int n) {
    BigInt temp = *this;
    temp.value.insert(temp.value.begin() + 1, n, 0);
    temp.get_real_length();
    return temp;
}

bool BigInt::greater(BigInt& b) {
    if (this->sign != b.sign) {
        return this->sign == 0 ? true : false;
    }
    if (this->get_real_length() != b.get_real_length()) {
        return this->real_length > b.real_length;
    }
    vector<int>::iterator iter1 = this->value.end() - 1;
    vector<int>::iterator iter2 = b.value.end() - 1;
    while (iter1 > this->value.begin() && iter2 > b.value.begin()) {
        if (*iter1 != *iter2) {
            return *iter1 > *iter2;
        }
        --iter1;
        --iter2;
    }
    return false;
}

BigInt BigInt::absolute() {
    BigInt temp = *this;
    temp.set_sign(true);
    return temp;
}

BigInt BigInt::negative() {
    BigInt temp = *this;
    temp.set_sign(!this->get_positive_sign());
    return temp;
}

BigInt BigInt::power(int power) {
    if (power < 0)
    {
        throw runtime_error("ERROR, power function only support >= 0");
    }
    if (power == 0)
    {
        return BigInt(1);
    }
    
    BigInt temp(0);
    if (power > 5 || this->get_real_length() >= 16)
    {
        temp = this->quick_pow(power);
    }
    else
    {
        temp = *this;
        while (--power)
        {
            temp *= *this;
        }
    }
    
    return temp;
}

BigInt BigInt::quick_pow(int power) {
    if (power == 0)
    {
        return BigInt(1);
    }
    BigInt res = quick_pow(power/2);
    if (power%2)
    {
        return res*res*(*this);
    }
    else
    {
        return res*res;
    }
}



BigInt BigInt::add(BigInt& b) {
    BigInt temp(max(this->get_real_length(), b.get_real_length()), 1, true);
    auto iter1 = this->value.begin() + 1;
    auto iter2 = b.value.begin() + 1;
    auto iter = temp.value.begin() + 1;
    int value1 = 0;
    int value2 = 0;
    int carry = 0;
    int sum = 0;
    if (this->get_positive_sign() == b.get_positive_sign()) // the same sign
    {
        temp.set_sign(this->get_positive_sign());
        while (true) {
            if (iter1 == this->value.end() && iter2 == b.value.end() && carry == 0) {
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
            if (iter == temp.value.end()) {
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
            if (*this > absolute_b) {
                a_abs_greater_b = true;
                temp.set_sign(true);
            } else {
                a_abs_greater_b = false;
                temp.set_sign(false);
            }
        } else {
            if (b > absolute_a) {
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
    // return sub of self, if x = 123456, return x[start=1: end=3] = 123
    int real_length = this->get_real_length();
    if (end == -1) {
        end = real_length;
    }
    if (start > real_length || start < 1 || end < start) {
        throw runtime_error("ERROR sub_value start, end is wrong!");
    }
    BigInt temp(end - start + 1, 1, this->get_positive_sign());
    temp.value = vector<int>(this->value.begin() + start, this->value.begin() + end + 1);
    temp.value.insert(temp.value.begin(), 0);
    temp.set_sign(true);
    temp.get_real_length();
    return temp;
}

BigInt BigInt::simple_multiply(BigInt& b) {
    if (*this == 0 || b == 0) {
        return BigInt(0);
    }
    int len_a = this->get_real_length();
    int len_b = b.get_real_length();
    vector<int> temp(len_a + len_b, 0);
    bool positive = this->get_positive_sign() == b.get_positive_sign() ? true : false;
    int carry = 0;
    int i, j;
    for (i = 1; i <= len_a; ++i) { // not carry first
        for (j = 1; j <= len_b; ++j) {
            temp[i + j - 1] += this->value[i] * b.value[j];
        }
    }
    i = 1;
    j = 0;
    while (i < (len_a + len_b) || carry != 0) { // calculate carry
        if (i >= temp.size()) {
            temp.push_back(0);
        }
        j = temp[i] + carry;
        temp[i] = j % 10;
        carry = j / 10;
        ++i;
    }
    BigInt ans("0");
    ans.value = temp;
    ans.get_real_length();
    ans.set_sign(positive);
    return ans;
}

BigInt BigInt::karatsuba(BigInt& a, BigInt& b) {
    int len_a = a.get_real_length();
    int len_b = b.get_real_length();
    if (len_a < 500 || len_b < 500 || (len_a - len_b) > 10) {
        return a.simple_multiply(b);
    }
    int half = min(len_a, len_b) / 2;

    BigInt bb = a.sub_value(1, half);
    BigInt aa = a.sub_value(half + 1, -1);
    BigInt dd = b.sub_value(1, half);
    BigInt cc = b.sub_value(half + 1, -1);

    BigInt z2 = this->karatsuba(aa, cc);
    BigInt z0 = this->karatsuba(bb, dd);
    aa = aa + bb;
    cc = cc + dd;
    BigInt z1 = this->karatsuba(aa, cc);
    z1 = z1 - z0 - z2;

    z2.value.insert(z2.value.begin() + 1, 2 * half, 0);
    z1.value.insert(z1.value.begin() + 1, half, 0);

    return z2 + z1 + z0;
    ;
}

BigInt BigInt::multiply(BigInt& b) {
    if (*this == 0 || b == 0) {
        return BigInt(0);
    }
    BigInt temp = this->karatsuba(*this, b);
    temp.get_real_length();
    temp.set_sign(this->get_positive_sign() == b.get_positive_sign() ? true : false);
    return temp;
}

vector<BigInt> BigInt::div_and_mod(BigInt& b) {
    if (b == 0) {
        throw runtime_error("ERROR zero, 0 could not be the divisor");
    }
    if (this->absolute() < b.absolute()) {
        BigInt temp = *this;
        return vector<BigInt>{BigInt(0), temp};
    }
    if (*this == b) {
        return vector<BigInt>{BigInt(1), BigInt(0)};
    }
    int cost = this->get_real_length();
    if (cost < 20 && false) {
        string aa = this->to_string();
        string bb = b.to_string();
        long long int aint = stoll(aa, nullptr, 10);
        long long int bint = stoll(bb, nullptr, 10);
        return vector<BigInt>{BigInt(aint / bint), BigInt(aint % bint)};
    }
    cost -= b.get_real_length();
    BigInt j(0);
    BigInt one(1);
    BigInt ans(1);
    BigInt divided = this->absolute();
    BigInt divisor = b.absolute();
    BigInt temp(1);
    while (cost >= 0) {
        j = 0;
        while (divided >= (j * divisor).multi_ten(cost)) {
            j = j + one;
        }
        j = j - one;
        temp = j.multi_ten(cost);
        ans = ans + temp;
        divided = divided - divisor * temp;
        cost -= 1;
    }
    ans = ans - one;
    ans.set_sign(this->get_positive_sign() == b.get_positive_sign() ? true : false);
    divided.set_sign(this->get_positive_sign());
    return vector<BigInt>{ans, divided};
}

void BigInt::operator=(BigInt b) {
    bool positive = b.sign == 0 ? true : false;
    string value = b.to_string();
    if (positive == false) {
        value = value.substr(1);
    }
    this->set_number(value, positive);
}

bool BigInt::operator==(BigInt& b) {
    return (this->to_string() == b.to_string());
}
bool BigInt::operator==(BigInt&& b) {
    return *this == b;
    return (this->to_string() == b.to_string());
}

bool BigInt::operator!=(BigInt& b) {
    return !(this->to_string() == b.to_string());
}
bool BigInt::operator!=(BigInt&& b) {
    return !(this->to_string() == b.to_string());
}

bool BigInt::operator>=(BigInt& b) {
    return !(*this < b);
}
bool BigInt::operator>=(BigInt&& b) {
    return !(*this < b);
}

bool BigInt::operator>(BigInt& b) {
    return this->greater(b);
}
bool BigInt::operator>(BigInt&& b) {
    return this->greater(b);
}

bool BigInt::operator<=(BigInt& b) {
    return !(*this > b);
}
bool BigInt::operator<=(BigInt&& b) {
    return !(*this > b);
}

bool BigInt::operator<(BigInt& b) {
    if (this->to_string() == b.to_string()) {
        return false;
    }
    return !this->greater(b);
}
bool BigInt::operator<(BigInt&& b) {
    if (this->to_string() == b.to_string()) {
        return false;
    }
    return !this->greater(b);
}

BigInt BigInt::operator+(BigInt& b) {
    return this->add(b);
}

BigInt BigInt::operator+(BigInt&& b) {
    return this->add(b);
}

BigInt BigInt::operator-(BigInt& b) {
    BigInt temp = b;
    temp.set_sign(!b.get_positive_sign());
    return this->add(temp);
}

BigInt BigInt::operator-(BigInt&& b) {
    BigInt temp = b;
    temp.set_sign(!b.get_positive_sign());
    return this->add(temp);
}

BigInt BigInt::operator*(BigInt& b) {
    //    return this->simple_multiply(b);
    return this->multiply(b);
}

BigInt BigInt::operator*(BigInt&& b) {
    //    return this->simple_multiply(b);
    return this->multiply(b);
}

BigInt BigInt::operator/(BigInt& b) {
    return this->div_and_mod(b)[0];
}

BigInt BigInt::operator/(BigInt&& b) {
    return this->div_and_mod(b)[0];
}

BigInt BigInt::operator%(BigInt& b) {
    return this->div_and_mod(b)[1];
}

BigInt BigInt::operator%(BigInt&& b) {
    return this->div_and_mod(b)[1];
}

BigInt& BigInt::operator++() {
    *this = *this + 1;
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt before = *this;
    *this = *this + 1;
    return before;
}

BigInt& BigInt::operator--() {
    *this = *this - 1;
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt before = *this;
    *this = *this - 1;
    return before;
}

BigInt& BigInt::operator+=(BigInt& b) {
    *this = *this + b;
    return *this;
}

BigInt& BigInt::operator+=(BigInt&& b) {
    *this = *this + b;
    return *this;
}

BigInt& BigInt::operator-=(BigInt& b) {
    *this = *this - b;
    return *this;
}

BigInt& BigInt::operator-=(BigInt&& b) {
    *this = *this - b;
    return *this;
}

BigInt& BigInt::operator*=(BigInt& b) {
    *this = *this * b;
    return *this;
}

BigInt& BigInt::operator*=(BigInt&& b) {
    *this = *this * b;
    return *this;
}

BigInt& BigInt::operator/=(BigInt& b) {
    *this = *this / b;
    return *this;
}

BigInt& BigInt::operator/=(BigInt&& b) {
    *this = *this / b;
    return *this;
}

BigInt& BigInt::operator%=(BigInt& b) {
    *this = *this % b;
    return *this;
}

BigInt& BigInt::operator%=(BigInt&& b) {
    *this = *this % b;
    return *this;
}

std::ostream& operator<<(std::ostream& os, BigInt& x) {
    os << x.to_string();
    return os;
}

std::ostream& operator<<(std::ostream& os, BigInt&& x) {
    os << x.to_string();
    return os;
}
