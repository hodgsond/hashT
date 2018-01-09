/***********************************
Author: Daniel Hodgson
Header file for node
this is for a linked list, not much 
going on here, just a single linked 
list for our key value pairs
************************************/


template <typename T1, typename T2>
class node
{
private:
	T1 key;    
	T2 value;
	node* next;
public:
	node(T1 aKey, T2 aValue)
	{
		key = aKey;
		value = aValue;
		next = NULL;
	}
	T1 getKey() { return key; }
	T2 getValue() { return value; }
	node<T1, T2>* getNext() { return next; }
	void setKey(T1 aKey) { this->key = aKey; }
	void setValue(T2 aValue) { this->value = aValue; }
	void setNext(node<T1, T2>* aNext) { this->next = aNext; }
};