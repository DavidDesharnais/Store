#pragma once

#include "DynArray.h"
#include "SLList.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <sstream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <stdlib.h>

struct Item
{
	char type[16];
	char name[16];
	unsigned int cost;
	unsigned int weight;

};


class Store
{
	DynArray<Item> contents;
	unsigned int size;
public:
	void Load(const char * path);
	void SortByType();
	void SortByName();
	void SortByPrice();
	void SortByWeight();
	void Display();
	bool Search(const char * name);

	Item GetContent(int itemIndex) { return contents[itemIndex]; }
	unsigned int GetSize() { return size; }
};


class Inventory
{
	SLList <Item> items;
	unsigned int coins;
	unsigned int weight;
	unsigned int maxWeight;

public:
	void AddItem(Item x);
	void RemoveItem(Item x);
	void Display();

	unsigned int GetCoins() { return coins; }
	unsigned int GetWeight() { return weight; }
	unsigned int GetMaxWeight() { return maxWeight; }

	void SetCoins(unsigned int newCoins) { coins = newCoins; }
	void SetWeight(unsigned int newWeight) { weight = newWeight; }
	void SetMaxWeight(unsigned int newMaxWeight) { maxWeight = newMaxWeight; }
	void clear();
};


class TransactionManager
{
	struct Transaction
	{
		Item theItem;
		bool bought;
	};

	Store theStore;
	Inventory theInventory;
	SLList<Transaction> theHistory;

public:
	void Buy(int itemIndex);
	void Sell(int itemIndex);
	void Undo();

	Store GetStore() { return theStore; }
	Inventory GetInventory() { return theInventory; }
	void SetStore(Store& shop) { theStore = shop; }
	void SetTheInventory(Inventory& newInventory) { theInventory = newInventory; }
};