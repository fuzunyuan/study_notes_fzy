// 这一题的难点在于不能使用除法
// 结题思路就是将给定的nums看成是二维，然后遍历两次即可
// 具体的细节如下:
/*
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        
        vector<int> result(nums.size(), 1);
        result[1] = nums[0];
        for(int i = 2; i < nums.size(); i++) {
            result[i] = result[i - 1] * nums[i - 1];
        }

        int temp = 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            temp = temp * nums[i + 1];
            result[i] = result[i] * temp;
        }

        return result;
    }
};
*/

// class Solution {
// public:
//     vector<int> productExceptSelf(vector<int>& nums) {
        
//     }
// };