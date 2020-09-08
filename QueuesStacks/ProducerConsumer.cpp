/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
#include <ctype.h>
// you may include more libraries as needed

using namespace std;

ProducerConsumer :: ProducerConsumer()
{
	queueFront = -1;
	queueEnd = -1;
}

bool ProducerConsumer :: isEmpty()
{
	if (queueFront == -1) 
	{
		return true;
	}
    else 
    {
    	return false;
    }
}

bool ProducerConsumer :: isFull()
{
    if(queueFront == 0 && queueEnd == SIZE - 1)
    {
        return true;
    }
    if (queueFront == queueEnd + 1) 
    {
        return true;
    }
    return false;
}

void ProducerConsumer :: enqueue(string item)
{
    if(isFull())
    {
        cout << "Queue full, cannot add new item" <<endl;
    } 
    else 
    {
        if (queueFront == -1) 
        {
        	queueFront = 0;
        }
        queueEnd = (queueEnd + 1) % SIZE;
        queue[queueEnd] = item;
        counter = counter + 1;
        cout << endl << "Inserted " << item << endl;
    }	
}

void ProducerConsumer :: dequeue()
{
    string element;
    if(isEmpty())
    {
    	cout << "Queue empty, cannot dequeue an item" << endl;
        return;
    } 
    else 
    {
        element = queue[queueFront];
        if(queueFront == queueEnd){
            queueFront = -1;
            queueEnd = -1;
        } 
        else {
            queueFront = (queueFront+1) % SIZE;
        }
        counter = counter - 1;
        return;
    }	
}

string ProducerConsumer :: peek()
{
	if (isEmpty())
	{
		cout << "Queue empty, cannot peek" << endl;
		return "";
	}
	return queue[queueFront];
}

int ProducerConsumer :: queueSize()   //changed
{
	return counter;
}
  
void ProducerConsumer :: display()
{
    /* Function to display status of Circular Queue */
    int i;
    if(isEmpty()) {
        cout << endl << "Empty Queue" << endl;
    }
    else
    {
        cout << "Front -> " << queueFront;
        cout << endl << "Items -> ";
        for (i=queueFront; i!=queueEnd;i=(i+1)%SIZE)
        {
            cout << queue[i];
        }
        cout << queue[i];
        cout << endl << "Rear -> " << queueEnd << endl;
    }
}