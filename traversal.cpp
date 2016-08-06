//
//  traversal.cpp
//  
//
//  Created by Liang-Ying Chih on 2016/4/24.
//
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

void post(vector<int> *tree, int index)
{
    if(index*2 < tree->size()){
        if(tree->at(index*2) != -1)
        post(tree, index*2);
        
        if(index*2+1 < tree->size()){
            if(tree->at(index*2+1) != -1)
            post(tree, index*2+1);
        }
    }
    if(index != 1)
        cout<<tree->at(index)<<" ";
    else
        cout<<tree->at(1)<<endl;
}
void pre(vector<int> *tree, int index)
{
    
    cout<<tree->at(index)<<" ";
    if(index*2 < tree->size()){
        if(tree->at(index*2) != -1)
            pre(tree, index*2);
    }
        if(index*2+1 < tree->size()){
            if(tree->at(index*2+1) != -1)
                pre(tree, index*2+1);
        }
}
void in(vector<int> *tree, int index)
{
    
    if(index*2 < tree->size()){
        if(tree->at(index*2) != -1)
            in(tree, index*2);
    }
        cout<<tree->at(index)<<" ";
        if(index*2+1 < tree->size()){
            if(tree->at(index*2+1) != -1)
                in(tree, index*2+1);
        }
    
}

int main()
{
    int e;
    vector<int> tree;
    while(cin>>e)
        tree.push_back(e);
    /*vector<int> temp1, temp2;
    pre(&tree, 1, &temp1);
    for(int i=0; i<temp1.size()-1; i++){
        cout<<temp1[i]<<" ";
    }
    cout<<temp1[temp1.size()-1]<<endl;
    
    in(&tree, 1, &temp2);
    for(int i=0; i<temp2.size()-1; i++){
        cout<<temp2[i]<<" ";
    }
    cout<<temp2[temp2.size()-1]<<endl;*/
    pre(&tree, 1);
    cout<<endl;
    in(&tree, 1);
    cout<<endl;
    post(&tree, 1);
    return 0;

}