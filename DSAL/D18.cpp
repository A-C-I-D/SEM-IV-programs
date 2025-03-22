//Given sequence k = k1 <k2 < … < kn of n sorted keys, with a search probability pi for each key ki. Build the Binary search tree that has the least search cost given the access probability for each key ?

#include <iostream>
#include <vector>
using namespace std;

class OBST {
    vector<int> keys;
    vector<float> prob;
    int n;

public:
    OBST(vector<int> k, vector<float> p) {
        keys = k;
        prob = p;
        n = k.size();
    }

    float optimalBST() {
        vector<vector<float>> cost(n, vector<float>(n, 0));
        vector<vector<float>> sum(n, vector<float>(n, 0));

        for (int i = 0; i < n; i++) {
            cost[i][i] = prob[i];
            sum[i][i] = prob[i];
        }

        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;
                sum[i][j] = sum[i][j - 1] + prob[j];
                cost[i][j] = INT_MAX;

                for (int r = i; r <= j; r++) {
                    float left = (r > i) ? cost[i][r - 1] : 0;
                    float right = (r < j) ? cost[r + 1][j] : 0;
                    float currCost = left + right + sum[i][j];

                    if (currCost < cost[i][j])
                        cost[i][j] = currCost;
                }
            }
        }
        return cost[0][n - 1];
    }
};

int main() {
    vector<int> keys = {10, 20, 30, 40};
    vector<float> prob = {0.1, 0.2, 0.4, 0.3};

    OBST obst(keys, prob);
    cout << "Minimum Cost of Optimal BST: " << obst.optimalBST() << endl;

    return 0;
}
