#include <iostream>
#include "TST.h"

using namespace std;

//lookup hello, insert goodbye, delete yesterday, insert hello, delete goodbye, range_search band to cat



int main(int argc, char* argv[]){
    TST t1;
    

    for(int i= 0; i< argc; i++){

        if(string(argv[i]) == "lookup"){
            
            if(t1.lookup(argv[i+1]) == 0){
                cout<<string(argv[i+1]) + " not found\n";
                ++i;
            } else {
                cout<<string(argv[i+1]) + " found, count = "+ to_string(t1.lookup(argv[i+1]))+ "\n";
                ++i;
            }

        }

        if(string(argv[i]) == "insert"){
            string s = to_string(t1.insert(string(argv[i+1])));
            cout<<string(argv[i+1]) + " inserted, new count = " + s + "\n";
            i = i+1;
        }
        
        if(string(argv[i]) == "delete"){
            int temp = t1.remove(argv[i+1]);
            if(temp == -1){
                ++i;
            } else if (temp > 0){
                cout<< string(argv[i+1]) + " deleted, new count = " + to_string(temp) + "\n";
            
            } else {
                cout<< string(argv[i+1]) + " deleted\n";
            }

        }
        
        if(string(argv[i]) == "range_search"){
            string word1 = string(argv[i+1]);
            string word2 = string(argv[i+3]);
            t1.search(word1,word2);
            i = i+3;

        }


    }

    return 0;
}




