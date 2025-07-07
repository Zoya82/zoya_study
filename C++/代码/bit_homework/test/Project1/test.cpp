#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;  // 记录出现一次和出现两次的位
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;  // 第一次出现的位记录在 ones  核心：二进制1的抵消
            twos = (twos ^ num) & ~ones;  // 第二次出现的位记录在 twos
        }
        return ones;  // 只出现一次的数最终保留在 ones
    }
};

int main() {
    vector<int> nums = { 2,3,99,2,3,2,3 };
    Solution sol;
    cout << "只出现一次的元素是: " << sol.singleNumber(nums) << endl;
    return 0;
}
