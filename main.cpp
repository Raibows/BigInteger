#include <iostream>
#include <string>
#include "BigInt.h"


int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    string value1 = "+987";
    string value2 = "65";
    BigInt x1 = BigInt(value1);
    BigInt x2 = BigInt(value2);
    BigInt x9 = x1  + x2;
	cout << x9.to_string().c_str() << endl;
	x9 = x9 * BigInt(43+21);
    cout << x9.to_string().c_str() << endl;
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

    BigInt x4("-546454654654666578878");
    x1 = x4 + x3;
    printf("%s\n", x1.to_string().c_str());
    x1 = x3 + x4;
    printf("%s\n", x1.to_string().c_str());
    x1 = x4 - x3;
    printf("%s\n", x1.to_string().c_str());

    x1 = BigInt("-987650");
    x2 = BigInt("4322132132131232354365475688790789781");
    x3 = x1 * x2;
    printf("* is %s\n", x3.to_string().c_str());
    printf("equal %d", x3.to_string() == "-4268753800299411634789062064034223527204650");



    return 0;
}
