/*******************************************************************************
https://practice.geeksforgeeks.org/problems/merge-two-bst-s/1

Given two BST, you need to print the elements of both BSTs in sorted form.

Input Format:
The first line of input contains an integer T denoting the no of test cases. Then T test 
cases follow. Each test case contains three lines. The first line of each test case 
contains an integer N and M denoting the size of the two BST's. Then In the next two line 
are space separated values of the two BST's.

Output Format:
For each testcase, in a new line, print the elements of both BSTs in sorted form.

Your Task:
This is a function problem, you don't have to take any input. Just complete the function 
merge() that nodes of both BSTs as parameters.
*******************************************************************************/

#include <fstream>
#include<bits/stdc++.h>
using namespace std;
struct Node {
    int data;
    Node* right;
    Node* left;
    
    Node(int x){
        data = x;
        right = NULL;
        left = NULL;
    }
};
void insert(Node ** tree, int val)
{
    if(!(*tree))
    {
        *tree = new Node(val);
        return;
    }
    if(val < (*tree)->data)
    { insert(&(*tree)->left, val);}
    else if(val > (*tree)->data)
    { insert(&(*tree)->right, val);}
}
void merge(Node *root1,Node *root2);
int main()
{
#ifdef LOCAL
    fstream file(INPUT_FILE);
#else
    istream & file = std::cin;
#endif
    
    int T;
    file>>T;
    while(T--)
    {
        Node *root1;Node *root2;
        root1 = NULL;
        root2=NULL;
        int N;
        file>>N;
        int M;
        file>>M;
        for(int i=0;i<N;i++)
        {
            int k;
            file>>k;
            insert(&root1, k);}
        for(int i=0;i<M;i++)
        {
            int k;
            file>>k;
            insert(&root2, k);} 
       merge(root1,root2);
        cout<<endl;
    }
}

/*This is a function problem.You only need to complete the function given below*/

/* The structure of Node is
struct Node {
    int data;
    Node* right;
    Node* left;
    
    Node(int x){
        data = x;
        right = NULL;
        left = NULL;
    }
};*/

#include <queue>

using std::queue;

/*You are required to complete below method */
void sort(queue<Node*> & nodes, Node *root)
{
    if (!root) { return; }

    sort(nodes, root->left);
    nodes.push(root);
    sort(nodes, root->right);
}

void merge(Node *root1, Node *root2)
{
    queue<Node*> t1, t2;
    sort(t1, root1);
    sort(t2, root2);

    while (!t1.empty() || !t2.empty()) {
        queue<Node*> *q;

        if (t1.empty())      { q = &t2; }
        else if (t2.empty()) { q = &t1; }
        else {
            int a = t1.front()->data;
            int b = t2.front()->data;

            q = (a < b) ? &t1 : &t2;
        }

        std::cout << q->front()->data << " ";
        q->pop();
    }
}
