//
//  stock.cpp
//  
//
//  Created by Liang-Ying Chih on 2016/5/1.
//
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct mygreater{
    bool operator()(vector<int> &a, vector<int> &b){
        if(a[2] == b[2])
            return a[0] > b[0];
        else
            return a[2] > b[2];
    }
};

struct mysmaller{
    bool operator()(vector<int> &a, vector<int> &b){
        if(a[2] == b[2])
            return a[0] > b[0];
        else
            return a[2] < b[2];
    }
};
int main()
{
    int bidID, clientID, action, price, share;
    
    priority_queue<vector<int>, vector<vector<int> >, mygreater> sellList;
    priority_queue<vector<int>, vector<vector<int> >, mysmaller> buyList;
    vector<vector<int> > tradeRecord;
    tradeRecord.reserve(200000);
    
    vector<int> teuer, billig;
    
    vector<int> cancelled;
    cancelled.reserve(200000);
    for(int i=0; i<200000; i++)
        cancelled[i] = 0;
    

    while(cin>>bidID>>clientID>>action>>price>>share){
        if(action == 0){
            vector<int> bid;
            bid.push_back(bidID);
            bid.push_back(clientID);
            bid.push_back(price);
            bid.push_back(share);
            buyList.push(bid);
            //make_heap(buyList.begin(), buyList.end(), greater());
        }
        else if(action == 1){
            vector<int> bid;
            bid.push_back(bidID);
            bid.push_back(clientID);
            bid.push_back(price);
            bid.push_back(share);
            sellList.push(bid);
            //make_heap(sellList.begin(), sellList.end(), smaller());
        }
        else{ //cancel price->bidID to be cancelled share immer 0
            
            cancelled[price] = 1;
            
        }
        //trade[0]->buyClient trade[1]->sellClient trade[2]->sellPrice trade[3]->share
        //list[1]->clientID list[2]->price list[3]->share
        bool try_next = false;
        if(!buyList.empty()){
            while(cancelled[buyList.top()[0] ]){
                buyList.pop();
                if(buyList.empty())
                    break;
            }
        }
        if(!sellList.empty()){
            while(cancelled[sellList.top()[0] ]){
                sellList.pop();
                if(sellList.empty())
                    break;
            }
        }
        if(!buyList.empty() && !sellList.empty())
            try_next = buyList.top()[2] >= sellList.top()[2];
        /*else
            try_next = false;*/
        while(try_next){
            if(buyList.top()[3] < sellList.top()[3]){
                vector<int> trade;
                trade.push_back(buyList.top()[1]);
                trade.push_back(sellList.top()[1]);
                trade.push_back(sellList.top()[2]);
                trade.push_back(buyList.top()[3]);
                vector<int> temp = sellList.top();
                sellList.pop();
                temp[3] -= buyList.top()[3];
                sellList.push(temp);
                buyList.pop();
                tradeRecord.push_back(trade);
            }
            else if(buyList.top()[3] > sellList.top()[3]){
                vector<int> trade;
                trade.push_back(buyList.top()[1]);
                trade.push_back(sellList.top()[1]);
                trade.push_back(sellList.top()[2]);
                trade.push_back(sellList.top()[3]);
                vector<int> temp = buyList.top();
                buyList.pop();
                temp[3] -= sellList.top()[3];
                buyList.push(temp);
                sellList.pop();
                tradeRecord.push_back(trade);
            }
            else{
                vector<int> trade;
                trade.push_back(buyList.top()[1]);
                trade.push_back(sellList.top()[1]);
                trade.push_back(sellList.top()[2]);
                trade.push_back(sellList.top()[3]);
                buyList.pop();
                sellList.pop();
                tradeRecord.push_back(trade);
            }
            if(!buyList.empty()){
                while(cancelled[buyList.top()[0] ]){
                    buyList.pop();
                    if(buyList.empty())
                        break;
                }
            }
            if(!sellList.empty()){
                while(cancelled[sellList.top()[0] ]){
                    sellList.pop();
                    if(sellList.empty())
                        break;
                }
            }
            if(!buyList.empty() && !sellList.empty())
                try_next = buyList.top()[2] >= sellList.top()[2];
            else
                try_next = false;
        }
    }
    
    for(int i=0; i<tradeRecord.size(); i++){
        //cout<<i<<"\t"<<tradeRecord[i][0]<<"\t"<<tradeRecord[i][1]<<"\t"<<tradeRecord[i][2]<<"\t"<<tradeRecord[i][3]<<endl;
        printf("%d\t%d\t%d\t%d\t%d\n", i, tradeRecord[i][0], tradeRecord[i][1], tradeRecord[i][2], tradeRecord[i][3]);
    }
    
    return 0;
    
}

