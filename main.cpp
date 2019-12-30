#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "BigInt.h"


int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    string value1 = "+1234567891000002132131230";
    string value2 = "1234567891000002132131231";
    BigInt x1 = BigInt(value1);
    BigInt x2 = BigInt(value2);
    if (x1 == x2) {
        printf("equal \n");
    }
    if (x1 != x2) {
        printf("not equal \n");
    }
    if (x1 > x2) {
        printf("> \n");
    }
    if (x1 >= x2) {
        printf(">= \n");
    }
    if (x1 < x2) {
        printf("< \n");
    }
    if (x1 <= x2) {
        printf("<= \n");
    }
    cout << x1.to_string() << endl << x2.to_string() << endl;


    vector<int> test{0, 1, 2, 3, 4};
    vector<int>::iterator iter = test.begin() + 1;
    printf("%d begin \n", *iter);
    iter = test.end() - 1;
    printf("%d end \n", *iter);


    return 0;
}
