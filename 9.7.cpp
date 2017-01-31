/**
    9.7 A circus is designing a tower routine consisting of people standing atop one another's shoulders. For practical and aesthetic reasons, each person must be both shorter and lighter than the person below him or her. Given the heights and weights of each person in the circus, write a method to compute the largest possible number of people in such a tower.
    EXAMPLE:
    Input (ht, wt): (65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 110)
    Output: The longest tower is length 6 and includes from top to bottom:
        (56, 90) (60, 95) (65, 100) (68, 110) (70, 150) (75, 190)

The input is not good for the test.
    add two persions: (50, 100), (80, 50)

    sort by height
        (50, 100) (56, 90) (60, 95) (65, 100) (68, 110) (70, 150) (75, 190) (80, 50)

    Sort array in an ascening order of height and then weight.
        (50, 100) (56, 90) (60, 95) (65, 100) (68, 110) (70, 150) (75, 190) (80, 50)
    Now what is the longest array of weight from
        100, 90, 95, 100, 110, 150, 190, 50

    Equivalent. given array, what is the longest sorted array?
        5 3 4 2 2 5 6 3 3 4 4 7 9

    When a number meets greater number, it can
        1) include the number into the array
        2) exclude the number to get more in the array
    The same applies to the first number.

    1. The first number, 5
        1) we build an array with 5
        2) we skip 5; we start with 3 and do the same as done with 5
    2. Once we decide to include 5, we can proceed to next 5 before 6, when
        1) we include 6
        2) we exclude 6
    and so on.


    Let Xi be indicator variable that says whether i-th number is included or not.
    Let's play with an array:
        5 3 4 2 2 5 6 3 3 4 4 7 9

    For example, we can build an array as
        5         5 6         7 9
    Xi are
        1 0 0 0 0 1 1 0 0 0 0 1 1

    If we build an array as
        5 3 4 2 2 5 6 3 3 4 4 7 9
        5         5           7 9
    Xi are
        1 0 0 0 0 1 0 0 0 0 0 1 1

    Note that it is not necessary to include 6 to buid the longest array.
    If 6 is the last number, we must include it, but it could be shorter.
    It is because the rest could be
        ... 5 6 5 5 5 5 7 9

    So given problem is equivalent to this problem:
        how to make the sum of Xi the largest?

    . Xi depends on Xi-1.
    . There are two possibilities, so in case of n numbers, in general, there are 2^n possibilities; due to a condition below, there are less ones.

    Let Fi be the longest array starting with i-th number. So we are looking for F0.
    Fi can be represented by a tuple as, for instance,
        Fi = (1, 0, ..., 1, 1)
    which says Xi = 1, Xi+1 = 0, ..., Xn-2 = 1, Xn-1 = 1.

    How is Fi related to X's?
    What is (recursive) equations or relations that are satisfied by Fi or Xi?

    Assume we are in i-the step, i.e., we determine Xi.
    Let a be the last element into the array; a might be None.

        a is None
            Xi can be 0 or 1
        a is not None
            Xi = 0  if ai < a
            Xi = 1  if ai = a
            Xi = 0 or 1 if ai > a
 */

#define USE_TABLE   // dynamic programming
//#define DEBUG

#include <iostream>
#ifdef USE_TABLE
#include <vector>
#include <map>
#endif
using namespace std;
#include <stdio.h>  // snprintf

int a[] = {
    5, 3, 4, 2, 2, 5, 6, 3, 3, 4, 4, 7, 9,
    5, 3, 4, 2, 2, 5, 6, 3, 3, 4, 4, 7, 9,
};
#define LEN ((int) ((sizeof(a) / sizeof(int))))
bool X[LEN];    // indicator variable

#ifdef USE_TABLE
struct N
{
#ifdef DEBUG
    unsigned m_counter; /**< how many hits */
#endif
    unsigned m_n;   /**< size of array */
    N() :
#ifdef DEBUG
        m_counter(0),
#endif
        m_n(0)
    {}
    N(unsigned n) :
#ifdef DEBUG
        m_counter(1),
#endif
        m_n(n)
    {}
};

/**
    in case of no last number,
    tells N at given index
 */
vector<N>               table_Fx(LEN, N());
vector<map<int, N> >    table_Fo(LEN, map<int, N>());
#endif
 
unsigned F(int index, int last_a, bool is_last_a_none)
{
    if (index == LEN)
        return 0;

    if (index < 0 || index > LEN)
        throw "out of range";

#ifdef USE_TABLE
    if (is_last_a_none) {
        N& nref = table_Fx[index];
        if (nref.m_n > 0) {
#ifdef DEBUG
            ++nref.m_counter;
#endif
            return nref.m_n;
        }
    } else {
        map<int, N>& m = table_Fo[index];
        map<int, N>::iterator mi = m.find(last_a);
        if (mi != m.end()) {
#ifdef DEBUG
            ++mi->second.m_counter;
#endif
            return mi->second.m_n;
        }
    }
#endif

    unsigned n;
    if (is_last_a_none || a[index] > last_a) {
        unsigned n1 = 1 + F(index + 1, a[index], false);
        unsigned X1[LEN];
        for (int i = 0; i < LEN; ++i)
            X1[i] = X[i];
        unsigned n2 = F(index + 1, last_a, is_last_a_none);
        unsigned X2[LEN];
        for (int i = 0; i < LEN; ++i)
            X2[i] = X[i];
        X[index] = n1 > n2;
        for (int i = index + 1; i < LEN; ++i)
            X[i] = n1 > n2 ? X1[i] : X2[i];
        n = n1 > n2 ? n1 : n2;
    } else {
        if (a[index] < last_a) {
            X[index] = false;
            n = F(index + 1, last_a, false);
        } else if (a[index] == last_a) {
            X[index] = true;
            n = 1 + F(index + 1, last_a /* a[index] */, false);
        }
    }
#ifdef USE_TABLE
    if (is_last_a_none) {
        N& nref = table_Fx[index];
        nref.m_n = n;
#ifdef DEBUB
        nref.m_counter = 1;
#endif
    } else {
        map<int, N>& m = table_Fo[index];
        m[last_a] = N(n);
    }
#endif
    return n;
}

int main(void)
{
    unsigned n = F(0, -1, true);
    cout << "n = " << n << endl;
    for (int i = 0; i < LEN; ++i)
        cout << a[i] << "(" << X[i] << ") ";
    cout << endl;

#ifdef USE_TABLE
#ifdef DEBUG
    cout << "table_Fx:" << endl;
    for (size_t i = 0; i < table_Fx.size(); ++i) {
        const N& nref = table_Fx[i];
        cout << "[" << i << "]: " << nref.m_n << " (" << nref.m_counter << ")" << endl; 
    }
    cout << "table_Fo:" << endl;
    for (size_t i = 0; i < table_Fx.size(); ++i) {
        map<int, N>& m = table_Fo[i];
        cout << "  [" << i << "]" << endl;
        for (map<int, N>::iterator iter = m.begin(); iter != m.end(); ++iter) {
            const N& nref = iter->second;
            cout << "    " << iter->first << ": " << nref.m_n << " (" << nref.m_counter << ")" << endl; 
        }
    }
#endif
#endif

    cout << "n = " << n << endl;
    for (int i = 0; i < LEN; ++i)
        cout << a[i] << " ";
    cout << endl;
    for (int i = 0; i < LEN; ++i) {
        char s[32];
        snprintf(s, 32, "%d", a[i]);
        string str(s);
        string str0(str.size(), ' ');
        if (X[i])
            cout << str << " ";
        else
            cout << str0 << " ";
    }
    cout << endl;
    return 0;
}
