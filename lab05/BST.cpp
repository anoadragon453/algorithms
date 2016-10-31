#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

/****************************************************************
 * CONSTRUCTOR
 *   Creates an empty binary tree
 ****************************************************************/
BST::BST() {
  root = NULL;
}

/****************************************************************
 * DESTRUCTOR
 *   Free all memory used by current tree
 ****************************************************************/
BST::~BST() {
  while (root != NULL)
	{
		BST::Delete(root->val);
	}
}

void BST::Insert(int toInsert) {
  Node *x = root;
  Node *y = NULL;
  Node *z = new Node;
  
  // Insert val into new node
  z->val = toInsert;
  z->left = NULL;
  z->right = NULL;

  if (x == NULL)
    root = z;

  while (x != NULL)
  {
    y = x;
    if (z->val < x->val)
    {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  
  z->parent = y;

  if (y == NULL)
  {
    // BST is empty
    root = z;
  } else if (z->val < y->val) {
    y->left = z;
  } else {
    y->right = z;
  }

}

Node *treeMinimum(Node *x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}

void BST::Delete(int toDelete) {
	Node *z = new Node;
	z = BST::Search(toDelete);

	if (z->left == NULL)
		BST::Transplant(z, z->right);
	else if (z->right == NULL)
		BST::Transplant(z, z->left);
	else
	{
		Node *y = new Node;
	  y = treeMinimum(z->right);
		if (y->parent != z)
		{
			BST::Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		BST::Transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}
}

// Replaces one subtree as a child of its parent with
// another subtree
void BST::Transplant(Node *u, Node *v) {
  if (u->parent == NULL)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != NULL)
    v->parent = u->parent;
}

Node *BST::Successor(Node *x) {
  if (x->right == NULL)
    return BST::Minimum(x->right);
  Node *parent = x->parent;
  while (parent != NULL && x == parent->right)
  {
    x = parent;
    parent = parent->parent;
  }

  return parent;
}

Node *BST::Minimum(Node *x) {
  while (x->left != NULL)
  {
    x = x->left;
  }
}

Node *BST::Maximum(Node *x) {
  while (x->right != NULL)
  {
      x = x->right;
  }
}

Node *search(Node *root, int toFind) {
	if (root == NULL || toFind == root->val)
		return root;
	if (toFind < root->val)
		return search(root->left, toFind);
	else
		return search(root->right, toFind);
}

Node *BST::Search(int toFind) {
	return search(root, toFind);
}

void BST::Print(TraversalOrder Order) {
  if(Order==InOrderTrav)
    InOrder(root);
  else if(Order==PreOrderTrav)
    PreOrder(root);
  else if(Order==PostOrderTrav)
    PostOrder(root);
}

void BST::PreOrder(Node *x) {
  if (x == NULL)
    return;
  cout << x->val << endl;
  BST::PreOrder(x->left);
  BST::PreOrder(x->right);
}

void BST::InOrder(Node *x) {
  if (x == NULL)
    return;
  BST::InOrder(x->left);
  cout << x->val << endl;
  BST::InOrder(x->right);
}

void BST::PostOrder(Node *x) {
  if (x == NULL)
    return;
  BST::PostOrder(x->left);
  BST::PostOrder(x->right);
  cout << x->val << endl;
}
