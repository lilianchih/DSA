//
//  preposition.cpp
//  
//
//  Created by Liang-Ying Chih on 2016/6/12.
//
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, unsigned int> last1;
typedef unordered_map<string, last1 *> last2;
typedef unordered_map<string, last2 *> last3;
typedef unordered_map<string, last3 *> last4;
typedef unordered_map<string, last4 *> last5;

string prep[20] = {"about", "after", "at", "before", "between", "by", "down", "for", "from", "in", "near", "of", "on", "to", "since", "than", "under", "up", "with", "without"};

int *eda(vector< vector<string> > *possible, const vector<string> &original)
{
    int *count = new int[2];
    // insert
    for(int i=0; i<20; i++){
        for(int j=0; j<original.size()+1; j++){
            vector<string> temp;
            for(int k=0; k<original.size(); k++)
                temp.push_back(original[k]);
            temp.insert(temp.begin()+j, prep[i]);
            possible->push_back(temp);
        }
    }
    count[0] = possible->size();
    // insert & insert
    for(int i=0; i<original.size()+1; i++){
        for(int j=i; j<original.size()+1; j++){
            for(int l=0; l<20; l++){
                for(int h=0; h<20; h++){
                    vector<string> temp;
                    for(int k=0; k<original.size(); k++)
                        temp.push_back(original[k]);
                    temp.insert(temp.begin()+i, prep[l]);
                    temp.insert(temp.begin()+j+1, prep[h]);
                    possible->push_back(temp);
                }
            }
        }
    }
    count[1] = possible->size();
    return count;
}

