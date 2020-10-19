#include <iostream>
#include <utility>
#include <string>


#ifndef TST_H
#define TST_H

using namespace std;



//things i want to ask, the functions are returning to console or just returning a string
//how to take inputs from argv
//Makefiles
//testbench?
//confirm the structure i made is correct

//getting impression from the report is that, the program will run, we type up "lookup" or "insert" or "delete" etc, and a following word/words and the program will return a string?

//Make sure to make executable as project1.out


class TST
 {
     public:

 
    //variables of the data type

    TST(); //constructor
    ~TST(); //destructor
    int lookup(string word); //searchs TST for a word
    int insert(string word); //inserts a word into TST


    int remove(string word); //remove a word from TST if count == 1, if not - 1;
    
    void search(string word1, string word2); //print out words that are in between word1 and word2


    struct Node {
        //2 pairs that are (word,count)
        pair <string, int> leftkey;
        pair <string, int> rightkey;

        Node *left, *mid, *right;

    };

    void printInOrder(Node *n); //print in order 
    int insert(string word, Node *n); //helper function
    int removeHARD(string word, Node *n); //helper function
    Node* lookup(string word, Node *n); //helper function
    void search(string word1, string word2, Node *n);//helper function 

    Node* getNode(string word, Node* n); //helper function that finds the Node
    void clear(Node* n); //recursive helper for deleting TST
    Node *root;




};



#endif