/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the cpp file for the Fund Class
*/

#include "Fund.h"

Fund::Fund()
{
	ID = 0;
	amount = 0;
	name = "";
}

Fund::Fund(int ID, int amount, string name)
{
	this->ID = ID;
	this->amount = amount;
	this->name = name;
}

Fund::Fund(const Fund& other)
{
	this->ID = other.ID;
	this->amount = other.amount;
	this->name = other.name;
}
Fund::~Fund()
{
	amount = 0;
}

string Fund::GetName() const
{
	return name;
}

int Fund::GetAmount() const
{
	return amount;
}

int Fund::GetID() const 
{
	return ID;
}


bool Fund::Add(int money)
{
	amount += money;
	return true;
}

bool Fund::Remove(int money)
{
	amount -= money;
	return true;
}

void Fund::AddToHistory(Transaction trans)
{
	hist.AddToHistory(trans);
}

History Fund::GetHistory() const
{
	return hist;
}

//Checks if the history is empty
bool Fund::EmptyHistory() const
{
	return hist.isEmpty();
}

Fund& Fund::operator = (const Fund& rhs)
{
	this->ID = rhs.ID;
	this->amount = rhs.amount;
	this->name = rhs.name;
	this->hist = rhs.hist;
	return *this;
}