int *edb1(vector< vector<string> > *possible, const vector<string> &original, const vector<int> &seque)
{
    int *count = new int[3];
    // delete
    for(int j=seque[0]; j<seque[0]+seque.size(); j++){
        vector<string> temp;
        for(int i=0; i<original.size(); i++)
            temp.push_back(original[i]);
        temp.erase(temp.begin()+j);
        possible->push_back(temp);
    }
    count[0] = possible->size();
    // substitute
    for(int j=seque[0]; j<seque[0]+seque.size(); j++){
        vector<string> temp;
        for(int k=0; k<original.size(); k++)
            temp.push_back(original[k]);
        for(int i=0; i<20; i++){
            temp[j] = prep[i];
            possible->push_back(temp);
            
        }
    }

    count[1] = possible->size();

    // insert
    for(int i=0; i<20; i++){
        for(int j=seque[0]; j<seque[0]+seque.size()+1; j++){
            vector<string> temp;
            for(int k=0; k<original.size(); k++)
                temp.push_back(original[k]);
            temp.insert(temp.begin()+j, prep[i]);
            possible->push_back(temp);
        }
    }
    count[2] = possible->size();
    return count;
}
int *edb2(vector< vector<string> > *possible, const vector<string> &original, const vector< vector<int> > &seque)
{
    int *count = new int[5];
    // delete & delete
    for(int i=seque[0][0]; i<seque[0][0]+seque[0].size(); i++){
        for(int j=seque[1][0]; j<seque[1][0]+seque[1].size(); j++){
            vector<string> temp;
            for(int k=0; k<original.size(); k++)
                temp.push_back(original[k]);
            temp.erase(temp.begin()+i);
            temp.erase(temp.begin()+j-1);
            possible->push_back(temp);
        }
    }
    count[0] = possible->size();
    // delete & substitute
    for(int i=seque[0][0]; i<seque[0][0]+seque[0].size(); i++){
        for(int j=seque[1][0]; j<seque[1][0]+seque[1].size(); j++){
            for(int k=0; k<20; k++){
                vector<string> temp;
                for(int l=0; l<original.size(); l++)
                    temp.push_back(original[l]);
                temp.erase(temp.begin()+i);
                temp[j-1] = prep[k];
                possible->push_back(temp);
                
            }
        }
    }
    // substitute & delete
    for(int i=seque[1][0]; i<seque[1][0]+seque[1].size(); i++){
        for(int j=seque[0][0]; j<seque[0][0]+seque[0].size(); j++){
            for(int k=0; k<20; k++){
                vector<string> temp;
                for(int l=0; l<original.size(); l++)
                    temp.push_back(original[l]);
                temp.erase(temp.begin()+i);
                temp[j] = prep[k];
                possible->push_back(temp);
                
            }
        }
    }
    count[1] = possible->size();
    // substitute & substitute
    for(int i=seque[0][0]; i<seque[0][0]+seque[0].size(); i++){
        for(int j=seque[1][0]; j<seque[1][0]+seque[1].size(); j++){
            for(int k=0; k<20; k++){
                for(int h=0; h<20; h++){
                    vector<string> temp;
                    for(int l=0; l<original.size(); l++)
                        temp.push_back(original[l]);
                    temp[i] = prep[k];
                    temp[j] = prep[h];
                    possible->push_back(temp);
                }
            }
        }
    }
    // insert & delete
    for(int i=seque[0][0]; i<seque[0][0]+seque[0].size()+1; i++){
        for(int j=seque[1][0]; j<seque[1][0]+seque[1].size(); j++){
            for(int l=0; l<20; l++){
                vector<string> temp;
                for(int k=0; k<original.size(); k++)
                    temp.push_back(original[k]);
                temp.insert(temp.begin()+i, prep[l]);
                temp.erase(temp.begin()+j+1);
                possible->push_back(temp);

            }
        }
    }
    // delete & insert
    for(int i=seque[1][0]; i<seque[1][0]+seque[1].size()+1; i++){
        for(int j=seque[0][0]; j<seque[0][0]+seque[0].size(); j++){
            for(int k=0; k<20; k++){
                vector<string> temp;
                for(int l=0; l<original.size(); l++)
                    temp.push_back(original[l]);
                temp.insert(temp.begin()+i, prep[k]);
                temp.erase(temp.begin()+j);
                possible->push_back(temp);
            }
        }
    }
    count[2] = possible->size();
    // substitute & insert
    for(int j=seque[1][0]; j<seque[1][0]+seque[1].size()+1; j++){
        for(int i=seque[0][0]; i<seque[0][0]+seque[0].size(); i++){
            for(int l=0; l<20; l++){
                for(int h=0; h<20; h++){
                    vector<string> temp;
                    for(int k=0; k<original.size(); k++)
                        temp.push_back(original[k]);
                    temp.insert(temp.begin()+j, prep[l]);
                    temp[i] = prep[h];
                    possible->push_back(temp);
                }
            }
        }
    }
    // insert & substitute
    for(int i=seque[0][0]; i<seque[0][0]+seque[0].size()+1; i++){
        for(int j=seque[1][0]; j<seque[1][0]+seque[1].size(); j++){
            for(int l=0; l<20; l++){
                for(int h=0; h<20; h++){
                    vector<string> temp;
                    for(int k=0; k<original.size(); k++)
                        temp.push_back(original[k]);
                    temp.insert(temp.begin()+i, prep[l]);
                    temp[j+1] = prep[h];
                    possible->push_back(temp);
                }
            }
        }
    }
    count[3] = possible->size();
    // insert & insert
    for(int i=seque[0][0]; i<seque[0][0]+seque[0].size()+1; i++){
        for(int j=seque[1][0]; j<seque[1][0]+seque[1].size()+1; j++){
            for(int l=0; l<20; l++){
                for(int h=0; h<20; h++){
                    vector<string> temp;
                    for(int k=0; k<original.size(); k++)
                        temp.push_back(original[k]);
                    temp.insert(temp.begin()+i, prep[l]);
                    temp.insert(temp.begin()+j+1, prep[h]);
                    possible->push_back(temp);
                }
            }
        }
    }
    count[4] = possible->size();
    return count;
}
int *edb3(vector< vector<string> > *possible, const vector<string> &original, const vector< vector<int> > &seque)
{
    int *count = new int[4];
    // delete & delete & delete
    vector<string> temp;
    temp.push_back(original[1]);
    temp.push_back(original[3]);
    possible->push_back(temp);
    count[0] = possible->size();
    // delete & delete & substitute
    for(int h=0; h<20; h++){
        vector<string> temp;
        temp.push_back(original[1]);
        temp.push_back(original[3]);
        temp.push_back(prep[h]);
        possible->push_back(temp);
    }
    //delete & substitute & delete
    for(int h=0; h<20; h++){
        vector<string> temp;
        temp.push_back(original[1]);
        temp.push_back(prep[h]);
        temp.push_back(original[3]);
        possible->push_back(temp);
    }
    //substitute & delete & delete
    for(int h=0; h<20; h++){
        vector<string> temp;
        temp.push_back(prep[h]);
        temp.push_back(original[1]);
        temp.push_back(original[3]);
        possible->push_back(temp);
    }
    count[1] = possible->size();
    //insert & delete & delete
    for(int h=0; h<20; h++){
        vector<string> temp;
        temp.push_back(prep[h]);
        temp.push_back(original[0]);
        temp.push_back(original[1]);
        temp.push_back(original[3]);
        possible->push_back(temp);
        temp[0] = original[0];
        temp[1] = prep[h];
        possible->push_back(temp);
    }
    //delete & insert & delete
    for(int h=0; h<20; h++){
        vector<string> temp;
        temp.push_back(original[1]);
        temp.push_back(prep[h]);
        temp.push_back(original[2]);
        temp.push_back(original[3]);
        possible->push_back(temp);
        temp[1] = original[2];
        temp[2] = prep[h];
        possible->push_back(temp);
    }
    //delete & delete & insert
    for(int h=0; h<20; h++){
        vector<string> temp;
        temp.push_back(original[1]);
        temp.push_back(original[3]);
        temp.push_back(prep[h]);
        temp.push_back(original[4]);
        possible->push_back(temp);
        temp[2] = original[4];
        temp[3] = prep[h];
        possible->push_back(temp);
    }
    //delete & substitute & substitute
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(original[1]);
            temp.push_back(prep[i]);
            temp.push_back(original[3]);
            temp.push_back(prep[j]);
            possible->push_back(temp);
        }
    }
    //substitute & delete & substitute
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(prep[i]);
            temp.push_back(original[1]);
            temp.push_back(original[3]);
            temp.push_back(prep[j]);
            possible->push_back(temp);
        }
    }
    //substitute & substitute & delete
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(prep[i]);
            temp.push_back(original[1]);
            temp.push_back(prep[j]);
            temp.push_back(original[3]);
            possible->push_back(temp);
        }
    }
    count[2] = possible->size();
    //substitute & substitute & substitute
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            for(int k=0; k<20; k++){
                vector<string> temp;
                temp.push_back(prep[i]);
                temp.push_back(original[1]);
                temp.push_back(prep[j]);
                temp.push_back(original[3]);
                temp.push_back(prep[k]);
            }
        }
    }
    //delete & insert & substitute
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(original[1]);
            temp.push_back(prep[i]);
            temp.push_back(original[2]);
            temp.push_back(original[3]);
            temp.push_back(prep[j]);
            possible->push_back(temp);
            temp[1] = original[2];
            temp[2] = prep[i];
            possible->push_back(temp);
        }
    }
    //delete & substitute & insert
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(original[1]);
            temp.push_back(prep[i]);
            temp.push_back(original[3]);
            temp.push_back(prep[j]);
            temp.push_back(original[4]);
            possible->push_back(temp);
            temp[3] = original[2];
            temp[4] = prep[j];
            possible->push_back(temp);
        }
    }
    //insert & delete & substitute
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(prep[i]);
            temp.push_back(original[0]);
            temp.push_back(original[1]);
            temp.push_back(original[3]);
            temp.push_back(prep[j]);
            possible->push_back(temp);
            temp[0] = original[0];
            temp[1] = prep[i];
            possible->push_back(temp);
        }
    }
    //insert & substitute & delete
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(prep[i]);
            temp.push_back(original[0]);
            temp.push_back(original[1]);
            temp.push_back(prep[j]);
            temp.push_back(original[3]);
            possible->push_back(temp);
            temp[0] = original[0];
            temp[1] = prep[i];
            possible->push_back(temp);
        }
    }
    //substitute & insert & delete
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(prep[i]);
            temp.push_back(original[1]);
            temp.push_back(prep[j]);
            temp.push_back(original[2]);
            temp.push_back(original[3]);
            possible->push_back(temp);
            temp[2] = original[2];
            temp[3] = prep[j];
            possible->push_back(temp);
        }
    }
    //substitute & delete & insert
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            vector<string> temp;
            temp.push_back(prep[i]);
            temp.push_back(original[1]);
            temp.push_back(original[3]);
            temp.push_back(prep[j]);
            temp.push_back(original[4]);
            possible->push_back(temp);
            temp[3] = original[4];
            temp[4] = prep[j];
            possible->push_back(temp);
        }
    }
    count[3] = possible->size();
    return count;
}
void search2(vector<int> *n, vector<unsigned int> *f, const vector<string> &c, int i, last2 *dict2)
{
    last2::iterator it1 = dict2->find(c[0]);
    if(it1 != dict2->end()){
        last1::iterator it2 = (it1->second)->find(c[1]);
        if(it2 != (it1->second)->end()){
            n->push_back(i);
            f->push_back(it2->second);
        }
    }
}
void search3(vector<int> *n, vector<unsigned int> *f, const vector<string> &c, int i, last3 *dict3)
{
    last3::iterator it1 = dict3->find(c[0]);
    if(it1 != dict3->end()){
        last2::iterator it2 = (it1->second)->find(c[1]);
        if(it2 != (it1->second)->end()){
            last1::iterator it3 = (it2->second)->find(c[2]);
            if(it3 != (it2->second)->end()){
                n->push_back(i);
                f->push_back(it3->second);
            }
        }
    }
}
void search4(vector<int> *n, vector<unsigned int> *f, const vector<string> &c, int i, last4 *dict4)
{
    last4::iterator it1 = dict4->find(c[0]);
    if(it1 != dict4->end()){
        last3::iterator it2 = (it1->second)->find(c[1]);
        if(it2 != (it1->second)->end()){
            last2::iterator it3 = (it2->second)->find(c[2]);
            if(it3 != (it2->second)->end()){
                last1::iterator it4 = (it3->second)->find(c[3]);
                if(it4 != (it3->second)->end()){
                    n->push_back(i);
                    f->push_back(it4->second);
                }
            }
        }
    }
}
void search5(vector<int> *n, vector<unsigned int> *f, const vector<string> &c, int i, last5 *dict5)
{
    last5::iterator it1 = dict5->find(c[0]);
    if(it1 != dict5->end()){
        last4::iterator it2 = (it1->second)->find(c[1]);
        if(it2 != (it1->second)->end()){
            last3::iterator it3 = (it2->second)->find(c[2]);
            if(it3 != (it2->second)->end()){
                last2::iterator it4 = (it3->second)->find(c[3]);
                if(it4 != (it3->second)->end()){
                    last1::iterator it5 = (it4->second)->find(c[4]);
                    if(it5 != (it4->second)->end()){
                        n->push_back(i);
                        f->push_back(it5->second);
                    }
                }
            }
        }
    }
}

