/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the cpp file for the Transaction Class
*/

#include "Transaction.h"

Transaction::Transaction()
{
	type = '0';
	firstName = "";
	lastName = "";
	ID = 0;
	money = 0;
	TransferID = 0;
	failed = false;
}

Transaction::Transaction(char t, string fn, string ln, int id, int m, int tID, bool f)
{
	type = t;
	firstName = fn;
	lastName = ln;
	ID = id;
	money = m;
	TransferID = tID;
	failed = f;
}

Transaction::~Transaction()
{
	type = '0';
	firstName = "";
	lastName = "";
	ID = 0;
	money = 0;
	TransferID = 0;
	failed = false;
}

char Transaction::GetType() const
{
	return type;
}

string Transaction::GetFirstName() const
{
	return firstName;
}

string Transaction::GetLastName() const
{
	return lastName;
}

int Transaction::GetID() const
{
	return ID;
}

int Transaction::GetMoney() const
{
	return money;
}

int Transaction::GetTransferID() const
{
	return TransferID;
}

bool Transaction::HasFailed() const
{
	return failed;
}

void Transaction::SetType(char newType)
{
	type = newType;
}

void Transaction::SetFirstName(string newFN)
{
	firstName = newFN;
}

void Transaction::SetLastName(string newLN)
{
	lastName = newLN;
}

void Transaction::SetID(int newID)
{
	ID = newID;
}

void Transaction::SetMoney(int newMoney)
{
	money = newMoney;
}

void Transaction::SetTransferID(int newID)
{
	TransferID = newID;
} 

void Transaction::SetFailed(bool hasFailed)
{
	failed = hasFailed;
}

void Transaction::Fail()
{
	failed = true;
}

ostream& operator<<(ostream& outStream, const Transaction& trans)
{
	outStream << trans.type << " " ;
	switch (trans.type)
	{
		case 'O':
		{
			outStream << trans.lastName << " " << trans.firstName << " " << trans.ID;
			if (trans.failed)
			{
				outStream << " (Failed)";
			}
			break;
		}

		// Deposits money from an account
		case 'D':
		{
			outStream << trans.ID << " " << trans.money;
			if (trans.failed)
			{
				outStream << " (Failed)";
			}
			break;
		}

		// Withdraws money from an account
		case 'W':
		{
			outStream << trans.ID << " " << trans.money;
			if (trans.failed)
			{
				outStream << " (Failed)";
			}
			break;
		}

		// Transfers money from one account to another
		case 'T':
		{
			outStream << trans.ID << " " << trans.money << " " << trans.TransferID;
			if (trans.failed)
			{
				outStream << " (Failed)";
			}
			break;
		}

		// Prints out the history of an account
		case 'H':
		{
			outStream << trans.ID;
			if (trans.failed)
			{
				outStream << " (Failed)";
			}
			break;
		}

		default:
		{
			cerr << "ERROR: Invalid Transaction Type" << endl;
			break;
		}
	}
	
	return outStream;
}

istream& operator>>(istream& inStream, Transaction& trans)
{
	trans.type = '0';
	trans.firstName = "";
	trans.lastName = "";
	trans.ID = 0;
	trans.money = 0;
	trans.TransferID = 0;
	trans.failed = false;

	inStream >> trans.type;

	switch (trans.type)
	{
		case 'O':
		{
			inStream >> trans.lastName >> trans.firstName >> trans.ID;
			break;
		}

		// Deposits money from an account
		case 'D':
		{
			inStream >> trans.ID >> trans.money;
			break;
		}

		// Withdraws money from an account
		case 'W':
		{
			inStream >> trans.ID >> trans.money;
			break;
		}

		// Transfers money from one account to another
		case 'T':
		{
			inStream >> trans.ID >> trans.money >> trans.TransferID;
			break;

		}

		// Prints out the history of an account
		case 'H':
		{
			inStream >> trans.ID;
			break;
		}

		default:
		{
			cerr << "ERROR: Invalid Transaction Type" << endl;
			break;
		}
	}
	return inStream;
}