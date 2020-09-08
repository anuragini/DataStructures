#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Put helper functions here


MovieNode* createNode(int rank, string title, int year, float rating)
{
    MovieNode* newNode = new MovieNode(rank, title, year, rating);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

MovieNode* addNodeHelper(MovieNode* currNode, int rank, string title, int year, float rating)
{
    if(currNode == NULL){
        return createNode(rank, title, year, rating);
    }
    else if(currNode->title < title){
        currNode->right = addNodeHelper(currNode->right,rank, title, year, rating);
    }
    else if(currNode->title > title){
        currNode->left = addNodeHelper(currNode->left,rank, title, year, rating);
    }
    return currNode;

}

void printTreeHelper(MovieNode* currNode){
     if(currNode)
     {
        printTreeHelper(currNode->left);
        cout<< "Movie: " << currNode->title << " " << currNode->rating << endl;
        printTreeHelper(currNode->right);
     }
     else
     {
         //tree is empty
     }
 }

 void queryMoviesHelper(MovieNode* currNode, float rating, int year){
     //preorder sorting - current node, left, right
     if(currNode)
     {
        if (currNode->rating > rating && currNode -> year > year)
        {
            cout<< currNode->title << "(" << currNode->year << ") " << currNode->rating << endl;
            
        }
        queryMoviesHelper(currNode->left, rating, year);
        queryMoviesHelper(currNode->right, rating, year);
     }
 }
 
 
 MovieNode* searchKeyHelper(MovieNode* currNode, string data){
    if(currNode == NULL)
        return NULL;

    if(currNode->title == data)
        return currNode;

    if(currNode->title > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

float sumRatings(MovieNode* root) 
{ 
    if (root == NULL) 
        return 0; 
    return (root->rating + sumRatings(root->left) + sumRatings(root->right)); 
} 

int countNodes(MovieNode *node)
{
    int c =  1;             //Node itself should be counted
    if (node ==NULL)
        return 0;
    else
    {
        c += countNodes(node->left);//sum nodes on left
        c += countNodes(node->right);//sum nodes on the right
        return c;
    }
}

void printLevelNodesHelper(MovieNode *node , int k)  
{  
    if(node == NULL)  
        return;  
    if( k == 0 )  
    {  
        cout<< "Movie: " << node->title << " " << node->rating << endl;
        return;  
    }  
    else
    {  
        printLevelNodesHelper( node->left, k - 1 ) ;  
        printLevelNodesHelper( node->right, k - 1 ) ;  
    }  
} 


//--------------------------------
// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  root = NULL; 
}

MovieTree::~MovieTree() {
  //write your code
}

void MovieTree::printMovieInventory() {
    if (root == NULL)
    {
        cout<<"Tree is Empty. Cannot print"<<endl; 
        return;
    }
    printTreeHelper(root);
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) 
{
    root = addNodeHelper(root, ranking, title, year, rating);
    //cout<<title<<" has been added"<<endl;
}

void MovieTree::findMovie(string title) {
    MovieNode* node = searchKeyHelper(root, title);
    if(node != NULL) {
        cout<<"Movie Info:"<<endl;
        cout<<"=================="<<endl;
        cout<<"Ranking:"<< node->ranking << endl;
        cout<<"Title  :"<< node->title << endl;
        cout<<"Year   :"<< node->year << endl;
        cout<<"rating :"<< node->rating <<endl;
        return;
    }
    else
    {
        cout <<"Movie not found." <<endl;
        return;
    }
}

void MovieTree::queryMovies(float rating, int year) {
    if (root == NULL)
    {
        cout<< "Tree is Empty. Cannot query Movies" <<endl;
        return;
    }
    cout <<"Movies that came out after "<< year<< " with rating at least "<< rating << ":" << endl;
    queryMoviesHelper(root, rating, year);
}

void MovieTree::averageRating() {
    if(root == NULL)
    {
        cout << "Average rating:0.0" << endl;
        return;
    }
    int c = countNodes(root);
    //cout<<"total count " << c << endl;
    float sum = sumRatings(root);
    //cout<<"total rating " << sum << endl;
    float average = sum/(float(c));
    cout << "Average rating:" << average << endl;

}

void MovieTree::printLevelNodes(int level) {
  printLevelNodesHelper(root, level);
}





//-------------------------------------------------------------------

//#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Query movies"<< endl;
    cout << "3. Print the inventory"<< endl;
    cout << "4. Average Rating of movies"<< endl;
    cout << "5. Print Movies at Distance k" << endl;
    cout << "6. Quit"<< endl;
}
//int main(int argc, char** argv) {
int main() {
    

  
    int input;

    // Tree
    MovieTree* tree = new MovieTree();

    //ifstream iFile(argv[1]);
    ifstream iFile("Movies.csv");
    string line;

    // Variables for each line
    int ranking;
    int year;
    float rating;
    string title;

    // File IO
    while(getline(iFile, line)) {
        stringstream ss(line);
        string field;

        int counter = 0;
        while(getline(ss, field, ',')) {
            if (counter == 0)
                ranking = stoi(field);
            else if (counter == 1)
                title = field;
            else if (counter == 2)
                year = stoi(field);
            else if (counter == 3)
                rating = stof(field);
            counter++;
        }
        //cout<<ranking << " " <<title<<" "<<year<<" "<<rating<<endl;
        tree->addMovieNode(ranking, title, year, rating);
    }
    tree->printMovieInventory();
    tree->findMovie("Forrest Gump1");
    tree->averageRating();
    tree->queryMovies(7.0, 1987);
    tree->printLevelNodes(4);

    
    /*
    cin >> input;

    while (1) {
        if (input == 1) {
            string movie_title;
            cout << "Enter title:" << endl;
            cin.ignore();
            getline(cin, movie_title);
            tree->findMovie(movie_title);
        }
        else if (input == 2){
            float query_rating;
            int query_year;
            cout << "Enter minimum rating:" << endl;
            cin.ignore();
            cin >> query_rating;
            cout << "Enter minimum year:" << endl;
            cin.ignore();
            cin >> query_year;
            tree->queryMovies(query_rating, query_year);

        }
        else if (input == 3){
            tree->printMovieInventory();
        }
        else if (input == 4){
            tree->averageRating();
        }
        else if (input == 5){
            int level_k;
            cout << "Enter Level k: " << endl;
            cin.ignore();
            cin >> level_k;
            tree->printLevelNodes(level_k);
        }
        else if (input == 6){
            cout << "Goodbye!" << endl;
            break;
        }
        displayMenu();
        cin >> input;
    } */
    return 0;
}
