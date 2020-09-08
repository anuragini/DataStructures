/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */

Country * head;
 
CountryNetwork::CountryNetwork()
{
    Country* head = NULL; 
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
 
void CountryNetwork::insertCountry(Country* previous, string countryName)
//if previous is pointing to null, the list is empty
{
    
    Country* temp = new Country(); 
    temp -> name = countryName; 
    temp -> message = "";
    temp -> numberMessages = 0; 
    temp -> next = NULL;
    
    if (previous == NULL) //add node to the beginning of the list
    {
        //newNode next is head;
        //head is newNode
        //temp->next = head;
        head = temp; //head has the address of new node temp
        cout << "adding: " << countryName << " (HEAD)" << endl;
        
    }
    else
    {
        cout << "adding: " << countryName << " (prev: " << previous->name <<")" << endl;
        temp->next = previous->next; //Make next of new node as next of prev_node
        previous->next = temp; //move the next of prev_node as new_node
    }
}


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    
    Country*  previous = NULL;
    insertCountry(previous,"United States");
    
    //find the pointer to the first item
    previous = searchNetwork("United States");
    insertCountry(previous, "Canada"); 
    
    previous = searchNetwork("Canada");
    insertCountry(previous, "Brazil");
    
    previous = searchNetwork("Brazil");
    insertCountry(previous,"India");
    
    previous = searchNetwork("India");
    insertCountry(previous,"China");
    
    previous = searchNetwork("China");
    insertCountry(previous,"Australia");
    

}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    Country* ptr = head;
    while(ptr != NULL)
    {
        //cout << "finding nemo " << ptr->name <<endl;
        if (ptr -> name == countryName)
        {
            return ptr;
        }
        ptr = ptr->next; 
    }
    return NULL;

}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    Country* ptr = head;
    if (ptr == NULL)
    {
        cout<<"Empty list"<<endl;
        return;
    }
    bool isFound = false;
    while(ptr != NULL)
    {
        //cout << ptr->name <<endl;
        string s = ptr->name;
        ptr -> message = message;
        ptr -> numberMessages = ptr -> numberMessages +1;
        cout << ptr->name << " [# messages received: " << ptr->numberMessages << "] received: " << ptr->message << endl;

        if(s == receiver)
        {
            isFound = true; 
            break;
        }
        ptr = ptr->next;
       
    }
    if(isFound == false)
    {
        cout<<"Country not found"<<endl;
    }

}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    if (head == NULL)
    {
        return;
    }
    cout<<"== CURRENT PATH =="<<endl;
    Country* ptr = head;
    while (ptr->next != NULL) //suggested by instructor to change from ptr != NULL
    {        
        cout << ptr->name << " -> ";
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
    cout << "===" <<endl;
}


int main()
{
    CountryNetwork CountryNet;
    CountryNet.loadDefaultSetup();
    CountryNet.transmitMsg("India","this is a test");
    CountryNet.printPath();
    
}


