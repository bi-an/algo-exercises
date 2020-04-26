//https://www.cnblogs.com/AndyJee/p/4693099.html

//题目1： 长为n的数组，每个数的范围在0~(n-1)

// 思路：对于已经排序好的数组，由于长度为n，每个数的范围为0~(n-1)，所以每个数都等于其下标
// 如果不等，我们就一直与其大小对应的下标的数交换，这样通过部分排序的方法，可以找出该数，而不需要全部排序.
//时间复杂度： O(n) ?
//空间复杂度： O(1)
class Solution
{
 public:
  // Parameters:
  //        numbers:     an array of integers
  //        length:      the length of array numbers
  //        duplication: (Output) the duplicated number in the array number
  // Return value:       true if the input is valid, and there are some duplications in the array number
  //                     otherwise false
  bool duplicate(int numbers[], int length, int *duplication)
  {
    if (!numbers || !duplication || length <= 0)
      return false;
    for (int i = 0; i < length; i++)
    {
      if (numbers[i] < 0 || numbers[i] > length - 1)
        return false;
    }
    for (int i = 0; i < length; i++)
    {
      while (numbers[i] != i)
      { //这里改成if也能在剑指offer上测试通过，但是不正确，如：int numbers[] = { 0,9,1,2,3,4,5,6,8,0 };
        int temp = numbers[i];
        if (numbers[temp] == temp)
        {
          *duplication = temp;
          return true;
        }
        swap(numbers[i], numbers[temp]);
      }
    }
    return false;
  }
};

//法二： hash表
//时间复杂度: O(n)
//空间复杂度: O(n)
class Solution
{
 public:
  bool duplicate(int numbers[], int length, int *duplication)
  {
    if (!numbers || !duplication || length <= 0)
      return false;
    for (int i = 0; i < length; i++)
    {
      if (numbers[i] < 0 || numbers[i] > length - 1)
        return false;
    }
    //另外：计算哈希表的实际长度：
    //方式1： 哈希表初始化为0, 然后对数字频次计数，if(hash>0) hash_size++;
    //方式2： 设置hash表的掩码
    //bool *mask = new bool[length];
    //for(int i=0;i<length;i++){
    //	mask[i]=false;
    //}
    int *hash = new int[length]();
    for (int i = 0; i < length; i++)
    {
      hash[numbers[i]]++;
      //mask[numbers[i]]=true;
    }
    for (int i = 0; i < length; i++)
    {
      if (hash[i] > 1)
      {
        *duplication = i;
        return true;
      }
    }
    return false;
  }
};

// 题目2： 不修改数组查找重复的数
// 长为n+1的数组，每个数在1~n范围（这就保证了必然有一个数是重复的，根据抽屉原则，可以用频次来找出这个重复的数，这是和题目1不同的地方。）
// 抽屉原则：抽屉编号0~(n-1)，二分搜索抽屉，重复的数必然在数的个数大于抽屉数的区间，再到这个区间去二分查找。
// 时间换空间：时间复杂度O(nlogn)，空间复杂度O(1)
class Solution
{
 public:
  bool duplicate(int numbers[], int length, int *duplication)
  {
    if (!numbers || !duplication || length <= 0)
      return false;
    int start = 1, end = length - 1;

    while (end >= start)
    {
      int middle = start + ((end - start) >> 1);
      int count = countRange(numbers, length, start, middle);
      if (end == start)
      {
        if (count > 1)
        {
          *duplication = start;
          return true;
        }
        else
        {
          break;
        }
      }
      if (count > middle - start + 1)
      {
        end = middle;
      }
      else
      {
        start = middle + 1;
      }
    }
    return false;
  }
  int countRange(const int *numbers, int length, int min, int max)
  {
    if (numbers == nullptr)
      return 0;
    int count = 0;
    for (int i = 0; i < length; i++)
    {
      if (numbers[i] >= min && numbers[i] <= max)
        count++;
    }
    return count;
  }
};
//点评：这个方法不能保证能找出所有重复的数，例如对于[2,3,4,2,3]来说，不能找出2，只能找出3：因为1~2之间有两个数，而2正好出现了两次。
//所以，使用这个方法不能用于题目1，题目1对应的频次可能相等（n个数：0~n-1）。
