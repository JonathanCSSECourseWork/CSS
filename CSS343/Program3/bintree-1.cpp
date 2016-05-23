//
//  bintree.cpp
//  Program2
//
//  Created by Jonathan Velazquez on 4/9/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//
//Purpose- The purpose of this program is to create a binary tree class using a NodeData class.

#include "bintree.h"


/* ------------------------------------operator<<-----------------------------------------------
 
 Description
 
 operator<< : // Overloaded <<: prints the Binary tree in order
 
 precondition: string or object must exist
 postconditions: the output will be stored in out
 
 --------------------------------------------------------------------------------------------*/
ostream &operator<<(ostream &out,  const BinTree &rhs ){
    
    
    rhs.outputHelper(out, rhs.root);
    
    return out<<endl;
}


/* ------------------------------------outputHelper-----------------------------------------------
 
 Description
 
 ouputHelper : // will help the operator<< to walk through the tree recursively
 
 precondition: string or object must exist
 postconditions: the output will be stored in out
 
 --------------------------------------------------------------------------------------------*/
void BinTree::outputHelper(ostream &output, BinTreeNode *root) const{
    
    if(root->leftChild!=NULL){                      //walking through the left side in order
        outputHelper(output, root->leftChild);
    }
    
    output<< *root->item <<" ";
    
    if(root->rightChild!=NULL){               //walking through the right side
        outputHelper(output, root->rightChild);
    }
    if(root->leftChild==NULL&& root->rightChild==NULL){
        // delete root;
        //  root = NULL;
    }
}


//Constructors

/* ------------------------------------BinTree Construstor-----------------------------------------------
 
 Description
 
 BinTree: Binary Trees root is initialized to NULL;
 
 Preconditions: Driver must creat a empty BinTree
 
 Postconditions: Empty Binary Tree has been created.
 
 ------------------------------------------------------------------------------------------------------*/


BinTree::BinTree() {
    
    root = NULL; //initializing the root Node to NULL;
    
    
}


/* ------------------------------------Copy Constructor-----------------------------------------------
 
 Description
 
 BinTree: the purpose of this constructor is to copy a BinTree without any memory leaks
 
 Preconditions: a BinTree object should exist
 
 
 postconditions: a copy of the original will now be available with the same values as input c
 
 ------------------------------------------------------------------------------------------------------*/

BinTree::BinTree( const BinTree &c){
    
    root = NULL; //initializing the root Node to NULL;
    
    *this = c; //setting *this = c using the overloaded Assignment operator to accomplish this
    
    
}
/* ------------------------------------BinaryTree destructor-----------------------------------------------
 
 Description
 
 Binary Tree: to delete a Binary Tree u
 
 Preconditions:none
 
 postconditions: the Binary Tree will delete using the makeEmpty() function
 
 --------------------------------------------------------------------------------------------*/
BinTree::~BinTree( ){
    makeEmpty();
    
}

// Assignment operators

/* ------------------------------------operator=-----------------------------------------------
 
 Description
 
 operator=: will assign two one Binary Tree to the other
 preconditions: two Binary Trees must exist
 
 postconditions: the assigned Binary Tree will be returned
 
 --------------------------------------------------------------------------------------------*/
BinTree& BinTree::operator=( const BinTree &rhs ){
    
    if (*this == rhs) //if they are equal nothing will change
    {
        return *this;
    }
    
    this->makeEmpty();
    
    assignmentHelper(rhs.root, this->root);
    
    return *this;
    
}
/* ------------------------------------assignmentHelper-----------------------------------------------
 
 Description
 
 assignmentHelper: will help out the operator= to recursiveley assign the data the other Binary Tree
 preconditions: two Binary Trees must exist
 
 postconditions: the assigned Binary Tree will be returned
 
 --------------------------------------------------------------------------------------------*/

void BinTree::assignmentHelper(BinTreeNode* rhs, BinTreeNode* &lhs){
    
    if (rhs != NULL)
    {
        
        lhs = new BinTreeNode;
        NodeData *temp = new NodeData(*rhs->item);
        lhs->item = temp;
        
        assignmentHelper(rhs->leftChild, lhs->leftChild);//walking through the both binary trees
        assignmentHelper(rhs->rightChild, lhs->rightChild); // walking through both binary trees
    }
    else
    {
        lhs = NULL;
    }
    
}


