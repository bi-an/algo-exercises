/*
 * @Author: your name
 * @Date: 2022-03-26 17:24:25
 * @LastEditTime: 2022-03-26 17:24:26
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\2043.简易银行系统.cc
 */

class Bank {
    int n;
    long[] balance;

    public Bank(long[] balance) {
        n = balance.length;
        this.balance = balance;
    }

    public boolean transfer(int account1, int account2, long money) {
        if (!isValidAccount(account1) || !isValidAccount(account2))
            return false;
        return withdraw(account1, money) && deposit(account2, money);
    }

    public boolean deposit(int account, long money) {
        if (!isValidAccount(account))
            return false;
        balance[account - 1] += money;
        return true;
    }

    public boolean withdraw(int account, long money) {
        if (!isValidAccount(account) || balance[account - 1] < money)
            return false;
        balance[account - 1] -= money;
        return true;
    }

    private boolean isValidAccount(int account) {
        return account >= 1 && account <= n;
    }
}

/**
 * Your Bank object will be instantiated and called as such:
 * Bank obj = new Bank(balance);
 * boolean param_1 = obj.transfer(account1,account2,money);
 * boolean param_2 = obj.deposit(account,money);
 * boolean param_3 = obj.withdraw(account,money);
 */
