#include <iostream>

// Node for the tree
struct node {
	int data;			// Data stored in the node
	node* parent;		// Parent of this node
	node* l_child;		// Left child of this node
	node* r_child;		// Right child of this node

	// Initializer (init data to entered data, init pointers to NULL)
	node(int initData) : data(initData), parent(NULL), l_child(NULL), r_child(NULL) {}
};

// Class for the tree
class BST {
private:
	node* root;				// Root of the tree

	// Function for in order traversal of the tree
	void inOrder(node* n) {
		if (n == NULL) return;		// Return once we have reached and empty node

		inOrder(n->l_child);		// Span a whole left branch
		if (n == root)				// If it is the root node, tell the user
			std::cout << n->data << "<-root" << std::endl;
		else						// Otherwise, just print the data
			std::cout << n->data << std::endl;
		inOrder(n->r_child);		// Span a whole right branch
	}

	// Function to find the smallest node in a sub branch
	node* smallestNodeRight(node* begin) {
		node* curr = begin;						// Begin with the first node in the sub branch
		while (curr->l_child != NULL) {			// Loop until there is not more left nodes
			curr = curr->l_child;
		}
		return curr;							// Return the lowest node (furthest node to the left)
	}

public:
	BST() : root(NULL) {}								// Default constructor
	BST(int initData) { root = new node(initData); }	// Constructor, initializes root

	// Insert function
	void insert(int data) {
		node* insertNode = new node(data);		// Node we are inserting into the tree

		// If the tree is empty (root == null)...
		if (root == NULL) {
			root = insertNode;					// Insert the node at the root
		}
		else {									// Otherwise...
			node* currSearch = root;			// Create a node for searching with
			node* currParent;					// Track the parent of the search node
			while (currSearch != NULL) {		// While we have not found an empty location
				currParent = currSearch;		// Get the parent of the search node

				// If our insert data is less than the current data
				if (insertNode->data < currSearch->data) {
					currSearch = currSearch->l_child;	// Go to the left branch
				}
				else {									// Otherwise...
					currSearch = currSearch->r_child;	// Go to the right branch
				}
			}

			// If the data already exists in the tree, do not insert
			if (currParent->data == insertNode->data) {
				return;
			}

			// If the data we are inserting is less than the current data... 
			if (insertNode->data < currParent->data) {
				currParent->l_child = insertNode;	// Insert to the left
			}
			else {									// Otherwise...
				currParent->r_child = insertNode;	// Insert to the right
			}

			insertNode->parent = currParent;		// Track the parent node
		}
	}

	// Function for finding a node in the tree
	node* find(int data) {
		node* currSearch = root;									// Start at the root

		while (currSearch != NULL && currSearch->data != data) {	// Keep searching until the data is found or we reach the end of the tree
			if (data < currSearch->data) {							// If our data is less than the current node, go left
				currSearch = currSearch->l_child;
			}
			else {													// If our data is greater than the current node, go right
				currSearch = currSearch->r_child;
			}
		}

		return currSearch;											// Return the data value
	}

	// Function for removing a node
	void remove(int data) {
		node* delNode = find(data);				// Find the node we want to delete

		if (delNode == NULL) return;			// If the node does not exist, exit

		if (delNode->l_child == NULL && delNode->r_child == NULL) {		// If we are deleting a leaf node (no children)...
			if (delNode == root) {				// If we are deleting the root node, set root to NULL
				root = NULL;
			}
			else if (delNode->data > delNode->parent->data) {	// Otherwise, check if we are the right child of the parent, and set the node right child to NULL
				delNode->parent->r_child = NULL;
			}
			else {												// Otherwise, check if we are the left child of parent and set parent's left child to NULL
				delNode->parent->l_child = NULL;
			}
		}
		else if (delNode->l_child == NULL && delNode->r_child != NULL) {	// If we are deleting a node with only the right child
			if (delNode == root) {			// If we are deleting the root, set the root to the right child
				root = delNode->r_child;
			}
			else if (delNode->data > delNode->parent->data) {	// If we are the right child of the parent, set the right child of the parent to our right child
				delNode->parent->r_child = delNode->r_child;
			}
			else {												// If we are the left child of the parent, set the left child of the parent to our right child
				delNode->parent->l_child = delNode->r_child;
			}

			delNode->r_child->parent = delNode->parent;			// Set the right child's parent to be our parent
		}
		else if (delNode->l_child != NULL && delNode->r_child == NULL) {	// If we are deleting a node with only a left child
			if (delNode == root) {
				root = delNode->l_child;		// If we are deleting the root, set the root to be our left child
			}
			else if (delNode->data > delNode->parent->data) {	// If we are the right child of the parent, set the parent's right child to be our left child
				delNode->parent->r_child = delNode->l_child;
			}
			else {												// If we are the left child of the parent, set the parent's left child to be our left child
				delNode->parent->l_child = delNode->l_child;
			}

			delNode->l_child->parent = delNode->parent;			// Set our left child's parent to be our parent
		}
		else {													// If we are deleting a node with two children
			node* lowestNode = smallestNodeRight(delNode->r_child);	// Find the smallest node to the right

			int tempData = lowestNode->data;			// Store the data from the smallest node
			node* tempNode = delNode;					// Store the node we are replacing

			delNode = lowestNode;						// Set the node we are deleting to be the smallest node

			if (delNode->r_child != NULL) {				// If the smallest node has a right child...
				if (delNode->data > delNode->parent->data) {
					delNode->parent->r_child = delNode->r_child;	// If we are the right child of the parent, set the parent's right child to be our right child
				}
				else {												// If we are the left child of the parent, set the parent's left child to be our right child
					delNode->parent->l_child = delNode->r_child;
				}
				delNode->r_child->parent = delNode->parent;			// Set our right child's parent to be our parent
			}
			else {										// If the smallest node is a leaf node
				if (delNode->data > delNode->parent->data) { // If we are the right child of our parent, set the parent's right child to be NULL
					delNode->parent->r_child = NULL;
				}
				else {										// If we are the left child of our parent, set the parent's left child to be NULL
					delNode->parent->l_child = NULL;
				}
			}

			tempNode->data = tempData;			// Set the replacement node's data to the replacement data
		}

		delete delNode;							// Delete the node
	}

	// Function for printing the tree
	void print() {
		inOrder(root);	// Call in-order traversal from the root
	}

};

int main() {
	BST bst;

	std::cout << "Inserting nodes...\n";

	int arr[] = { 10, 5, 15, 12, 13, 19, 18, 20, 3, 2, 8, 7, 6 };

	for (int val : arr) {
		bst.insert(val);
	}

	bst.print();

	bst.remove(15);

	std::cout << std::endl;

	bst.print();

	std::cout << "Found 10 at Node: " << bst.find(10) << std::endl;
	std::cout << "Found 16 at Node: " << bst.find(16) << std::endl;

	return 0;
}