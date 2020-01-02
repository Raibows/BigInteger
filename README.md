## C++ BigInteger
This is a normal implementation of BigInteger for C++, support the operation of much more than 2^64 or 1000 width integer. But please notice that the author@ChiZuo will not take any responsibility for any lost caused by any bugs in this respository. This implementation has a not bad performance in add and sub operations, but low performance in multiply and divide operations between very large numbers compared with BigInteger class in Java11.   

## Environment
Works well in C++11.
<table align=center>
    <thead>
        <tr>
        <td>Compiler</td><td>OS</td><td>Support</td>
        </tr>
    </thead>
    <tbody>
        <tr>
        <td>GCC-Clang 8.1.0</td><td>Windows</td><td>pass</td>
        </tr>
        <tr>
        <td>MSVC-Clang 8.0.1</td><td>Windows</td><td>pass</td>
        </tr>
        <tr>
        <td>MSVC 10.0</td><td>Windows</td><td>pass</td>
        </tr>
    </tbody>
</table>

## Function
Support and Finished:
1. [x] comparison ==, !=, <, <=, >, >=
2. [x] add +, ++, +=
3. [x] sub -, --, -=
4. [x] multiply *, *= (using Karatsuba Algorithm) 
5. [x] divide /, /=
6. [x] mod %, %=
7. [x] power

Unfinished but planned:  
1. support BigDecimal

## QuickStart
1. clone or download this project
2. include the header file (make sure at the same level as your source code file)
    ```
    #include <BigInt.h>
    ```
3. create BigInt object
   - input long long int
        ```
        long long int x = 123456789;
        BigInt temp(x);
        ```
   - input string object
        ```
        string pos_x = "123456789"; //or "+123456789", both means positive number
        BigInt pos_temp(pos_x);
        string neg_x = "-123456789"; //means negative number
        BigInt neg_temp(neg_x);
        ```
4. operation
For example, we want $[(x+1)^2 \times 123 \div y] \mod y$, which $x=-123456789, y=88888888$
    ```
    BigInt x("-123456789");
    BigInt y("88888888");
    ++x;
    x = x.power(2);
    x *= 123;
    x /= y;
    x %= y;
    ```
5. output
   - to string
    ```
    BigInt temp("-123456789");
    string temp_str = temp.to_string();
    ```
   - cout
    ```
    BigInt temp("-123456789");
    cout << temp;
    terminal will show: -123456789
    ```

## Reference
My work referenced:
1. Karatsuba in Wiki https://en.wikipedia.org/wiki/Karatsuba_algorithm (this page in zh has wrong in example codes)
2. An implementation of BigInteger for C++ https://github.com/panks/BigInteger

## License
Under Apache-2.0 license.