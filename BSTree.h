/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the h file for the Binary Search Tree Class
*/

#ifndef BSTREE_H
#define BSTREE_H

#include "Account.h"

class BSTree
{
public:
	// Constructor
	BSTree();

	// Copy Constructor
	BSTree(const BSTree& other);

	// Destructor
	~BSTree();

	// Inserts a new account into the tree
	bool Insert(Account* account);

	// Retrieve objects, first parameter is the ID of the account
	// Second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int&, Account*& account) const;

	// Remove objects, first parameter is the ID of the account
	// Second parameter holds pointer to found object, NULL if not found
	bool Remove(const int&, Account*& account);

	// Prints out the tree
	void Display() const;

	// Empties the tree
	void Empty();

	// Checks if the tree is empty
	bool isEmpty() const;

	// Prints out the tree
	friend ostream& operator<<(ostream& outStream, const BSTree& tree);

	// Assignment overload operator
	BSTree& operator = (const BSTree& rhs);

private:
	struct Node
	{
		Account* pAcct;
		Node* right;
		Node* left;
	};
	Node* root;

	// Recursive helper functions
	Node* Insert(Node* node, Account key);

	// Looks for a node
	Node* Find(Node* node, int key) const;

	// Finds the smallest node and returns the parent node
	Node* FindSmallest(Node* node, Node*& above) const;

	// Copies nodes
	void Copy(Node* lhs, Node* rhs);

	// Frees nodes
	void Free(Node* node);

	// Prints out nodes
	void Print(Node* node) const;

	// Adds nodes to the ostream
	ostream& OSPrint(ostream& outStream, Node* node) const;
};

#endif