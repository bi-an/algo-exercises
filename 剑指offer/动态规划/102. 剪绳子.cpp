//给定一根长度为n的绳子，请把绳子剪成m段（m、n都是整数，n>1并且m>1），
//每段绳子的长度记为k[0],k[1],…,k[m]。
//请问k[0]* k[1] * … *k[m]可能的最大乘积是多少？

//动态规划
//设f(n)为绳长为n的最大乘积，则f(n)=max(f(i)*f(n-i))。
//递归会产生很多重复计算，所以采用自底向上计算。
int maxProductAfterCutting_solution1(int length){
	if(length<2) return 0;
	if(length==2) return 1;
	if(length==3) return 2;

	int *products=new int[length+1];//products[i]表示绳长为i时的最大乘积值
	products[0]=0;
	products[1]=1;
	products[2]=2;
	products[3]=3;

	int max=0;
	for(int i=4;i<=n;i++){
		for(int j=1;j<=i/2;j++){
			int product=products[j]*products[i-j];
			if(product > max)
				max=product;
			products[i]=max;
		}
	}

	max=products[length];
	delete[] products;//千万不要忘记释放内存
	return max;
}

//贪婪算法
//当n>=5时，因为2(n-2)>n, 3(n-3)>n, 也就是说，剪一刀，分成2和n-2两段，或者分成3和n-3两段，都会使得乘积大于原长。
//并且当n>=5时，3(n-3)>2(n-2)，即应该尽可能剪去长度为3的绳子段。
//而当n==4时，因为2*2>1*3，所以此时应该剪成2+2，也就是说长度为4时，其实没有必要剪，只是题目要求必须剪一刀（m>1）。
//当n<=3时，上面已经讨论了。
int maxProductAfterCutting_solution2(int length){
	if(length<2) return 0;
	if(length==2) return 1;
	if(lenght==3) return 2;

	//尽可能多的减去长度为3的绳子段
	int timeOf3=length/3;

	//当最后剩下的绳子段为4时，不能减去长度3的绳子段
	//此时更好的方法是剪成2+2.
	if(length-timeOf3*3==1)
		timeOf3--;

	int timeOf2=(length-timeOf3*3)/2;

	return (int)(pow(3,timeOf3))*(int)(pow(2,timeOf2));
}
