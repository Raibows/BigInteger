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
public:
    BigInt(int length);
    BigInt(string value, bool positive_sign);
    BigInt(long long int value);
    string to_string();
};

BigInt::BigInt(int length) {
    this->value = vector<int>(length, 0);
    this->real_length = 0;
    this->sign = 0;
}

BigInt::BigInt(string value, bool positive_sign) {
    this->value = vector<int>(value.size(), 0);
    this->real_length = value.size();
    this->sign = positive_sign ? 0 : 1;
    this->value[0] = sign;
    int i = 0;
    for (string::iterator iter = value.end()-1; iter != value.begin()-1; --iter) {
        this->value[++i] = (*iter - '0');
    }
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

int main(int argc, char *argv[]) {
    string value = "1234567891000002132131230";
    BigInt x(value, false);
    cout << "hello" << endl;
    cout << x.to_string() << endl;
    return 0;
}
