/**
    4.1 Implement a function to check if a tree is balanced. For the purposes of this question, a balanced tree is defined to be a tree such that no two leaf nodes differ in distance from the root by more than one.


int balanced_depth(Node* node)
{
    if (!node)
        return 0;
    int left_depth = balanced_depth(node->left);
    if (left_depth < 0)
        return -1;
    int right_depth = balanced_depth(node->right);
    if (right_depth < 0)
        return -1;
    cout << "left_depth = " << left_depth << "; right_depth = " << right_depth << endl;
    return left_depth == right_depth ? (1 + left_depth) : -1;
}

int main(void)
{
    Node    root;
    int depth = balanced_depth(&root);
    if (depth < 0)
        cout << "unbalanced" << endl;
    else
        cout << "balanced with depth = " << depth << endl;
}


    4.2 Given a directed graph, design an algorithm to find out whether there is a route between two nodes.

    4.3 Given a sorted (increasing order) array, write an algorithm to create a binary tree with minimal height.

    1 2 3 4 5 6 7

        4
        |
    +-------+
    |       |
    2       6
    |       |
  +---+   +---+
  |   |   |   |
  1   3   5   7

    1 2 3 4 5 6

        4
        |
    +-------+
    |       |
    2       6
    |       |
  +---+   +---+
  |   |   |   |
  1   3   5   -


    1 2 3 4 5 6 7 8 9 A B C D E F

                   8
                   |
             +-----------+
             |           |
             4           C
             |           |
          +-----+     +-----+
          |     |     |     |
          2     6     A     E
          |     |     |     |
        +---+ +---+ +---+ +---+
        |   | |   | |   | |   |
        1   3 5   7 9   B D   F

    1 2 3 4 5 6 7 8 9 A B C D E

                   8
                   |
             +-----------+
             |           |
             4           C
             |           |
          +-----+     +-----+
          |     |     |     |
          2     6     A     E
          |     |     |     |
        +---+ +---+ +---+ +---+
        |   | |   | |   | |   |
        1   3 5   7 9   B D   -

    1 2 3 4 5 6 7 8 9 A B C D

                   8
                   |
             +-----------+
             |           |
             4           C
             |           |
          +-----+     +-----+
          |     |     |     |
          2     6     A     E
          |     |     |     |
        +---+ +---+ +---+ +---+
        |   | |   | |   | |   |
        1   3 5   7 9   B -   -

int a[] = {1, 2, 3};
void add_node(Node **node_ptr, int min, int max)
{
cout << "min = " << min << "; max = " << max << endl;
    if (min > max)
        throw "min > max";

    int n = max - min + 1;
    int i = min + (int) ceil(n / 2);
    Node *p = new Node(a[i]);
    p->left = 0;
    p->right = 0;
    assert(*node_ptr == 0);
    *node_ptr = p;
    if (n == 1) {
        cout << "neight left nor right" << endl;
        return;
    }
    if (i - 1 >= min) {
        cout << "left:" << endl;
        add_node(&p->left, min, i - 1);
    } else {
        cout << "no left" << endl;
    }
    if (max >= i + 1) {
        cout << "right:" << endl;
        add_node(&p->right, i + 1, max);
    } else {
        cout << "no right" << endl;
    }
}


    4.4 Given a binary search tree, design an algorithm which creates a linked list of all the nodes at each depth (i.e., if you have a tree with depth D, you'll have D linked list).

    4.5 Write an algorithm to find the 'next' node (i.e., in-order successor) of a given node in a binary search tree where each node has a link to its parent.

    4.6 Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not necessarily a binary search tree.

1. If we are allowed to use additional data structure, we can use two stacks.
Along a parent node, its parent node is pushed onto one stack. For other node, other stack is used.
Remove top node until there is no match; last removed node is the common ancestor.

2. What if it is a binary searach tree?

    1 2 3 4 5 6 7
         4
      2     6
     1 3   5 7

    1 2 2 3 4 4 5
         3
      2     4
     1 2   4 5

         3
      3     3
     3 3   3 3

at each node, left <= parent and right >= parent
Either left > parent or right < parent is not allowed.

    1 2 3 4 5 6 7 8 9 A B C D E F
                   8
                   |
             +-----------+
             |           |
             4           C
             |           |
          +-----+     +-----+
          |     |     |     |
          2     6     A     E
          |     |     |     |
        +---+ +---+ +---+ +---+
        |   | |   | |   | |   |
        1   3 5   7 9   B D   F

2, 7
5, 7
1, 7

Start with smaller node.
Follow ancestor until it is a root node or it is larger node.
Even if a root node is smaller, a root node is a common ancestor.


    4.7 You have two very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.

    4.8 You are given a binary tree in whch each node contains a value. Design an algorithm to print all paths whch sum up to that value. Note that it can be any path in the tree - it does not habve to start at the root.
 */

#include <iostream>
using namespace std;
#include <assert.h> // assert
#include <math.h>   // ceil
#include <stdlib.h> // strtol

