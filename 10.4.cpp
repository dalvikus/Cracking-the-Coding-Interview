/**
    10.4 Write a method to implement *, -, / operations. You should use only the + operator.

* is the simplest one:
    use + operator as many

    for example, 3 * 5 = 5 + 5 + 5


/ operator:
    use * operator to find x such that given b times x results in a:

        a / b = x

    iteratively solve it: b * x = a
        guess x
        if b * x = 0, stop
        if b * x < a, increase x (by two)
        if b * x > a, decrease x (by half)

        repeat this procedure with new x


- operator:
    1. how to make -a?
        1) use bits; assume ~a operator is available
        for example, a = 000101011
        -a = ?
        we all knows that a + (-a) = 0, which means
            000101011
          + ?????????
            111010101   ~a + 1
          -----------
            000000000

        a + (~a) = -1, so -a = ~a + 1
        2) use -1 as many; assume -1 is available
            not efficient
        3) ???
    or
    2. solve this
        a - b = x
        a = b + x
    if (a == b)
        x = 0
    if (a > b) {
        a = b + x
        iteratively solve it
            guess x (how ?)
            if b + x = a, stop
            if b + x < a, increase x (by two)
            if b + x > a, decreate x (by half)
    }
    if (a < b) {
        ???
    }
 */

#include <iostream>
using namespace std;

int main(void)
{
    int a = 2;
    cout << a << ": " << ~a << endl;

    return 0;
}
