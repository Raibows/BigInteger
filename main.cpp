#include "BigInt.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <time.h>

struct mydata {
    string x;
    string y;
    string ans;
    void setdata(string x, string y, string ans) {
        this->x = x;
        this->y = y;
        this->ans = ans;
    }
};

int main(int argc, char* argv[]) {

    BigInt x1("14524245501");
    BigInt x2("-11");
    long long int x3 = stoll(x1.to_string());
    long long int x4 = stoll(x2.to_string());
    x1++;
    x3++;
    cout << x1++ << endl;
    cout << x3++ << endl;
    x2 += 4;
    x4 += 4;
    x2 *= 15;
    x4 *= 15;
    cout << x2 << endl;
    cout << x4 << endl;
    x1 /= x2;
    x3 /= x4;
    --x1;
    --x3;
    cout << x1 % x2 << endl;
    cout << x3 % x4 << endl;

    cout << x2.power(3) << endl;
    printf("%f\n", pow(x4, 3));


    int num = 1000;
    int count = 0;
    int limit = 300;
    int loop = 1;
    cin >> loop;
    vector<float> timer;
    ios::sync_with_stdio(false);
    string path = "./testBig.csv";
    ifstream inFile(path, ios::in);
    if (!inFile) {
        cout << "打开文件失败！" << endl;
        exit(1);
    }
    string line;
    string single;
    vector<mydata> testdata(num);
    int i = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        vector<string> temp;
        while (getline(ss, single, ',')) {
            temp.push_back(single);
        }
        testdata[i++].setdata(temp[0], temp[1], temp[2]);
        if (testdata[i - 1].x.size() < limit || testdata[i - 1].y.size() < limit) {
            ++count;
        }
    }
    inFile.close();
    printf("共有%d条大整数乘法数据，其中小于%d长度的数据有%d条，大于%d长度的数据有%d条\n", num, limit, count, limit, num - count);
    i = 0;
    while (loop--) {
        clock_t t1 = clock();
        for (; i < num; ++i) {
            BigInt x(testdata[i].x);
            BigInt y(testdata[i].y);
            BigInt ans = x * y;
            
            if (ans != testdata[i].ans) {
                cout << i << "error" << endl;
                break;
            }
            /*ans = ans / x;
            if (ans != y) {
                cout << i << "wrong" << endl;
                break;
            }*/
            cout << "yes" << i << endl;
        }
        timer.push_back((clock() - t1) * 1.0 / CLOCKS_PER_SEC);
    }

    sort(timer.begin(), timer.end());
    float averge = 0;
    for (int i = 1; i < loop - 1; ++i) {
        averge += (timer[i] / (timer.size() - 2));
    }

    cout << loop << "benchmark is" << endl;
    cout << "averge:" << averge << endl;
    cout << "min   :" << *(timer.begin()) << endl;
    cout << "max   :" << *(timer.end() - 1) << endl;
    return 0;
}