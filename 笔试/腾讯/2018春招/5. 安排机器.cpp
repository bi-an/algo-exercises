#define _CRT_SECURE_NO_WARNINGS

/*
解决方案：

1、对机器和任务都分别进行排序：时间从大到小，时间相同的按照等级由大到小（cmp完成）

2、对每一个任务进行循环：（第一个 for 循环）

     第一个 while 找到 时间上能够处理当前任务的机器（先忽略等级要求），然后将 cnt 中对应等级位置加一操作

     第二个 for 循环，看对应等级上，有没有机器可以处理相应的任务，while循环已经保证了时间上的可操作性
 ———————————————— 
版权声明：本文为CSDN博主「adao哒哒哒」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_39883358/article/details/88683264
*/

//安排机器
#include <algorithm>
#include <iostream>
#include <stdio.h>

using namespace std;
#define LL long long
const int maxn = 1e5 + 10;
struct node
{
  int time, grade;
} machine[maxn], task[maxn];

int cnt[105];

int cmp(node a, node b)
{
  if (a.time == b.time)
  {
    return a.grade > b.grade;
  }
  return a.time > b.time;
}

int main()
{
  int numMachine, numTask;
  scanf("%d%d", &numMachine, &numTask);
  for (int i = 0; i < numMachine; i++)
  {
    scanf("%d%d", &machine[i].time, &machine[i].grade);
  }
  for (int i = 0; i < numTask; i++)
  {
    scanf("%d%d", &task[i].time, &task[i].grade);
  }
  sort(machine, machine + numMachine, cmp);
  sort(task, task + numTask, cmp);
  //	for(int i=0;i<numMachine;i++){
  //		printf("%d %d\n",e[i].time,e[i].grade);
  //	}
  //	for(int i=0;i<numTask;i++){
  //		printf("%d %d\n",f[i].time,f[i].grade);
  //	}

  int num = 0;
  LL ans = 0;
  memset(cnt, 0, sizeof(cnt));
  int i, j, k;
  for (i = 0, j = 0; i < numTask; i++)
  { //对于每个任务而言
    while (j < numMachine && machine[j].time >= task[i].time)
    {
      cnt[machine[j].grade]++;
      j++;
    }
    // 为什么从最低等级开始寻找？因为最高等级100，可能没有机器，浪费查找时间。如果等级和难度匹配，就足够了；
    // 不匹配时，也只需要在难度以上依次寻找，没必要从最高开始找
    for (k = task[i].grade; k <= 100; k++)
    {
      if (cnt[k])
      {
        num++;
        cnt[k]--;
        ans = ans + 200 * task[i].time + 3 * task[i].grade;
        break;
      }
    }
  }
  printf("%d %lld\n", num, ans);
  return 0;
}

// @Athor zzg
#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

struct Node
{
  int time, grade;
};

// 按照时间由大到小排序；时间相同的，按照等级由大到小排序
// 贪心算法：由于收益=时间*200+等级*3，时间所占的比重大得多，所以优先执行耗费时间多的任务，相同时间再执行难度大的任务
// 但是，本题出得不严谨，因为时间取值为：1<=时长<=999；等级取值为：1<=等级<=100，也就是说时长最小步长为1*200，等级跨度为3*100
// 假设: (1)时长为1、等级为100；(2)时长为2，等级为1。此时应该选择第(1)个，而不是第(2)个。
// 例子：
// 1 2
// 999 100
// 2 1
// 1 100
// 答案： 1（个任务） 500（个收益）。贪心的错误答案收益是403
bool cmp(Node n1, Node n2)
{
  if (n1.time == n2.time)
    return n1.grade > n2.grade;
  return n1.time > n2.time;
}

int main()
{
  int numMachine, numTask;
  scanf("%d%d", &numMachine, &numTask);
  vector<Node> machines, tasks;
  for (int i = 0; i < numMachine; i++)
  {
    Node tmp;
    scanf("%d%d", &tmp.time, &tmp.grade);
    machines.push_back(tmp);
  }
  for (int i = 0; i < numTask; i++)
  {
    Node tmp;
    scanf("%d%d", &tmp.time, &tmp.grade);
    tasks.push_back(tmp);
  }

  std::sort(machines.begin(), machines.end(), cmp);
  std::sort(tasks.begin(), tasks.end(), cmp);

  int cnt[101]; // hashMap: 机器等级->该等级上满足条件的机器数量
  memset(cnt, 0, sizeof(cnt));

  int num = 0;       // 最多能执行的任务
  long long ans = 0; // 最大收益，注意：这里的ans可能很大，所以要用long long，printf时也要注意

  // j不断累加、第二个for循环中的cnt[k]--，用来保证分配过的机器不再被使用
  for (int i = 0, j = 0; i < numTask; i++)
  { // 遍历任务
    while (j < numMachine && tasks[i].time <= machines[j].time)
    {                           // 遍历机器，寻找时间上满足任务条件的机器
      cnt[machines[j].grade]++; // 注意到，machines和tasks的时间都是从大到小排序的，如果某台机器满足前面的任务，那么它一定也满足后面的任务
      j++; // 所以，j不需要（也不能）倒退回去重新遍历机器
    }
    for (int k = tasks[i].grade; k < 101; k++)
    { // 遍历hashMap cnt，寻找等级上满足任务条件的机器（上面的while循环保证了时间上满足条件）
      if (cnt[k])
      {
        cnt[k]--; // 该台机器已经被使用
        ans += 200 * tasks[i].time + 3 * tasks[i].grade;
        num++;
        break;
      }
    }
  }

  printf("%d %lld", num, ans); // 打印ans要用%lld

  return 0;
}

// 不能简单排序，实际上需要找的是delta_x=2内的最值点，可以用二维线段树或者二维RMQ做
// https://www.nowcoder.com/test/question/done?tid=26786021&qid=161635#summary