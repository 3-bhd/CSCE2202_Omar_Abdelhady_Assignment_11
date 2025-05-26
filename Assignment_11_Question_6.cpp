#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

// Backtracking with pruning
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

// DP with pruning (tracks subset size)
int findMinDifference(vector<int>& arr, int n, 
                      int sumCalculated, int sumTotal,  
                      vector<vector<vector<int>>>& memo,
                      int subsetSize = 0, int maxSubsetSize = -1) {

    if (maxSubsetSize == -1) {
        maxSubsetSize = (arr.size() % 2 == 0) ? arr.size() / 2 : (arr.size() + 1) / 2;
    }

    // Prune if subset size exceeds allowed
    if (subsetSize > maxSubsetSize) {
        return INT_MAX;
    }

    // Base case: all elements considered
    if (n == 0) {
        // Only accept if both subset sizes are valid
        if (subsetSize <= maxSubsetSize && (arr.size() - subsetSize) <= maxSubsetSize) {
            return abs((sumTotal - sumCalculated) - sumCalculated);
        } else {
            return INT_MAX;
        }
    }

    // Memoization check
    if (memo[n][sumCalculated][subsetSize] != -1) {
        return memo[n][sumCalculated][subsetSize];
    }

    // Include current element in subset1 (increase subsetSize)
    int include = findMinDifference(arr, n - 1, 
                    sumCalculated + arr[n - 1], sumTotal, memo, subsetSize + 1, maxSubsetSize);

    // Exclude current element from subset1 (goes to subset2, subsetSize unchanged)
    int exclude = findMinDifference(arr, n - 1, 
                    sumCalculated, sumTotal, memo, subsetSize, maxSubsetSize);

    // Store and return
    return memo[n][sumCalculated][subsetSize] = min(include, exclude);
}

int main() {
    vector<int> set = {7, 2, 5, 9, 12, 4, 8, 6, 1, 14};
    int n = set.size();

    vector<int> subset1, subset2;
    vector<int> best1, best2;
    int minDiff = INT_MAX;

    cout << "Using Backtracking:" << endl;
    backTracking(set, n, 0, subset1, subset2, 0, 0, minDiff, best1, best2);

    int sum1 = accumulate(best1.begin(), best1.end(), 0);
    int sum2 = accumulate(best2.begin(), best2.end(), 0);

    cout << "Subset 1 = {";
    for (int num : best1) cout << num << " ";
    cout << "} and Subset 2 = {";
    for (int num : best2) cout << num << " ";
    cout << "}, both have sum = " << sum1 << " and " << sum2 << endl;

    cout << "Using Dynamic Programming:" << endl;
    int sumTotal = accumulate(set.begin(), set.end(), 0);
    int maxSubsetSize = (n % 2 == 0) ? n / 2 : (n + 1) / 2;
    vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(sumTotal + 1, vector<int>(maxSubsetSize + 2, -1)));
    int minDifference = findMinDifference(set, n, 0, sumTotal, memo, 0, maxSubsetSize);
    cout << "Minimum difference between two subsets = " << minDifference << endl;
    cout << "Subset 1 sum = " << sum1 << ", Subset 2 sum = " << sum2 << endl;
    cout << "Minimum difference = " << abs(sum1 - sum2) << endl;

    return 0;
}