//Logical binary operators
/* ------------------------------------operator==-----------------------------------------------
 
 Description
 
 operator==:compares two Binary Trees to see if they are equal
 
 preconditions:  two Binary Trees will be compared
 postconditions: true or false will be returned
 
 --------------------------------------------------------------------------------------------*/
bool BinTree::operator==(const BinTree &rhs) const
{
    if (this->root == NULL && rhs.root == NULL)
    {
        return true; //checks to see if both are empty
    }
    else
    {
        return equalityHelper(this->root, rhs.root);
    }
}

/* ------------------------------------equalityHelper-----------------------------------------------
 
 Description
 
 equalityHelper:helps compare two binary tree recursively
 
 preconditions:  two Binary Trees will be compared
 postconditions: true or false will be returned
 
 --------------------------------------------------------------------------------------------*/


bool BinTree::equalityHelper(BinTreeNode* lhs, BinTreeNode* rhs) const
{
    if (lhs == NULL && rhs == NULL)
    {
        return true;    //checks if NULL then returns tree because they are equal
    }
    
    if (lhs == NULL || rhs == NULL)
    {
        return false; // checks to see if one is NULL then returns false
    }
    
    if (*lhs->item == *rhs->item && lhs->leftChild == NULL && rhs->leftChild == NULL && lhs->rightChild == NULL && rhs->rightChild == NULL)
    {
        return true;
    }
    
    
    return (*lhs->item == *rhs->item && equalityHelper(lhs->leftChild, rhs->leftChild) && equalityHelper(lhs->rightChild, rhs->rightChild)); //comparying lhs item to the rhs item and calling it again to make sure it is not in the tree
}

/* ------------------------------------Operator!=-----------------------------------------------
 
 Description
 
 Operator!=: will check if two Polynomials are not equal
 preconditions:  two polynomials will be added together
 
 
 postconditions: true or false will be returned
 
 
 --------------------------------------------------------------------------------------------*/

bool BinTree::operator!=( const BinTree &rhs ) const
{
    return !(*this==rhs); //using overloaded operator== to check if not equal
    
}

/* ------------------------------------Retrieve-----------------------------------------------
 
 Description
 
 Retrieve: will check if the item is in the Binary Tree
 preconditions:  BinaryTree must exist
 
 
 postconditions: true or false will be returned
 
 
 --------------------------------------------------------------------------------------------*/

bool BinTree::retrieve( const NodeData & a, NodeData* & b)
{
    bool retVal = false; //initializine the retval
    
    retVal= retrieveHelper(root, a, b, retVal); //calling helper function to recursively walk through the tree
    return retVal;
    
}

/* ------------------------------------RetrieveHelper-----------------------------------------------
 
 Description
 
 RetrieveHelper: will recursively walk through the Binary Tree and check to see if the input item does exist
 it will return false if non existant or true of it is found
 preconditions:  a binary tree must be created prior to calling this function
 
 
 postconditions: true or false will be returned
 
 
 --------------------------------------------------------------------------------------------*/

bool BinTree::retrieveHelper(BinTreeNode *&root, const NodeData & a, NodeData* & b, bool& c){
    
    if(root->leftChild!=NULL){
        retrieveHelper(root->leftChild, a, b, c); //recursively walking through the left
    }
    if(*root->item==a){  //checks to see of the root item is the same as the target item
        
        
        b = root->item; //return point set to NodeData
        c= true; // if found it will return true
    }
    
    if(root->rightChild!=NULL){
        retrieveHelper(root->rightChild, a, b, c); //recursively walking through the right
    }
    return c; //c wil be wither true or false and returned
}

/* ------------------------------------getHeight-----------------------------------------------
 
 Description
 
 getHeight: will check if the item is in the Binary Tree
 preconditions:  BinaryTree must exist
 
 
 postconditions: if found the height of the input NodeData will be returned. If not found 0 will be returned
 
 
 --------------------------------------------------------------------------------------------*/

