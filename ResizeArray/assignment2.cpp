#include<iostream> 
#include<fstream>
#include <iomanip>
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

struct wordItem 
{
    string word;
    int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
    
    string fileName = ignoreWordFileName;
    //cout << fileName <<endl;
    //return;
    int len= 1;
    ifstream file(fileName);
    if(!file)
    {
        std::cout << "Failed to open " << ignoreWordFileName << std::endl;
        
        return;
    }
    string s;
    int count = 0;
    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            
            char  delimiter = ' ';
            string arr[len];
            int numElements = split(s, delimiter, arr, len); //arr[] = [the, king, is] //
            ignoreWords[count] = arr[0];
            count ++; // count will increment for each line
        }
    } //loop through all words in the file is complete
    /*
    for(int i = 0; i<count;i++)
    {
        cout<<ignoreWords[i]<<endl;
    }
    cout<<count<<endl;
    */
    
}


bool isStopWord(string word, string ignoreWords[])
{
    for(int i = 0; i<50;i++)
    {
        if(word == ignoreWords[i])
        {
            return true;
        }
        else 
        {
            //do not return flase as this will not loop or traverse the entire array
        }
    }
    return false; 
}
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
    int totalCount = 0; 
    for (int j = 0; j < length + 1; j++)
    {
        wordItem w = uniqueWords[j]; 
        string  s1 = w.word;
        int cnt = w.count;
        totalCount = totalCount + cnt; 

    }
    
    return totalCount;
}
void arraySort(wordItem uniqueWords[], int length)
{
    for(int i = 0; i<length;i++)
    {
        for(int j = i+1; j<length; j++)
        {
            if(uniqueWords[i].count < uniqueWords[j].count) //< is dsc, > is asc order
            {
                wordItem temp = uniqueWords[i];
                uniqueWords[i] = uniqueWords[j];
                uniqueWords[j] = temp;
            }
        }
    }
    return;
}
void printNext10(wordItem uniqueWords[], int N, int totalNumWords)
{
    //compute frequency
    cout << std::fixed;
    cout << std::setprecision(4);
    for (int j = N; j < N+10; j++)
    {
        wordItem w = uniqueWords[j]; 
        string  s1 = w.word; 
        int cnt = w.count;
        float frequency = float(cnt)/float(totalNumWords);
        cout<<frequency  << " - " << s1 <<endl;
    }
}

void WriteList(wordItem uniqueWords[], int length, string outputFileName)
{
    ofstream out_file;
    out_file.open(outputFileName);
    for(int i = 0; i<length;i++)
    {
        wordItem w = uniqueWords[i];
        out_file<<w.word << " " << w.count <<endl;
        //out_file<< w.count <<endl;
        
    }
}

wordItem* resize(wordItem* arrayPtr, int &capacity)
{
	// TODO increase the capacity by two times
	int newCapacity =  2 * capacity;
    //cout<<"Resizing from "<<capacity<<" to "<<newCapacity<<endl;

	//TODO dynamically allocate an array of size newCapacity
	wordItem *newArray = new wordItem[newCapacity];

	// TODO copy all data from oldArray to newArray
    for(int i = 0; i<capacity;i++)
    {
        newArray[i] = arrayPtr[i];
    }

	// TODO free the memory associated with oldArray
	delete[] arrayPtr;
    
	capacity = newCapacity;

	// TODO return the newArray;
    return newArray;

}



int main()
//int main(int argc, char const *argv[])
{
    
    
    /*
    if(argc != 4)
    {
        cout << "Usage: Assignment2Solution <number of words><inputfilename.txt> <ignoreWordsfilename.txt>" <<endl;
        return -1;
    }
    
    int N = stoi(argv[1]);
    string fileName = argv[2];
    const char * ignoreWordFileName = argv[3];
    */
    
    
    int N = 25;
    string fileName = "tom_sawyer.txt";
    const char * ignoreWordFileName = "ignoreWords.txt";
    

    
    
    //get stop words
    string ignoreWords[50];
    
    
    getStopWords(ignoreWordFileName, ignoreWords);

    
    //wordItem uniqueWords[10000]; //this workds without a need to resize
    int totalWordCount = 0;
    int uniqueWordsSize = 100;
    
    //int arr[5] = { 1, 2, 3, 4, 5 }; 
    //int *ptr = arr; 
  
    //wordItem uniqueWords[100];
    wordItem* uniqueWords = new wordItem[uniqueWordsSize];

    
    int len= 10000;
    ifstream file(fileName);
    if(!file)
    {
        cout<<"Failed to open the file."<<endl;
        return 0;
    }
    int countResize = 0; //how many times array was resized
    string s;
    int count = 0;

    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            char  delimiter = ' ';
            string arr[len];
            int numElements = split(s, delimiter, arr, len); //arr[] = [the, king, is] //
            totalWordCount = totalWordCount + numElements;
            //numElements is the number of words in the sentence
            for(int i = 0; i< numElements;i++)
            {
                string s1 = arr[i];
                bool exists = isStopWord(s1,ignoreWords);
                bool found = false;
                if(exists == false)
                {
                    for (int j = 0; j < count; j++)
                    {   
                        string s2 = uniqueWords[j].word;
                        if (s1 == s2)
                        {
                            uniqueWords[j].count = uniqueWords[j].count + 1; //this word already exists in the array of wordItem
                            found = true;
                            break;
                        }
                    }
                    if (found == false)
                    {
                        
                        //resize array if count+1<=length of array
                        if (count >= uniqueWordsSize)
                        {
                            uniqueWords = resize(uniqueWords,uniqueWordsSize);
                            countResize = countResize + 1;
                        }
                        wordItem w; //this is a new word being added to the array of worditem
                        w.word = s1; 
                        w.count = 1;
                        uniqueWords[count] = w;
                        count ++; // count will increment for each line
                    }
                }
            }

        }
    } //loop through all words in the file is complete
    
    cout<< "Array doubled: " <<countResize<< endl;
    cout<<"#"<<endl; 
    
    cout<<"Unique non-common words: "<<count<<endl; 
    cout<<"#"<<endl; 
    //WriteList(uniqueWords, count, "output.txt");

    int totalUniqueWordCount = count + 1;
    int x = getTotalNumberNonStopWords(uniqueWords, totalUniqueWordCount);
    cout <<"Total non-common words: "<<x<<endl;
    cout<<"#"<<endl; 
    cout<<"Probability of next 10 words from rank "<< N<<endl;
    cout<<"---------------------------------------"<<endl;
    
    arraySort(uniqueWords,totalUniqueWordCount);
    //WriteList(uniqueWords, totalUniqueWordCount-1, "output.txt");
    printNext10(uniqueWords, N, x);
    
}