#include "Store.h"

#include <iostream>				// needed for drawing the screen
#include <conio.h>				// needed for _kbhit and _getch.
using namespace std;
#include <Windows.h>
#include <ctime>



////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	srand(unsigned int(time(0)));

	Store theStore;
	Inventory theInventory;
	TransactionManager theManager;
	bool shopping = true;

	const char * path = "items.shp";
	theStore.Load(path);

	theInventory.SetCoins(5000);
	theInventory.SetMaxWeight(50);
	theInventory.SetWeight(0);

	cout << "\t\t\t Sorting the store\n\n";
	cout << "1. By Name\t 2. By Price\t 3. By Type\t 4. By Weight\t 5. No Sort\n\n";

	int choice = 0;

	for (;;)
	{
		choice = 0;
		cout << "How would you like to sort the store?\n";
		if (cin >> choice && choice >= 1 && choice <= 5)
		{
			cin.ignore(INT_MAX, '\n');
			break;
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	switch (choice)
	{
	case 1:
	{
		theStore.SortByName();
		break;
	}
	case 2:
	{
		theStore.SortByPrice();
		break;
	}
	case 3:
	{
		theStore.SortByType();
		break;
	}
	case 4:
	{
		theStore.SortByWeight();
		break;
	}
	case 5:
	{
		break;
	}
	}

	system("cls");

	theManager.SetStore(theStore);
	theManager.SetTheInventory(theInventory);

	theStore.Display();
	theInventory.Display();

	while (shopping)
	{

		cout << "\n1. Buy\t 2. Sell\t 3. Search\t 4. Undo transaction\t 5. Leave\n";

		int choice = 0;
		for (;;)
		{
			choice = 0;
			cout << "What do you want to do?\n";
			if (cin >> choice && choice >= 1 && choice <= 5)
			{
				cin.ignore(INT_MAX, '\n');
				break;
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		system("cls");

		switch (choice)
		{
		case 1:		// Buy Menu
		{
			theStore.Display();
			theInventory.Display();

			cout << "\t\t\tPurchasing an Item\n";
			for (;;)
			{
				choice = 0;
				cout << "What would you like to buy?\n";
				if (cin >> choice && choice >= 1 && choice <= (int)theStore.GetSize())
				{
					cin.ignore(INT_MAX, '\n');
					break;
				}
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			theManager.Buy(choice);
			break;
		}
		case 2:		// Sell Menu
		{
			theInventory.Display();
			cout << "\t\t\tSelling an Item\n";
			for (;;)
			{
				choice = 0;
				cout << "What would you like to sell?\n";
				if (cin >> choice && choice >= 1 && choice <= (int)theStore.GetSize())
				{
					cin.ignore(INT_MAX, '\n');
					break;
				}
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			theManager.Sell(choice);
			break;
		}
		case 3:		// Search menu
		{
			theStore.Display();
			theInventory.Display();

			char name[16];
			cout << "\n\t\t\tSearching for something\n\n";
			for (;;)
			{
				cout << "What would like to look for?\n";
				if (cin.get(name, 16))
				{
					cin.ignore(INT_MAX, '\n');
					break;
				}
				cin.ignore(INT_MAX, '\n');
				break;
			}

			theStore.Search(name);

			Sleep(1000);
			break;
		}
		case 4:		// Undo menu
		{
			cout << "\t\t\tUndoing last transaction\n";
			Sleep(500);
			theManager.Undo();
			break;
		}
		case 5:
		{
			shopping = false;
			break;
		}
		}
		theInventory.clear();
		theInventory = theManager.GetInventory();
		theStore = theManager.GetStore();
		system("cls");

		theStore.Display();
		theInventory.Display();
	}
	// complete.
	return 0;
}