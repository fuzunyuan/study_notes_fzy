// 394. 字符串解码

// 给定一个经过编码的字符串，返回它解码后的字符串。

// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 测试用例保证输出的长度不会超过 105。

 

// 示例 1：

// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"
// 示例 2：

// 输入：s = "3[a2[c]]"
// 输出："accaccacc"
// 示例 3：

// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"
// 示例 4：

// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"

// 解题思路还是使用两个栈来实现

// class Solution {
// public:
//     string decodeString(string s) {
//         stack<string> string_stack;
//         stack<int> number_stack;

//         int temp_number = 0;
//         string temp_string = "";

//         for (char a: s) {
//             if (a >= '0' && a <= '9') {
//                 temp_number = temp_number * 10 + a - '0';
//             } else if (a >= 'a' && a <= 'z'){
//                 temp_string += a;
//             } else if ( a == '[') {
//                 number_stack.push(temp_number);
//                 temp_number = 0;
                
//                 string_stack.push(temp_string);
//                 temp_string = "";
//             } else if (a == ']') {
//                 int k = number_stack.top();
//                 number_stack.pop();
                    // 这个地方是一个难点，解决嵌套的难点的地方
//                 string temp_1 = "";
//                 for (int i = 0; i < k - 1;i++) {
//                     temp_1 += temp_string;
//                 }

//                 temp_string += temp_1;
//                 temp_string = string_stack.top() + temp_string;
//                 string_stack.pop();
//             }
//         }

//         return temp_string;


//     }
// };