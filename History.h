/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the h file for the History Class
* Serves as a log
*/

#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Transaction.h"
using namespace std;

class History
{
public:
	History();
	~History();
	
	bool AddToHistory(Transaction event);
	bool isEmpty() const;

	// Prints out the History
	friend ostream& operator<<(ostream& outStream, const History& history);

private:
	vector<Transaction> past;
};

#endif