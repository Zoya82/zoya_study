#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;  // ��¼����һ�κͳ������ε�λ
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;  // ��һ�γ��ֵ�λ��¼�� ones  ���ģ�������1�ĵ���
            twos = (twos ^ num) & ~ones;  // �ڶ��γ��ֵ�λ��¼�� twos
        }
        return ones;  // ֻ����һ�ε������ձ����� ones
    }
};

int main() {
    vector<int> nums = { 2,3,99,2,3,2,3 };
    Solution sol;
    cout << "ֻ����һ�ε�Ԫ����: " << sol.singleNumber(nums) << endl;
    return 0;
}
