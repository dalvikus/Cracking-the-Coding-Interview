/**
8.3 Write a method that returns all subsets of a set.

8.4 Write a method to compute all permutations of a string.

8.5 Implement an algorithm to print all valid (e.g., properly opened and closed) combinations of n-paris of parentheses.

    EXAMPLE:
    input: 3 (e.g., 3 pairs of parentheses)
    output: ()()(), ()(()), (())(), ((()))

    typo: (()()) must be added!

8.6 Given an infinite number of quaters(25 cents), dimes(10 cents), nickets(5 cents) and pennies(1 cent), write code to calculate the number of ways of representing n cents.
 */

#include <set>
#include <iostream>
#include <vector>
using namespace std;
#include <stdlib.h> // strtol

#if 1   // 8.3
void print_set(const set<int>& s)
{
    cout << "{";
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
        cout << *it << ", ";
    cout << "}" << endl;
}
void subset(const set<int>& from, set<int>& to, vector<set<int> >& subsets)
{
    if (from.begin() == from.end()) {
        subsets.push_back(to);
        return;
    }
    set<int> s0(from);
    set<int>::iterator it = s0.begin();
    int i = *it;
    s0.erase(it);
    set<int> t1(to);
    subset(s0, t1, subsets);
    to.insert(i);
    set<int> t2(to);
    subset(s0, t2, subsets);
}
int ex8_3(int argc, const char *argv[])
{
    if (argc == 1) {
        cerr << "Ex. 8.3: " << argv[0] << " i1 i2 ..." << endl;
        return 1;
    }
    set<int> s0;
    for (int i = 1; i < argc; ++i) {
        char *endptr;
        long ln = strtol(argv[i], &endptr, 10);
        if (*endptr)
            cerr << "WARN: |" << argv[i] << "|: all not used" << endl;
        s0.insert(ln);
    }
    vector<set<int> >   subsets;
    set<int> s1;    // each subset
    subset(s0, s1, subsets);

    cout << "Set:" << endl;
    print_set(s0);
    cout << "# of subsets = " << subsets.size() << endl;
    for (vector<set<int> >::iterator it = subsets.begin(); it != subsets.end(); ++it)
        print_set(*it);

    return 0;
}
#endif  // 8.3

#if 1   // 8.5
void parenthesis(unsigned open, unsigned close, string s, vector<string>& ss)
{
    if (open == 0 && close == 0) {
        ss.push_back(s);
        return;
    }
    if (open > 0) {
        string s1(s);
        s1 += "(";
        parenthesis(open - 1, close, s1, ss);
    }
    if (close > 0 && close > open) {
        string s1(s);
        s1 += ")";
        parenthesis(open, close - 1, s1, ss);
    }
}

int ex8_5(int argc, const char *argv[])
{
    if (argc == 1) {
        cerr << "Ex. 8.5: " << argv[0] << " n" << endl;
        return 1;
    }
    char *endptr;
    long ln = strtol(argv[1], &endptr, 10);
    if (*endptr)
        cerr << "WARN: |" << argv[1] << "|: all not used" << endl;
    cout << "# of parenthesis = " << ln << endl;
    vector<string> ss;
    string s;
    parenthesis(ln, ln, s, ss);
    cout << "# of ways = " << ss.size() << endl;
    for (vector<string>::iterator it = ss.begin(); it != ss.end(); ++it)
        cout << *it << endl;

    return 0;
}
#endif  // 8.5

#if 1   // 8.7
struct Coin
{
    unsigned m_quarters;
    unsigned m_dimes;
    unsigned m_nickels;
    unsigned m_pennies;
    Coin(unsigned quarters, unsigned dimes, unsigned nickels, unsigned pennies) : m_quarters(quarters), m_dimes(dimes), m_nickels(nickels), m_pennies(pennies) {}
    void print(void)
    {
        cout << "(" << m_quarters << ", " << m_dimes << ", " << m_nickels << ", " << m_pennies << "): " << (25 * m_quarters + 10 * m_dimes + 5 * m_nickels + m_pennies) << endl;
    }
};

void distribute_pennies(unsigned cents, unsigned quarters, unsigned dimes, unsigned nickels, vector<Coin>& ways)
{
    ways.push_back(Coin(quarters, dimes, nickels, cents));
}
void distribute_nickels(unsigned cents, unsigned quarters, unsigned dimes, unsigned nickels, vector<Coin>& ways)
{
    unsigned c = cents;
    unsigned n = nickels;
    while (c >= 5) {
        ++n;
        distribute_pennies(c - 5, quarters, dimes, n, ways);
        c -= 5;
    }
    if (c > 0)
        distribute_pennies(c, quarters, dimes, n, ways);
}
void distribute_dimes(unsigned cents, unsigned quarters, unsigned dimes, unsigned nickels, vector<Coin>& ways)
{
    unsigned c = cents;
    unsigned d = dimes;
    while (c >= 10) {
        ++d;
        distribute_nickels(c - 10, quarters, d, nickels, ways);
        c -= 10;
    }
}
void distribute_quarters(unsigned cents, unsigned quarters, unsigned dimes, unsigned nickels, vector<Coin>& ways)
{
    unsigned c = cents;
    unsigned q = quarters;
    while (c >= 25) {
        ++q;
        distribute_dimes(c - 25, q, dimes, nickels, ways);
        c -= 25;
    }
}
int ex8_7(int argc, const char *argv[])
{
    if (argc < 3) {
        cerr << "Ex. 8.7: " << argv[0] << " not_used cents" << endl;
        return 1;
    }
    char *endptr;
    long cents = strtol(argv[2], &endptr, 10);
    if (*endptr)
        cerr << "WARN: |" << argv[2] << "|: all not used" << endl;
    if (cents < 0) {
        cerr << "ERR: cents must be non-negative; " << cents << endl;
        return 1;
    }
    cout << "cents = " << cents << endl;
    vector<Coin>    ways;
    distribute_quarters(cents, 0, 0, 0, ways);
    cout << "# of ways = " << ways.size() << endl;
    for (vector<Coin>::iterator it = ways.begin(); it != ways.end(); ++it)
        it->print();

    return 0;
}
#endif  // 8.7

int main(int argc, const char *argv[])
{
    ex8_3(argc, argv);
    ex8_5(argc, argv);
    ex8_7(argc, argv);

    return 0;
}
