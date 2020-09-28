/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the cpp file for the Account Class
*/

#include <map>
#include "Account.h"
using namespace std;

//GLOBAL CONSTANTS
// Represent the fund IDs
const int kFMM = 0;
const int kPPMM = 1;
const int kLTBond = 2;
const int kSTBond = 3;
const int k500IF = 4;
const int kCVF = 5;
const int kGEF = 6;
const int kGIF = 7;
const int kVF = 8;
const int kVSI = 9;

Account::Account()
{
	firstName = "UNKNOWN_FIRST";
	lastName = "UNKNOWN_LAST";
	ID = 0;
}

Account::Account(string firstName, string lastName, int id)
{

	this->firstName = firstName;
	this->lastName = lastName;
	this->ID = id;
	int fiveDigitID = id * 10;

	accountFunds.push_back(Fund(fiveDigitID + kFMM, 0, "Money Market"));
	accountFunds.push_back(Fund(fiveDigitID + kPPMM, 0, "Prime Money Market"));
	accountFunds.push_back(Fund(fiveDigitID + kLTBond, 0, "Long-Term Bond"));
	accountFunds.push_back(Fund(fiveDigitID + kSTBond, 0, "Short-Term Bond"));
	accountFunds.push_back(Fund(fiveDigitID + k500IF, 0, "500 Index Fund"));
	accountFunds.push_back(Fund(fiveDigitID + kCVF, 0, "Capital Value Fund"));
	accountFunds.push_back(Fund(fiveDigitID + kGEF, 0, "Growth Equity Fund"));
	accountFunds.push_back(Fund(fiveDigitID + kGIF, 0, "Growth Index Fund"));
	accountFunds.push_back(Fund(fiveDigitID + kVF, 0, "Value Fund"));
	accountFunds.push_back(Fund(fiveDigitID + kVSI, 0, "Value Stock Index"));
}

Account::Account(const Account& other)
{
	firstName = other.firstName;
	lastName = other.lastName;	
	ID = other.ID;
	for (auto fund : other.accountFunds)
	{
		Fund copy = fund;
		accountFunds.push_back(copy);
	}
}

Account::~Account()
{
	firstName = "";
	lastName = "";
	ID = 0;
}

// Deposit money from the account
bool Account::Deposit(int ID, int money)
{
	Transaction deposit('D', "", "", ID, money, 0, false);
	
	Fund* fund;
	bool fundExists = FindFund(ID, fund);
	
	if (fundExists)
	{
		fund->Add(money);
		fund->AddToHistory(deposit);
		return true;

	}

	deposit.Fail();
	fund->AddToHistory(deposit);
	return false;
}

