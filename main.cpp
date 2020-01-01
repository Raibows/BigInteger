#include <iostream>
#include <string>
#include "BigInt.h"
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>


struct mydata{
    string x;
    string y;
    string ans;
    void setdata(string x, string y, string ans) {
        this->x = x;
        this->y = y;
        this->ans = ans;
    }
};



int main(int argc, char *argv[]) {
    int num = 1000;
    int count = 0;
    int limit = 500;
    int loop = 1;
    vector<float> timer (10);
    ios::sync_with_stdio(false);
    string path = "./testBig.csv";
    ifstream inFile(path, ios::in);
    if (!inFile)
    {
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
        if (testdata[i-1].x.size() < limit || testdata[i-1].y.size() < limit) {
            ++count;
        }
    }
    inFile.close();
    printf("共有%d条大整数乘法数据，其中小于%d长度的数据有%d条，大于%d长度的数据有%d条\n", num, limit, count, limit, num-count);
    i = 0;
    while (loop--) {
        clock_t t1 = clock();
        for (; i < num; ++i) {
            BigInt x(testdata[i].x);
            BigInt y(testdata[i].y);
            BigInt ans = x * y;
            ans = ans / x;
//            if (x*y != BigInt(testdata[i].ans)) {
//                cout << i << "error" << endl;
//                break;
//            }
            if (ans != y) {
                cout << i << "wrong" << endl;
                break;
            }
            cout << "yes" << i << endl;
        }
        timer.push_back((clock() - t1) * 1.0 / CLOCKS_PER_SEC);
    }

    sort(timer.begin(), timer.end());
    float averge = 0;
    for (int i=1; i < loop-1; ++i) {
        averge += (timer[i] / (loop-2));
    }




    cout << loop << "benchmark is" << endl;
    cout << "averge:" << averge << endl;
    cout << "min   :" << timer[0] << endl;
    cout << "max   :" << timer[loop-1] << endl;
    return 0;
}