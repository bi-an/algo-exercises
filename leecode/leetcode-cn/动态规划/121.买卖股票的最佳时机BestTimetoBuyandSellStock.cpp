/*
 * @Author: your name
 * @Date: 2020-10-15 14:55:18
 * @LastEditTime: 2020-11-19 10:34:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \leecode\leetcode-cn\动态规划\121. 买卖股票的最佳时机 Best Time to Buy and Sell Stock.cpp
 */
/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

// （1）尽可能以最低价格买入；
// （2）以最高价格卖出；
// （3）卖出时间一定要在买入之后。
class Solution
{
 public:
  int maxProfit(vector<int> &prices)
  {
    if (prices.empty())
      return 0;
    int min_price_pos = 0, max_profit = 0;
    for (int i = 1; i < prices.size(); i++)
    {
      int profit = prices[i] - prices[min_price_pos];
      if (profit > max_profit)
        max_profit = profit;
      else if (profit < 0)
        min_price_pos = i; // 说明min_price_pos处不是最低的买入价格, i处的买入价格更低
    }
    return max_profit;
  }
};


// @Athor zzg
class Solution_2 {
public:
    int maxProfit(vector<int>& prices) {
		if(prices.empty()) return 0;
        int cur_min = prices[0];
        int res = 0;
        for(int i = 0;i<prices.size();i++){
            int diff = prices[i] - cur_min;
            if(diff > res)
                res = diff;
            if(diff < 0)
                cur_min = prices[i];
        }
        return res;
    }
};