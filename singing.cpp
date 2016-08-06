//
//  singing.cpp
//  
//
//  Created by Liang-Ying Chih on 2016/5/28.
//
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    typedef double E;
    int m, n;
    vector<E> pitch;
    vector<E> notes;
    pitch.reserve(1000);
    notes.reserve(100);
    E pp, nn;
    cin>>m;
    for(int i=0; i<m; i++){
        cin>>pp;
        pitch.push_back(pp);
    }
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>nn;
        notes.push_back(nn);
    }
    
    E dp[n][m];
    dp[0][0] = abs(pitch[0] - notes[0]);
    bool change[n][m];
    for(int i=1; i<m; i++)
        dp[0][i] = abs(pitch[i] - notes[0]) + dp[0][i-1];
   
    for(int j=1; j<n; j++){
        dp[j][0] = 200000;
    }
    
    for(int j=1; j<n; j++){
        for(int i=1; i<m; i++){
            if(dp[j-1][i-1] <= dp[j][i-1]){
                change[j][i] = true;
                dp[j][i] = abs(pitch[i] - notes[j]);
                dp[j][i] += dp[j-1][i-1];
            }
            else{
                change[j][i] = false;
                dp[j][i] = abs(pitch[i] - notes[j]);
                dp[j][i] += dp[j][i-1];
            }
        }
    }
    E dist = dp[0][m-1];
    int which = 0;
    for(int j=1; j<n; j++){
        if(dp[j][m-1] < dist){
            dist = dp[j][m-1];
            which = j;
        }
    }
    vector<int> song;
    song.reserve(100);
    for(int i=1; i<m; i++){
        if(change[which][m-i]){
            song.push_back(m-i);
            which--;
        }
    }
    song.push_back(0);
    cout<<dist<<endl;
    for(int k=song.size()-1; k>0; k--)
        cout<<song[k]<<" ";
    cout<<song[0]<<endl;
    return 0;
    
}
