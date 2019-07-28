#pragma once

template<typename Type>
class DynArray
{
private:
	Type* t;
	Type* t2;
	unsigned int arrayCapacity;
	unsigned int arraySize;

public:
	unsigned int i = 0;

	// Accessors
	int GetArraySize() const { return arraySize; }
	int GetArrayCapacity() const { return arrayCapacity; }

	// Mutators
	void SetArraySize(int newArraySize) { arraySize = newArraySize; }
	void SetArrayCapacity(int newArrayCapacity) { arrayCapacity = newArrayCapacity; }

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Constructor
	// Notes : Constructs an empty array (Size 0 Capacity 0)
	/////////////////////////////////////////////////////////////////////////////
	DynArray()
	{
		t = nullptr;
		t2 = nullptr;
		arraySize = 0;
		arrayCapacity = 0;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Destructor
	// Notes : cleans up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	~DynArray()
	{
		delete[] t;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	DynArray(const DynArray<Type>& that)
	{
		t = nullptr;
		*this = that;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	DynArray<Type>& operator=(const DynArray<Type>& that)
	{
		if (this != &that)
		{
			arraySize = that.arraySize;
			arrayCapacity = that.arrayCapacity;

			delete[] t;
			t = new Type[arrayCapacity];
			for (i = 0; i < arraySize; ++i)
				t[i] = that.t[i];

		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index to access
	// Return : Type & - returns the array element at [index]
	// Notes : performs no error checking. user should ensure index is 
	//		valid with the size() method
	/////////////////////////////////////////////////////////////////////////////
	Type& operator[](const unsigned int index)
	{
		return t[index];
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index to access
	// Return : const Type & - returns the array element at [index]
	// Notes : performs no error checking. user should ensure index is 
	//		valid with the size() method
	/////////////////////////////////////////////////////////////////////////////
	const Type& operator[](const unsigned int index) const
	{
		return t[index];
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	size
	// Returns : int - returns the number of items being stored
	// Notes : this function returns the number of items being stored, 
	/////////////////////////////////////////////////////////////////////////////
	unsigned int size() const
	{
		return arraySize;
	}

	void decSize()
	{
		--arraySize;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : capacity
	// Returns : int - returns the number of items the array can store before 
	//		the next resize
	// Notes : this function returns the number of items the array can store, 
	//		not the number of bytes
	/////////////////////////////////////////////////////////////////////////////
	unsigned int capacity() const
	{
		return arrayCapacity;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	clear
	// Notes : cleans up any dynamic memory and resets size and capacity to 0
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		delete[] t;
		t = nullptr;
		arraySize = 0;
		arrayCapacity = 0;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : append
	// Parameters : item - the item to be appended to the next open spot
	// Notes : this function will append the item to the next open spot. if 
	//		no room exists, the array's capacity will be doubled and then 
	//		the item will be added
	/////////////////////////////////////////////////////////////////////////////
	void append(const Type& item)
	{
		if (arraySize < arrayCapacity)
			t[arraySize] = item;
		else if (arraySize >= arrayCapacity && arraySize != 0)
		{
			t2 = new Type[arrayCapacity * 2];
			for (i = 0; i < arraySize; ++i)
				t2[i] = t[i];
			t2[arraySize] = item;

			arrayCapacity *= 2;
			delete[] t;
			t = t2;
		}
		else
		{
			t = new Type[1];
			t[0] = item;
			arrayCapacity = 1;
		}
		++arraySize;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : reserve
	// Parameters : newCap - the new capacity
	// Notes : 	- default parameter - reserve more space in the array, based on 
	//		the expansion rate (100%, 1 minimum).
	//		- non-default parameter, expand to the specified capacity
	//		- if newCap is LESS than the current capacity, do nothing. 
	//		This function should NOT make the array smaller.
	/////////////////////////////////////////////////////////////////////////////
	void reserve(const unsigned int & newCap = 0)
	{
		if (newCap == arrayCapacity || newCap == 0)
		{
			if (arrayCapacity != 0)
			{
				t2 = new Type[arrayCapacity * 2];
				for (i = 0; i < arraySize; ++i)
					t2[i] = t[i];

				arrayCapacity *= 2;
				delete[] t;
				t = t2;
			}
			else
			{
				t = new Type[1];
				arrayCapacity = 1;
			}
		}
		else if (newCap < arrayCapacity)
			return;
		else
		{
			t2 = new Type[newCap];
			for (i = 0; i < arraySize; ++i)
				t2[i] = t[i];

			arrayCapacity = newCap;
			delete[] t;
			t = t2;
		}
	}
};