//以下代码会缩短运行时间： 取消cin于stdin的同步
static const auto io_sync_off = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return nullptr;
}(); //lambda表达式，最后一个小括号表示调用，分号表示声明和定义

// 归并排序并统计逆序对数，排序是为了避免重复计算

class Solution
{
 public:
  static constexpr int P = 1000000007;
  int InversePairs(vector<int> data)
  {
    if (data.size() <= 1)
      return 0;

    vector<int> copy(data);
    int cnt = InversePairsCore(data, copy, 0, data.size() - 1);

    return cnt;
  }

  int InversePairsCore(vector<int> &data, vector<int> &copy, int begin, int end)
  { //注意： 参数传入必须是引用或者指针
    if (begin == end)
    {
      copy[end] = data[end];
      return 0;
    }

    int mid = (begin + end) / 2;
    int left = InversePairsCore(copy, data, begin, mid) % P;    // 记得交换copy和data
    int right = InversePairsCore(copy, data, mid + 1, end) % P; // 记得交换copy和data

    int cnt = 0;
    int pre = mid;
    int post = end;
    int cpIdx = end;
    while (pre >= begin && post >= mid + 1)
    {
      if (data[pre] > data[post])
      {
        cnt += post - mid;
        copy[cpIdx--] = data[pre--];
        if (cnt >= P) //数值过大求余
        {
          cnt %= P;
        }
      }
      else
      {
        copy[cpIdx--] = data[post--];
      }
    }

    for (; pre >= begin; pre--)
    {
      copy[cpIdx--] = data[pre];
    }

    for (; post >= mid + 1; post--)
    {
      copy[cpIdx--] = data[post];
    }

    return (cnt + left + right) % P; // 保证每次的返回数值都小于P
  }
};