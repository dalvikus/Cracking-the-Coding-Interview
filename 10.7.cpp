/**
    10.7 Design an algorithm to find the kth number such that the only prime fators are 3, 5, and 7.

    hint: pile up numbers from 3, 5, 7

(a, b, c) represents 3^a 5^b 7^c; (a, b, c) = 3^a 5^b 7^c

1. start with (0, 0, 0)
all possible next numbers
    (1, 0, 0)   3
    (0, 1, 0)   5
    (0, 0, 1)   7

2. what is next?
among next numbers
    from (0, 0, 0)
        (1, 0, 0)   3[1]
        (0, 1, 0)   5[2]
        (0, 0, 7)   7[3]

smallest one is (1, 0, 0) = 3
delete this entry from list of next numbers, so
    from (0, 0, 0)
        (0, 1, 0)   5[2]
        (0, 0, 1)   7[3]
new list of next numbers, since it comes from the first entry
    from (1, 0, 0)
        (2, 0, 0)   9[1]
        (1, 1, 0)   15[2]
        (1, 0, 1)   21[3]
so we have two lists of next numbers
    from (0, 0, 0)
        (0, 1, 0)   5[2]
        (0, 0, 1)   7[3]
    from (1, 0, 0)
        (2, 0, 0)   9[1]
        (1, 1, 0)   15[2]
        (1, 0, 1)   21[3]

2. what is next?
from two lists of next numbers, smallest one (0, 1, 0) = 5
delete the entry from the list
new list of next numbers from (0, 1, 0), which is the second entry, so (1, 1, 0) is an entry of another list, which comes from (1, 0, 0)
    (0, 2, 0)
    (0, 1, 1)

now we have three list of next numbers
    from (0, 0, 0)
        (0, 0, 1)   7[3]
    from (1, 0, 0)[1]
        (2, 0, 0)   9[1]
        (1, 1, 0)   15[2]
        (1, 0, 1)   21[3]
    from (0, 1, 0)[2]
        (0, 2, 0)   25[2]
        (0, 1, 1)   35[3]

from (1, 1, 0)
    (2, 1, 0)
    (1, 2, 0)
    (1, 1, 1)
from (0, 2, 0)
    (1, 2, 0)   X
    (1, 3, 0)
    (1, 2, 1)
3. what is next?
among three lists of next numbers, the smallest one is (0, 0, 1) = 7; the third entry in the list coming from (0, 0, 0)
delete the entry
new list from (0, 0, 1); (1, 0, 1) and (0, 1, 1) comes from other list; (1, 0, 1) comes from (1, 0, 0) and (0, 1, 1) from (1, 0, 0)
    (0, 0, 2)

now we have three list of next numbers
    from (1, 0, 0)[1]
        (2, 0, 0)   9[1]
        (1, 1, 0)   15[2]
        (1, 0, 1)   21[3]
    from (0, 1, 0)[2]
        (0, 2, 0)   25[2]
        (0, 1, 1)   35[3]
    from (0, 0, 1)[3]
        (0, 0, 2)   49[3]

4. what is next?
among three lists of next numbers, the smallest one is (2, 0, 0) = 9

delete the (first) entry and add new list from (2, 0, 0) for next numbers

now we have
    from (1, 0, 0)[1]
        (1, 1, 0)   15[2]
        (1, 0, 1)   21[3]
    from (0, 1, 0)[2]
        (0, 2, 0)   25[2]
        (0, 1, 1)   35[3]
    from (0, 0, 1)[3]
        (0, 0, 2)   49[3]
    from (2, 0, 0)[1]
        (3, 0, 0)   27[1]
        (2, 1, 0)   45[2]
        (2, 0, 1)   63[3]

5. and so one

at given moment in time, we have a finite list of next numbers where all entries are sorted, so only that amount of comparision is needed to get next number

claim that
1) for an entry coming from i-th entry, it generates a list of next numbers as
    (a, b, c) from i-th entry of (x, y, z)
    1st entry:
        (a + 1, b, c)
        (a, b + 1, c)
        (a, b, c + 1)
    2nd entry:

if (a, b, c) is 1st entry,
    (a + 1, b, c)
    (a, b + 1, c)
    (a, b, c + 1)
if (a, b, c) is 2nd entry
    (a, b + 1, c)
    (a, b, c + 1)
if (a, b, c) is 3rd entry
    (a, b, c + 1)

        what is (x, y, z)?
        2nd entry of (a, b - 1, c)
            (a + 1, b - 1, c)
            (a, b, c)
            (a, b - 1, c + 1)
        2nd entry of (
        no (a + 1, b, c) because (a, b, c) is a
            i) 2nd entry of the 1st entry of (a - 1, b, c)
                (a, b, c)
                (a - 1, b + 1, c)
                (a - 1, b, c + 1)
            2nd entry of the 2nd entry of (a, b - 1, c)
        (a, b + 1, c)
        (a, b, c + 1)
    3rd entry:
        (a, b, c + 1)
 */

