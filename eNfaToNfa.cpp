//
// Created by Kledis on 17-Feb-20.

//(e-NFA) to NFA

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int N=100;
int n, m;
vector<int> enfa[N][N], nfa[N][N];
set<int> closure[N];

void print_nfa() {

    for(int i=0; i<n; i++) {
        cout << "Q" << i << "\t";
        for(int j=0; j<m; j++) {
            cout << "{ ";
            for(int el: nfa[i][j]) cout << el << " ";
            cout << "}\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    cout << "Vendosni nr e gjendjeve ";
    cin >> n;
    cout << "Vendosni nr e simboleve";
    cin >> m;
    cout << "Vendosni kalimet:\n\n";

    // Transition table
    for(int i=0; i<n; i++) {
        cout << "Gjendja " << i << endl;
        for(int j=0; j<=m; j++) {

            cout << "Nr i kalimeve per ";
            if(j == 0)
                cout << "eps";
            else cout << char(j + 'a' - 1);
            cout << ": ";
            int temp; cin >> temp;
            enfa[i][j].resize(temp);
            if(temp == 0)
                continue;
            if(temp == 1)
                cout << "Vendosni gjendjen: ";
            else
                cout << "Vendosni " << temp << " gjendjet: ";

            for(int k=0; k<enfa[i][j].size(); k++) {
                cin >> enfa[i][j][k];
            }
        }
        cout << endl;
    }

    // Find epsilon closure for each state
    for (int i = 0; i < n; i++) {
        closure[i].insert(i);
        int s1 = 1;
        int s2 = 0;

        while (s1 != s2) {
            s1 = closure[i].size();
            set<int>::iterator itr;
            for (itr = closure[i].begin(); itr != closure[i].end(); ++itr) {
                for (int j = 0; j < enfa[*itr][0].size(); j++) {
                    closure[i].insert(enfa[*itr][0][j]);
                }
            }
            s2 = closure[i].size();
        }
    }


    // Find epsilon* --> symbol --> epsilon* for each state and symbol
    for(int i=0; i<n; i++) {
        for(int ii: closure[i]) {
            for(int j=1; j<=m; j++) {  						//loop symbols ,skip j=0->epsilon
                for(int k=0; k<enfa[ii][j].size(); k++) {
                    int cur = enfa[ii][j][k];
                    for(int iii: closure[cur]) {
                        if(find(nfa[i][j-1].begin(), nfa[i][j-1].end(), iii) == nfa[i][j-1].end())
                            nfa[i][j-1].push_back(iii);
                    }
                }
            }
        }
    }

    print_nfa();

    return 0;
} 
  