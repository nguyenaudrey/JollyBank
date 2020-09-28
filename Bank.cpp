/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the cpp file for the Bank Class
*/

#include "Bank.h"
#include "Account.h"

Bank::Bank()
{

}

Bank::~Bank()
{
	while (!bankOperations.empty())
	{
		bankOperations.pop();
	}
}

bool Bank::QueueOperations(string fileName)
{
	ifstream file;
	file.open(fileName);

	// Checks if file has been opened. If so, reads items and adds to list
	if (file.is_open())
	{
		// Reads in contents of file
		while (!file.fail() && !file.eof())
		{
			Transaction newTrans;
			file >> newTrans;
			bankOperations.push(newTrans);
		}
		file.close();
		return true;
	}

	// Terminates program and throws an error if file not found
	else
	{
		cerr << "Could not find file: " << fileName << endl;
		return false;
	}
}

void Bank::PerformOperations()
{
	vector<int> accountIDs;

	while (!bankOperations.empty())
	{
		Transaction current = bankOperations.front();
		bankOperations.pop();

		char type = current.GetType();

		switch (type)
		{
			// Opens an account
			case 'O':
			{
				Account* open;
				Account newAccount(current.GetFirstName(), current.GetLastName(), current.GetID());
				bool success = accounts.Insert(&newAccount);
				if (success)
				{
					accountIDs.push_back(current.GetID());
				}
				else
				{
					cerr << "ERROR: Account " << current.GetID() << " is already open. Transaction refused." << endl;
				}

				break;
			}

			// Deposits money from an account
			case 'D':
			{
				Account* deposit;
				int fourDigitID = current.GetID()/10;
				bool found = accounts.Retrieve(fourDigitID, deposit);
				if (found)
				{
					deposit->Deposit(current.GetID(), current.GetMoney());
				}
				else
				{
					cerr << "ERROR: Account " << fourDigitID << " not found. Deposit refused." << endl;
				}
				break;
			}
			
			// Withdraws money from an account
			case 'W':
			{
				Account* withdraw;
				int fourDigitID = current.GetID()/10;
				bool found = accounts.Retrieve(fourDigitID, withdraw);
				if (found)
				{
					withdraw->Withdraw(current.GetID(), current.GetMoney());
				}
				else
				{
					cerr << "ERROR: Account " << fourDigitID << " not found. Withdrawal refused." << endl;
				}
				break;
			}
			
			// Transfers money from one account to another
			case 'T':
			{
				Account* acct;
				int fourDigitID = current.GetID()/10;
				int transFourDigitID = current.GetTransferID() / 10;
				bool found1 = accounts.Retrieve(fourDigitID, acct);
				bool found2 = accounts.Retrieve(transFourDigitID, acct);
				if (found1 && found2)
				{
					bool success = acct->Transfer(current.GetID(), current.GetMoney(), current.GetTransferID());
				}
				else if (found1)
				{
					cerr << "ERROR: Account " << transFourDigitID << " not found. Transferal refused." << endl;
				}
				else if (found2)
				{
					cerr << "ERROR: Account " << fourDigitID << " not found. Transferal refused." << endl;
				}
				else {
					cerr << "ERROR: Accounts " << fourDigitID << "and " << transFourDigitID  << " not found. Transferal refused." << endl;
				}
				break;
			}

			// Prints out the history of an account
			case 'H':
			{
				Account* hist;
				int currentID = current.GetID();
				
				if (currentID > 999 && currentID < 10000)
				{
					bool found = accounts.Retrieve(currentID, hist);
					if (found)
					{
						hist->DisplayHistory();
					}
					else
					{
						cerr << "ERROR: Account " << current.GetID() << " not found. Transferal refused." << endl;
					}
				}

				else if (currentID > 9999 && currentID < 100000)
				{
					int fourDigitID = current.GetID()/10;
					bool found = accounts.Retrieve(fourDigitID, hist);
					if (found)
					{
						hist->DisplayFundHistory(currentID);
					}
					else
					{
						cerr << "ERROR: Account " << current.GetID() << " not found. Transferal refused." << endl;
					}
				} 
				break;
			}
			
			default:
			{
				cerr << "ERROR: Invalid transaction type" << endl;
				break;
			}

		}
	}
	cout << endl << "Processing Done. Final Balances" << endl;
	for (int i = 0; i < accountIDs.size(); i++)
	{
		Account* acct;
		bool foundacct = accounts.Retrieve(accountIDs[i], acct);
		if (foundacct)
		{
			acct->DisplayBalances();
		}
		cout << endl;
	}
	
}