#include <iostream>
#include <vector>
using namespace std;
#include <stdlib.h> // strtol
#include <stdio.h>  // snprintf

enum EntryType
{
    FIRST   = 0,
    SECOND  = 1,
    THIRD   = 2
};

struct Repr
{
    Repr(unsigned a, unsigned b, unsigned c, unsigned n, EntryType et) : m_a(a), m_b(b), m_c(c), m_n(n), m_et(et) {
    }

    unsigned m_a;
    unsigned m_b;
    unsigned m_c;
    unsigned m_n;
    EntryType m_et;

    void get_next_numbers(vector<Repr>& reprs)
    {
        reprs.clear();
        switch (m_et) {
        case FIRST:
            reprs.push_back(Repr(m_a + 1, m_b, m_c, 3 * m_n, FIRST));
            reprs.push_back(Repr(m_a, m_b + 1, m_c, 5 * m_n, SECOND));
            reprs.push_back(Repr(m_a, m_b, m_c + 1, 7 * m_n, THIRD));
            break;
        case SECOND:
            reprs.push_back(Repr(m_a, m_b + 1, m_c, 5 * m_n, SECOND));
            reprs.push_back(Repr(m_a, m_b, m_c + 1, 7 * m_n, THIRD));
            break;
        default:    // THIRD
            reprs.push_back(Repr(m_a, m_b, m_c + 1, 7 * m_n, THIRD));
            break;
        }
    }

    string str(void)
    {
        char s[128];
        snprintf(s, 128, "(%u, %u, %u) = %u [%d]", m_a, m_b, m_c, m_n, m_et);
        return string(s);
    }
    void print(void)
    {
        cout << str() << endl;
    }
};

Repr kth(int k)
{
    if (k <= 0)
        throw "k <= 0";

    vector<vector<Repr> > reprs_list;
    Repr repr1 = Repr(0, 0, 0, 1, FIRST);
    vector<Repr> reprs;
    repr1.get_next_numbers(reprs);
/*
    for (vector<Repr>::iterator it = reprs.begin(); it != reprs.end(); ++it) {
        it->print();
    }
 */
    reprs_list.push_back(reprs);
    for (int i = 0; i < k; ++i) {
        size_t smallest_index;
        unsigned smallest = -1;
        for (size_t reprs_index = 0; reprs_index < reprs_list.size(); ++reprs_index) {
            vector<Repr>& reprs = reprs_list[reprs_index];
/*
            cout << "reprs[" << reprs_index << "]:" << endl;
            for (size_t j = 0; j < reprs.size(); ++j) {
                cout << "   repr[" << j << "]: " << reprs[j].str() << endl;
            }
 */
            if (reprs[0].m_n < smallest) {
                smallest = reprs[0].m_n;
                smallest_index = reprs_index;
            }
        }
        cout << "smallest = " << smallest << endl;
//      cout << "smallest_index = " << smallest_index << endl;
        // delete
        vector<Repr>& reprs_deleted = reprs_list[smallest_index];
        Repr    repr = reprs_deleted[0];
        repr1 = repr;
        reprs_deleted.erase(reprs_deleted.begin());
        if (reprs_deleted.size() == 0)
            reprs_list.erase(reprs_list.begin() + smallest_index);
        vector<Repr> reprs;
        repr.get_next_numbers(reprs);
/*
        for (size_t j = 0; j < reprs.size(); ++j)
            reprs[j].print();
 */
        reprs_list.push_back(reprs);
    }
    return repr1;
}

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        cerr << "Q: 10.7 Design an algorithm to find the kth number such that the only prime fators are 3, 5, and 7." << endl;
        cerr << "Usage: " << argv[0] << " k1 k2 ..." << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        char *endptr;
        long k = strtol(argv[i], &endptr, 10);
        if (*endptr)
            cerr << "WARN: |" << argv[i] << "|: all not used" << endl;
        if (k <= 0) {
            cerr << "ERR: |" << argv[i] << "|: must be positive" << endl;
            continue;
        }
        cout << "INFO: k = " << k << endl;
        cout << k << "-th number is " << kth(k).str() << endl;
    }

    return 0;
}
