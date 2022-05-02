#include <bits/stdc++.h>
#define int long long
using namespace std;
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

int interval[3],rate[3],n,dp[(1LL<<MAXL)][2],info[MAXL][3];

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
    if((interval[st]>=s + (rem+rate[st]-1)/rate[st])) 
    {
        int x=s + max(0LL,(rem+rate[st]-1)/rate[st]); // charging lie within the interval then return the end time
        if(x>info[a][1]) { 
            return -1;
        }
        return x;
    }
    if(st==2){  // if end time of last interval
        return -1;
    }
    return ftime(a,interval[st]+1,rem-(interval[st]-s+1)*rate[st]); // when charging needed other interval to charge then
}
//main function
signed main() {

    cout<<"Enter no. of EVS\n";
    cin>>n;
    cout<<"Enter the arrival,departure and charge of every EVS\n";
    for(int i=0;i<n;i++) {
        for(int j=0;j<3;j++) {
            cin>>info[i][j];
        }
    }
    cout<<"Enter the ending time of morning, afternoon and evening respectively\n";
    for(int i=0;i<3;i++) {
        cin>>interval[i];
    }
    cout<<"Enter the rate of charging during morning, afternoon and evening respectively\n";
    for(int i=0;i<3;i++) {
        cin>>rate[i];
    }
    // dp[i][0] store min ending time for car
    // dp[i][1] store index of previous car
    for(int i=1;i<(1LL<<n);i++) {
        dp[i][0]=INF;
        for(int j=0;j<n;j++) {
            if(dp[i-(1LL<<j)][0]==INF || ((1LL<<j)&i)==0) {
                continue;
            }
            int finishtime = ftime(j,max(dp[i-(1LL<<j)][0],info[j][0]),info[j][2]);
            if(finishtime!=-1 && dp[i][0]>finishtime) {
                dp[i][0]=finishtime;
                dp[i][1]=j; //this car is placed
            }
        }
    }
    //finding how many maximum car can be charged
    int x=0,cntx=0;
    for(int i=0;i<(1LL<<n);i++) {
        if(dp[i][0]==INF) {
            continue;
        }
        int cnt=0;
        for(int j=0;j<n;j++) {
            if((1LL<<j)&i) {
                cnt++;
            }
        }
        if((cnt>cntx) || (cnt==cntx && dp[x][0]>dp[i][0])) {
            x=i;
            cntx=cnt;
        }
    }
    cout<<"In the most optimal solution, which maximizes no. of cars charged in least time, the following cars will be able to get fully charged\n";
    for(int i=0;i<n;i++) {
        if((1LL<<i)&x) {
            cout<<"EVS: "<<i<<" will get charged" <<"\n";
        }
    }
    cout<<"\n";
    vector<int>res[2]; //car no. , placed at start time
    int curr=x;
    // finding ending time for each car those can be charged within their departure time
    while(curr>0) {
        res[0].push_back(dp[curr][1]);
        res[1].push_back(dp[curr][0]);
        curr=curr-(1LL<<dp[curr][1]);
    }
    cout<<"The optimal solution is: {EVS no. , Time when car is placed }\n";
    for(int i=(int)res[0].size()-1;i>=0;i--) {
        
        cout<<res[0][i]<<" "<<res[1][i]<<"\n";
    }
    return 0;
}