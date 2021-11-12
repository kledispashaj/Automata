//
// Created by Kledis on 20-Feb-20.
//
//Dfa minimization using Table filling method

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;

const int N = 100;

int t[N][N]; // transition table
bool fs[N]; // final states
bool marked[N][N];
vector<int>  ec[N]; // set of equivalence classes
int total; //number of states of the new dfa

// n is no of states, m is no of input symbols
int n, m;

// Returns the index of the equivalence class
int check(int q){
    for (int i = 0; i < total; i++) {
        for (int j = 0; j <ec[i].size() ; j++) {
            if (ec[i][j]==q)
                return i;
        }
    }
return -1;
}

// Prints the minimised DFA
void print_min(){
    for (int i = 0; i < total; i++) {
        cout<<"[";
        for(int el:ec[i])
            cout<<el;
        cout<<"]\t";

        for (int j = 0; j < m; j++) {
           int a= check(t[ec[i][0]][j]);
            cout<<"[";
            for(int el:ec[a])
                cout<<el;
            cout<<"]\t";
        }
        cout<<endl;
    }
}

int main(){

    cout<<"Vendosni nr e gjendjeve: ";
    cin>>n;
    cout<<"Vendosni nr e simboleve: ";
    cin>>m;
    int tmp;
    cout<<"Vendosni nr e gjendjeve fundore: ";
    cin>>tmp;
    cout<<"Vendosni gjendjet fundore: ";
    for (int l = 0; l < tmp; ++l) {
        int tmp2;
        cin>>tmp2;
        fs[tmp2]=1;
    }
    cout<<"Plotesoni tabelen e kalimeve: ";
    // Input transition table:
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> t[i][j];
        }
    }
    //find reachable states
    set <int> reachable;
    reachable.insert(0);
    int s1=1;
    int s2=0;

    while(s1!=s2){
        s1=reachable.size();
        set <int> :: iterator itr;
        for (itr = reachable.begin(); itr != reachable.end(); ++itr){
            for (int i = 0; i < m; i++) {
                reachable.insert(t[*itr][i]);
            }
        }
        s2=reachable.size();
    }
    //print reachable states
    set <int> :: iterator itr;
    for (itr = reachable.begin(); itr != reachable.end(); ++itr){
        cout<<*itr<<" ";
        }

    //mark (final,non final) pairs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if(fs[i]!=fs[j])
                marked[i][j]=1;
        }
    }

    bool a=true;
    //mark other pairs
    while (a) {
        a = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (!marked[i][j]) {
                    for (int k = 0; k < m; k++) {
                        if (t[i][k] == t[j][k])
                            continue;
                        if (t[i][k] > t[j][k]) {
                            if (marked[t[i][k]][t[j][k]]) {
                                marked[i][j] = 1;
                                a = true;
                            }
                        } else if (marked[t[j][k]][t[i][k]]) {
                            marked[i][j] = 1;
                            a = true;
                        }
                    }
                }
            }
        }
    }

    //insert unmarked states to equivalent classes table
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < k; i++) {
            if (!marked[k][i]&&(reachable.find(k) != reachable.end())&&(reachable.find(i) != reachable.end())){
                int a =check(k);
                int b= check(i);
                if(a==b){
                    if(a!=-1)
                        continue;
                    else {
                        ec[total].push_back(k);
                        ec[total].push_back(i);
                        total++;
                    }
                }
               else if(a==-1)
                    ec[b].push_back(k);
               else if (b==-1)
                    ec[a].push_back(i);
            }
        }
    }
    //insert remaining states
    for (itr = reachable.begin(); itr != reachable.end(); ++itr){
        if(check(*itr)==-1)
            ec[total++].push_back(*itr);
    }
    
   //print the table of marking
    for (int k = 0; k < n; k++) {
        cout<<"R"<<k<<": ";
        for (int i = 0; i < k; i++) {
            cout<<marked[k][i];

        }
        cout<<endl;

    }
    cout<<endl;

    for (int i = 0; i < total; i++) {
        sort(ec[i].begin(), ec[i].end());
    }
    print_min();

    return 0;
}

