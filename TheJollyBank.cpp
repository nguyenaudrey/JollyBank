/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #5: The Jolly Banker
* Description: This is the driver for the Bank
*/

#include "Bank.h"

int main(int argc, char* argv[])
{
	BSTree real;
	Account newAcct("Angela", "Harris", 2000);
	Account egg("Brad", "Harris", 3000);
	Account bread("Lily", "Tumor", 2300);
	Account milfy("Millie", "Leafy", 4000);
	Account aru("Arugula", "Veggie", 3200);
	Account h("Haploid", "Diploid", 1500);
	Account a("Frog", "Allocake", 1800);
	real.Insert(&newAcct); real.Insert(&egg); real.Insert(&bread); real.Insert(&milfy);
	real.Insert(&aru); real.Insert(&h); real.Insert(&a);
	real.Display();
	Account* empty;
	real.Remove(2000, empty);
	//real.Remove(3200, empty);
	cout << empty << endl;
	cout << real << endl;

	//Bank JollyBank;
	//JollyBank.QueueOperations(argv[1]);
	//JollyBank.PerformOperations();

} 