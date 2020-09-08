#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"

using namespace std;

TreeNode* createNode(char firstLetter, int ranking, string title, int year, float rating, TreeNode* parentNode)
{
    TreeNode* newNode = new TreeNode();
    newNode->titleChar = firstLetter;
    newNode->parent = parentNode;
    LLMovieNode* movieNode = new LLMovieNode(ranking, title, year, rating);
    newNode->head = movieNode;
    //cout<< "first movie: " << movieNode->title <<endl;
    return newNode;
}

TreeNode* addMovieHelper(TreeNode* currNode, int ranking, string title, int year, float rating, TreeNode* parentNode)
{
    //add tree node if it does not exist. If it exists, add movie to the linked list for the treenode
    if(currNode == NULL){
        return createNode(title[0], ranking, title, year, rating, parentNode);
    }
    else if(title[0] > currNode->titleChar){
        currNode->rightChild = addMovieHelper(currNode->rightChild, ranking, title, year, rating, currNode);
    }
    else if(title[0] < currNode->titleChar){
        currNode->leftChild = addMovieHelper(currNode->leftChild, ranking, title, year, rating, currNode);
    }
    return currNode;
}

void printMovies(LLMovieNode* head) {
    //cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    LLMovieNode* ptr = head;

    if (ptr == NULL)
        cout << "nothing in path" << endl;
    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr->next != NULL)
        {
            cout << " >> "<<ptr->title << " " << ptr->rating <<endl;
            ptr = ptr->next;
        }
        cout << " >> " << ptr->title << " " << ptr->rating << endl;
        //cout << "NULL" << endl;
    }
    //cout << "===" << endl;
}

void printMovieInventoryHelper(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	printMovieInventoryHelper(root->leftChild);
	
	if (root->head != NULL)
	{
    	cout<<"Movies starting with letter: "<< root->titleChar<<endl; 
    	LLMovieNode* m = root->head;
    	printMovies(m);
	}
	
	printMovieInventoryHelper(root->rightChild);
}



void _grader_inorderTraversal(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}

TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
    {
        return curr;
    }
    else if(curr->titleChar == key)
    {
        return curr;
    }
    else if (curr->titleChar > key) //earlier, it was curr->titleChar > key
    {
        return searchCharHelper(curr->leftChild, key);
    }
    else
    {
        return searchCharHelper(curr->rightChild, key);
    }
}

void addMovieToLinkedList(LLMovieNode* &head, int ranking, string title, int year, float rating) 
//Extremely important to pass the head pointer by reference (&head), otherwise the movie linked list will not update.
{
    //cout << "adding: " << title << endl;
    LLMovieNode *m = new LLMovieNode;
    LLMovieNode* ptr = head;
    m->ranking = ranking;
    m->title = title;
    m->year = year;
    m->rating = rating;
    
    //insert after head - but we need it sorted, so can't use it
    //m->next = head->next;
    //head->next = m;
    
    if (title < head->title)
    {
        m->next = head;
        head = m;
        return;
    }

	while(ptr->next != NULL && ptr->next->title < m->title)
		ptr = ptr->next;

	m->next = ptr->next;
	ptr->next = m;

}

TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

// This function deletes the Node with 'value' as it's key. This is to be called inside removeRange() function
// SILVER TODO Complete the implementation of this function
TreeNode* deleteTreeNodeHelper(TreeNode * currNode, char value)
{
  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->titleChar)
  {
    currNode->leftChild = deleteTreeNodeHelper(currNode->leftChild, value);
  }
  else if(value > currNode->titleChar)
  {
    currNode->rightChild = deleteTreeNodeHelper(currNode->rightChild, value);
  }
  // We found the node with the value
  else
  {
    // Case : No child
    if(currNode->leftChild == NULL && currNode->rightChild == NULL)
    {
        delete(currNode);
        currNode = NULL;
    }
    // Case : Only right child
    else if(currNode->leftChild == NULL)
    {
        TreeNode* temp = currNode->rightChild; 
        temp->parent = currNode->parent; 
        if (currNode->parent != NULL) {
            if (temp->titleChar < currNode->parent->titleChar) {
                currNode->parent->leftChild = temp;
            } else {
                currNode->parent->rightChild = temp;
            }
        }
        delete(currNode);
        currNode = temp; 
        return currNode;
    }
    // Case : Only left child
    else if(currNode->rightChild == NULL)
    {
        TreeNode* temp = currNode->leftChild;
        temp->parent = currNode->parent;
        if (currNode->parent != NULL) {
            if (temp->titleChar < currNode->parent->titleChar) {
                currNode->parent->leftChild = temp;
            } else {
                currNode->parent->rightChild = temp;
            }
        }
        delete(currNode);
        currNode = temp;
        return currNode;

    }
    // Case: Both left and right child
    else
    {
        ///Replace with Minimum from right subtree
        TreeNode* temp = getMinValueNode(currNode->rightChild);
        char data = temp->titleChar; 
        currNode->titleChar = data;
        LLMovieNode* m = temp->head;
        currNode->head = m;
        currNode->rightChild = deleteTreeNodeHelper(currNode->rightChild, data);


    }

  }
return currNode;
}

