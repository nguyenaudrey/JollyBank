/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the h file for the Transaction Class
*/

#ifndef Transaction_H
#define Transaction_H

#include <iostream>
#include <string>
using namespace std;

class Transaction
{
public:
	Transaction();
	Transaction(char t, string fn, string ln, int id, int m, int tID, bool f);
	~Transaction();

	char GetType() const;
	string GetFirstName() const;
	string GetLastName() const;
	int GetID() const;
	int GetMoney() const;
	int GetTransferID() const;
	bool HasFailed() const;
	
	void SetType(char newType);
	void SetFirstName(string newFN);
	void SetLastName(string newLN);
	void SetID(int newID);
	void SetMoney(int newMoney);
	void SetTransferID(int newID);
	void SetFailed(bool hasFailed);

	void Fail(); 

	friend ostream& operator<<(ostream& outStream, const Transaction& trans);
	friend istream& operator>>(istream& inStream, Transaction& trans);

private:
	char type;
	string firstName;
	string lastName;
	int ID;
	int money;
	int TransferID;
	bool failed;

};

#endif