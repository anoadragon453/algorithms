
#ifndef BST_H
#define BST_H

// Representation of an element in the tree
struct Node {
  int val;   // Value of the node
  Node *left;   // Pointer to the left node
  Node *right;  // Pointer to the right node
  Node *parent; // Pointer to the parent node
};

class BST {
  // Public Definitions
  public: 
	  enum TraversalOrder { InOrderTrav, PreOrderTrav, PostOrderTrav };

  // Public Functions/Variables
  public:
    BST();  // Constructor
   ~BST(); // Destructor
    void Insert(int toInsert);
    void Delete(int toDelete);
    void Print(enum TraversalOrder);

  // Private Functions/Variables
  private:
    Node *root;

    Node *Search(int toFind); // Searche for a node in the tree
    Node *Successor(Node *curr); // Find the successor of the given node
    Node *Minimum(Node *curr); // Find the minimum node of the given subtree
    Node *Maximum(Node *curr); // Find the minimum node of the given subtree
    void Transplant(Node *u, Node *v); // Replace the subtree rooted at node u with the subtree rooted at node v
    void InOrder(Node *curr); // Inorder traversal
    void PreOrder(Node *curr); // Preorder traversal
    void PostOrder(Node *curr); // Postorder traversal
};

#endif