int main()
{
    //unordered_map< vector<string>, vector<int> * > no_prep;
    //vector< vector<string> > dict;
    last2 dictionary2;
    dictionary2.reserve(221607);
    last3 dictionary3;
    dictionary3.reserve(130856);
    last4 dictionary4;
    dictionary4.reserve(97357);
    last5 dictionary5;
    dictionary5.reserve(82441);
    // ********** build dictionaries **********
    ifstream fin2, fin3, fin4, fin5;
    fin2.open("/tmp2/dsa2016_project/2gm.small.txt");
    if(!fin2.is_open())
        cout<<"Fail to open input file 2!"<<endl;
    else{
        string temp1, temp2;
        string prev1 = "";
        unsigned int count;
        while(fin2>>temp1>>temp2>>count){
            if(prev1 != temp1){
                last1 *one = new last1;
                (*one)[temp2] = count;
                dictionary2.insert(pair<string, last1 *>(temp1, one));
                prev1 = temp1;
            }
            else{
                dictionary2[temp1]->insert(pair<string, unsigned int>(temp2, count));
            }
        }
        fin2.close();
    }
    
    fin3.open("/tmp2/dsa2016_project/3gm.small.txt");
    if(!fin3.is_open())
        cout<<"Fail to open input file 3!"<<endl;
    else{
        string temp1, temp2, temp3;
        string prev1 = "";
        string prev2 = "";
        unsigned int count;
        while(fin3>>temp1>>temp2>>temp3>>count){
            if(prev1 != temp1){
                last2 *two = new last2;
                last1 *one = new last1;
                (*one)[temp3] = count;
                (*two)[temp2] = one;
                dictionary3.insert(pair<string, last2 *>(temp1, two));
                prev1 = temp1;
                prev2 = temp2;
            }
            else if(prev2 != temp2){
                last1 *one = new last1;
                (*one)[temp3] = count;
                dictionary3[temp1]->insert(pair<string, last1 *>(temp2, one));
                prev2 = temp2;
            }
            else{
                (*(dictionary3[temp1]))[temp2]->insert(pair<string, unsigned int>(temp3, count));
            }
        }
        fin3.close();
    }
    
    fin4.open("/tmp2/dsa2016_project/4gm.small.txt");
    if(!fin4.is_open())
        cout<<"Fail to open input file 4!"<<endl;
    else{
        string temp1, temp2, temp3, temp4;
        string prev1 = "";
        string prev2 = "";
        string prev3 = "";
        unsigned int count;
        while(fin4>>temp1>>temp2>>temp3>>temp4>>count){
            if(prev1 != temp1){
                last3 *three = new last3;
                last2 *two = new last2;
                last1 *one = new last1;
                (*one)[temp4] = count;
                (*two)[temp3] = one;
                (*three)[temp2] = two;
                dictionary4.insert(pair<string, last3 *>(temp1, three));
                prev1 = temp1;
                prev2 = temp2;
                prev3 = temp3;
            }
            else if(prev2 != temp2){
                last2 *two = new last2;
                last1 *one = new last1;
                (*one)[temp4] = count;
                (*two)[temp3] = one;
                dictionary4[temp1]->insert(pair<string, last2 *>(temp2, two));
                prev2 = temp2;
                prev3 = temp3;
            }
            else if(prev3 != temp3){
                last1 *one = new last1;
                (*one)[temp4] = count;
                (*(dictionary4[temp1]))[temp2]->insert(pair<string, last1 *>(temp3, one));
                prev3 = temp3;
            }
            else{
                (*((*(dictionary4[temp1]))[temp2]))[temp3]->insert(pair<string, unsigned int>(temp4, count));
            }
        }
        fin4.close();
    }
    
    fin5.open("/tmp2/dsa2016_project/5gm.small.txt");
    if(!fin5.is_open())
        cout<<"Fail to open input file 5!"<<endl;
    else{
        string temp1, temp2, temp3, temp4, temp5;
        string prev1 = "";
        string prev2 = "";
        string prev3 = "";
        string prev4 = "";
        unsigned int count;
        while(fin5>>temp1>>temp2>>temp3>>temp4>>temp5>>count){
            if(prev1 != temp1){
                last4 *four = new last4;
                last3 *three = new last3;
                last2 *two = new last2;
                last1 *one = new last1;
                (*one)[temp5] = count;
                (*two)[temp4] = one;
                (*three)[temp3] = two;
                (*four)[temp2] = three;
                dictionary5.insert(pair<string, last4 *>(temp1, four));
                prev1 = temp1;
                prev2 = temp2;
                prev3 = temp3;
                prev4 = temp4;
            }
            else if(prev2 != temp2){
                last3 *three = new last3;
                last2 *two = new last2;
                last1 *one = new last1;
                (*one)[temp5] = count;
                (*two)[temp4] = one;
                (*three)[temp3] = two;
                dictionary5[temp1]->insert(pair<string, last3 *>(temp2, three));
                prev2 = temp2;
                prev3 = temp3;
                prev4 = temp4;
            }
            else if(prev3 != temp3){
                last2 *two = new last2;
                last1 *one = new last1;
                (*one)[temp5] = count;
                (*two)[temp4] = one;
                (*(dictionary5[temp1]))[temp2]->insert(pair<string, last2 *>(temp3, two));
                prev3 = temp3;
                prev4 = temp4;
            }
            else if(prev4 != temp4){
                last1 *one = new last1;
                (*one)[temp5] = count;
                (*((*(dictionary5[temp1]))[temp2]))[temp3]->insert(pair<string, last1 *>(temp4, one));
                prev4 = temp4;
            }
            else{
                (*((*((*(dictionary5[temp1]))[temp2]))[temp3]))[temp4]->insert(pair<string, unsigned int>(temp5, count));
            }
        }
        fin5.close();
    }
    //cout<<"done"<<endl;
    // ********** query **********
    while(cin){
        vector<string> phrase;
        string temp;
        while(cin>>temp){
            phrase.push_back(temp);
            if(cin.get() == '\n')
                break;
        }
        if(phrase.size() == 0)
            break;
        cout<<"query: "<<phrase[0];
        for(int i=1; i<phrase.size(); i++)
            cout<<" "<<phrase[i];
        cout<<endl;
        vector< vector<string> > candidate;
        candidate.reserve(10000);
        bool prev = false;
        vector< vector<int> > sequences;
        sequences.reserve(3);
        for(int j=0; j<phrase.size(); j++){
            if(find(prep, prep+20, phrase[j]) != prep+20){
                if(prev)
                    sequences[sequences.size()-1].push_back(j);
                else{
                    vector<int> new_start;
                    new_start.push_back(j);
                    sequences.push_back(new_start);
                }
                prev = true;
            }
            else
                prev = false;
        }
        vector<int> candidate_no;
        candidate_no.reserve(100);
        vector<unsigned int> freq;
        freq.reserve(100);
        int how_long = phrase.size();
        if(sequences.size() == 0){
            int *c;
            candidate.push_back(phrase);
            c = eda(&candidate, phrase);
            if(how_long == 2){
                search2(&candidate_no, &freq, candidate[0], 0, &dictionary2);
                for(int k=1; k<c[0]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[0]; k<c[1]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
            }
            else if(how_long == 3){
                search3(&candidate_no, &freq, candidate[0], 0, &dictionary3);
                for(int k=1; k<c[0]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[0]; k<c[1]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else if(how_long == 4){
                search4(&candidate_no, &freq, candidate[0], 0, &dictionary4);
                for(int k=1; k<c[0]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else if(how_long == 5)
                search5(&candidate_no, &freq, candidate[0], 0, &dictionary5);
            else
                cout<<"Query is too long."<<endl;
        }
        else if(sequences.size() == 1){
            int *c;
            c = edb1(&candidate, phrase, sequences[0]);
            if(how_long == 2){
                for(int k=c[0]; k<c[1]; k++)
                    search2(&candidate_no, &freq, candidate[k], k, &dictionary2);
                for(int k=c[1]; k<c[2]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
            }
            else if(how_long == 3){
                for(int k=0; k<c[0]; k++)
                    search2(&candidate_no, &freq, candidate[k], k, &dictionary2);
                for(int k=c[0]; k<c[1]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[1]; k<c[2]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
            }
            else if(how_long == 4){
                for(int k=0; k<c[0]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[0]; k<c[1]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[1]; k<c[2]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else if(how_long == 5){
                for(int k=0; k<c[0]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[0]; k<c[1]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else
                cout<<"Query is too long."<<endl;
        }
        else if(sequences.size() == 2){
            int *c;
            c = edb2(&candidate, phrase, sequences);
            if(how_long == 3){
                for(int k=c[0]; k<c[1]; k++)
                    search2(&candidate_no, &freq, candidate[k], k, &dictionary2);
                for(int k=c[1]; k<c[2]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[2]; k<c[3]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[3]; k<c[4]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else if(how_long == 4){
                for(int k=0; k<c[0]; k++)
                    search2(&candidate_no, &freq, candidate[k], k, &dictionary2);
                for(int k=c[0]; k<c[1]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[1]; k<c[2]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[2]; k<c[3]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else if(how_long == 5){
                for(int k=0; k<c[0]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[0]; k<c[1]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[1]; k<c[2]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else
                cout<<"Query is too long."<<endl;
        }
        else if(sequences.size() == 3){
            if(how_long == 5){
                int *c;
                c = edb3(&candidate, phrase, sequences);
                for(int k=0; k<c[0]; k++)
                    search2(&candidate_no, &freq, candidate[k], k, &dictionary2);
                for(int k=c[0]; k<c[1]; k++)
                    search3(&candidate_no, &freq, candidate[k], k, &dictionary3);
                for(int k=c[1]; k<c[2]; k++)
                    search4(&candidate_no, &freq, candidate[k], k, &dictionary4);
                for(int k=c[2]; k<c[3]; k++)
                    search5(&candidate_no, &freq, candidate[k], k, &dictionary5);
            }
            else
                cout<<"Query is too long."<<endl;
        }
        else
            cout<<"Threre are more than three sequences."<<endl;
       
        int position, which;
        //remove duplicates
        
        int how_many_outputs = (10 < freq.size()? 10 : freq.size());
        vector< vector<string> > print_out;
        vector<unsigned int> print_f;
        while(freq.size() != 0 && print_out.size() < 10){
            position = max_element(freq.begin(), freq.end()) - freq.begin();
            which = candidate_no[position];
            bool printed = false;
            for(int k=0; k<print_out.size(); k++){
                if(candidate[which] == print_out[k]){
                    printed = true;
                    break;
                }
            }
            if(!printed){
                print_out.push_back(candidate[which]);
                print_f.push_back(freq[position]);
            }
            freq.erase(freq.begin()+position);
            candidate_no.erase(candidate_no.begin()+position);
        }
        cout<<"output: "<<print_out.size()<<endl;
        for(int j=0; j<print_out.size(); j++){
            cout<<print_out[j][0];
            for(int k=1; k<print_out[j].size(); k++)
                cout<<" "<<print_out[j][k];
            cout<<"\t"<<print_f[j]<<endl;
        }
    }
    

    return 0;
}