// Withdraw money from the account
bool Account::Withdraw(int ID, int money)
{
	Transaction withdraw('W', "", "", ID, money, 0, false);
	Fund* fund;
	bool fundExists = FindFund(ID, fund);
	
	if (fundExists)
	{
		// Checks if there is enough money
		if (fund->GetAmount() >= money)
		{
			fund->Remove(money);
			fund->AddToHistory(withdraw);
			return true;
		}
		
		// Checks if it is a linked fund it can deposit from
		else
		{
			int fundID = (fund->GetID()) % 10;
			int fiveDigitID = (fund->GetID() - fundID); 

			switch (fundID)
			{
				case kFMM:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kPPMM, linkedFund);

					int first = fund->GetAmount();
					int second = money - fund->GetAmount();

					if (linkedFund->GetAmount() >= second)
					{
						fund->Remove(first);
						Transaction firstWithdraw('W', "", "", ID, first, 0, false);
						fund->AddToHistory(firstWithdraw);

						linkedFund->Remove(second);
						Transaction secondWithdraw('W', "", "", linkedFund->GetID(), second, 0, false);
						linkedFund->AddToHistory(secondWithdraw);
						return true;
					}
					break;
				}

				case kPPMM:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kFMM, linkedFund);

					int first = fund->GetAmount();
					int second = money - fund->GetAmount();

					if (linkedFund->GetAmount() >= second)
					{
						fund->Remove(first);
						Transaction firstWithdraw('W', "", "", ID, first, 0, false);
						fund->AddToHistory(firstWithdraw);

						linkedFund->Remove(second);
						Transaction secondWithdraw('W', "", "", linkedFund->GetID(), second, 0, false);
						linkedFund->AddToHistory(secondWithdraw);
						return true;
					}
					break;
				}

				case kLTBond:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kSTBond, linkedFund);

					int first = fund->GetAmount();
					int second = money - fund->GetAmount();

					if (linkedFund->GetAmount() >= second)
					{
						fund->Remove(first);
						Transaction firstWithdraw('W', "", "", ID, first, 0, false);
						fund->AddToHistory(firstWithdraw);

						linkedFund->Remove(second);
						Transaction secondWithdraw('W', "", "", linkedFund->GetID(), second, 0, false);
						linkedFund->AddToHistory(secondWithdraw);
						return true;
					}
					break;
				}

				case kSTBond:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kLTBond, linkedFund);

					int first = fund->GetAmount(); 
					int second = money - fund->GetAmount();

					if (linkedFund->GetAmount() >= second)
					{
						fund->Remove(first);
						Transaction firstWithdraw('W', "", "", ID, first, 0, false);
						cout << firstWithdraw << endl; 
						fund->AddToHistory(firstWithdraw);

						linkedFund->Remove(second);
						Transaction secondWithdraw('W', "", "", linkedFund->GetID(), second, 0, false);
						cout << secondWithdraw << endl; 
						linkedFund->AddToHistory(secondWithdraw);
						return true;
					}
					break;
				}

				default:
				{
					withdraw.Fail();
					fund->AddToHistory(withdraw);
					cerr << "ERROR: Not enough funds to withdraw " << money << " from " << firstName
						<< " " << lastName << " " << fund->GetName() << endl;
					return false;
				}
			}
		}

	}

	
	return false;
}

