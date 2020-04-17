
// 快速排序标准写法
// https://en.wikipedia.org/wiki/Quicksort
// 一趟分割
// 交换次数：small值的个数+1(选取的元素)
int Partition(int *arr, int lo, int hi)
{
  int pivot = arr[hi]; // 选取最后一个元素作为比较标准pivot
  int i = lo;          //i指向应该存放下一个small值的位置
  for (int j = lo; j <= hi - 1; j++)
  {
    if (arr[j] < pivot)
    { // 把每一个small值换到相应位置
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[hi]);
  return i; // 返回分割后的pivot的位置
}

void quickSort(int *arr, int lo, int hi)
{
  if (arr == nullptr || lo > hi || lo < 0 || hi < 0)
    return;

  int index = Partition(arr, lo, hi);

  quickSort(arr, lo, index - 1);

  quickSort(arr, index + 1, hi);
}

// 快速排序： 随机化快排
// 交换次数：small值的个数+2(选取的元素交换了2次)
int Partition(int *arr, int lo, int hi)
{
  int pos = rand() % (hi - lo + 1) + lo;
  int pivot = arr[pos];
  swap(arr[pos], arr[hi]); //总结：也就多交换了这一步

  int i = lo; //i指向下一个small位置
  for (int j = lo; j < hi; j++)
  {
    if (arr[j] < pivot)
    { //把每一个small值换到相应位置
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[hi]);
  return i;
}