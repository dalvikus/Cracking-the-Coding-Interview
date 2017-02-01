/**
8.3 Write a method that returns all subsets of a set.

8.4 Write a method to compute all permutations of a string.
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

int main(int argc, const char *argv[])
{
    ex8_3(argc, argv);

    return 0;
}
