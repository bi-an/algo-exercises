void printBin(int num) {
	int i, k = sizeof(int)-1;//例如：对于32位系统，sizeof(int)=32,则k=31
	for (i = 0; i < 32; i++) {
		printf("%d", (num >> k) & 1);//移位并输出
		k--;
	}
	printf("\n");
}