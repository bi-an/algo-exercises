/*
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.

Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Note:
The n will be in the range [1, 1000].
*/

// 质因子分解

// 1. 质数的性质：
// 对于一个合数n(composite)，
// (1) 如果能被d=2整除，那么不断整除n；
// (2) d++=>d=3, 如果能被3整除，那么不断整除n；
// (3) d++=>d=4, n不可能被4整除，因为如果能被4整除，在第(1)步已经除完了；
// (4) d++=>d=5, 如果能被5整除，那么不断整除n；
// (5) d++=>d=6, n不可能被6整除，因为已经在第(1)(2)步已经除完了。
// 总结：这样下来，d一定是质数。这种方式是质因子分解。

// 2. 将步骤分组，每组一个C，若干P，C表示Copy，P表示Paste
// 例如CPPCPPPCPP，分组为[CPP] [CPPP] [CPP]，各组长度记为g_1, g_2, ... , g_i, ... 
// 则第1组操作完，得到g_1个'A'；
// 第2组操作完，得到g_1*g_2个'A'；
// 第i组操作完成，得到g_1*g_2*...*g_i个'A'。
// 而步骤总数为g_1+g_2+...+g_i+...+g_n.
// 这样，要得到N个'A', 即把N因式分解，使得各个因子之和最小:
// min sum=g_1+g_2+...+g_n 
// s.t. N=g_1*g_2*...*g_n

// 3. 为什么要质因子分解？
// 如果某个因子g_i为合数，那么g_i=p*q，因为(p-1)*(q-1)>=1, 当p>=2,q>=2，所以此时p*q>=p+q
// 即 g_i=p*q>=p+q，所以g_i应该再次分解，分解结果使得sum变小。

// 质因子分解
class Solution {
public:
    int minSteps(int n) {
        if(n<=0) return 0;
        int sum=0, d=2; // 由于d从2开始累加，所以这是质因子分解，原因见上面第1点
        while(n>1){
        	while(n%d==0){ // 如果能整除d，则用n一直整除d
        		sum+=d;
        		n/=d;
        	}
        	d++;
        }
        return sum;
    }
};