#include<iostream> 
using namespace std; 

void insertCountry(Country* previous, string countryName)
{
    if(previous == NULL){
    head = new Node;
    head = 
    newCountryName->next = NULL;
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL)
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }

  else{

      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
  }