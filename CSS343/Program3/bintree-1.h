//  bintree.hpp
//  Program2
//
//  Created by Jonathan Velazquez on 4/9/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//

#ifndef bintree_h
#define bintree_h
#include <iostream>

#include "nodedata.h"

class BinTree {
    
    friend ostream &operator<<( ostream &out, const  BinTree &rhs );
public:
    //Constructors
    BinTree( );
    BinTree( const BinTree &copy);
    
    //Destructor
    ~BinTree( );
    
    //Assignment operators
    BinTree &operator=( const BinTree &rhs );
    
    //Logical binary operators
    bool operator==( const BinTree &rhs ) const;
    bool operator!=( const BinTree &rhs ) const;
    
    //checks to see if the item is in the tree
    bool retrieve( const NodeData &, NodeData* & );
    
    //will get hight of the NodeData
    int getHeight( const NodeData &) const;
    
    // binary tree to array
    void bstreeToArray(NodeData* []);
    
    //array to binary tree
    void arrayToBSTree(NodeData* []);
    
    //insert an item to binary tree
    bool insert( NodeData* );
    
    void displaySideways() const;			// provided below, displays the tree sideways
    
    //makes the binary tree empty
    void makeEmpty();
  
    
    bool isEmpty() const; //ture if tree is empty, otherwise false;
    
    
private:
    
    
    struct BinTreeNode{
        
        NodeData* item;
        BinTreeNode *leftChild;
        BinTreeNode *rightChild;
    };
    BinTreeNode* root;
    
    // utility functions
    void outputHelper(ostream&, BinTreeNode *)const;
    
    void sideways(BinTreeNode*, int) const;			// provided below, helper for displaySideways()
    
    // helper for insert
    bool insertHelper(BinTreeNode *& , NodeData*);
    
    // helper for getHeight
    int getHeightHelper(BinTreeNode *, const NodeData&, int) const;
    
    // helper for the getHeighthelper
    int getHeightHelper(BinTreeNode*) const;
    //bool retrieve(BinTreeNode *&, const NodeData &, NodeData* &, bool &retVal );
    bool retrieveHelper(BinTreeNode *&, const NodeData &, NodeData* &, bool &retVal );
    
    //helper function for operator==
    bool equalityHelper(BinTreeNode *, BinTreeNode* )const;
    
    //helper funciton for assignment operator recursively
    void assignmentHelper(BinTreeNode*, BinTreeNode* &);
    
    //helper function for makeEmpty recursively
    void makeEmptyHelper(BinTreeNode *&);
    
    //helper function for bstreetoarray
    int bstreeToArrHelp(BinTreeNode *&,  NodeData**,int);
    
    //helper fucntion for arrayToBS recursively
    void arrayToBSTHelp(BinTreeNode*, int, int, NodeData**);         // Recursive build
    
    //BinTreeNode* copyHelp(const BinTreeNode*);
    
};

#endif /* bintree_hpp */
