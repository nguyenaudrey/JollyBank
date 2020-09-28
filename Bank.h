/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the h file for the Fund Class
*/

#ifndef BANK_H
#define BANK_H

#include <queue>
#include <iostream>
#include <string>
#include "BSTree.h"
#include "Transaction.h"
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();

	bool QueueOperations(string fileName);
	void PerformOperations();

private:
	BSTree accounts;
	queue<Transaction> bankOperations;
};

#endif