/*
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
        // 先确定四个边界
        // 这个题的难点在与边界的控制
        // 有点类似于脑筋急转弯
        
        int l1 = 0, l2 = matrix[0].size() - 1, l3 = matrix.size() - 1, l4 = 0;

        vector<int> result;

        while(true) {
            // 从左向右
            for (int i = l4; i <= l2; i++) result.push_back(matrix[l1][i]);
            if  (++l1 > l3) break;
            // 从上向下
            for (int i = l1; i <= l3; i++) result.push_back(matrix[i][l2]);
            if  (--l2 < l4) break;
            // 从右向左
            for (int i = l2; i >= l4; i--) result.push_back(matrix[l3][i]);
            if  (--l3 < l1) break;
            // 从上向下
            for (int i = l3; i >= l1 ;i--) result.push_back(matrix[i][l4]);
            if  (++l4 > l2) break;
        }

        return result;
    }
};
*/