// Transfer money from one fund to another
bool Account::Transfer(int to, int money, int from)
{
	Fund* first;
	Fund* second;
	Transaction transfer('T', "", "", to, money, from, false);
	bool firstFundExists = FindFund(to, first);
	bool secondFundExists = FindFund(from, second);
	if (firstFundExists && secondFundExists)
	{
		// Checks if there is enough money
		if (first->GetAmount() >= money)
		{
			first->Remove(money);
			first->AddToHistory(transfer);
			second->Add(money);
			second->AddToHistory(transfer);
			return true; 
		}

		else
		{
			int fundID = (first->GetID()) % 10;
			int fiveDigitID = (first->GetID() - fundID);

			switch (fundID)
			{
				case kFMM:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kPPMM, linkedFund);

					int firstLinkAmount = first->GetAmount();
					int secondLinkAmount = money - first->GetAmount();

					if (linkedFund->GetAmount() >= secondLinkAmount)
					{
						// If linked fund is equal to the fund we are trying to transfer to, fail the transaction
						if (linkedFund->GetID() == second->GetID())
						{
							transfer.Fail();
							first->AddToHistory(transfer);
							second->AddToHistory(transfer);
							return false;
						}

						else
						{
							Transaction fTransfer('T', "", "", to, firstLinkAmount, from, false);
							first->Remove(firstLinkAmount);
							first->AddToHistory(fTransfer);

							Transaction lTransfer('T', "", "", linkedFund->GetID(), secondLinkAmount, from, false);
							linkedFund->Remove(secondLinkAmount);
							linkedFund->AddToHistory(lTransfer);

							
							second->Add(money);
							second->AddToHistory(fTransfer);
							second->AddToHistory(lTransfer);
							return true;
						}
					}
					break;
				}

				case kPPMM:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kFMM, linkedFund);

					int firstLinkAmount = first->GetAmount();
					int secondLinkAmount = money - first->GetAmount();

					if (linkedFund->GetAmount() >= secondLinkAmount)
					{
						// If linked fund is equal to the fund we are trying to transfer to, fail the transaction
						if (linkedFund->GetID() == second->GetID())
						{
							transfer.Fail();
							first->AddToHistory(transfer);
							second->AddToHistory(transfer);
							return false;
						}

						else
						{
							Transaction fTransfer('T', "", "", to, firstLinkAmount, from, false);
							first->Remove(firstLinkAmount);
							first->AddToHistory(fTransfer);

							Transaction lTransfer('T', "", "", linkedFund->GetID(), secondLinkAmount, from, false);
							linkedFund->Remove(secondLinkAmount);
							linkedFund->AddToHistory(lTransfer);


							second->Add(money);
							second->AddToHistory(fTransfer);
							second->AddToHistory(lTransfer);
							return true;
						}
					}
					break;
				}

				case kLTBond:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kSTBond, linkedFund);

					int firstLinkAmount = first->GetAmount();
					int secondLinkAmount = money - first->GetAmount();

					if (linkedFund->GetAmount() >= secondLinkAmount)
					{
						// If linked fund is equal to the fund we are trying to transfer to, fail the transaction
						if (linkedFund->GetID() == second->GetID())
						{
							transfer.Fail();
							first->AddToHistory(transfer);
							second->AddToHistory(transfer);
							return false;
						}

						else
						{
							Transaction fTransfer('T', "", "", to, firstLinkAmount, from, false);
							first->Remove(firstLinkAmount);
							first->AddToHistory(fTransfer);

							Transaction lTransfer('T', "", "", linkedFund->GetID(), secondLinkAmount, from, false);
							linkedFund->Remove(secondLinkAmount);
							linkedFund->AddToHistory(lTransfer);


							second->Add(money);
							second->AddToHistory(fTransfer);
							second->AddToHistory(lTransfer);
							return true;
						}
					}
					break;
				}

				case kSTBond:
				{
					Fund* linkedFund;
					FindFund(fiveDigitID + kLTBond, linkedFund);

					int firstLinkAmount = first->GetAmount();
					int secondLinkAmount = money - first->GetAmount();

					if (linkedFund->GetAmount() >= secondLinkAmount)
					{
						// If linked fund is equal to the fund we are trying to transfer to, fail the transaction
						if (linkedFund->GetID() == second->GetID())
						{
							transfer.Fail();
							first->AddToHistory(transfer);
							second->AddToHistory(transfer);
							return false;
						}

						else
						{
							Transaction fTransfer('T', "", "", to, firstLinkAmount, from, false);
							first->Remove(firstLinkAmount);
							first->AddToHistory(fTransfer);

							Transaction lTransfer('T', "", "", linkedFund->GetID(), secondLinkAmount, from, false);
							linkedFund->Remove(secondLinkAmount);
							linkedFund->AddToHistory(lTransfer);


							second->Add(money);
							second->AddToHistory(fTransfer);
							second->AddToHistory(lTransfer);
							return true;
						}
					}
					break;
				}

				default:
				{
					transfer.Fail();
					first->AddToHistory(transfer);
					second->AddToHistory(transfer);
					cerr << "ERROR: Not enough funds to transfer " << money << " from " << firstName
						<< " " << lastName << " " << first->GetName() << " to " << second->GetName() << endl;
					break;
				}
			
			}
		}
	}

	transfer.Fail();
	first->AddToHistory(transfer);
	second->AddToHistory(transfer);
	return false;
}

bool Account::FindFund(int id, Fund* & fund)
{
	for(unsigned int i = 0; i < accountFunds.size(); i++)
	{
		if (accountFunds[i].GetID() == id)
		{
			fund = &(accountFunds[i]);
			return true;
		}
	}
	cerr << "ERROR: Fund of ID " << id << " does not exist" << endl; 
	return false;
}

