/***********************************
Author: Daniel Hodgson
Header file for hashtable
hashtable will be a template class
************************************/

#include <iostream>
#include "node.h"

using namespace std;

template <typename T1, typename T2>
class hashtable 
{
public:
	hashtable() //default constructor
	{ 
		this->size = 50000;
		this->used = 0; 
		this->collisions = 0;
		this->table = new node<T1, T2>*[size];
		for(int i = 0; i < size; i++)
			this->table[i] = NULL;
	}

	void insert(T1 aKey, T2 aValue = 1) //add a value to the hashtable, call update if table too small, and use hash to find the position
	{
		if (this->size == this->used)
			this->update();
		node<T1,T2>* current = find(aKey);
		if (current == NULL) //Node does not exist, time to make one
		{
			unsigned int bucket = hashString(aKey, this->size);
			//T2 aValue(1);
			node<T1, T2>* newNode = new node<T1, T2>(aKey, aValue);
			table[bucket] = newNode;
		}
		else if (current->getKey() != aKey) //Node exists at bucket, but new one needs to be made as next
		{
			T2 aValue(1);
			node<T1, T2>* newNode = new node<T1, T2>(aKey, aValue);
			current->setNext(newNode);
			this->collisions++;
		}
		else //Our node exists, but needs to be incremented.
			current->setValue(current->getValue() + 1);
		this->used++;
	}

	void display() //display the contents in the array
	{
		int totalVal = 0;
		for (int i = 0; i < this->size; i++)
		{
			node<T1, T2> *current = this->table[i];
			while (current != NULL)
			{
				cout << i << " " << current->getKey() << " : " << current->getValue() << endl;
				totalVal += current->getValue();
				current = current->getNext();
			}
		}
		cout << "Total Values: " << totalVal << endl;
	}

	void update() //double the size of the array, reinsert elements
	{
		node<T1, T2>** tempTable = new node<T1, T2>*[this->size];
		cout << "Used: " << used << endl;
		this->used = 0;
		this->collisions = 0;
		int j = 0;
		for (int i = 0; i < this->size; i++)
		{
			node<T1, T2> *current = this->table[i];
			while (current != NULL)
			{
				tempTable[j++] = new node<T1, T2>(current->getKey(), current->getValue());
				current = current->getNext();
			}
		}
		cout << "j: " << j << endl;
		this->table = new node<T1, T2>*[this->size * 2];
		this->size += this->size;
		for (int i = 0; i < size; i++)
			this->table[i] = NULL;
		for (int i = 0; i < j; i++)
		{
			this->insert(tempTable[i]->getKey(), tempTable[i]->getValue());
			this->used += tempTable[i]->getValue() - 1;
		}
	}

	void lookup(T1 aKey)
	{
		node<T1, T2>* current = this->find(aKey);
		if (current->getKey() == aKey)
		{
			cout << "'" << current->getKey() << "' occured " << current->getValue() << " time";
			if (current->getValue() > 1)
				cout << "s";
			cout << ".\n";
		}
		else
		{
			cout << "Item not found in table.\n";
		}
	}

	node<T1,T2>* find(T1 aKey)  //check if value exists in array
	{
		unsigned int bucket = hashString(aKey, this->size);
		node<T1,T2>* current = this->table[bucket];
		while (current != NULL)
		{
			if (current->getKey() == aKey)
				break;                    //There exists a node with our key, return that node pointer and go no further
			if(current->getNext() != NULL)
				current = current->getNext(); //If this is NULL, then our node does not exist, otherwise go to the next spot in the linked list
			else
				break;
		}
		return current;
	}

	unsigned int getSize() { return this->size; }
	unsigned int getUsed() { return this->used; }
	unsigned int getCollisions() { return this->collisions; }

private:
	node<T1, T2>** table;        //expanding array of type defined at runtime
	unsigned int size;           //size of the array
	unsigned int used;           //number of used array elements
	unsigned int collisions;
};


unsigned int hashString(string key, int size) //generate a bucket from a key
{
	unsigned int bucket = 1;
	for (int i = 0; i < key.size() - 1; i++)
	{
		bucket *= key[i];
	}
	return bucket % size;
	//return reinterpret_cast<unsigned int>(aKey) % size;
}