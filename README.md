# 简介

这是刷题笔记，主要是 `力扣` 和 `剑指offer` 。

有一本算法的电子书，里面有很多面试题(似乎是txt)，好像在笔记本电脑上，回去找找。


## 时间复杂度

- `O(n)`的算法数据范围`n < 10^8`。
- `O(n * logn)`的算法数据范围`n <= 10^6`。
- `O(n * sqrt(n) )`的算法数据范围`n < 10^5`。
- `O(n^2)`的算法数据范围`n < 5000`。
- `O(n^3)`的算法数据范围`n < 300`。
- `O(2^n)`的算法数据范围`n < 25`。
- `O(n!)`的算法数据范围`n < 11`。


## 网站：
[算法技能树](https://edu.csdn.net/skill/algorithm?utm_source=AI_act_algorithm)

## Unicode 字符

在百度中问 AI ：

“正号的unicode上标字符是什么”，答案：‌正号的Unicode上标字符是“⁺”。

负号的unicode上标字符显示成什么？答：‌⁻¹‌：表示1的负数上标


上标字符转换器：https://teshuzifu.cn/shangbiaozhuanhuan.html

上下标符号：https://www.cnblogs.com/chenyanbin/p/18560013

① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨ ⑩ ⑪ ⑫ ⑬ ⑭ ⑮ ⑯ ⑰ ⑱ ⑲ ⑳
上标：º ¹ ² ³ ⁴⁵ ⁶ ⁷ ⁸ ⁹ ⁺ ⁻ ⁼ ⁽ ⁾ ⁿ ′ ½
下标：₀ ₁ ₂ ₃ ₄ ₅ ₆ ₇ ₈ ₉ ₊ ₋ ₌ ₍ ₎


## Git 报错“Failed to connect to github.com port 443”

[解决方法](https://blog.csdn.net/zpf1813763637/article/details/128340109)

由于安装了 VPN ，我们设置 http 和 https 为 VPN 的代理：

```bash
git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890
```
