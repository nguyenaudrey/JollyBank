/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the cpp file for the BSTree Class
*/

#include "BSTree.h"

// Constructor
BSTree::BSTree()
{
	root = nullptr;
}

// Deconstructor
BSTree::~BSTree()
{
	Empty();
}


// Inserts the node into the tree
bool BSTree::Insert(Account* account)
{
	if (isEmpty())
	{
		Node* newRoot = new Node;
		Account* newAccount = new Account(*account);
		newRoot->pAcct = newAccount;
		newRoot->left = nullptr;
		newRoot->right = nullptr;
		root = newRoot;
		return true;
	}
	
	Account* check;
	bool exists = Retrieve(account->GetID(), check);
	if (exists)
	{
		return false;
	}

	else 
	{
		Insert(root, *account);
		return true;
	}
}

//Copy Constructor
BSTree::BSTree(const BSTree& other)
{
	if (other.isEmpty())
	{
		root = nullptr;
	}

	else
	{
		Node* newRoot = new Node;
		Account* newAccount = new Account(*other.root->pAcct);
		newRoot->pAcct = newAccount;
		newRoot->left = nullptr;
		newRoot->right = nullptr;

		root = newRoot;

		Copy(root, other.root);
	}

}

BSTree::Node* BSTree::Insert(Node* node, Account key)
{
	if (node == nullptr)
	{
		Node* newNode = new Node;
		Account* newAccount = new Account(key);
		newNode->pAcct = newAccount;
		newNode->left = nullptr;
		newNode->right = nullptr;
		return newNode;
	}

	if (key < *(node->pAcct))
	{
		node->left = Insert(node->left, key);
	}

	else if (key > *(node->pAcct))
	{
		node->right = Insert(node->right, key);
	}

	return node;
}

// retrieve object, first parameter is the ID of the account
// second parameter holds pointer to found object, NULL if not found
bool BSTree::Retrieve(const int& key, Account*& account) const
{
	if (isEmpty())
	{
		account = nullptr;
		return false;
	}

	Node* temp = Find(root, key);
	
	if (temp != nullptr)
	{
		account = temp->pAcct;
		return true;
	}
	account = nullptr;
	return false;
	
}

BSTree::Node* BSTree::Find(Node* node, int key) const
{
	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->pAcct->GetID() == key)
	{
		return node;
	}

	if (node->pAcct->GetID() < key)
	{
		return Find(node->right, key);
	}

	if (node->pAcct->GetID() > key)
	{
		return Find(node->left, key);
	}
}

// displays the contents of a tree to cout
void BSTree::Display() const
{
	if (isEmpty())
	{
		cout << "Tree is empty" << endl;
		return;
	}
	Print(root);
	cout << endl;
}

void BSTree::Print(Node* node) const
{
	if (isEmpty())
	{
		return;
	}

	if (node->left != nullptr)
	{
		Print(node->left);
	}

	cout << *(node->pAcct) << " ";

	if (node->right != nullptr)
	{
		Print(node->right);
	}

}

bool BSTree::Remove(const int& id, Account*& account) 
{
	if (root->pAcct->GetID() == id)
	{
		Node* temp = root;
		Node* left = root->left;
		Node* right = root->right;

		if (left != nullptr && right != nullptr)
		{
			Node* newRight;
			Node* smallest = FindSmallest(right, newRight);
			root = smallest;
			root->right = newRight;
			root->left = left;
			newRight->right = nullptr;
		}
		else if (left != nullptr) 
		{
			root = left;
		}
		else if (right != nullptr)
		{
			root = right;
		}

		delete temp->pAcct;
		delete temp;
		temp = nullptr;
		return true;
	}
	
	Node* theNode;
	theNode = Find(root, id);
	
	if ((theNode != nullptr)  && (theNode->pAcct->GetID() == id))
	{
		Node* temp = theNode;
		Node* left = theNode->left;
		Node* right = theNode->right;
		Node* nextRight;

		if (left != nullptr && right != nullptr)
		{
			Node* newRight;
			cout << "WE ARE NOT NULL" << endl;
			theNode = FindSmallest(right, newRight);
			theNode->right = newRight;
			newRight->right = nullptr;
		}
		else if (left != nullptr)
		{
			theNode = left;
		}
		else if (right != nullptr)
		{
			theNode = right;
		}

		delete temp->pAcct;
		delete temp;
		temp = nullptr;
		return true;
	}
	return false;
}


BSTree::Node* BSTree::FindSmallest(Node* node, Node*& above) const
{
	// Return if node is the smallest
	if (node->left == nullptr)
	{
		above = node;
		return node;
	}

	return FindSmallest(node->left, above);
}

// Empties the tree
void BSTree::Empty()
{
	if (isEmpty())
	{
		return;
	}

	Free(root);
	root = nullptr;
}

// Helper function for Empty
void BSTree::Free(Node* node)
{
	if (isEmpty())
	{
		return;
	}
	
	if (node->left != nullptr)
	{
		Free(node->left);
	}
	
	if (node->right != nullptr)
	{
		Free(node->right);
	}
	
	delete node->pAcct;
	delete node;
}

// Checks if the tree is empty
bool BSTree::isEmpty() const
{
	return (root == nullptr);
}


void BSTree::Copy(Node* lhs, Node* rhs)
{
	if (rhs != nullptr)
	{
		// Copy left node
		if (rhs->left != nullptr)
		{
			Node* newLeft = new Node;
			Account* newLAccount = new Account(*rhs->left->pAcct);
			newLeft->pAcct = newLAccount;
			newLeft->left = nullptr;
			newLeft->right = nullptr;
			lhs->left = newLeft;

			Copy(lhs->left, rhs->left);
		}

		// Copy right node
		if (rhs->right != nullptr)
		{
			Node* newRight = new Node;
			Account* newRAccount = new Account(*rhs->right->pAcct);
			newRight->pAcct = newRAccount;
			newRight->left = nullptr;
			newRight->right = nullptr;
			lhs->right = newRight;

			Copy(lhs->right, rhs->right);
		}
		
	}
}

// Assignment overload operator
BSTree& BSTree::operator = (const BSTree& rhs)
{
	Empty();

	if (rhs.isEmpty())
	{
		return *this;
	}

	Node* newRoot = new Node;
	Account* newAccount = new Account(*rhs.root->pAcct);
	newRoot->pAcct = newAccount;
	newRoot->left = nullptr;
	newRoot->right = nullptr;

	root = newRoot;

	Copy(root, rhs.root);

	return *this;

}

ostream& operator<<(ostream& outStream, const BSTree& tree)
{
	if (tree.isEmpty())
	{
		outStream << "Tree is empty" ;
		return outStream;
	}
	cout << endl;
	return outStream;
}

ostream& BSTree::OSPrint(ostream& outStream, Node* node) const
{
	if (isEmpty())
	{
		return outStream;
	}

	if (node->left != nullptr)
	{
		Print(node->left);
	}

	outStream << node->pAcct << " ";

	if (node->right != nullptr)
	{
		Print(node->right);
	}

	return outStream;
}
	

