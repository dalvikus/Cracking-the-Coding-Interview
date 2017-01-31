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

    4.4 Given a binary search tree, design an algorithm which creates a linked list of all the nodes at each depth (i.e., if you have a tree with depth D, you'll have D linked list).

    4.5 Write an algorithm to find the 'next' node (i.e., in-order successor) of a given node in a binary search tree where each node has a link to its parent.

    4.6 Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not necessarily a binary search tree.

    4.7 You have two very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.

    4.8 You are given a binary tree in whch each node contains a value. Design an algorithm to print all paths whch sum up to that value. Note that it can be any path in the tree - it does not habve to start at the root.
 */

#include <iostream>
using namespace std;

struct Node
{
    Node*   left;
    Node*   right;
    int value;
    Node(int val = -1) : left(0), right(0), value(val) {}
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

int main(void)
{
    Node    root;
    int depth = balanced_depth(&root);
    if (depth < 0)
        cout << "unbalanced" << endl;
    else
        cout << "balanced with depth = " << depth << endl;
}
