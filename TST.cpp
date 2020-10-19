#include <iostream>
#include <utility>
#include <string>
#include "TST.h"

using namespace std;

TST::TST() : root(0) { } //constructor

void TST::clear(Node *n){
    if(n){
        clear(n->left);
        clear(n->mid);
        clear(n->right);
        delete n;

    }


}



TST::~TST()
{
//
 clear(root);

} //destructor



int TST::lookup(string word)
{

    if( !lookup(word, root)){
        return 0;
    } else {
        if( lookup(word, root)->leftkey.first == word){
            return lookup(word, root)->leftkey.second;
        } else{
            return lookup(word, root)->rightkey.second;
        }

    }

    
return 0;
} //searchs TST for a word

TST::Node* TST::lookup(string word, Node *n)
{
    //if n doesn't exist
    if( !n){ return NULL; }
    
    //if leftkey matches word
    if( n->leftkey.first == word ){
        return n;
    }
    //if rightkey matches word
    if(n->rightkey.first == word){
        return n;
    }
    //if word is less than left key
    if( word.compare(n->leftkey.first) < 0){
        return lookup(word, n->left);
    //if word is greater than right key
    } else if (word.compare(n->rightkey.first) > 0 ) {
        return lookup(word, n->right);
    } else {
    //if word is greater than left key and less than right key
        return lookup(word, n->mid);

    }

}
 
int TST::insert(string word)
{
    //if root doesn't exist
    if (!root){
        root = new Node();
        root->rightkey.first = word;
        ++root->rightkey.second;
        return 1;
    }
    return insert(word, root);


} //inserts a word into TST

int TST::insert(string word, Node *n)
{
    //if word is already in TST and is leftkey
    if(word.compare(n->leftkey.first) == 0){
        ++n->leftkey.second;
        return n->leftkey.second;
    }    
    //if word is already in TST and is rightkey
    if(word.compare(n->rightkey.first) == 0){
        ++n->rightkey.second;
        return n->rightkey.second;
    }

    //if the node's rightkey exist but the leftkey does not
    if( n->leftkey.first == "" && (n->rightkey.first != "") ) {
        //if word is greater than rightkey
        if( word.compare(n->rightkey.first) > 0){
            if( !n->right){
                n->right = new Node();
                n->right->rightkey.first = word;
                ++n->right->rightkey.second;
                return 1;
            } else {
                return insert(word, n->right);

            }
        } else {
            //If word is less than right key

            //If there are no left/mid child, assign word to leftkey
            if( !(n->mid) && !(n->left)){
                n->leftkey.first = word;
                ++n->leftkey.second;
                return 1;
            }

            //if mid doesn't exist and left does, either set leftkey to word or insert in left tree
            if( !n->mid){
                if( word.compare(n->left->rightkey.first) > 0){
                    n->leftkey.first = word;
                    ++n->leftkey.second;
                    return 1;
                } else {
                    insert(word, n->left);
                }
            } else {
            //If Mid exist and left doesn't
            //Either set leftkey to word or insert into mid tree
                if( word.compare(n->mid->rightkey.first) < 0){
                    n->leftkey.first = word;
                    ++n->leftkey.second;
                    return 1;
                } else {
                    insert(word, n->mid);
                }

            }


        }
       
    }

    //if word is greater than right key
    if ( word.compare(n->rightkey.first) > 0){
        //if right node does exist
        if(n->right){
            return insert(word, n->right);
        } else {
            //if right node doesn't exist
            n->right = new Node();
            n->right->rightkey.first = word;
            ++n->right->rightkey.second;
            return 1;
        }    

    //if word is less than left key
    } else if (word.compare(n->leftkey.first) < 0){
        //check if left node exists
        if(n->left){
            return insert(word, n->left);
        } else {
            //if left node doesn't exist
            n->left = new Node();
            n->left->rightkey.first = word;
            ++n->left->rightkey.second;
            return 1;

        }
    
     //word is greater than leftkey and less than rightkey   
    } else {                                   
        //if mid node does exist
        if (n->mid){
            return insert(word, n->mid);
        } else {
            //if mid node doesn't exist
            n->mid = new Node();
            n->mid->rightkey.first = word;
            ++n->mid->rightkey.second;
            
            return 1;
        }

    }



    return false;
}

