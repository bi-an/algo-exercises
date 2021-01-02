/*
求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？
为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,
但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,
可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。
*/

// 非递归 《编程之美·2.4 1的数目》
// 将数分成个位、十位、百位、......分别统计，例如n=13时，个位为1有1、11，十位为1有10、11、12、13，注意到11被统计了两次，但是11中恰好有两个1，正确。
// 一个数abcde,
// 个位为1的次数:(1)e=0时，iCount+=abcd; (举例分析: 如12340, 当个位为1，其他位可以为0~1233，也即这些数共有1234，就是abcd个)
//				(2)e=1时，iCount+=abcd*10^0+0+1; (如12341，当各位为1，其他位可以为0~1234，也即这些数共有abcd+1个)
// 				(3)e>1时，iCount+=(abcd+1)*10^0; (如12345，当各位为1，其他位可以为0~1234，共有abcd+1个)
// 十位为1的次数:(1)d=0时，iCount+=abc*10^1; (如果12305，当十位为1，高位可以为0~122，同时低位(个位)可以为0~9，共有abc*10个)
//				(2)d=1时，iCount+=abc*10^1+e+1; (如果12315，当十位为1，高位可以为122，同时低位可以为0~9；或者高位为123，同时低位为0~5；共有abc*10+e+1个)
//				(3)d>1时，iCount+=(abc+1)*10^1;
// 百位为1的次数:(1)c=0时，iCount+=(ab*10^2);
//				(2)c=1时，iCount+=(ab*10^2)+de+1;
//				(3)c>1时，iCount+=(ab+1)*10^2;
class Solution
{
 public:
  int NumberOf1Between1AndN_Solution(int n)
  {
    int iLowerNum = 0;
    int iHigherNum = 0;
    int iCurrNum = 0;
    int iFactor = 1;
    int iCount = 0;
    while (n / iFactor != 0)
    {
      iLowerNum = n - n / iFactor * iFactor;
      iCurrNum = n / iFactor % 10;
      iHigherNum = n / (iFactor * 10);

      switch (iCurrNum)
      {
        case 0:
          iCount += iHigherNum * iFactor;
          break;
        case 1:
          iCount += iHigherNum * iFactor + iLowerNum + 1;
          break;
        default:
          iCount += (iHigherNum + 1) * iFactor;
      }
      iFactor *= 10;
    }
    return iCount;
  }
};

// 写法2
class Solution
{
 public:
  int NumberOf1Between1AndN_Solution(int n)
  {
    int iHigh = n, cnt = 0, iFactor = 1, iCurr = 0;
    while (iHigh)
    {
      iCurr = iHigh % 10;
      iHigh /= 10;
      if (iCurr == 0)
      {
        cnt += iHigh * iFactor;
      }
      else if (iCurr == 1)
      {
        cnt += iHigh * iFactor + n % iFactor + 1;
      }
      else
      {
        cnt += (iHigh + 1) * iFactor;
      }
      iFactor *= 10;
    }
    return cnt;
  }
};

// 找规律，递归 《剑指offer》
// 例如21345, 分成两段1~1345和1346~21345
// 先求第二段，第一段可以递归。
// 1出现在最高位时，(1)有10000~19999，即有10^4个；(2)如果数字最高位为1而不是2，例如数字是12345而不是21345，那么只有10000~12345，就是2345个；
// 1出现在其他位时，由于最高位为2，再分成两段1346~11345和11346~21345；
//				   对每一段，其他位任意一位为1，除去最高位外其他位可以为0~999，
//                 例如1346~11345，若次高位为1，(a)最高位为1，其他位可以为000~345；(b)最高位为0，其他位可以位346~999；总共10^3；
//		           所以是2*10^3.
class Solution
{
 public:
  int NumberOf1Between1AndN_Solution(int n)
  {
    char strN[50];
    //sprintf_s(strN,sizeof(strN),"%d",n);
    sprintf(strN, "%d", n);

    int first = *strN - '0';
    size_t len = strlen(strN);

    if (first == 0 && len == 1)
      return 0;
    if (first > 0 && len == 1)
      return 1; //后面的atoi(strN+1)的前提是len>1

    int numFirstDigit = 0;
    if (first > 1)
      numFirstDigit = pow(10, len - 1);
    else if (first == 1)
      numFirstDigit = atoi(strN + 1) + 1;

    int numOtherDigits = 0;
    numOtherDigits = first * (len - 1) * pow(10, len - 2);

    int numRecusive = NumberOf1Between1AndN_Solution(atoi(strN + 1));
    return numFirstDigit + numOtherDigits + numRecusive;
  }
};
