/*******************************************************************************
https://practice.geeksforgeeks.org/problems/connect-nodes-at-same-level/1

Given a binary tree, connect the nodes that are at same level.
Structure of the given Binary Tree node is like following.

struct Node
{
      int data;
      Node* left;
      Node* right;
      Node* nextRight; 
}
Initially, all the nextRight pointers point to garbage values. Your function should set 
these pointers to point next right for each node.
       10                          10 ------> NULL
      / \                       /      \
     3   5       =>            3 ------> 5 --------> NULL
    / \   \                  /  \         \
   4   1   2                4 --> 1 -----> 2 -------> NULL

Input Format:
The input contains T, denoting number of testcases. For each testcase there will be third 
lines. The first line contains number of edges. The second line contains relation between 
nodes. The second line contains two nodes and a character separated by space. The first 
node denotes data value, second node denotes where it will be assigned to the previous node 
which will depend on character 'L' or 'R' i.e. the 2nd node will be assigned as left child
to the 1st node if character is 'L' and so on. The first node of second line is root node. 
The struct or class Node has a data part which stores the data, pointer to left child and 
pointer to right child. There are multiple test cases. For each test case, the function will 
be called individually.

Output Format:
For each testcase, in a new line, print the level order and inorder traversals.

Your Task:
You don't have to take input. Complete the function connect() that takes node as parameter 
and connects the nodes at same level.
*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* nextRight;
    Node(int x){
        data = x;
        left = right = NULL;
        nextRight = NULL;
    }
};
void connect(struct Node *p);
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
void printSpecial(Node *root)
{
   if (root == NULL)
     return;
   Node *node = root;
   while (node != NULL)
   {
      printf("%d ", node->data);
      node = node->nextRight;
   }
   if (root->left)
     printSpecial(root->left);
   else
     printSpecial(root->right);
}
void inorder(Node *root)
{
    if (root == NULL)
       return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
/* Driver program to test size function*/
int main()
{
  int t;
  scanf("%d
", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d",&n);
     struct Node *root = NULL;
     struct Node *child;
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
        if (m.find(n1) == m.end())
        {
           parent = new Node(n1);
           m[n1] = parent;
           if (root == NULL)
             root = parent;
        }
        else
           parent = m[n1];
        child = new Node(n2);
        if (lr == 'L')
          parent->left = child;
        else
          parent->right = child;
        m[n2]  = child;
     }
     connect(root);
     printSpecial(root);
     printf("
");
     inorder(root);
     printf("
");
  }
  return 0;
}

/*This is a function problem.You only need to complete the function given below*/
/* struct Node
{
  int data;
  Node *left,  *right;
  Node *nextRight;  // This has garbage value in input trees
}; */

#include <queue>
#include <utility>

using std::queue;
using std::pair;

// Should set the nextRight for all nodes
void connect(Node *p)
{
    queue<pair<int, Node*>> next;
    next.push({ 0, p });
    
    pair<int, Node*> last(0, nullptr);
    
    while (!next.empty()) {
        auto & entry = next.front();
        
        Node *current = entry.second;
        next.pop();
        
        if (!current) { continue; }
        
        if ((last.second != nullptr) && (last.first == entry.first)) {
            last.second->nextRight = current;
        }
        
        last = entry;
        
        next.push({ entry.first + 1, current->left });
        next.push({ entry.first + 1, current->right });
    }
}
