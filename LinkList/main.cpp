/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>
#include <ctype.h>

void displayMenu();  // declaration for main's helper-function

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    int menu; 
    CountryNetwork CountryNet;
    while(true)
    {
        displayMenu();
        cin >> menu;
        if(menu!= 1 && menu!=2 && menu!=3 && menu!=4 && menu!=5)
        {
          cout<<"Invalid input."<<endl;
    
        }
        
        if(menu == 1)
        {
           CountryNet.loadDefaultSetup();
    
           
        }
        else if(menu == 2)
        {
         CountryNet.printPath();
        }
         else if(menu == 3)
        {
            string receiver = ""; 
            string message = "";
            cout<<"Enter name of the country to receive the message:"<<endl;
            cin >> receiver;
            cout << "Enter the message to send:" << endl;
            cin.ignore();
            getline(cin,message,'\n');
            CountryNet.transmitMsg(receiver, message);
        }
        else if(menu == 4)
        {
            string newCountry = ""; 
            string previousCountry = "";
            cin.ignore();
            
            cout<<"Enter a new country name:"<<endl;
            getline(cin,newCountry,'\n');
            cout<<"Enter the previous country name (or First):"<<endl;
            getline(cin,previousCountry,'\n');
            Country*  previous = NULL;
            previous = CountryNet.searchNetwork(previousCountry);
            CountryNet.insertCountry(previous, newCountry);
            
        }
        if(menu == 5)
        {
            break;
        }
        
        
    }
    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
