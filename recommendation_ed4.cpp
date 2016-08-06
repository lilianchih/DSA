#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;
const int TOTAL = 73209277;
int main()
{
    ifstream fin;
    int U, I, R, T;

    typedef unordered_map<int, int> TimeToResult;
    typedef unordered_map<int, TimeToResult *> UserToTime;
    typedef unordered_map<int, UserToTime *> ItemToUser;

    ItemToUser imap;

    typedef ItemToUser::iterator IterateItem;
    typedef UserToTime::iterator IterateUser;
    typedef TimeToResult::iterator IterateTime;

    fin.open("/tmp2/KDDCUP2012/track1/rec_log_train.txt"); //\/tmp2/KDDCUP2012/track1/rec_log_train.txt
    if(!fin.is_open())
        cout<<"Fail to open input file!"<<endl;
    else{
        while(fin>>U>>I>>R>>T){
                TimeToResult *tmap = new TimeToResult;
                (*tmap)[T] = R;
            if(imap.find(I) == imap.end()){
                UserToTime *umap = new UserToTime;
                TimeToResult *tmap = new TimeToResult;
                tmap->insert(pair<int, int>(T, R));
                imap.insert(pair<int, UserToTime *>(I, umap));
                umap->insert(pair<int, TimeToResult *>(U, tmap));
            }
            else if(imap[I]->find(U) == imap[I]->end()){
                    TimeToResult *tmap = new TimeToResult;
                    tmap->insert(pair<int, int>(T, R));
                    imap[I]->insert(pair<int, TimeToResult *>(U, tmap));
            }
            else
                (*(imap[I]))[U]->insert(pair<int, int>(T, R));
        }
    }
    unordered_map<int, int> HowManyTimes;
        HowManyTimes.reserve(1392872);
        for(IterateItem it1=imap.begin(); it1!=imap.end(); it1++){
            for(IterateUser it2=(it1->second)->begin(); it2!=(it1->second)->end(); it2++){
                if( HowManyTimes.find((it2->first)) != HowManyTimes.end() )
                    HowManyTimes[it2->first] += (it2->second)->size();
                else
                    HowManyTimes[it2->first] = (it2->second)->size();
            }
        }
    //cout<<"done"<<endl;

//***************************START_QUERY**************************************************
    int how_many_input;
    cin>>how_many_input;
    while(how_many_input--){
    string input;
    cin>>input;
//**************************ACCEPT********************************************************
    if(input == "accept"){
    int _user, _item, _timestamp;
    cin>>_user>>_item>>_timestamp;
    if(imap.find(_item) != imap.end()){
        if(imap[_item]->find(_user) != imap[_item]->end()){
            if( (*(imap[_item]))[_user]->find(_timestamp) != (*(imap[_item]))[_user]->end() ){
                cout<<(*((*(imap[_item]))[_user]))[_timestamp]<<endl;
            }
            else
                cout<<0<<endl;
        }
        else
            cout<<0<<endl;
    }
    else
        cout<<0<<endl;
    }
//**********************ITEMS*************************************************************
    if(input == "items"){
    int u1, u2;
    cin>>u1>>u2;
    vector<int> common_items;
    common_items.reserve(100);
    for(IterateItem it=imap.begin(); it!=imap.end(); it++){
        if((it->second)->find(u1) != (it->second)->end() && (it->second)->find(u2) != (it->second)->end())
            common_items.push_back(it->first);
    }
    if(common_items.size() == 0)
        cout<<"EMPTY"<<endl;
    else{
    sort(common_items.begin(), common_items.end());
    for(vector<int>::iterator it=common_items.begin(); it!=common_items.end(); it++)
        printf("%d\n",*it);
    }
    }
//***********************USERS************************************************************
    if(input == "users"){
    int i1, i2, t1, t2;
    cin>>i1>>i2>>t1>>t2;
    vector<int> u1, u2;
    u1.reserve(1000);
    u2.reserve(1000);
    if(imap.find(i1) != imap.end() && imap.find(i2) != imap.end()){
    for(IterateUser it1=imap[i1]->begin(); it1!=imap[i1]->end(); it1++){
        for(IterateTime it2=(it1->second)->begin(); it2!=(it1->second)->end(); it2++){
            if(t2 >= it2->first && it2->first >= t1){
                u1.push_back(it1->first);
                break;
            }
        }
    }
    for(IterateUser it1=imap[i2]->begin(); it1!=imap[i2]->end(); it1++){
        for(IterateTime it2=(it1->second)->begin(); it2!=(it1->second)->end(); it2++){
            if(t2 >= it2->first && it2->first >= t1){
                u2.push_back(it1->first);
                break;
            }
        }
    }
    sort(u1.begin(), u1.end());
    sort(u2.begin(), u2.end());
    vector<int> common_users;
    common_users.reserve(100);
    set_intersection(u1.begin(), u1.end(), u2.begin(), u2.end(), back_inserter(common_users));
    if(common_users.size() != 0){
        for(int i=0; i<common_users.size(); i++)
            cout<<common_users[i]<<endl;
    }
    else
        cout<<"EMPTY"<<endl;
    }
    else
        cout<<"EMPTY"<<endl;
    }

//*************************RATIO**************************************************************
    if(input == "ratio"){
        int item, threshold;
        cin>>item>>threshold;
        vector<int> Us;
        for(unordered_map<int, int>::iterator it=HowManyTimes.begin(); it!=HowManyTimes.end(); it++){
            if((it->second) > threshold)
                Us.push_back(it->first);
        }
        int total = Us.size();
        int a = 0;
        if(imap.find(item) != imap.end()){
        for(IterateUser it1=imap[item]->begin(); it1!=imap[item]->end(); it1++){
            if(find(Us.begin(), Us.end(), it1->first) != Us.end()){
                for(IterateTime it2=(it1->second)->begin(); it2!=(it1->second)->end(); it2++){
                    if((it2->second) == 1){
                        a++;
                        break;
                    }
                }
            }
        }
        }
        cout<<a<<"/"<<total<<endl;
    }
//******************************FINDTIME_ITEM***************************************************
    if(input == "findtime_item"){
        int item, user;
        vector<int> Us, Ts;
        Us.reserve(100);
        cin>>item;
        while(scanf("%d", &user) == 1)
            Us.push_back(user);
        for(IterateUser it1=imap[item]->begin(); it1!=imap[item]->end(); it1++){
            if(find(Us.begin(), Us.end(), it1->first) != Us.end()){
               for(IterateTime it2=(it1->second)->begin(); it2!=(it1->second)->end(); it2++)
                Ts.push_back(it2->first);
            }
        }
        sort(Ts.begin(), Ts.end());
        Ts.erase(unique(Ts.begin(), Ts.end()), Ts.end());
        if(Ts.size() != 0){
            for(int i=0; i<Ts.size(); i++)
                cout<<Ts[i]<<endl;
        }
        else
            cout<<"EMPTY"<<endl;
    }

    }//end of while loop

    return 0;
}
