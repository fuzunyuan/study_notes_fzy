// 这道题的难点在于，将整个矩阵看作是45°旋转
// 如果值比matrix[i][j] 大，那么就 j++
// 如果值比matrix[i][j] 小，那么就 i--
/*
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int length_1 = matrix.size();
        int length_2 = matrix[0].size();

        int i = length_1 - 1;
        int j =  0;

        while( i >= 0 && j < length_2) {
            if (target == matrix[i][j]) {
                return true;
            } else if (target > matrix[i][j]) {
                j++;
            } else {
                i--;
            }
        } 

        return false;
        
    }
};
*/