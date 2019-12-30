#include <iostream>
#include <string>
#include "BigInt.h"


int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    string value1 = "+0000000000000000";
    string value2 = "-0000000";
    BigInt x1 = BigInt(value1);
    BigInt x2 = BigInt(value2);
	cout << x1.to_string().c_str() << endl;
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
    x1 = BigInt("-213213213213213219546812312439752745435345213218364");
    x2 = BigInt("+154878464444444468798431233131231234235423516132131235654648");
    x4 = x1 * x2;
    printf("multiply is %s\n", x4.to_string().c_str());
    x3 = x1.multiply(x2);
    printf("multiply is %s\n", x3.to_string().c_str());
    printf("equal or not %d", x3==x4);
    return 0;
}
