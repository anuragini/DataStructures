//Resize array

#include<iostream> 
#include<fstream>
#include <array>
using namespace std; 

void resize(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        cout <<arr[i] <<endl;;
    }
    
    int* resize_arr = new int[size * 2];
    for(int i = 0; i < size; i++)
        resize_arr[i] = arr[i];
    
    size = size * 2;
    arr = resize_arr;
    delete[] resize_arr;
    
    cout << "resize" <<endl;
    
    for(int i = 0; i < size; i++)
    {
        cout <<arr[i] <<endl;;
    }
}

int main()
{
    int size = 5;
    int* arr = new int[size];
    for(int i = 0; i < size; i++)
    {
        arr[i]=i*10;
    }
    resize(arr,size);
    size = 10;

        
  
}