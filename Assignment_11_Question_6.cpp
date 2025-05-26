#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

void backTracking(const vector<int>& set, int n, int index, vector<int>& subset1, vector<int>& subset2, 
                                int sum1, int sum2, int& minDiff, vector<int>& best1, vector<int>& best2) {

    if (n % 2 == 0) { //Check Valid Subsets Sizes
        if (subset1.size() > n / 2 || subset2.size() > n / 2) return;
    } else {
        if (subset1.size() > (n + 1) / 2 || subset2.size() > (n + 1) / 2) return;
    } 

    if (index == n) { // Base case: all elements have been considered
        int diff = abs(sum1 - sum2);
        if (diff < minDiff) { // Check if the current subsets have a smaller difference
            minDiff = diff; 
            best1 = subset1;
            best2 = subset2;
        }
        return;
    }

    // Include current element in subset1
    subset1.push_back(set[index]);
    backTracking(set, n, index + 1, subset1, subset2, sum1 + set[index], sum2, minDiff, best1, best2);
    subset1.pop_back();

    // Include current element in subset2
    subset2.push_back(set[index]);
    backTracking(set, n, index + 1, subset1, subset2, sum1, sum2 + set[index], minDiff, best1, best2);
    subset2.pop_back();
}

int main() {
    vector<int> set = {7, 2, 5, 9, 12, 4, 8, 6, 1, 14};
    int n = set.size();

    vector<int> subset1, subset2;
    vector<int> best1, best2;
    int minDiff = INT_MAX;

    backTracking(set, n, 0, subset1, subset2, 0, 0, minDiff, best1, best2);

    int sum1 = accumulate(best1.begin(), best1.end(), 0);
    int sum2 = accumulate(best2.begin(), best2.end(), 0);

    cout << "Subset 1 = {";
    for (int num : best1) cout << num << " ";
    cout << "} and Subset 2 = {";
    for (int num : best2) cout << num << " ";
    cout << "}, both have sum = " << sum1 << " and " << sum2 << endl;

    return 0;
}