// 方法一：与运算
class Solution {
public:
    int findComplement(int num) {
        int num1 = num;

        for (int i = sizeof(int) * 8 - 1, this_bit = (1 << i); i >= 0 && (this_bit & num) == 0; i--, this_bit = (1 << i)) {
            num1 |= this_bit;
        }
        num |= num1;
        return ~num;
    }
};

// 方法二：异或
class Solution {
public:
    int findComplement(int num) {
        int mask = 1;
        for(int i=1;i<=31 && mask <= num;i++) {
            mask <<= 1; // 找到最高位的1的位置
        }
        return num ^ (mask == 0x80000000 ? 0x7fffffff : (mask - 1)); // 注意mask可能溢出/符号变化
    }
};