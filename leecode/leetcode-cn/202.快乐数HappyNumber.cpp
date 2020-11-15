/*
快慢指针法：
fast每次计算两次平方和，slow每次计算1次平方和
当slow==fast时，说明到达循环点
此时判断循环是否是由1引起的，是则是快乐数，否则不是快乐数。
*/

class Solution
{
 public:
  int digitSquareSum(int n)
  {
    int sum = 0, tmp;
    while (n)
    {
      tmp = n % 10;
      sum += tmp * tmp;
      n /= 10;
    }
    return sum;
  }

  bool isHappy(int n)
  {
    int slow, fast;
    slow = fast = n;
    do
    {
      slow = digitSquareSum(slow);
      fast = digitSquareSum(fast);
      fast = digitSquareSum(fast); // 如果平方和达到1，那么之后的平方和将一直是1
    } while (slow != fast);        //  Floyd Cycle detection algorithm. 弗洛伊德判圈算法
    return slow == 1;
  }
};