struct Node
{
    Node*   parent;
    Node*   left;
    Node*   right;
    int value;
    Node(int val = -1) : parent(0), left(0), right(0), value(val) {}
    ~Node()
    {
        if (left) {
            delete left;
            left = 0;
        }
        if (right) {
            delete right;
            right = 0;
        }
    }
};

int balanced_depth(Node* node)
{
    if (!node)
        return 0;
    int left_depth = balanced_depth(node->left);
    if (left_depth < 0)
        return -1;
    int right_depth = balanced_depth(node->right);
    if (right_depth < 0)
        return -1;
    cout << "left_depth = " << left_depth << "; right_depth = " << right_depth << endl;
    return left_depth == right_depth ? 1 + left_depth : -1;
}

int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
void add_node(Node **node_ptr, int min, int max)
{
cout << "min = " << min << "; max = " << max << endl;
    if (min > max)
        throw "min > max";

    int n = max - min + 1;
    int i = min + (int) ceil(n / 2);
    Node *p = new Node(a[i]);
    assert(*node_ptr == 0);
    *node_ptr = p;
    if (n == 1) {
        cout << "neight left nor right" << endl;
        return;
    }
    if (i - 1 >= min) {
        cout << "left:" << endl;
        add_node(&p->left, min, i - 1);
        if (p->left)
            p->left->parent = p;
    } else {
        cout << "no left" << endl;
    }
    if (max >= i + 1) {
        cout << "right:" << endl;
        add_node(&p->right, i + 1, max);
        if (p->right)
            p->right->parent = p;
    } else {
        cout << "no right" << endl;
    }
}

/**
 * test if node_a is an ancestor of node_b
 *
 *  @param ancestor
 *  @param descendant
 *
 *  @return ancestor if it is; otherwise null
 */
Node *direct_ancestor(Node* ancestor, Node* descendant)
{
    if (!ancestor || !descendant)
        return 0;

    Node* node = descendant;
    do {
        if (node == ancestor)
            break;
        node = node->parent;
    } while (node);

    return node;
}


Node* find_lowest_common_ancestor(Node* node_a, Node* node_b)
{
    if (!node_a || !node_b)
        return 0;

    // test if node_a or all ancestors of it is the ancestor of node_b
    // find the lowest node among ancestors of node_a including node_a itself such that
    // the node is the ancestor of node_b
    Node* node = node_a;
    do {
        Node* ancestor = direct_ancestor(node, node_b);
        if (ancestor) {
            // node is a direct ancestor of node_b
            // so a common ancestor is node->parent
            break;
        }
        node = node->parent;
    } while (node);
    return node ? ((node == node_a || node == node_b) ? node->parent : node) : 0;
}

Node* find_node(Node* root, int n)
{
    Node* node = root;
    while (node) {
        int value = node->value;
        if (value == n)
            break;
        node = n < value ? node->left : node->right;
    }

    return node;
}

void print_node(Node *node)
{
    if (!node)
        return;
    cout << "Node: " << node << " (" << node->value << "): parent = " << node->parent << " (" << (node->parent ? node->parent->value : -1) << ")" << endl;
    cout << "Left:" << endl;
    print_node(node->left);
    cout << "Right: " << endl;
    print_node(node->right);
}

int ex4_6(int argc, const char *argv[])
{
    if (argc != 3) {
        cerr << "Ex. 4.6: " << argv[0] << " value1 value2" << endl;
        return 1;
    }
    char *endptr;
    long val_a = strtol(argv[1], &endptr, 10);
    if (*endptr)
        cerr << "WARN: |" << argv[1] << "|: all not used" << endl;
    long val_b = strtol(argv[2], &endptr, 10);
    if (*endptr)
        cerr << "WARN: |" << argv[2] << "|: all not used" << endl;
    cout << "INFO: val_a = " << val_a << "; val_b = " << val_b << endl;

    Node *root = 0;
    add_node(&root, 0, sizeof(a) / sizeof(int) - 1);
    print_node(root);
    Node* node_a = find_node(root, val_a);
    cout << "node_a: " << node_a << "(" << node_a->value << ")" << endl;
    Node* node_b = find_node(root, val_b);
    cout << "node_b: " << node_b << "(" << node_b->value << ")" << endl;
    Node* node = find_lowest_common_ancestor(node_a, node_b);
    cout << "lowest common ancestor of (" << (node_a ? node_a->value : -1) << ", " << (node_b ? node_b->value : -1) << ") is " << (node ? node->value : -1) << endl;
    if (root)
        delete root;

    return 0;
}

int ex4_3(void)
{
    Node *root = 0;
    add_node(&root, 0, sizeof(a) / sizeof(int) - 1);
    print_node(root);
    if (root)
        delete root;
    return 0;
}

int ex4_1(void)
{
    Node    root;
    int depth = balanced_depth(&root);
    if (depth < 0)
        cout << "unbalanced" << endl;
    else
        cout << "balanced with depth = " << depth << endl;

    return 0;
}

int main(int argc, const char *argv[])
{
    ex4_1();
    ex4_3();
    ex4_6(argc, argv);

    return 0;
}
