#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        for (int st = 0; st < (1 << n); st++) {  //st��1�������������Ӽ���Ԫ�ظ�����1��λ�þ����˵ڼ���Ԫ�����Ӽ���
            vector<int> tmp;  //tmp��Ҫÿ�γ�ʼ��
            for (int i = 0; i < n; i++) {
                if ((st >> i) & 1) tmp.push_back(nums[i]);
            }
            ret.push_back(tmp);
        }
        return ret;
    }
};

int main() {
    vector<int> nums = { 1, 2, 3 };  // �̶�����
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
