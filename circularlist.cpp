#include <iostream>
#include <string>

using namespace std;

template<class T>
class ListItem
{
public:
  ListItem(T item) : next(0)
	{
		item_value = item;
	}

	T item_value;

	ListItem<T>* next;
	// ListItem<T>* prev;
};


template<class T>
class CircularList
{
public:	
	CircularList();
	
	void insertAtEnd(T value);
	void insertAfter(ListItem<T>* item, value);
	
	ListItem<T>* find(T value);
	ListItem<T>* start;
	// ListItem<T>* end;
private:

};

template<class T>
CircularList<T>::CircularList() : start(0), end(0)
{

}

template<class T>
void CircularList<T>::insertAtEnd(T value)
{
	if(start == 0)
	{
		start = new ListItem<T>(value);
		start->next = start;
		return;
	}
	auto currentItem = start;

	while(currentItem->next != start)
	{
		currentItem = currentItem->next;
	}

	auto newItem = new ListItem<T>(value);
	currentItem->next = newItem;
	newItem->next = start;
}

template<class T>
ListItem<T>* CircularList<T>::find(T value)
{
	if(start == 0)
	{
		return 0;
	}
	auto currentItem = start;

	while(currentItem->item_value != value)
	{
		currentItem = currentItem->next;	
	}

	return currentItem;
}

int main()
{

	return 0;
}
