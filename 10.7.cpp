/**
    10.7 Design an algorithm to find the kth number such that the only prime fators are 3, 5, and 7.

    hint: pile up numbers from 3, 5, 7

Update
======
We need only three queues; each is related to 3, 5, and 7.
See below 1. Start with these queues:
    (1, 0, 0)   3
    (0, 1, 0)   5
    (0, 0, 1)   7

Each has only one. The smallest one from first entries of each queue is
    (1, 0, 0) = 3
Next numbers from this are
    (2, 0, 0) = 9
    (1, 1, 0) = 15
    (1, 0, 1) = 17

The first is appended into the first queue, so the first queue looks like
    (2, 0, 0)   9
after removing the first entry: (1, 0, 0).
The second is appended into the second queue, so the second queue looks like
    (0, 1, 0)   5
    (1, 1, 0)   15
The third goes into the third queue:
    (0, 0, 1)   7
    (1, 0, 1)   21

Procedure
After comparing the first entries from each quque, once the smallest number is removed from the corresponing queue, generate next numbers from this number as
    If it comes from the first queue, it generates three numbers:
        3 * n
        5 * n
        7 * n
    The first one is appended into the first queue; the second into the second queue; the third into the third queue.
    If it comes from the second queue, it generates two numbers:
        5 * n
        7 * n
    The first one is appended into the second queu; the second into the third queue.
    If it comes from the third queue, it generates only one number:
        7 * n
    which is appended into third queue.
Claims:
    Claim 1. If it comes from the second queue, it is not necessary to generate 3 * n because it is already generated when the smaller one is removed from the first queue.
    Claim 2. A generated number is appended into a queue, it is the largest one in the queue such that all numbers in a queue are sorted in ascening order.


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
 */

#include <iostream>
#include <deque>
using namespace std;
#include <stdlib.h> // strtol
#include <stdio.h>  // snprintf
#include <assert.h> // assert

enum EntryType
{
    FIRST   = 0,
    SECOND  = 1,
    THIRD   = 2
};

typedef unsigned long num;

struct Repr
{
    Repr(unsigned a, unsigned b, unsigned c, num n, EntryType et) : m_a(a), m_b(b), m_c(c), m_n(n), m_et(et) {
    }

    unsigned m_a;
    unsigned m_b;
    unsigned m_c;
    num m_n;
    EntryType m_et;

    void get_next_numbers(deque<Repr>& reprs)
    {
        reprs.clear();
        switch (m_et) {
        case FIRST:
            if (3 * m_n < m_n)
                throw "overflow";
            reprs.push_back(Repr(m_a + 1, m_b, m_c, 3 * m_n, FIRST));
            if (5 * m_n < m_n)
                throw "overflow";
            reprs.push_back(Repr(m_a, m_b + 1, m_c, 5 * m_n, SECOND));
            if (7 * m_n < m_n)
                throw "overflow";
            reprs.push_back(Repr(m_a, m_b, m_c + 1, 7 * m_n, THIRD));
            break;
        case SECOND:
            if (5 * m_n < m_n)
                throw "overflow";
            reprs.push_back(Repr(m_a, m_b + 1, m_c, 5 * m_n, SECOND));
            if (7 * m_n < m_n)
                throw "overflow";
            reprs.push_back(Repr(m_a, m_b, m_c + 1, 7 * m_n, THIRD));
            break;
        default:    // THIRD
            if (7 * m_n < m_n)
                throw "overflow";
            reprs.push_back(Repr(m_a, m_b, m_c + 1, 7 * m_n, THIRD));
            break;
        }
    }

    string str(void)
    {
        char s[128];
        snprintf(s, 128, "(%u, %u, %u) = %lu [%d]", m_a, m_b, m_c, m_n, m_et);
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

    deque<Repr> repr3_queue;
    deque<Repr> repr5_queue;
    deque<Repr> repr7_queue;
    Repr repr1 = Repr(0, 0, 0, 1, FIRST);
    deque<Repr> reprs;
    repr1.get_next_numbers(reprs);
    for (size_t i = 0; i < reprs.size(); ++i) {
        const Repr& repr = reprs[i];
        switch (repr.m_et) {
        case FIRST:
            repr3_queue.push_back(repr);
            break;
        case SECOND:
            repr5_queue.push_back(repr);
            break;
        case THIRD:
            repr7_queue.push_back(repr);
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < k; ++i) {
        Repr repr3 = repr3_queue.front();
        Repr repr5 = repr5_queue.front();
        Repr repr7 = repr7_queue.front();
        if (repr3.m_n < repr5.m_n && repr3.m_n && repr7.m_n) {
            // repr3
            repr1 = repr3;
            repr3_queue.pop_front();
        } else if (repr5.m_n < repr3.m_n && repr5.m_n < repr7.m_n) {
            // repr5
            repr1 = repr5;
            repr5_queue.pop_front();
        } else {
            // repr7
            repr1 = repr7;
            repr7_queue.pop_front();
        }
        deque<Repr> reprs;
        try {
            repr1.get_next_numbers(reprs);
        } catch (const char *err) {
            cerr << "ERR: " << err << endl;
            break;
        }
        for (size_t j = 0; j < reprs.size(); ++j) {
            const Repr& repr = reprs[j];
            switch (repr.m_et) {
            case FIRST:
                repr3_queue.push_back(repr);
                break;
            case SECOND:
                repr5_queue.push_back(repr);
                break;
            case THIRD:
                repr7_queue.push_back(repr);
                break;
            default:
                break;
            }
        }
        cout << "k[" << (1 + i) << "]: " << repr1.m_n << endl;
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