// Displays history
void Account::DisplayHistory()
{
	cout << "Transaction History for " << firstName << " " << lastName << " by fund." << endl;

	Fund* theFund;
	int fivedigitid = (ID * 10);

	FindFund(fivedigitid + kFMM, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Money Market: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}
	
	FindFund(fivedigitid + kPPMM, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Prime Money Market: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kLTBond, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Long-Term Bond: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kSTBond, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Short-Term Bond: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + k500IF, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "500 Index Fund: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kCVF, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Capital Value Fund: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kGEF, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Growth Equity Fund: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kGIF, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Growth Index Fund: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kVF, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Value Fund: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}

	FindFund(fivedigitid + kVSI, theFund);
	if (!theFund->EmptyHistory())
	{
		cout << "Value Stock Index: $" << theFund->GetAmount() << endl;
		cout << theFund->GetHistory();
	}
}

void Account::DisplayBalances()
{
	cout << firstName << " " << lastName << " Account ID: " << ID << endl;
	Fund* theFund;
	int fivedigitid = ID * 10;

	FindFund(fivedigitid + kFMM, theFund);
	cout << "    Money Market: $" << theFund->GetAmount() << endl;
	
	FindFund(fivedigitid + kPPMM, theFund);
	cout << "    Prime Money Market: $" << theFund->GetAmount() << endl;
	
	FindFund(fivedigitid + kLTBond, theFund);
	cout << "    Long-Term Bond: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + kSTBond, theFund);
	cout << "    Short-Term Bond: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + k500IF, theFund);
	cout << "    500 Index Fund: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + kCVF, theFund);
	cout << "    Capital Value Fund: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + kGEF, theFund);
	cout << "    Growth Equity Fund: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + kGIF, theFund);
	cout << "    Growth Index Fund: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + kVF, theFund);
	cout << "    Value Fund: $" << theFund->GetAmount() << endl;

	FindFund(fivedigitid + kVSI, theFund);
	cout << "    Value Stock Index: $" << theFund->GetAmount() << endl;
}

//Transaction History for Hank Williams 500 Index Fund: $10000
void Account::DisplayFundHistory(int ID)
{
	Fund* theFund;
	FindFund(ID, theFund);

	cout << "Transaction History for " << firstName << " " << lastName << " " << theFund->GetName()
		 << ": $" << theFund->GetAmount() << endl;
	cout << theFund->GetHistory();
}

int Account::GetID() const
{
	return ID;
}

string Account::GetFirstName() const
{
	return firstName;
}

string Account::GetLastName() const
{
	return lastName;
}

// Checks if less than 
bool Account::operator<(const Account& account) const
{
	if (ID < account.ID)
	{
		return true;
	}

	else
	{
		return false;
	}
}

// Checks if greater than
bool Account::operator>(const Account& account) const
{
	if (ID > account.ID)
	{
		return true;
	}

	else
	{
		return false;
	}
}

// Checks for equality
bool Account::operator==(const Account& account) const
{
	if (ID == account.ID)
	{
		return true;
	}

	else
	{
		return false;
	}
}

// Checks for inequality
bool Account::operator!=(const Account& account) const
{
	if (ID != account.ID)
	{
		return true;
	}

	else
	{
		return false;
	}
}

// Prints out the account.
ostream& operator<<(ostream& outStream, const Account& other)
{
	outStream << other.firstName << " " << other.lastName << " " << other.ID;
	return outStream;
}

//Reads in a account
istream& operator>>(istream& inStream, Account& other)
{
	inStream >> other.lastName >> other.firstName >> other.ID;
	return inStream;
}

// Assignment overload operator
Account& Account::operator = (const Account& rhs)
{
	firstName = rhs.firstName;
	lastName = rhs.lastName;
	ID = rhs.ID;
	for (auto fund : rhs.accountFunds)
	{
		Fund copy = fund;
		accountFunds.push_back(copy);
	}
	return *this;
}