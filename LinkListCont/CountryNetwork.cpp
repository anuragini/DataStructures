/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
/* finished. do not touch. */
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    
    // if we are passed an empty list, just create a new head node, and return
    if (head == NULL)
    {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        head = new Country;
        head->name = countryName;
        head->numberMessages = 0;
        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        //case where it's a new head Country
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country *c = new Country;
        c->name = countryName;
        c->numberMessages = 0;
        c->next = head;
        head = c;
    }else{
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->numberMessages = 0;
        newCountry->next = previous->next;
        previous->next = newCountry;
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    //traverse and find the prev and curr
    //curr = countryName passed that needs to be deleted
    //prev->next = curr->next
    //free up curr
    if(head == NULL)
    {
        return;
    }
    if(head->name == countryName) //first node is dropped
    {
        Country * firstNode = head;
        head = head -> next;
        free(firstNode);
        return;
    }
    Country* curr = head; 
    Country* prev;
    bool isFound = false;
    while (curr != NULL && curr->name != countryName)
    {
        prev = curr;//prev = head;
        curr = curr->next;
    }
    if(curr == NULL) //it reached the last node and did not find the countryName
    {
        cout<<"Country does not exist."<<endl;
        return;
    }
    
    prev->next = curr->next;
    free(curr);
    return;
    
}
void CountryNetwork::deleteCountry1(string countryName) 
{
    if(head == NULL)
    {
        return;
    }
    Country*firstNode = head; 
    free(firstNode); 
    Country*curr = head; 
    Country* prev; 
    while(curr!=NULL&&curr->name!=CountryName)
    {
        prev = curr; 
        curr = curr->next; 
        
    }
    if(curr==NULL)
    {
        return;
    }
    prev->next = curr->next; 
    free(curr);
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    int num_countries = 6;
    string countries[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    // deleteEntireNetwork();
    Country* prev = NULL;
    for(int i = 0; i < num_countries; i++)
    {
        insertCountry(prev, countries[i]);
        prev = searchNetwork(countries[i]);
    }
}



/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
// Search until the head is NULL, or we find the country
    Country* ptr = head;
    while (ptr != NULL && ptr->name != countryName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
* Purpose: Creates a loop from last node to the country specified.
* @param countryName name of the country to loop back
* returns pointer to last node before loop creation (to break the loop)
*/
Country* CountryNetwork::createLoop(string countryName)
{
    Country* ptr = head;
    Country* loopPtr = NULL;
    Country* lastPtr;
    while (ptr != NULL)
    {
        if (ptr->name == countryName)
        {
            loopPtr = ptr;// we have found the country
        }

        if (ptr->next == NULL) //last node
        {
            lastPtr = ptr;
        }
        ptr = ptr->next;
    }
    //ptr will be the last node when the while loop is done
    if (loopPtr!=NULL)
    {
        lastPtr->next = loopPtr;
        //cout<<"loop created"<<endl;
    }
    return lastPtr;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
    if(head == NULL)
    {
        return;
    }
    Country* curr = head;
    Country* nextnode;
    while (curr != NULL)
    {
        nextnode = curr->next;
        head = nextnode;
        cout << "deleting: " << curr->name << endl;
        free(curr);
        
        curr = nextnode;
    }
    cout << "Deleted network" << endl;
    
}

/*
*Purpose: to detect loop in the linkedlist
* @param
* returns true if loop is detected. Otherwise return false.
*/
bool CountryNetwork::detectLoop() {
    Country* slow; 
    Country* fast; 
    slow = head; 
    fast = head; 
    while(fast!=NULL && fast->next!=NULL  )
    {
        fast = fast->next->next; 
        slow = slow->next;
        if(slow == fast)
        {
            return true;
        }
        
        
    }
    return false;
}

/*
* Purpose: Take the chunk of nodes from start index to end index
*          Move that chunk at the end of the List
*@param: start index
*@param: end index
* return none
*/
void CountryNetwork:: readjustNetwork(int start_index, int end_index)
{
    if(head == NULL)
    {
        cout<<"Linked List is Empty"<<endl;
        return;
    }
    if(start_index > end_index)
    {
        cout<<"Invalid indices"<<endl;
        return;
    }
    if(end_index < 0)
    {
        cout<<"Invalid end index."<<endl;
        return;
    }
    if(start_index < 0)
    {
        cout<<"Invalid start index."<<endl;
        return;
    }
    
    Country*prevStart = NULL;
    Country* start = NULL;
    Country* end = NULL;
    Country* curr = head;
    Country* nextnode;
    int count = 0;
    while (curr != NULL)
    {

        //cout<<count<<endl;
        //cout <<curr->name << endl;;;
        if(count == start_index-1)
        {
            prevStart = curr;
        }
        if(count == start_index)
        {
            start = curr;
            //cout <<"start  " << curr->name << endl;
        }
        if(count == end_index)
        {
            end = curr;
            //cout <<"end "<<curr->name << endl;
            //cout<<"ASDASDASDASD"<<endl;
        }
        
        if (curr->next == NULL) //we are at the last node in the list
        {
            if (start == NULL || end == NULL)
            {
                break;
            }
            //curr is australia, start = united states, end = canada (start index = 0, end index = 1)
            if (prevStart != NULL)
            {
                prevStart->next = end->next; //end->next is what comes after the substring ends
            }
            else
            {
                head = end->next;
            }
            curr->next = start; //start node gets attached to the previous tail of the list
            end -> next = NULL; //this is the last node
            
            return;
        }
        curr = curr->next;
        count++;
    }
    if(end_index >= count)
    {
        cout<<"Invalid end index"<<endl;
        return;
    }
    if(start_index >= count)
    {
        cout<<"Invalid start index."<<endl;
    }
    if(count == start_index-1)
    {
        prevStart = curr;
    }
    if(count == start_index)
    {
        start = curr;
    }
    if(count == end_index)
    {
        end = curr;
    }
    if(curr->next == NULL)
    {
        if(start == NULL || end == NULL)
        {
            break;
        }
        if(prevStart NULL)
        {
            
        }
    }
}
void CountryNetwork:: readjustNetwork1(int start_index, int end_index)
{
    if(head == NULL)
    {
        return;
    }
    if(start_index > end_index)
    {
        cout<<"Invalid indices"<<endl;
    }
    if(end_index < 0)
    {
        cout<<"Invalid Indices"<<endl;
    }
    Country*prevStart = NULL; 
    Country* start = NULL;
    Country* end = NULL; 
    Country* curr = NULL; 
    Country* nextnode = NULL; 
    int count = 0; 
    while(curr!=NULL)
    {
        prevStart = prevStart->next;
    }
}




/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    Country* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr->next != NULL)
        {
            cout << ptr->name << " -> ";
            ptr = ptr->next;
        }
        cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}

int main()
{
    CountryNetwork CountryNet;
    CountryNet.loadDefaultSetup();
    //CountryNet.transmitMsg("India","this is a test");
    //CountryNet.printPath();
    CountryNet.deleteCountry1("United States");
    //CountryNet.printPath();
    //CountryNet.deleteEntireNetwork();
    CountryNet.printPath();
    CountryNet.readjustNetwork(0,1);
    CountryNet.printPath();
    //Country* loop = CountryNet.createLoop("India");
    //bool loopExists = CountryNet.detectLoop();
    //cout<<loopExists<<endl;

    
}