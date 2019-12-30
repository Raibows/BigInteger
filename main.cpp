#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "BigInt.h"


int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    string value1 = "+1234567891000002132131230";
    string value2 = "8234567891000002132131231";
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


    BigInt x3(-14782131232130);
    printf("hhh %s \n", x3.to_string().c_str());
    printf("%d \n", x3.get_real_length());

    BigInt x4(-96487);
    x1 = x4 + x3;
    printf("%s\n", x1.to_string().c_str());
    x1 = x3 + x4;
    printf("%s\n", x1.to_string().c_str());
    x1 = x4 - x3;
    printf("%s\n", x1.to_string().c_str());
    return 0;
}
