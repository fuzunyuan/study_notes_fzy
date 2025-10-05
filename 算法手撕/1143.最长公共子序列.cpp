// 这一题难点在与i j 循环过程中下标的变化

/*
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1, 0));

        int result = 0;
        for (int i = 1; i <= text1.size(); i++) {
            for(int j = 1; j <= text2.size();j++){

                if (text2[j-1] == text1[i-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }

                if (dp[i][j] > result) {
                    result = dp[i][j];
                }

            }

        }

        return result;
    }
};*/