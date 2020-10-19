#include <iostream>
#include "TST.h"


#include <vector>

using namespace std;

//"lookup hello, insert goodbye, delete yesterday, insert hello, delete goodbye, range_search band to cat"




int main(int argc, char* argv[]){
    TST t1;
    vector<string> allwords;

    string words(argv[1]);
   
    
    string temp = "";
    for(int i = 0; i < words.size(); i++){
        if( words[i] == ' ' || words[i] == ','){
            
            if( temp != ""){
            allwords.push_back(temp);
            temp = "";
            }
        } else {
            temp = temp + words[i];

        }
        
    }
    allwords.push_back(temp);


   

    for(int i= 0; i< allwords.size() ; i++){

        if(string(allwords[i]) == "lookup"){
            
            if(t1.lookup(allwords[i+1]) == 0){
                cout<<string(allwords[i+1]) + " not found\n";
                ++i;
            } else {
                cout<<string(allwords[i+1]) + " found, count = "+ to_string(t1.lookup(allwords[i+1]))+ "\n";
                ++i;
            }

        }

        if(string(allwords[i]) == "insert"){
            string s = to_string(t1.insert(string(allwords[i+1])));
            cout<<string(allwords[i+1]) + " inserted, new count = " + s + "\n";
            i = i+1;
        }
        
        if(string(allwords[i]) == "delete"){
            int temp = t1.remove(allwords[i+1]);
            if(temp == -1){
                ++i;
            } else if (temp > 0){
                cout<< string(allwords[i+1]) + " deleted, new count = " + to_string(temp) + "\n";
            
            } else {
                cout<< string(allwords[i+1]) + " deleted\n";
            }

        }
        
        if(string(allwords[i]) == "range_search"){
            string word1 = string(allwords[i+1]);
            string word2 = string(allwords[i+3]);
            t1.search(word1,word2);
            i = i+3;

        }


    }

    return 0;
}




