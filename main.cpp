#include <iostream>
#include <string>
#include "BigInt.h"
#include <fstream>
#include <sstream>
#include <time.h>


struct data{
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
    vector<data> testdata(num);
    int i = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        vector<string> temp;
        while (getline(ss, single, ',')) {
            temp.push_back(single);
        }
        testdata[i++].setdata(temp[0], temp[1], temp[2]);
    }
    inFile.close();
    i = 0;
    clock_t t1 = clock();

    for (; i < num; ++i) {
        BigInt x(testdata[i].x);
        BigInt y(testdata[i].y);
        if (x*y != testdata[i].ans) {
            cout << i << "error" << endl;
            break;
        }
        cout << "yes" << i << endl;
    }





    cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC  << "秒" <<endl;
    return 0;
}