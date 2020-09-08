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
	queueFront = 0;
	queueEnd = 0;
}

bool ProducerConsumer :: isEmpty()
{
	if (counter == 0) 
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
    	if (counter == 0)
    	{
    		//queueEnd and queueFront do not shcnage
    	}
    	if (counter > 0)
    	{
    		queueEnd++;
    	}
    	if (queueEnd >= SIZE)
    	{
    		queueEnd = (queueEnd+1) % SIZE;	
    	}
        //queueEnd = (queueEnd+1) % SIZE;
        queue[queueEnd] = item;
        counter = counter + 1;
        //cout << "queueEnd " << queueEnd << " item " << item << endl;
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

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main()
{
	ProducerConsumer q;
	int numItems;
	string itemProduced, input, temp;
	while (true)
	{
		menu();
    	getline(cin, input);
    	if (stoi(input) == 1)
    	{
    		cout << "Enter the number of items to be produced:" << endl;
    		getline(cin, temp);
    		numItems = stoi(temp);
    		
    		for (int i=0; i<numItems; i++)
    		{
    			cout << "Item" << i+1 << ":" << endl;
    			getline(cin, itemProduced);
    			q.enqueue(itemProduced);
    			
    		}
    		//q.display();
    	}
    	else if (stoi(input) == 2)
    	{
    	    cout << "Enter the number of items to be consumed:" << endl;
    		getline(cin, temp);
    		numItems = stoi(temp);
    		for (int i=0; i<numItems; i++)
    		{
    		    if (q.queueSize() == 0)
    			{
    				cout << "No more items to consume from queue" << endl;
    				break;
    			}
    			string s = q.peek();
    			cout << "Consumed: " << s << endl;
    			q.dequeue();
    			
    		}
    		//q.display();
    	}
    	else if (stoi(input) == 3)
    	{
    		//q.display();
    		cout << "Number of items in the queue:" << q.queueSize() <<endl;
    		break; //exit the program
    	}
    	
		
	}
}

// Use getline for reading
//int main(int argc, char const *argv[])
int main1()
{
	ProducerConsumer q;
    
    q.dequeue(); //fails because thelist is empty
    
    q.enqueue("1");
    q.enqueue("2");
    q.enqueue("3");
    q.enqueue("4");
    q.enqueue("5");
    q.enqueue("6");
    cout <<"queue size " << q.queueSize() << endl; //6
    q.display();
    q.dequeue();
    cout <<"queue size " << q.queueSize() << endl; //5
    q.display();
    q.enqueue("7");
    cout <<"queue size " << q.queueSize() << endl; //6
    q.display();
    
    return 0;	
}
