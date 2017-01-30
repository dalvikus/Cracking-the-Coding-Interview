/**
    9.3 Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm that finds an element in the array. You may assume that the array was originally sorted in increasing order.

    EXAMPLE:
    Input: find 5 in array (15, 16, 19, 20, 25 1 3 4 5 7 10 14)
    Output: 8 (the index of 5 in the array)

Find lowest number in O(log n).
Use binary search on left side or right side depending on given number.
 */

#include <iostream>
using namespace std;

int main(void)
{
    int a[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    int n = sizeof(a) / sizeof(int);
    if (n == 0)
        throw "no element";
    cout << "# of elements = " << n << endl;

    cout << "a[]: {";
    for (int i = 0; i < n; ++i)
        cout << a[i] << ",";
    cout << "}" << endl;
    int b = a[0];
    int min_index = 0;
    int max_index = n - 1;
    int absolute_index;
    while (1) {
        cout << "INFO: min_index = " << min_index << "; max_index = " << max_index << endl;
        int middle_index = (max_index - min_index + 1) / 2; // relative index
/*
        cout << "a[" << min_index << ", " << max_index << "]: {";
        for (int i = min_index; i <= max_index; ++i)
            cout << a[i] << ", ";
        cout << "}" << endl;
 */
        absolute_index = min_index + middle_index;
        if (min_index + 1 == max_index)
            break;
//      cout << b << "; n = " << n << "; a[" << absolute_index << "] = " << a[absolute_index] << endl;
        if (a[absolute_index] > b)
            min_index = absolute_index;
        else
            max_index = absolute_index;
    }
    cout << "a[" << absolute_index << "] = " << a[absolute_index] << endl;

    // search given number in range
    //  [0, absolute_index - 1] if given number > b
    //  [absolute_index, n - 1] if given number < b
    return 0;
}
