#include <assert.h>
#include <iostream>
#include <time.h>
using namespace std;

//https://www.cnblogs.com/angelye/p/7508292.html

//	--------------------------------------------------------------------------------------------------
//	排序法		最差时间分析		最好时间分析		平均时间复杂度				稳定度		空间复杂度
//	--------------------------------------------------------------------------------------------------
//	冒泡排序		O(n^2)							O(n^2)						稳定			O(1)
//	快速排序	    O(n2)							O(n*log2n)					不稳定		O(log2n)~O(n)
//	归并排序		O(nlogn)						O(nlogn)					稳定			O(n)或O(1)
//	选择排序	    O(n^2)							O(n^2)						不稳定		O(1)
//	二叉树排序	O(n^2)							O(n*log2n)					不一定		O(n)
//	插入排序		O(n^2)							O(n^2)						稳定			O(1)
//	堆排序		O(n*log2n)						O(n*log2n)					不稳定		O(1)
//	希尔排序		O(n^2)			O(nlogn)		depends on gap sequence		不稳定		O(1)
//	--------------------------------------------------------------------------------------------------

// 稳定： 两个相等数不会被交换位置。
// 内部排序：不需要借助辅助内存；
// 外部排序：借助辅助内存。

//快速排序的时间：主要在于比较和交换
//归并排序的时间：主要在于比较和内存复制？（有一个辅助内存）

class sortObj
{
 public:
  sortObj() : key(0) {}
  sortObj(int32_t val) : key(val) {}

  bool operator>(sortObj &obj2) const
  {
    return key > obj2.key;
  }
  bool operator>=(sortObj &obj2) const
  {
    return key >= obj2.key;
  }
  bool operator<(sortObj &obj2) const
  {
    return key < obj2.key;
  }
  bool operator<=(sortObj &obj2) const
  {
    return key <= obj2.key;
  }
  bool operator==(sortObj &obj2) const
  {
    return key == obj2.key;
  }

  //void* operator new(size_t sz) {
  //	void* m = malloc(sz);
  //	if (!m) printf("out of memory!\n");
  //	return m;
  //}

  //void* operator[](size_t pos) {//当只有一个成员变量时，编译器会生成一个默认的
  //	key=
  //}

  int32_t key;
  //int key2;
};