int TST::removeHARD(string word, Node *n){
/*2)Removing node w no children
    Removing 1 key
        If it is right key, move left key over to right
        If it is left key, do nothing
    Removing last key
        Delete node

3)Removing node with children
    Removing 1 key
        Erase the key, if it is right key, shift left key over to right
        If it is left key, do nothing
    Removing last key
    Node* getNode(word,root);
*/
    Node* x = getNode(word,root);

    //if deleting only 1 of 2 keys
    if( (word == x->leftkey.first && (x->rightkey.first != "")) || (word == x->rightkey.first && (x->leftkey.first != "")) ){
        //if deleting the left key
        if(word == x->leftkey.first){
            //go into mid and farthest left and replace that left key w the deleted key
            if(x->mid){
                Node* temp = x->mid;
                while(temp->left){
                    temp = temp->left;
                }

                if(temp->leftkey.first != ""){
                    x->leftkey.first = temp->leftkey.first;
                    x->leftkey.second = temp->leftkey.second;
                    temp->leftkey.first = "";
                    temp->leftkey.second = 0;
                    return 0;
                } else {
                    x->leftkey.first = temp->rightkey.first;
                    x->leftkey.second = temp->rightkey.second;
                    removeHARD(temp->rightkey.first,temp);
                    
                }
            } else {
                x->leftkey.first = "";
                x->leftkey.second = 0;
                return 0;
            }
        } else{
            //if deleting right key
            //if mid exists, go through right tree and keep going right
            if(x->mid){
                Node* temp = x->mid;
                while(temp->right){
                    temp = temp->right;
                }

                if(temp->leftkey.first != ""){
                    x->rightkey.first = temp->leftkey.first;
                    x->rightkey.second = temp->leftkey.second;
                    temp->leftkey.first = "";
                    temp->leftkey.second = 0;
                    return 0;
                } else {
                    x->rightkey.first = temp->rightkey.first;
                    x->rightkey.second = temp->rightkey.second;
                    removeHARD(temp->rightkey.first,temp);
                }

            } else {
                //if mid doesn't exist
                //replace right key with left key, let left key be 0
                x->rightkey.first = x->leftkey.first;
                x->rightkey.second = x->leftkey.second;

                x->leftkey.first = "";
                x->leftkey.second = 0;
                return 0;
            }

        }

    }
    
    //if deleting last key in node
     if( (word == x->leftkey.first && (x->rightkey.first == "")) || (word == x->rightkey.first && (x->leftkey.first == "")) ){
            delete x;
            return 0;
    }


    


    return 0;

}









int TST::remove(string word)
{

    if(!getNode(word, root)){
        return -1;
    }
    //CASEs 1
    if(getNode(word,root)->leftkey.first == word){
        if(getNode(word,root)->leftkey.second > 1){
            --getNode(word,root)->leftkey.second;
            return getNode(word,root)->leftkey.second;
        }
    }

    if(getNode(word,root)->rightkey.first == word){
        if(getNode(word,root)->rightkey.second > 1){
            --getNode(word,root)->rightkey.second;
            return getNode(word,root)->rightkey.second;
        }
    }

    return removeHARD(word,root);


} //remove a word from TST if count == 1, if not -1;




TST::Node* TST::getNode(string word, Node *n){
    if(!n){
        return NULL;
    }

    if( (n->leftkey.first == word ) || (n-> rightkey.first == word) ){
        return n;
    }

    if( word.compare(n->rightkey.first) > 0){
        return getNode(word, n->right);
    } else if ( word.compare(n->leftkey.first) < 0){
        return getNode(word, n->left);
    } else {
        return getNode(word, n->mid);
    }

}











void TST::search(string word1, string word2){

return search(word1, word2, root);

}

void TST::search(string word1, string word2, Node *n){

    if(n){
        search(word1, word2, n->left);
        if(word1.compare(n->leftkey.first) < 0 || word1.compare(n->leftkey.first) == 0){
            if(n->leftkey.first != "")            
            cout<<n->leftkey.first + "\n";
        } 
        search(word1, word2, n->mid);
        if(word2.compare(n->rightkey.first) > 0 || word2.compare(n->rightkey.first) == 0){
        if(n->rightkey.first != "")              
        cout<<n->rightkey.first + "\n";
        }    
        search(word1, word2, n->right);
    }

}



void TST::printInOrder(Node *n){
    if(n){
        printInOrder(n->left);
        if(n->leftkey.first != "")
        cout<<n->leftkey.first + "\n";
        printInOrder(n->mid);
        if(n->rightkey.first != "")        
        cout<<n->rightkey.first + "\n";
        printInOrder(n->right);

    }


}

