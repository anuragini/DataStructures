/*
Errors fixed: numEntries was getting incremented two times once outside the function and inside it
the second error was a space after a comma 
the program returned -1 when it should have returned 0
*/

#include<iostream> 
#include<fstream>
using namespace std; 

int insertIntoSortedArray(float myArray[], int numEntries, float newValue)
{
    numEntries = numEntries + 1;
    myArray[numEntries - 1] = newValue;
    for(int i = 0; i<numEntries;i++)
    {
        for(int j = i+1; j<numEntries; j++)
        {
            if(myArray[i] < myArray[j])
            {
                float temp = myArray[i];
                myArray[i] = myArray[j];
                myArray[j] = temp;
            }
        }
    }
    //print - comment this out as they do not want you to prit it out in the function. Stupid people!!
    for (int i = 0; i<numEntries;i++)
    {
        if (i == 0)
        {
            cout<<myArray[i];
        } 
        else 
        {
            cout<<", "<<myArray[i];
        }
    }
    cout << endl;
    
    return numEntries;
}

int main(int argc, char const *argv[])
//int main()
{
    
    float myArray[100];
    int numEntries;
    float newValue;
    string fileName = argv[1]; //"numbers.txt"; 
    //string fileName = "numbers.txt"; 
    int len=1;
    ifstream file(fileName);
    if(!file)
    {
        cout<<"Failed to open the file."<<endl;
        
        return -1;
    }
    string s;
    int count = 0;
    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            newValue = stod(s); // change string s to an integer value for ocunt
            numEntries = count;
            numEntries = insertIntoSortedArray(myArray, numEntries, newValue);
            count ++; // count will increment for each line
        }
    }
}