int BinTree::getHeight(const NodeData &key) const
{
    int level = 0; //initialize the level counter
    
    
    level= getHeightHelper(this->root, key, level); //setting level to the the height of the helper function
    
    return level; //level will be returned
}
/* ------------------------------------getHeightHelper-----------------------------------------------
 
 Description
 
 getHeightHelper: will check if the item is in the Binary Tree
 preconditions:  BinaryTree must exist
 
 
 postconditions: if found the height of the input NodeData will be returned. If not found 0 will be returned
 
 
 --------------------------------------------------------------------------------------------*/
int BinTree::getHeightHelper( BinTreeNode * current,const NodeData &key, int level) const
{
    
    
    if (current == NULL)
    {
        return 0;   //when the node is empty there is nothing there so we return 0
    }
    else if (*current->item == key) //if the item is found we will walk through an adition
    {
        
        return getHeightHelper(current);   // node found then we call an additinal helper method
    }
    else
    {
        int left = getHeightHelper( current->leftChild, key,level);  // search left
        int right = getHeightHelper( current->rightChild, key, level);    // search right
        
        if(left>right){
            level = left;
            return level;
            
        }else{
            level = right;
            return level; //return the level
        }
    }
    
    
}
/* ------------------------------------getHeightHelper-----------------------------------------------
 
 Description
 
 getHeightHelper: will help the helper of the getHeight
 preconditions:  BinaryTree must exist
 
 
 postconditions: if found the height of the input NodeData will be returned. If not found 0 will be returned
 
 
 --------------------------------------------------------------------------------------------*/
int BinTree::getHeightHelper(BinTreeNode* current) const
{
    if (current == NULL)
    {
        return 0;   // have reached a leaf node
    }
    else
    {
        
        int left = getHeightHelper(current->leftChild);//go left
        int right = getHeightHelper(current->rightChild); //go right
        if(left>right){
            return 1+left;
        }else{
            return 1+right;
        }
    }
}

/* ------------------------------------bsTreeToArray-----------------------------------------------
 
 Description
 
 bsTreeToArray: will put all the items from the binary tree to the array
 preconditions:  BinaryTree must exist
 
 
 postconditions: putting all the items from the Binary Tree to an array
 
 
 --------------------------------------------------------------------------------------------*/

void BinTree::bstreeToArray(NodeData* Array[]){
    int start = 0;
    bstreeToArrHelp(root,Array, start ); //calling helper method to recursively walk through the tree
    
    makeEmpty(); //making sure to empty out the binary tree after inserting to the array
    
    
}

/* ------------------------------------bsTreeToArrayHelp-----------------------------------------------
 
 Description
 
 bsTreeToArrayHelp: will help bstreeToArray to walk through the binary tree to pull out the items
 preconditions:  BinaryTree must exist
 
 
 postconditions: putting all the items from the Binary Tree to an array recursively walking the tree
 
 
 --------------------------------------------------------------------------------------------*/

int BinTree::bstreeToArrHelp(BinTreeNode *& root, NodeData * array[], int low)
{
    
    //cout<<*root->item;
    
    //low++;
    if(root->leftChild!=NULL){    //walking through the left side recurviely
        low = bstreeToArrHelp(root->leftChild, array, low);
    }
    NodeData *temp;
    temp = root->item;
    root->item = NULL;
    
    array[low++] = temp; //inserting into the array in order
    temp = NULL;
    delete temp;
    if(root->rightChild!=NULL){ //walking through the right side recursively
        
        low= bstreeToArrHelp(root->rightChild, array, low);
    }
    
    return low;
}



/* ------------------------------------arrayToBSTree-----------------------------------------------
 
 Description
 
 arrayToBSTree: will put all the items from the array to the binary tree balanced
 preconditions:  array must exist
 
 
 postconditions: Binary tree will be filled
 
 
 --------------------------------------------------------------------------------------------*/


void BinTree::arrayToBSTree(NodeData* ndArray []){
    int size = 0;
    for (int i = 0 ; i<100; i++){
        if(ndArray[i]){             //checking size of array
            size++;
        }
        
        
    }
    // ensure we start with empty tree, then call recursive helper
    makeEmpty();
    
    
    arrayToBSTHelp(root, 0, size - 1, ndArray);
    
    // empty array (fill with NULLs) to make sure it is empty
    for (int i = 0; i < size; i++) {
        ndArray[i] = NULL;
    }
    
}
/* ------------------------------------arraytoBsTreeHelper-----------------------------------------------
 
 Description
 
 makeEmpty: will delete all the items from the binary tree and delete the items to prevent memory leaks
 preconditions:  BinTree must exist
 
 
 postconditions: Binary tree will filled
 
 
 --------------------------------------------------------------------------------------------*/
