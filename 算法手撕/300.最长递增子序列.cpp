/*
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums.size();
        }
        vector<int> result(nums.size(), 1);
        int max_final = result[0];
        for(int i = 1; i < nums.size(); i++) {
            for(int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    result[i] = max(result[j] + 1, result[i]);
                }
            }
            
            if (max_final < result[i]) {
                max_final = result[i];
            }
        }

        return max_final;
    }
};
*/