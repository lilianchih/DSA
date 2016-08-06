//
//  spell_check.cpp
//  
//
//  Created by Liang-Ying Chih on 2016/5/14.
//
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

void ed1(vector<string> *possible, const string &misspelled)
{
    for(int i=0; i<misspelled.length()+1; i++){
        for(int j=0; j<26; j++){
            char c = 97 + j;
            string temp = misspelled;
            temp.insert(i, 1, c);
            
                possible->push_back(temp);
        }
    }
    for(int i=0; i<misspelled.length(); i++){
        string temp = misspelled;
        temp.erase(i, 1);
        
            possible->push_back(temp);
    }
    for(int i=0; i<misspelled.length(); i++){
        for(int j=0; j<26; j++){
            char c = 97 + j;
            string temp = misspelled;
            temp[i] = c;
            
                possible->push_back(temp);        }
    }
    for(int i=0; i<misspelled.length()-1; i++){
        string temp = misspelled;
        char c = temp[i];
        temp[i] = temp[i+1];
        temp[i+1] = c;
        
            possible->push_back(temp);
    }

}

int main()
{
    unordered_set<string> dict;
    ifstream fin;
    fin.open("/tmp2/dsa2016_hw5/cmudict-0.7b");
    if(!fin.is_open())
        cout<<"Fail to open input file!"<<endl;
    // **********CONSTRUCT DICTIONARY**********
    else{
        string firstWord;
        int n = 0;
        while (fin >> firstWord)
        {
            if(n >= 126){
                
                for(int i=0; i<firstWord.length(); i++)
                    firstWord[i] = tolower(firstWord[i]);
                
               
                dict.insert(firstWord);
            }
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            n++;
        }
    }
    
    // **********INPUT WORDS**********
    string firstWord2;
    while (cin >> firstWord2)
    {
        cout<<firstWord2<<" ==>";
        
        if(dict.find(firstWord2) != dict.end())
            cout<<" OK"<<endl;
        else{
            vector<string> possible1, possible2;
            
            ed1(&possible1, firstWord2);
            for(int i=0; i<possible1.size(); i++)
                ed1(&possible2, possible1[i]);
            set<string> print;
            for(int i=0; i<possible2.size(); i++){
                if(dict.find(possible2[i]) != dict.end())
                    print.insert(possible2[i]);
            }
           
            if(print.size() == 0)
                cout<<" NONE";
            else{
                for(set<string>::iterator it = print.begin(); it != print.end(); it++)
                    cout<<" "<<*it;
            }
            cout<<endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


}