void BinTree::arrayToBSTHelp(BinTreeNode *root, int low, int high, NodeData* ndArray[])
{
    // base case
    if (low > high) {
        
        root = NULL;
    }
    
    else{
        int mid = (low + high) / 2; //will get mid data from array to make a balanced tree
        
        NodeData* temp; // temp NodeData pointer to insert
        temp = ndArray[mid];    // assigns mid element from array section to temp
        ndArray[mid] = NULL;    // NULLING Out the array element
        
        insert(temp);   // inserts NodeData int BST
        arrayToBSTHelp(root,  low, mid - 1,ndArray);    // The Left side of the balnced tree
        arrayToBSTHelp(root,  mid + 1, high, ndArray);   // Fill right side of the tree
    }
}

/* ------------------------------------insert-----------------------------------------------
 
 Description
 
 insert: add items to the binary tree by calling a helper method
 
 preconditions:  BinTree must exist
 
 
 postconditions: Binary tree will filled one by one
 
 
 --------------------------------------------------------------------------------------------*/
bool BinTree::insert( NodeData *newItem ){
    
    return insertHelper(root,newItem); //calls helper method
    
    
}
/* ------------------------------------insertHelper-----------------------------------------------
 
 Description
 
 insert: add items to the binary tree recursively
 
 preconditions:  BinTree must exist
 
 
 postconditions: Binary tree will filled one by one
 
 
 --------------------------------------------------------------------------------------------*/
bool BinTree::insertHelper(BinTreeNode *&root, NodeData *newItem){
    
    if(root==NULL){                 //when it is null we need to create a new node
        root = new BinTreeNode();
        
        root->item = newItem;
        root->leftChild = NULL;         //makes left child null
        root->rightChild=NULL;          //makes right child null
        
    }else if (*newItem<*root->item){            //if less then the item it will go left
        insertHelper(root->leftChild, newItem);
        
    }else if(*newItem>*root->item){             //if greater then the item it will go right
        insertHelper(root->rightChild,newItem);
        
    }else{
        return false;
    }
    
    return true;
    
}

/* ------------------------------------makeEmpty-----------------------------------------------
 
 Description
 
 makeEmpty: will delete all the items from the binary tree and delete the items to prevent memory leaks
 preconditions:  BinTree must exist
 
 
 postconditions: Binary tree will be emptied
 
 
 --------------------------------------------------------------------------------------------*/

void BinTree::makeEmpty(){
    //checkig to see if it is already empty
    if(root!=NULL){
        makeEmptyHelper(root);
    }
}

/* ------------------------------------makeEmptyHelper-----------------------------------------------
 
 Description
 
 makeEmptyHelper: will help the makeEmpty() to walk through the Binary tree and delete all the items recursively
 preconditions:  BinTree must exist
 
 
 postconditions: Binary tree will be emptied
 
 
 --------------------------------------------------------------------------------------------*/
void BinTree::makeEmptyHelper(BinTreeNode *&root){
    
    // recursive case
    
    if(root!=NULL)
    {
        if (root->leftChild) {                  //walkning through the left side and making it empty
        makeEmptyHelper(root->leftChild);
    }
        
        if (root->rightChild) {                 //walkign through the right side and making it empty
            makeEmptyHelper(root->rightChild);
        }
        delete root->item;                      //deleting to avaid memory leaks
        
        root->item = NULL;
        
        delete root;
        root=NULL;
        
    }
    
    
    
}

/* ------------------------------------isEmpty-----------------------------------------------
 
 Description
 
 isEmpty: checks to see if the binary is empty
 
 
 postconditions: true or false will be returned
 
 
 --------------------------------------------------------------------------------------------*/
bool BinTree::isEmpty() const
{
    if (this->root == NULL)
    {
        return true; //if its empty
    }
    
    return false;   //if its not empty
    
}
//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
    sideways(root, 0);
}
//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(BinTreeNode* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->rightChild, level);
        
        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }
        
        cout << *current->item << endl;        // display information of object
        sideways(current->leftChild, level);
    }
}
