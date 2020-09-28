/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the cpp file for the History Class
*/

#include <iostream>
#include "History.h"

History::History()
{
	
}

History::~History()
{
	past.clear();
}

bool History::AddToHistory(Transaction event)
{
	past.push_back(event);
	return true;
}


//Checks if the history is empty
bool History::isEmpty() const
{
	return past.empty();
}

ostream& operator<<(ostream& outStream, const History& history)
{
	for (auto val : history.past)
	{
		outStream << "  " << val << endl;
	}
	return outStream;
}