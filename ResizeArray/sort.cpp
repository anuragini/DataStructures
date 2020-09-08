#include<iostream>
using namespace std;
int main ()
{
    int num[5] = {5,4,7,45,0};
    int i, j, desc;

   
    for (i = 0; i < 5; ++i)   //  'for' loop is used for sorting the numbers in descending order
    {
        for (j = i + 1; j < 5; ++j)
        {
            if (num[i] < num[j]) //dsc order
            //if (num[i] > num[j]) //asc order
            {
                desc = num[i];
                num[i] = num[j];
                num[j] = desc;
            }
        }
    }
    cout<<"\n Numbers in Descending Order : \n";
    for (i = 0; i < 5; ++i)
    {
        cout<<" ";
        cout<<num[i];
        cout<<"\n";
    }
}