void deleteMovieLinkedList(LLMovieNode* &head, string title) {
    //traverse and find the prev and curr
    //curr = movie title passed that needs to be deleted
    //prev->next = curr->next
    //free up curr
    if(head == NULL)
    {
        return;
    }
    if(head->title == title) //first node is dropped
    {
        LLMovieNode* firstNode = head;
        head = head -> next;
        free(firstNode);
        return;
    }
    LLMovieNode* curr = head; 
    LLMovieNode* prev;
    bool isFound = false;
    while (curr != NULL && curr->title != title)
    {
        prev = curr;//prev = head;
        curr = curr->next;
    }
    if(curr == NULL) //it reached the last node and did not find the movie
    {
        cout<<"Movie: " <<title<<" not found, cannot delete."<<endl;
        return;
    }
    
    prev->next = curr->next;
    free(curr);
    return;
    
}
void destroyNode(TreeNode *currNode){
    if(currNode!=NULL)
    {
        destroyNode(currNode->leftChild);
        destroyNode(currNode->rightChild);
        
        //Get the linked list of movies and delete them for a given tree node
        LLMovieNode* curr = currNode->head; 
        LLMovieNode* temp;
        while (curr != NULL)
        {
            temp = curr;
            curr = curr->next;
            //cout<<"deleting LL node " << temp->title<<endl;
            delete temp;
            temp = NULL;
        }
        //cout<<"deleting tree node " << currNode->titleChar<<endl;
        delete currNode;
        currNode = NULL;
    }
 }
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

MovieTree::~MovieTree()
{
    destroyNode(root);
}

void MovieTree::printMovieInventory()
{
    printMovieInventoryHelper(root);
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    LLMovieNode* movieLLNode;
    char c = title[0];
    TreeNode* treeNode;
    treeNode = searchChar(c);
    if (treeNode == NULL) {
        root = addMovieHelper(root, ranking, title, year, rating, NULL); //NULL is the parent of root
    }
    else
    {
        //treeNode exists. Update the linked list of movies for this node
        addMovieToLinkedList(treeNode->head, ranking, title, year, rating);
    }
}

void MovieTree::deleteMovie(std::string title)
{
    if (root == NULL)
    {
        cout<<"Movie: " <<title<<" not found, cannot delete."<<endl;
        return;
    }
    LLMovieNode* movieLLNode;
    char c = title[0];
    TreeNode* treeNode;
    treeNode = searchChar(c);
    deleteMovieLinkedList(treeNode->head, title);
    if(treeNode->head == NULL)
    {
        TreeNode* tn = deleteTreeNodeHelper(treeNode, c);
        if (treeNode == root){
            root = tn;
        }
    }
}

void MovieTree::leftRotation(TreeNode* curr)
{
    
    TreeNode* x = curr;
    TreeNode* y = x->rightChild;
    TreeNode* yl = y->leftChild;
    
    if(x->rightChild == NULL)
    {
        return;
    }
    if (curr == root)
    {
        //cout<<"We are at the root" <<endl;
        x->rightChild = yl;
        y->leftChild = x;
        x->parent = y;
        y->parent = NULL;
        root = y;
        return;
    }
    
    //rotate
    TreeNode* xp = x->parent;
    x->rightChild = yl;
    y->leftChild = x;
    x->parent = y;
    y->parent = xp;
    if (y->titleChar < xp->titleChar)
    {
        xp->leftChild = y;
    }
    else
    {
        xp->rightChild = y;
    }
    
    return;

}

void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}

TreeNode* MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}


// ------------------------- copy main.driver here ------//

static const char *USAGE = " [filename]\n\
\tread movies from filename and build an interactive bst";

//int main(int argc, char *argv[])
int main()
{
	ifstream dataFile;
	string dataLine;

	MovieTree movies;

	//if (argc != 2)
	//{
	//	cerr << argv[0] << USAGE << endl;
	//	return 1;
	//}

	//dataFile.open(argv[1]);
	dataFile.open("Movies3.csv");

	if (!dataFile.is_open())
	{
		//cerr << "Could not open " << argv[1] << " for reading!" << endl;
		cout<<"could not open file"<<endl;
		return 2;
	}

	while (getline(dataFile, dataLine))
	{
		int ranking, releaseYear;
    	float rating;
		string title;
		string datum;
		stringstream dataStream(dataLine);

		// ranking
		getline(dataStream, datum, ',');
		ranking = stoi(datum);

		// title
		getline(dataStream, title, ',');
		// cout << "Adding: " << title << endl;

		// releaseYear
		getline(dataStream, datum, ',');
		releaseYear = stoi(datum);

		// rating
		getline(dataStream, datum, ',');
		rating = stof(datum);

		movies.addMovie(ranking, title, releaseYear, rating);
	}
	
	//movies.inorderTraversal();
	movies.printMovieInventory();
	
	//movies.deleteMovie("Taxi to the Dark Side"); 
	//movies.deleteMovie("Hands on a Hardbody"); 
	//movies.deleteMovie("Down from the Mountain"); 
	//movies.deleteMovie("Dogtown and Z-Boys"); 
	//delete 3 movies
	//movies.deleteMovie("Down from the Mountain");
	//movies.deleteMovie("Dancin' Outlaw");
	//movies.deleteMovie("Dogtown and Z-Boys");
	
    movies.deleteMovie("Gladiator");
    movies.deleteMovie("The Matrix");
    
    
    //movies.leftRotation(treeNode);
	//movies.inorderTraversal();
	movies.printMovieInventory();
	
	
	cout <<"done!"<<endl;


	return 0;
}