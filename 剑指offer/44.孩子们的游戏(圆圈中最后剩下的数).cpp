/*
每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。
HF作为牛客的资深元老,自然也准备了一些小游戏。
其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。
每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,
从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。
请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)
*/

// 用环形链表模拟圆圈
class Solution
{
 public:
  int LastRemaining_Solution(int n, int m)
  {
    if (n == 0)
      return -1;
    if (m == 0)
      return n - 1;

    list<int> List; // list不是环形结构，所以每次到达List.end()要将其换成链表头List.begin()
    for (size_t i = 0; i < n; i++)
    {
      List.push_back(i);
    }
    int pos = 0;
    while (List.size() > 1)
    {
      pos += m - 1;       // pos不断累加，保证下一次循环从下一个小朋友开始
      pos %= List.size(); // list不是环形结构，所以每次到达List.end()要将其换成链表头List.begin()
      auto itr = List.begin();
      for (int i = 0; i < pos; i++)
        ++itr;
      List.erase(itr);
    }
    return List.front();
  }
};

// 优化思路：
// 1. 环形链表模拟圈，最重要的两步：itr=begin, list.size()每次都要重算。 所以，不需要list，只要每次保存list.size()和下一次的第一个人编号就可以。
// 2. 上面从n个人到最后一个人，这样会有很多重复运算（其实没有重复计算，与动态规划是一样的）-> 动态规划：从最后剩下的一个人倒推到第n个人。

//设f(n,m)表示最后的结果(当前选出的小朋友编号)（当前有n个小朋友）
class Solution
{
 public:
  int LastRemaining_Solution(int n, int m)
  {
    if (n < 1 || m < 1)
      return -1;
    int res = 0; //n=1时，f(n,m)=0
    for (size_t i = 2; i <= n; i++)
    {
      //res=(res+m)%n;//wrong
      res = (res + m) % i; //f(n,m)=[f(n-1,m)+m]%n, 这里的n实际上是i，需要不断迭代。 注释：表示在上一次的基础上，再沿环走m步
    }
    return res;
  }
};