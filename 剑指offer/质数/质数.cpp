//判断是否是质数
static bool isPrime(uint64_t num)
{
  if (num <= 1)
    return false;
  //两个较小数另外处理
  if (num == 2 || num == 3)
    return true;
  //不在6的倍数两侧的一定不是质数
  if (num % 6 != 1 && num % 6 != 5)
    return false;
  uint64_t tmp = uint64_t(std::sqrt(num));
  //在6的倍数两侧的也可能不是质数
  for (uint64_t i = 5; i <= tmp; i += 6)
    if (num % i == 0 || num % (i + 2) == 0) //如果能被6的倍数两侧的数整除，那么一定不是质数
      return false;
  //排除所有，剩余的是质数
  return true;
}

// 方法二： Sieve of Eratosthenes算法
// 左右都是闭区间
int countPrimes(int n)
{
  if (n <= 1)
    return 0;
  vector<bool> is_prime(n + 1, true);
  for (int i = 2; i * i <= n; i++)
  {
    if (i != 2 && i % 2 == 0)
      continue;
    if (is_prime[i])
      // i的倍数不可能是质数
      for (int j = i * i; j <= n; j += i) // j从i*i开始是为了降低重复计算
        is_prime[j] = false;
  }
  int cnt = 0;
  for (int i = 2; i <= n; i++)
  {
    if (is_prime[i])
      cnt++;
  }
  return cnt;
}
