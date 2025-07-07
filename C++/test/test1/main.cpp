#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        for (int st = 0; st < (1 << n); st++) {  //st中1的数量决定了子集中元素个数，1的位置决定了第几个元素在子集内
            vector<int> tmp;  //tmp需要每次初始化
            for (int i = 0; i < n; i++) {
                if ((st >> i) & 1) tmp.push_back(nums[i]);
            }
            ret.push_back(tmp);
        }
        return ret;
    }
};

int main() {
    vector<int> nums = { 1, 2, 3 };  // 固定输入
    Solution sol;
    vector<vector<int>> result = sol.subsets(nums);

    cout << "[";
    for (int i = 0; i < result.size(); ++i) {
        cout << "[";
        for (int j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}