//冒泡排序，稳定
template <typename T>
void bubbleSort(T *arr, int len)
{
  if (len <= 0 || arr == nullptr)
    return;
  //int times_of_swap = 0;
  for (size_t i = 0; i < len - 1; i++)
  {
    for (size_t j = 0; j < len - 1 - i; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

//时间复杂度：最好：比较次数O(n)，交换次数O(1):正序时，比较n-1次，交换0次；
//最坏：比较O(n^2)，交换O(n^2): 逆序，比较(1+(n-1))*(n-1)/2次， 交换3*(1+(n-1))*(n-1)/2次。
//期望：比较O(n^2)，交换O(n^2)。
//稳定排序，相等的两个数的位置不会发生交换。
void bubbleSort(int numbers[], int size)
{
  if (numbers == nullptr || size <= 0)
    return;
  for (int i = size - 2; i >= 0; i--)
  { //总比较次数=(size-2)
    for (int j = 0; j <= i; j++)
    {
      if (numbers[j] > numbers[j + 1])
      {
        swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

//快速排序，不稳定，适用于大规模数组。对于小规模数组效率不高。平均效率最高。
//基本快排
//时间复杂度：最坏O(n^2)，比如对于已经排序的数组，而每次都选取最后一个元素的作为比较标准的时候。
//期望时间复杂度O(nlogn)。
template <class T>
void qSort(T *arr, int start, int end)
{
  int len = end - start + 1;
  if (arr == nullptr || len <= 1)
    return;
  T key = arr[start];
  size_t i = start;
  size_t j = end;
  while (i < j)
  {
    while (i < j)
    {
      if (arr[j] < key)
      {
        swap(arr[i], arr[j]);
        break;
      }
      j--;
    }
    while (i < j)
    {
      if (arr[i] > key)
      {
        swap(arr[i], arr[j]);
        break;
      }
      i++;
    }
  }
  qSort(arr, start, i - 1);
  qSort(arr, i + 1, end);
}

//随机化快排
//时间复杂度：虽然最坏情况仍然是O(n^2)，但最坏情况不再依赖于输入数据，而是由于随机函数取值不佳。
//			实际上，随机化快速排序得到理论最坏情况的可能性仅为1/(2^n)。
//			所以随机化快速排序可以对于绝大多数输入数据达到O(nlogn)的期望时间复杂度。
//一趟分割：在数组中找一个数字，比它小的放在左边， 比它大的放在右边。
int Partition(int numbers[], int len, int start, int end)
{
  if (numbers == nullptr || len <= 0 || start < 0 || end > len || start > end)
    return -1;
  int i = rand() % (end - start + 1) + start;
  swap(numbers[i], numbers[end]); //先存到数组的末尾
  int small = start - 1;
  for (i = start; i < end; i++)
  {
    if (numbers[i] < numbers[end])
    {
      ++small;        //small始终指向当前遍历到的左边值最后一个位置
      if (i != small) //此时index指向左边值的位置，small指向的是右边值的位置, 这个if好像可以去掉
        swap(numbers[i], numbers[small]);
    }
  }
  ++small;
  swap(numbers[small], numbers[end]); // 此时small指向随机选取的那个数
  return small;
}
//递归
void qSort(int numbers[], int size)
{
  if (numbers == nullptr || size <= 1)
    return;
  int i = Partition(numbers, size, 0, size - 1);
  if (i >= 1)
    qSort(numbers, i - 1);
  if (i < size - 1)
    qSort(numbers + i + 1, size - i - 1);
}

//平衡快排
//选择有代表性的数字作为比较标准，通常选择这个数据的方法是取开头、结尾、中间3个数据，通过比较选出其中的中值，一般该值接近实际中值。
//即使遇到两头大中间小的情况，即这个比较数字接近最值，那么也至少能将两部分分开，实际效率也会有2倍左右的增加，
//而且利于数据微打乱, 从而破坏退化的结构。

//归并排序，稳定排序，速度仅次于快速排序
//一般用于对总体无序，但是各子项相对有序的数列，应用见2011年普及复赛第3题“瑞士轮”的标程。
//时间复杂度：最好O(nlogn), 最坏O(nlogn)，平均O(nlogn)
//空间复杂度：如果使用辅助内存O(n)，如果使用链表O(1)
//应用：求逆序对
template <typename T>
void mergeSort(T *arr, int start, int end)
{
  if (arr == nullptr || end - start <= 0)
    return;
  int left = start;
  int mid = start + (end - start) / 2;
  int right = mid + 1;

  mergeSort(arr, start, mid);
  mergeSort(arr, mid + 1, end);
  int len = end - start + 1;
  T *tmpArr = new T[len];
  int pos = 0;
  while (left <= mid && right <= end)
  {
    if (arr[left] < arr[right])
      tmpArr[pos++] = arr[left++];
    else
      tmpArr[pos++] = arr[right++];
  }
  while (left <= mid)
    tmpArr[pos++] = arr[left++];
  while (right <= end)
    tmpArr[pos++] = arr[right++];
  memcpy(arr + start, tmpArr, sizeof(T) * len);
  delete[] tmpArr;
  tmpArr = nullptr;
}

//归并排序
//对两组分别有序的数，比较和合并，合并成一个有序的大序列
void merge(int sourceArr[], int tempArr[], int start, int middle, int end)
{
  //if (sourceArr == nullptr || tempArr == nullptr || end <= start) return;
  int left = start, right = middle + 1;
  int len = end - start + 1;
  int pos = start;
  while (left <= middle && right <= end)
  {
    if (sourceArr[left] < sourceArr[right])
      tempArr[pos++] = sourceArr[left++];
    else
      tempArr[pos++] = sourceArr[right++];
  }
  while (left <= middle)
    tempArr[pos++] = sourceArr[left++];
  while (right <= end)
    tempArr[pos++] = sourceArr[right++];
  memcpy(sourceArr + start, tempArr + start, sizeof(int) * len);
}
//递归最深处，两组数变成分别有序的，对其merge，退出该层递归，再merge，......
//递归是先进后出，也就是自上而下将变成自下而上，问题最终被分解成对两组分别有序的数，比较、排序、合并。
void mergeSort1(int sourceArr[], int tempArr[], int start, int end)
{
  if (sourceArr == nullptr || tempArr == nullptr || end <= start)
    return;
  int middle = (start + end) / 2;
  mergeSort1(sourceArr, tempArr, start, middle);
  mergeSort1(sourceArr, tempArr, middle + 1, end);
  merge(sourceArr, tempArr, start, middle, end);
}
void mergeSort(int sourceArr[], int len)
{
  int *tempArr = new int[len];
  mergeSort1(sourceArr, tempArr, 0, len - 1);
}

//插入排序
//插入排序的基本操作就是将一个数据插入到已经排好序的有序数据中
//算法适用于少量数据的排序，时间复杂度为O(n^2)。是稳定的排序方法
//基本思想是：每步将一个待排序的记录，按其关键码值的大小插入前面已经排序的文件中适当位置上，直到全部插入完为止。
//分为：直接插入排序、二分插入排序、希尔插入排序
//希尔排序法又称缩小增量法。希尔排序法的基本思想是：
//先选定一个整数，把待排序文件中所有记录分成个组，所有距离为的记录分在同一组内，并对每一组内的记录进行排序。
//然后，取，重复上述分组和排序的工作。
//当到达gap=1时，所有记录在统一组内排好序。

//直接插入排序
//从第一个数开始（1个数可以认为是排好序的数组），从当前位置出发，由后往前两两比较交换，则到达头部之后，这部分变成有序的。
void insert_sort_directly(int data[], int len)
{
  if (data == nullptr || len <= 1)
    return;
  int i = 1;
  while (i < len)
  {
    int j = i;
    while (j > 0 && data[j - 1] > data[j])
    {
      swap(data[j - 1], data[j]);
      j--;
    }
    i++;
  }
}

//二分插入排序
//平均比较次数: nlog2n 平均移动次数: n2/4  时间复杂度： O（n2）
//二分法找出要插入的准确位置，然后整个数组(排序好的部分）后移
void insert_sort_binary(int data[], int len)
{
  if (data == nullptr || len <= 1)
    return;
  int i = 1;
  while (i < len)
  {
    int x = data[i]; //待插入的数
    int right = i - 1;
    int left = 0;
    int pos = -1;
    while (left <= right)
    {
      int middle = (left + right) / 2;
      if (data[left] == x)
      {
        pos = left + 1; //插在data[left]的后面，保证稳定性
        break;
      }
      if (data[left] > x)
      {
        pos = left; //插在data[left]的前面
        break;
      }
      if (data[right] < x)
      {
        pos = right + 1; //插在data[right]的后面
        break;
      }
      if (data[middle] >= x)
        right = middle - 1;
      else
        left = middle + 1;
    }
    if (pos >= 0)
    {
      //swap(data[i], data[len - 1]);
      for (int jj = i; jj > pos; jj--)
      {
        data[jj] = data[jj - 1];
      }
      data[pos] = x;
    }
    i++;
  }
}

//希尔排序
//（直接插入排序的改进，实际为分组的直接插入排序）
//希尔排序的时间复杂度与增量序列的选取有关，例如希尔增量时间复杂度为O(n²)，而Hibbard增量的希尔排序的时间复杂度为O(n^(3/2)),
//希尔排序时间复杂度的下界是n*log2n.
//希尔排序没有快速排序算法快 O(n(logn))，因此中等大小规模表现良好，对规模非常大的数据排序不是最优选择。
//但是比O(n^2)复杂度的算法快得多。并且希尔排序非常容易实现，算法代码短而简单。
//此外，希尔算法在最坏的情况下和平均情况下执行效率相差不是很多，与此同时快速排序在最坏的情况下执行的效率会非常差。
//最后的1-gap排序，保证一定可以完成排序，希尔排序的好处在于减少了交换或者移动数字的次数。
//分析（比直接插入排序好的原因）：
//希尔排序是按照不同步长对元素进行插入排序，当刚开始元素很无序的时候，步长最大，所以插入排序的元素个数很少，速度很快；
//当元素基本有序了，步长很小，插入排序对于有序的序列效率很高。所以，希尔排序的时间复杂度会比o(n^2)好一些。
//采用Shell gap(希尔增量)
void shellSort(int data[], int len)
{
  if (data = nullptr || len <= 0)
    return;
  //int gap=len/2;
  for (int gap = len / 2; gap >= 1; gap /= 2)
    for (int i = 0; i < len; i++)
    {
      for (int j = gap; j < len; j += gap)
      {
        if (data[j - gap] > data[j])
          swap(data[j - gap], data[j]);
      }
    }
}

//对年龄排序，要求时间复杂度O(n)
void SortAges(int ages[], int len)
{
  if (ages == nullptr || len <= 0)
    return;

  const int oldestAge = 99;
  int timesOfAge[oldestAge + 1];
  for (int i = 0; i <= oldestAge; i++)
    timesOfAge[i] = 0;

  for (int i = 0; i < len; i++)
  {
    int age = ages[i];
    if (age < 0 || age > oldestAge)
      throw new exception("age out of range.");
    timesOfAge[age]++;
  }

  int pos = 0;
  for (int i = 0; i <= oldestAge; i++)
  {
    for (int j = 0; j < timesOfAge[i]; j++)
      ages[pos++] = i;
  }
}

//二分查找
//当有多个满足条件时，返回第一个下标
template <typename T>
int binarySearch(T *arr, int len, const T &key)
{
  if (arr == nullptr || len <= 0)
    return -1;
  int left = 0;
  int right = len - 1;
  int pos = -2;
  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    if (arr[mid] < key)
      left = mid + 1;
    else if (arr[mid] > key)
      right = mid - 1;
    else
    {
      pos = mid;
      break;
    }
  }
  if (pos < 0)
    return -1;
  while (arr[pos] == key)
    pos--;

  return pos + 1;
}

//二分查找
//当有多个满足条件时，任意返回一个满足条件的
template <typename T>
size_t binarySearch(T *arr, size_t len, const T &key)
{
  assert(arr != nullptr && len);
  size_t left = 0;
  size_t right = len - 1;
  while (left <= right)
  {
    size_t mid = left + (right - left) / 2;
    if (arr[mid] > key)
      right = mid - 1; //因为mid已经比较过了，所以下一次比较时，去掉这个numbers[mid]
    else if (arr[mid] < key)
      left = mid + 1;
    else
      return mid;
  }
  return len; //因为返回值为size_t, 而arr[len]不存在
}

//二分查找，自己写的，测试通过
//分析退出条件：可以列举size=1,size=2,size=3等情形。
int BiSearch_Iteratively(int numbers[], int size, int value)
{
  if (!numbers || size <= 0)
    return -1;
  int left = 0, right = size - 1;
  int pos = -1;
  while (left <= right)
  {
    int middle = (left + right) / 2; //right-left<=1时，middle==left
    //只要不重复比较middle处的值，这里可以注释掉。
    // if (middle == left) {
    // 	if (numbers[left] == value)
    // 		pos = left;
    // 	else if (numbers[right] == value)
    // 		pos = right;
    // 	break;
    // }
    if (numbers[middle] == value)
    {
      pos = middle;
      break;
    }
    else if (numbers[middle] > value)
      right = middle - 1; //middle下标处的数已经比较过了，下一次比较不需要计入；当然改成"right=middle;"也行，这时候if(middle==left){}部分不能去掉，则测试通过。
    else if (numbers[middle] < value)
      left = middle + 1;
  }
  return pos;
}

//Question: 这里能不能用template?->可以
int compr(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

template <class T>
bool comp(const T &a, const T &b)
{
  return a < b;
}

int min(int x, int y, bool (*comp)(const int &, const int &))
{
  if (comp(x, y))
    return x;
  else
    return y;
}

void test1()
{
  int x = 10, y = 20;
  int res = min(x, y, comp<int>); //res=10;
}

void test()
{
  int arr[10];
  const int len = sizeof(arr) / sizeof(int);
  srand(time(NULL));
  for (size_t i = 0; i < len; i++)
  {
    //srand(time(NULL));
    arr[i] = rand() % 101;
  }
  //for (size_t i = 0; i < len; i++) {
  //	printf("%d ", arr[i]);
  //}
  //printf("\n");

  int arr1[len];
  for (size_t i = 0; i < len; i++)
  {
    arr1[i] = arr[i];
  }
  qsort(arr1, len, sizeof(int), compr);
  //for (size_t i = 0; i < len; i++) {
  //	printf("%d ", arr1[i]);
  //}
  //printf("\n");

  //bubbleSort<int>(arr, 10);
  //qSort<int>(arr,0,len-1);
  //mergeSort<int>(arr,0,len-1);
  //for (size_t i = 0; i < len; i++) {
  //	printf("%d ",arr[i]);
  //}
  //printf("\n");

  //for (size_t i = 0; i < len; i++) {
  //	if (arr[i] != arr1[i]) {
  //		printf("Wrong!\n");
  //		return;
  //	}
  //}
  //printf("Correct!\n");
  int pos1 = rand() % len;
  arr1[pos1 - 1] = arr1[pos1];
  for (size_t i = 0; i < len; i++)
  {
    printf("%d ", arr1[i]);
  }
  printf("\n");
  int val = binarySearch(arr1, len, arr1[pos1]);
  printf("%d %d\n", val, arr1[pos1]);
  if (arr1[val] == arr1[pos1])
    printf("Correct!\n");
  else
    printf("Wrong!\n");
}
