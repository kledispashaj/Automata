//
// Created by Kledis on 15-Feb-20.
//
// NFA TO DFA


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N=100;
int n, m;
vector<int> nfa[N][N]; //  nfa table
int dfa[N][N]; //  dfa table with entries into ds
vector<int> ds[N]; // stores the union of nfa states
int total; // total no. of states of dfa

void print_dfa() {
    cout << endl;
    for(int i=0; i<total; i++) {

        cout << "[";
        for(int el: ds[i])
            cout << el;
        cout << "]\t";

        for(int j=0; j<m; j++) {
            cout << "[";
            for(int el: ds[dfa[i][j]] )
                cout << el;
            cout << "]\t";
        }
        cout << endl;
    }
    cout << endl;
}


int main() {

    cout << "Vendosni nr e gjendjeve: ";
    cin >> n;
    cout << "Nr i simboleve: ";
    cin >> m;
    cout << "Vendosni kalimet:\n\n";

    // Transition table nfa
    for(int i=0; i<n; i++) {
        cout << "Gjendja " << i << endl;
        for(int j=0; j<m; j++) {

            cout << "Nr i kalimeve per ";
            cout << char(j + 'a');
            cout << ": ";
            int no; cin >> no;
            nfa[i][j].resize(no);
            if(no == 0)
                continue;
            if(no == 1)
                cout << "Vendosni gjendjen: ";
            else
                cout << "Vendosni" << no << " gjendjet: ";

            for(int k=0; k<nfa[i][j].size(); k++) {
                cin >> nfa[i][j][k];
            }
        }
        cout << endl;
    }


    queue<int> q;

    // add {0} as the initial state
    vector<int> v;
    v.push_back(0); q.push(0);
    ds[total++] = v;

    // keep adding new states reachable from initial state
    while(!q.empty()) {

        int top = q.front();
        q.pop();

        //find the possible set of states for each input symbol.
        for(int j=0; j<m; j++) {
            vector<int> temp;
            for(int i=0; i < ds[top].size(); i++) {
                for(int el: nfa[ds[top][i]] [j])
                    temp.push_back(el);
            }

            sort(temp.begin(), temp.end());
            temp.resize(unique(temp.begin(), temp.end()) - temp.begin());

            // check if this state (temp) is encountered before
            int index = -1;
            for(int i=0; i<total; i++) {
                if(ds[i] == temp) {
                    index = i;
                    break;
                }
            }
            if(index == -1) {
                ds[total] = temp;
                dfa[top][j] = total;
                q.push(total);
                total++;
            }
            else {
                dfa[top][j] = index;
            }

        }
    }

    print_dfa();

    return 0;
} 
  