#include "Store.h"

void Store::Load(const char * path)
{
	std::ifstream shop;

	shop.open(path);

	if (shop.is_open())
	{
		int count;
		shop >> count;
		size = count;
		contents.reserve(count);
		Item temp;

		for (int i = 0; i < count; i++)
		{
			shop >> temp.type >> temp.name >> temp.cost >> temp.weight;
			contents.append(temp);
		}
		shop.close();
	}
}

void Store::SortByType()
{
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		for (unsigned int j = 0; j < contents.size(); j++)
		{
			if (strcmp(contents[i].type, contents[j].type) < 0)
			{
				swap(contents[i], contents[j]);
			}
		}
	}
}

void Store::SortByName()
{
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		for (unsigned int j = 0; j < contents.size(); j++)
		{
			if (strcmp(contents[i].name, contents[j].name) < 0)
			{
				swap(contents[i], contents[j]);
			}
		}
	}

}

void Store::SortByPrice()
{
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		for (unsigned int j = 0; j < contents.size(); j++)
		{
			if (contents[i].cost > contents[j].cost)
			{
				swap(contents[i], contents[j]);
			}
		}
	}
}

void Store::SortByWeight()
{
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		for (unsigned int j = 0; j < contents.size(); j++)
		{
			if (contents[i].weight > contents[j].weight)
			{
				swap(contents[i], contents[j]);
			}
		}
	}
}

void Store::Display()
{
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		if (strlen(contents[i].type) > 7)
		{
			if (strlen(contents[i].name) > 7)
			{
				cout << contents[i].type << '\t' << contents[i].name << '\t' << contents[i].cost << '\t' << contents[i].weight << '\n';
			}
		}

		if (strlen(contents[i].type) > 7)
		{
			if (strlen(contents[i].name) < 7)
			{
				cout << contents[i].type << '\t' << contents[i].name << "\t\t" << contents[i].cost << '\t' << contents[i].weight << '\n';
			}
		}

		if (strlen(contents[i].type) < 7)
		{
			if (strlen(contents[i].name) > 7)
			{
				cout << contents[i].type << "\t\t" << contents[i].name << '\t' << contents[i].cost << '\t' << contents[i].weight << '\n';
			}
		}

		if (strlen(contents[i].type) < 7)
		{
			if (strlen(contents[i].name) < 7)
			{
				cout << contents[i].type << "\t\t" << contents[i].name << "\t\t" << contents[i].cost << '\t' << contents[i].weight << '\n';
			}
		}

	}
	cout << '\n';
}

bool Store::Search(const char * name)
{
	for (unsigned int i = 0; i < contents.size(); ++i)
	{
		if (_strcmpi(contents[i].name, name) == 0)
		{
			cout << name << " has been found!\n";
			return true;
		}
	}
	cout << name << " could not be found...\n";
	return false;
}

void Inventory::AddItem(Item x)
{
	items.addHead(x);
}

void Inventory::RemoveItem(Item x)
{
	SLLIter<Item> i(items);
	for (i.begin(); !i.end(); ++i)
	{
		if (i.current().name == x.name && i.current().type == x.type)
			items.remove(i);
	}
}

void Inventory::Display()
{
	cout << "Cash: " << coins << " gold " << '\t' << "Weight: " << weight << "/" << maxWeight << '\n';

	SLLIter<Item> i(items);
	for (i.begin(); !i.end(); ++i)
	{
		if (strlen(i.current().type) < 7 && strlen(i.current().name) < 7)
		{
			cout << i.current().type << "\t\t" << i.current().name << "\t\t" << i.current().cost << '\t' << i.current().weight << '\n';
		}

		else if (strlen(i.current().type) < 7 && strlen(i.current().name) > 7)
		{
			cout << i.current().type << "\t\t" << i.current().name << '\t' << i.current().cost << '\t' << i.current().weight << '\n';
		}

		else if (strlen(i.current().type) > 7 && strlen(i.current().name) < 7)
		{
			cout << i.current().type << '\t' << i.current().name << "\t\t" << i.current().cost << '\t' << i.current().weight << '\n';
		}

		else if (strlen(i.current().type) > 7 && strlen(i.current().name) > 7)
		{
			cout << i.current().type << "\t\t" << i.current().name << "\t\t" << i.current().cost << '\t' << i.current().weight << '\n';
		}
	}
}

void Inventory::clear()
{
	items.clear();
}


void TransactionManager::Buy(int itemIndex)
{
	itemIndex--;
	if (theInventory.GetCoins() >= theStore.GetContent(itemIndex).cost && theInventory.GetWeight() + theStore.GetContent(itemIndex).weight <= theInventory.GetMaxWeight())
	{
		theInventory.AddItem(theStore.GetContent(itemIndex));
		Transaction purchase;
		purchase.bought = true;
		purchase.theItem = theStore.GetContent(itemIndex);
		theInventory.SetCoins(theInventory.GetCoins() - purchase.theItem.cost);
		theInventory.SetWeight(theInventory.GetWeight() + purchase.theItem.weight);
		if (theHistory.size() < 5)
		{
			theHistory.addHead(purchase);
		}

		else
		{
			SLLIter<Transaction> i(theHistory);

			int index = 0;
			for (i.begin(); !i.end(); ++i)
			{
				index++;
				if (index > 4)
					break;
			}

			if (theHistory.size() < 5)
			{
				theHistory.addHead(purchase);
			}
			else
			{
				theHistory.remove(i);
				theHistory.addHead(purchase);
			}
		}
	}
	else
	{
		if (theInventory.GetCoins() < theStore.GetContent(itemIndex).cost)
		{
			cout << "You do not have enough gold to purchase this item\n";
		}

		if (theInventory.GetWeight() + theStore.GetContent(itemIndex).weight > theInventory.GetMaxWeight())
		{
			cout << "Purchasing this item would overburden you, so you put it back\n";
		}
		Sleep(1000);
	}
}

void TransactionManager::Sell(int itemIndex)
{
	itemIndex--;
	if (itemIndex >= 0)
	{
		theInventory.RemoveItem(theStore.GetContent(itemIndex));
		theInventory.SetCoins(theInventory.GetCoins() + (theStore.GetContent(itemIndex).cost / 2));
		theInventory.SetWeight(theInventory.GetWeight() - theStore.GetContent(itemIndex).weight);
		Transaction sold;
		sold.bought = false;
		sold.theItem = theStore.GetContent(itemIndex);

		if (theHistory.size() < 5)
		{
			theHistory.addHead(sold);
		}

		else
		{
			SLLIter<Transaction> i(theHistory);

			for (i.begin(); !i.end(); ++i)
			{
			}

			theHistory.remove(i);
			theHistory.addHead(sold);
		}
	}

	else
	{
		cout << "You don't have anyhing to sell in this pocket\n";
	}
}

void TransactionManager::Undo()
{
	if (theHistory.size() > 0)
	{
		SLLIter<Transaction> i(theHistory);
		i.begin();

		if (i.current().bought == true)
		{
			theInventory.SetCoins(theInventory.GetCoins() + i.current().theItem.cost);
			theInventory.SetWeight(theInventory.GetWeight() - i.current().theItem.weight);
			Item temp = i.current().theItem;
			theInventory.RemoveItem(temp);
		}

		else
		{
			theInventory.SetCoins(theInventory.GetCoins() - i.current().theItem.cost);
			theInventory.SetWeight(theInventory.GetWeight() + i.current().theItem.weight);
			theInventory.AddItem(i.current().theItem);
		}

		theHistory.remove(i);
	}

	else
	{
		cout << "You don't have anything left to undo\n";
		Sleep(1000);
	}
}