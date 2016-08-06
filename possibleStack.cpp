//
//  possibleStack.cpp
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
#include <stack>

using namespace std;

bool next_comb(int* comb, const int n, const int k) {
    int i = k - 1;
    const int e = n - k;
    do
        comb[i]++;
    while (comb[i] > e + i && i--);
    if (comb[0] > e)
        return 0;
    while (++i < k)
        comb[i] = comb[i - 1] + 1;
    return 1;
}
void all_comb(int n, int k, vector<vector<int> > *possibility) {
    int* comb = new int[k];
    for (int i = 0; i < k; i++)
        comb[i] = i;
    do{
        vector<int> temp;
        for(int i=0; i<n; i++)
            temp.push_back(-1);
        for (int i = 0; i < k; i++)
            temp.at(comb[i]) = 1;
        int sum = 0;
        bool correct = true;
        for(int i=0; i<n; i++){
            sum += temp[i];
            if(sum < 0){
                correct = false;
                break;
            }
        }
        if(correct)
            possibility->push_back(temp);
    }
    while (next_comb(comb, n, k));
    
}

int main()
{
    int n;
    cin>>n;
    vector<vector<int> > possibility;
    /*stack<int> numbers;
    for(int i=1; i<=n; i++){
        stack.push(i);
    }*/
    
    all_comb(2*n, n, &possibility);
    for(int i=0; i<possibility.size(); i++){
        stack<int> numbers;
        int m = 1;
        for(int j=0; j<possibility[i].size(); j++){
            if(possibility[i][j] == 1){
                numbers.push(m);
                m++;
            }
            else{
                cout<<numbers.top()<<" ";
                numbers.pop();
            }
        }
        cout<<endl;
    }
    return 0;
}