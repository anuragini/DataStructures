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
                myArray[j] = temp;//did your phone die?
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

int main2()
{
    	
    // the elements of the following array will
    // be inserted one by one using your
    // insertIntoSortedArray function
    float newValue;
    int numEntries = 0;
    int listsize=6;
    float list[6] = {29.5, 44.0 ,35.1 ,16.2, 9,200.4};
    for(int i = 0; i<listsize;i++)
    {
        newValue = list[i];
        numEntries = insertIntoSortedArray(list, numEntries, newValue);
    }

}
//int main(int argc, char const *argv[])
int main()
{
    
    float myArray[100];
    int numEntries;
    float newValue;
    string fileName = "numbers.txt"; 
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
            numEntries = count + 1;
            int y = insertIntoSortedArray(myArray, numEntries, newValue);
            count ++; // count will increment for each line
        }
        

    }


}