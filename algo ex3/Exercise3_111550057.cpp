#include<iostream>
#include<vector>
#include<algorithm>
#define vi vector<int>
using namespace std;

int n,m;
vector<vi> table;
vi memo;

int maxIncrease(int cur,int d){
    int mm=0;
    for(int i=0;i<min(d+1,n);i++){
        if(memo[d-i]!=-1 && table[i][cur]!=-1){
            mm=max(mm,memo[d-i]+table[i][cur]);
        }
    }
    return mm;
}

void highestScore(){
    for(int k=1;k<m;k++){
        vi temp((n-1)*m+1);
        temp=memo;
        for(int i=1;i<=(n-1)*(k+1);i++){
            memo[i]=maxIncrease(k,i);
        }
    }
}

void solve(){
    cin>>n>>m;
    table=vector<vi>(n,vi(m+1,0));
    vi firstrow(m+1,0);
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            int a;
            cin>>a;
            if(i==1){
                firstrow[j]=a;
            }
            else{
                table[i-1][j]=a-firstrow[j];
            }
        }
    }

    memo= vi((n-1)*m+1,0);
    for(int i=1;i<n;i++){
        memo[i]=table[i][0];
    }
    highestScore();

    int f=0;
    for(int i=0;i<firstrow.size();i++){
        f+=firstrow[i];
    }
    int q;
    cin>>q;
    while(q--){
        int d;
        cin>>d;
        cout<<memo[d-m]+f<<endl;
    }
    return;
}

int main(){
    int q;
    cin>>q;
    while(q--){
        solve();
    }
    return 0;
}