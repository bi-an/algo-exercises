//https://www.cnblogs.com/PrayG/p/5749832.html

//scanf()比cin快很多
//getchar() > scanf() > cin

//cin慢的原因主要在于默认cin与stdin总是保持同步, 这一步是消耗时间大户. stdin是标准输入，一般指键盘输入到缓冲区里的东西。
//cin、cout之所以效率低，是因为先把要输出的东西存入缓冲区，再输出，导致效率降低，
//只需要加上std::ios::sync_with_stdio(false)来关闭同步就好了。

//在ACM里，经常出现数据集超大造成 cin TLE的情况。其实cin只是C++为了兼容而采取的保守措施。
//我们可以在IO之前将stdio解除绑定，这样做了之后要注意不要同时混用cout和printf之类。
//在默认的情况下cin绑定的是cout，每次执行 << 操作符的时候都要调用flush，这样会增加IO负担。
//可以通过tie(0)（0表示NULL）来解除cin与cout的绑定，进一步加快执行效率。

//解决cin/cout效率低的问题：
//而这段语句可以来打消iostream的输入、输出缓存，可以节省许多时间，使效率与scanf与printf相差无几。
//int类型参数
static int x = []() 
{
    //lambda表达式  //static好像可以去掉   //全局变量在进入main函数之前被初始化   
      std::ios::sync_with_stdio(false);
      //这个函数是一个“是否兼容stdio”的开关，
      //C++为了兼容C，保证程序在使用了std::printf和std::cout的时候不发生混乱，将输出流绑到了一起。       
      cin.tie(NULL);
    //tie是将两个stream绑定的函数，空参数的话返回当前的输出流指针。解除cin与cout的绑定.       
      return 0;
        
}
();

//string类型参数
int _some = []() {
  cin.tie(0);
           ios::sync_with_stdio(false);
           return 0;
      
}();

//等价写法
int fun()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
     
}
int x = fun(); //全局变量在进入main之前被初始化，这样fun()也在main之前被执行

//除了对全局变量进行初始时调用fun()之外，即使fun()中含有static 变量，也只会在第一次调用fun()时初始化，也就是在main之后，在第一次调用时
int fun()
{
  static int x = 0; //第一次调用fun()时才初始化
  return x;
}
int main()
{
  int a = 0;
  a++;
  fun();
}

//如果scanf()还是很慢的话，可以用自行优化如下：
void get(int &x)
{
  char c = getchar();
  x = 0;
  while (c < '0' || c > '9')
    c = getchar();
  while (c <= '9' && c >= '0')
    x = x * 10 + c - 48, c = getchar();
}

void put(int x)
{
  int num = 0;
  char c[15];
  while (x)
    c[++num] = (x % 10) + 48, x /= 10;
  while (num)
    putchar(c[num--]);
  putchar('\n');
}
