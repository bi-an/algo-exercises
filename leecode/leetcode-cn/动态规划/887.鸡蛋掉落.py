# https://www.cnblogs.com/xym4869/p/12581145.html
// https://leetcode-cn.com/problems/super-egg-drop/solution/887-by-ikaruga/
# labuladong

# dp: 设 f(k,n) 为测试n层楼，当有k个鸡蛋时，最坏情况下，最少需要测试的次数。
# (1) 碎了，小明还剩下k-1个鸡蛋，i-1 层待测试楼层，于是问题变为 f(k-1, i-1)
# (2) 没碎，小明还剩下k个鸡蛋，n-i 层待测试楼层，于是问题变为 f(k, n-i)
# 公式中的"+1" : 因为第i层测试了一次

# @ref: labuladong
def superEggDrop(K: int, N: int) -> int:
    memo = dict() # 备忘录去重
    def dp(K, N):
        res = float('INF') # 如果在第一层楼碎了，那么res可以取0
        if  K==1: # K从1开始，因为K==1时，结果是确定的
            return N
        if N==0: # N从0开始，因为N==0时，结果是确定的；N==1时，结果不确定
            return 0
        # 避免重复计算
        if (K,N) in memo:
            return memo[(K,N)]
        # 穷举所有可能的选择
        for i in range(1,N+1):
            res = min(
                max(dp(K-1,i-1),dp(K,N-i))+1,
                res
            )
        # 记入备忘录
        memo[(K,N)]=res
        return res
    return dp(K,N)

if __name__ == "__main__":
    print(superEggDrop(2,100))
