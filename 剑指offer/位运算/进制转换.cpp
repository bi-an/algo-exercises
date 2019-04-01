// @return 写入的字节数
int dec2hex(int dec, char *hex, int bufferSize) {

	if(hex==nullptr) return 0;

	int maxIntBits=sizeof(int)*2; // TODO: 要能够根据输入的数判断，而不是仅仅判断最大值
	if(bufferSize<maxIntBits+1)
		return 0;

	int div = dec;
	int i = 0;
	char *cache = new char[bufferSize];
	for (; div != 0 && i < bufferSize; i++) {
		//rem = div - div / 16 * 16;
		int rem = div % 16;
		if (rem >= 0 && rem <= 9)
			cache[i] = rem + '0';
		else
			cache[i] = rem - 10 + 'A';
		div = div / 16;
	}
	if ((i & 0x1) != 0) {
		cache[i] = '0';
		i++;
	}

	// 倒过来
	for (int j = i-1, k=0; j >=0 ; j--, k++) {
		hex[k] = cache[j];
	}

	hex[i] = '\0';

	delete cache;

	return i;
}

// 法二：sprintf
// 注意：要记得位数不足时前置补零
int dec2hex(int dec, char *hex, int bufferSize) {

	if(hex==nullptr) return 0;

	int maxIntBits=sizeof(int)*2; // TODO: 要能够根据输入的数判断，而不是仅仅判断最大值
	if(bufferSize<maxIntBits+1)
		return 0;

	sprintf(hex, "%X", dec);
	int len = strlen(hex);
	if ((len&0x1) == 1) {
		for (int i = len; i >= 0; i--) { // sprintf会在末尾插入'\0'，所以hex[len]=='\0'
			hex[i + 1] = hex[i];
		}
		hex[0] = '0';
		len++;
	}

	return len;
}