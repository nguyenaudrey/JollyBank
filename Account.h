/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the h file for the Account Class
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>

#include "History.h"
#include "Fund.h"

using namespace std;

class Account
{
public:
	// Default Contructor
	Account();

	// Constructor
	Account(string firstName, string lastName, int id);

	//Copy Constructor
	Account(const Account& other);

	// Deconstructor
	~Account();

	// Deposit money from the account
	bool Deposit(int ID, int money);

	// Withdraw money from the account
	bool Withdraw(int ID, int money);

	// Transfer money from one fund to another
	bool Transfer(int from, int money, int to);

	// Displays history
	void DisplayHistory();

	// Displays balances
	void DisplayBalances();

	// Displays an individual fund's history
	void DisplayFundHistory(int ID);

	// Getters and setters
	int GetID() const;
	string GetFirstName() const;
	string GetLastName() const;

	// Checks if less than 
	bool operator<(const Account& account) const;

	// Checks if greater than
	bool operator>(const Account& account) const;

	// Checks for equality
	bool operator==(const Account& account) const;

	// Checks for inequality
	bool operator!=(const Account& account) const;
	
	// Assignment overload operator
	Account& operator = (const Account& rhs);

	// Prints out the account
	friend ostream& operator<<(ostream& outStream, const Account& kid);

	//Reads in a account
	friend istream& operator>>(istream& inStream, Account& kid);


private:
	string firstName;
	string lastName;
	int ID;
	vector<Fund> accountFunds;

	// Finds Fund
	bool FindFund(int id, Fund*& fund);
};


#endif