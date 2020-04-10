#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
typedef long long ll;

void update_all_for_jump_n_from(int pos, int jump, ll cost, const vector<ll>& vec, vector<vector<ll>>& min_price_vec){
    /* debugging prints
    cout << "pos: " << pos << endl;
    cout << "jump: " << jump << endl;
    cout << "cost: " << cost << endl;
    cout << "-------------" << endl;
    */
    jump += 1;
    if (pos + jump >= vec.size()) return;
    int new_pos = pos + jump;
    ll new_cost = cost + vec[new_pos];

    if(new_cost < min_price_vec[new_pos][jump])
        min_price_vec[new_pos][jump] = new_cost;

    new_pos -= jump;
    new_cost += vec[new_pos];
    while (new_pos >= 1){
        if (new_cost < min_price_vec[new_pos][jump])
            min_price_vec[new_pos][jump] = new_cost;
        new_pos -= jump;
        new_cost +=vec[new_pos];
    }
}


int main() {
    int n;
    while (cin >> n){
        vector<ll> vec(n+1);
        vector<vector<ll>> min_price_vec(n + 1);
        for(int i = 0; i < n + 1; i++)
            for(int j = 0; j < n; j++)
                min_price_vec[i].push_back(LLONG_MAX);
        for (int i=1;i<n+1;i++)
            cin >> vec[i];
        min_price_vec[1][0] = 0;

        update_all_for_jump_n_from(1,0,0, vec,min_price_vec);
        for(int i = 1; i < n; i++){
            for (int j = 1; j < n; j++){
                if (min_price_vec[j][i] != LLONG_MAX)
                    update_all_for_jump_n_from(j,i,min_price_vec[j][i], vec,min_price_vec);
            }
        }


        /*    print the NxN matrix
        for(const auto& x:min_price_vec){
            for (auto y: x)
                cout << y << "  ";
            cout<<endl;
        }............
         */
        cout << *min_element(min_price_vec[n].begin(), min_price_vec[n].end())<<endl;
    }
}


