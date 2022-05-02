#include <bits/stdc++.h>
using namespace std;
#define int long long
// n is no of EVS
int n;

//declaring global const MAX, MOD, INF

const int MAX=20;
const int INF=1e18;
const int MOD=1e9+7;
const int MAXL=20;

//global variable declaration
//interval store end time for three interval
// n no of EVS
// rate store rate for three interval
// dp for all 2^n possible cases
//info store EV arrival , departure and charge needed time

vector<vector<int>>info(200);
vector<int> end_time;
int rate[3],interval[3];

//function for calculation time belongs to which interval
int idx(int x) {
    if(x<=interval[0]) {
        return 0;
    }
    if(x<=interval[1]) {
        return 1;
    }
    return 2;
}

// calculation for end time of EVs
int ftime(int a,int s,int rem) {
    int st=idx(s);
    if((interval[st]>=s + (rem+rate[st]-1)/rate[st])) {
        int x=s + max(0LL,(rem+rate[st]-1)/rate[st]);  //charging lie within the interval then return the end time
        if(x>info[a][1]) { 
            return -1;
        }
        return x;
    }
    if(st==2) {  // if end time of last interval
        return -1;
    }
    return ftime(a,interval[st]+1,rem-(interval[st]-s+1)*rate[st]); // // when charging needed other interval to charge then
}

signed main() {
    //main function
    cout << "Enter no of vehicles\n";
    cin>>n;
    cout<<"Enter arrival, departure, charge needed for every EV\n";
    for(int i=0;i<n;i++) {
        int s,e,c;
      
        cin>>s>>e>>c;
        info[i]={s,e,c,i};
    }
    cout<<"Enter ending time of three interval\n";
    for(int i=0;i<3;i++) {
       
        cin>>interval[i];
    }
    cout<<"Enter rate of three time interval\n";
    for(int i=0;i<3;i++) {
       
        cin>>rate[i];
    }
    //sort according to priority based deadline if deadline same then first arrival
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = i+1 ; j < n ; j++)
        {
            if((info[i][1])>(info[j][1]))
            {
                swap(info[i],info[j]);
            }
            if((info[i][1])==(info[j][1]))
            {
                if(info[i][0]>info[j][0])
                {
                 swap(info[i],info[j]);
                }
            }
        }
    }
    // calling ftime to calulate ending time for EVS

    end_time.push_back(ftime(0,info[0][0],info[0][2]));
    for(int i = 1 ; i < n ; i++)
    {
        end_time.push_back(ftime(i , max(info[i][0],end_time[i-1]),info[i][2]));
    }
    // printing Solutions
    for(int i = 0 ; i < n ; i++)
    {
        cout<<"arrival and end time for EV "<<info[i][3]<<" \n";
        if(end_time[i] == INF)
        {
        cout<<"not possible to charge EV in given departure time \n";
        }
        else
        {
            cout << info[i][0] << " " <<end_time[i]<<"\n";
        }
    }
  

    return 0;
}