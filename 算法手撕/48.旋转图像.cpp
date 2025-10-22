// 这一题的难点在于找到旋转的对应关系
// 1. 难点1，知道将整个矩阵给切换成4分
// 2. 难点2，知道每个部分的对应关系，i j之间的对应
/*
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int length = matrix.size();
        int end_1 = length / 2;
        int end_2 = -1;
        if (length % 2 == 0) {
            end_2 = length / 2;
        } 
        else {
            end_2 = (length + 1) / 2;
        }

        for(int i = 0; i < end_1; i++) {
            for (int j = 0; j < end_2; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[length - 1 -j][i];
                matrix[length - 1 - j][i] = matrix[length - 1 - i][length - 1 - j];
                matrix[length - 1 - i][length - 1 - j] = matrix[j][length - 1 -i];
                matrix[j][length - 1 - i] = temp;
            }
        }
    }
*/