#include<iostream> 
#include<fstream>
using namespace std;


int split(string s, char delimiter, string inputarr[],int len)// this will take in four parameters
{
    s = s + delimiter;//
    string arr[len];
    int count = 0;
    string word = "";
    if(s.length() == 0 || s == "")// if s is equal to zero or s equals blank return zero
    {
        return 0; 
    }
    for(int i = 0; i < s.length();i++)// for loop cycling thorugh the entire string
    {
        if(s[i] == delimiter) // if the index equals delimiter
        {
            if (word.length() > 0)// when word length is more than zero 
            {
                arr[count] = word;// the count will equal the word 
                word = "";// this will be a blank
                count++;//iterate count
            }
        }
        else
        {
            if (s[i] != delimiter)//is s does not equal the delimter
            {
                word = word + s[i]; // string will be concatenated
            }
           

        }
    }
    for (int i=0; i<len; i++)// cycle through the count for the array
    {
        inputarr[i] = arr[i];// this will equal the new array
        
        
    }
    //return count
    return count;
}

struct Park{
    string parkname;
    string state;
    int area;
};

// length: Number of items currently stored in the array
void addPark(Park parks[], string parkname, string state, int area, int length)
{
    Park park; 
    park.parkname = parkname; 
    park.state = state; 
    park.area = area;
    parks[length] = park;
    //cout <<"addpark " <<length<<endl;
    //cout<<park.parkname<<" "<<park.state<<" "<<park.area<<endl;
    
}
// length: Number of items in the array
void printList(Park parks[], int length)
{
    for(int i = 0; i<length;i++)
    {
        Park park = parks[i];
        cout<<park.parkname<<"["<<park.state<<"]area: "<<park.area<<endl;
    }
}
void WriteList(Park parks[], int length, string outputFileName, int upper_bound, int lower_bound)
{
    ofstream out_file;
    out_file.open(outputFileName);
    for(int i = 0; i<length;i++)
    {
        Park park = parks[i];
        if(park.area > lower_bound && park.area < upper_bound)
        {
            out_file<<park.parkname<<"["<<park.state<<"]area: "<<park.area<<endl;
        }
        
    }
}
//int main(int argc, char const *argv[])
int main()
{
    
    Park parks[100];
    string parkname;
    string state;
    int area;
    int length;
    /*
    string fileName = argv[1]; //input file
    string outputFileName = argv[2]; 
    string lb = argv[3];
    string ub = argv[4]; 
    int lower_bound = stoi(lb);
    int upper_bound = stoi( ub); 
    */
    
    
    string fileName = "parks1.csv"; 
    string outputFileName = "output.csv"; 
    int lower_bound = 200000;
    int upper_bound = 900000; 

    int len=3;
    ifstream file(fileName);
    if(!file)
    {
        cout<<"Failed to open the file."<<endl;
        
        return 0;
    }
    string s;
    int count = 0;
    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            
            char  delimiter = ',';
            string arr[len];
            int numElements = split(s, delimiter, arr, len);
            parkname = arr[0]; 
            state = arr[1]; 
            area = stoi(arr[2]);
            length = count;
            addPark(parks,  parkname,  state,  area,  length); 
            //cout <<length<<endl;
            
            //cout<<s<<endl;
            count ++; // count will increment for eah line

        }
    }
    int numElements = length + 1;
    printList(parks,numElements); //length is the maximum index + 1
    WriteList(parks, numElements, outputFileName, upper_bound, lower_bound);

}