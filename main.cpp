#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

#define max_length 256


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

bool BigInt::get_positive_sign() {
    return this->sign == 0 ? true : false;
}

int BigInt::get_real_length() {
    return this->real_length;
}


void BigInt::set_number(string value, bool positive_sign) {
    this->value = vector<int>(value.size(), 0);
    this->sign = positive_sign ? 0 : 1;
    this->value[0] = sign;
    int i = 0;
    for (string::iterator iter = value.end()-1; iter != value.begin()-1; --iter) {
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
    vector<int>::iterator iter = this->value.end();
    while(*iter == 0) {
        ++iter;
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
    return this->to_string() == b.to_string();
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
    }
    return false;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    string value = "+1234567891000002132131230";
    BigInt x(value);
    cout << value.size() << endl;
    cout << x.to_string() << endl;
    cout << x.get_positive_sign() << endl << x.get_real_length() <<endl;
    return 0;
}
