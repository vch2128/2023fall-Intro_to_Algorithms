#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<limits>
#include<fstream>
#define ll long long
using namespace std;

vector< vector<long long int> > y;
vector<int> input;
ifstream fs;
ofstream ofs;

void cleary(){
    for(size_t i=0;i<y.size();i++){
        y[i].clear();
        y[i].resize(0);
    }
    y.clear();
    y.resize(0);
}

void printy(){
    for(size_t a=0;a<y.size();a++){
            for(size_t b=0;b<y[a].size();b++){
                if(y[a][b]==2147483649){
                    ofs<<"x";
                }
                else{
                    ofs<<y[a][b];
                }
                if(b!=y[a].size()-1){
                    ofs<<" ";
                }
            }
            ofs<<endl;
        }
}

void swap(int a,int b,int c,int d){
    ll temp=0;
    temp=y[a][b];
    y[a][b]=y[c][d];
    y[c][d]=temp;
}

int cmpi(ll t,ll u,ll l){
    if(u>=l){
        if(t<u){
            return 1;
        }
        else if(t<l){
            return 2;
        }
    }
    else{
        if(t<l){
            return 2;
        }
        else if(t<u){
            return 1;
        }
    }
    return 0;
}

bool cmpi2(ll t, ll o){
    if(o>t){
        return 1;
    }
    return 0;
}

int cmpe(ll t, ll r,ll d){
    if(r<=d){
        if(t>r){
            return 1;
        }
        else if(t>d){
            return 2;
        }
    }
    else{
        if(t>d){
            return 2;
        }
        else if(t>r){
            return 1;
        }
    }
    return 0;
}

bool cmpe2(ll t, ll o){
    if(t>o){
        return 1;
    }
    return 0;
}

void exheapify(int i,int j,int m,int n){
    int fl=0;
    if(i<m-1&&j<n-1){
        fl=cmpe(y[i][j],y[i][j+1],y[i+1][j]);
        if(fl==1){
            swap(i,j,i,j+1);
            exheapify(i,j+1,m,n);
        }
        else if(fl==2){
            swap(i,j,i+1,j);
            exheapify(i+1,j,m,n);
        }
    }
    else if(i==m-1&&j<n-1){
        fl=cmpe2(y[i][j],y[i][j+1]);
        if(fl==1){
            swap(i,j,i,j+1);
            exheapify(i,j+1,m,n); 
        }
    }
    else if(i<m-1&&j==n-1){
        fl=cmpe2(y[i][j],y[i+1][j]);
        if(fl==1){
            swap(i,j,i+1,j);
            exheapify(i+1,j,m,n); 
        }
    }
}

void insertheapify(int i,int j){
    int fl=0;
    if(i>0&&j>0){
        fl=cmpi(y[i][j],y[i-1][j],y[i][j-1]);
        if(fl==1){
            swap(i,j,i-1,j);
            insertheapify(i-1,j);
        }
        else if(fl==2){
            swap(i,j,i,j-1);
            insertheapify(i,j-1);
        }
    }
    else if(i>0&&j==0){
        fl=cmpi2(y[i][j],y[i-1][j]);
        if(fl==1){
            swap(i,j,i-1,j);
            insertheapify(i-1,j);
        }
    }
    else if(i==0&&j>0){
        fl=cmpi2(y[i][j],y[i][j-1]);
        if(fl==1){
            swap(i,j,i,j-1);
            insertheapify(i,j-1);
        }
    }
}

void readyoung(bool op){
    vector<long long int> temp;
    string line,t;
    stringstream ss,ss2;
    int k;
    cleary();
    if(op==1){
        input.clear();
        input.resize(0);
        getline(fs,line);
        ss<<line;
        while(1){
            ss>>k;
            if(ss.fail()){
                break;
            }
            input.push_back(k);
        }
    }
    getline(fs,line);
    while(line.size()!=1){
        ss.str("");
        ss.clear();
        temp.clear();
        temp.resize(0);
        ss<<line;
        while(1){
            ss>>t;
            if(ss.fail()){
                break;
            }
            if(t=="x"){
                temp.push_back(2147483649);
            }
            else{
                ss2<<t;
                ss2>>k;
                temp.push_back(k);
                ss2.str("");
                ss2.clear();
            }
        }
        y.push_back(temp);
        getline(fs,line);
    }
}

void insert(){    
    readyoung(1);
    int m,n;
    m=y.size();
    n=y[0].size();
    ofs<<"Insert";
    for(size_t i=0;i<input.size();i++){
        y[m-1][n-1]=input[i];
        insertheapify(m-1,n-1);
        ofs<<" "<<input[i];
    }
    ofs<<endl;
    printy();
}

void extract(){
    readyoung(0);
    int m,n;
    m=y.size();
    n=y[0].size();
    ofs<<"Extract-min "<<y[0][0]<<endl;
    y[0][0]=2147483649;
    exheapify(0,0,m,n);
    printy();
}

int main(){
    int t,op;
    string line;
    fs.open("input.txt");
    ofs.open("output.txt");
    
    if(fs.is_open()){
        fs>>t;
        while(t--){
            fs>>op;
            getline(fs,line);
            if(op==1){
                insert();
            }
            else if(op==2){
                extract();
            }
            if(t>0){
                ofs<<endl;
            }
        }
    }
    else{
        cout<<"fail";
    }

    fs.close();
    ofs.close();
    return 0;
}



/*
2
1
6 7
2 3 12 14
4 8 16 x
5 9 x x
x x x x

1
13
1 3 5
2 4 7
6 9 14
11 12 x


*/