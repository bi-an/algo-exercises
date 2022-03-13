class Solution {
  final int MASK1 = (1 << 7); // binary: 1000 0000
  final int MASK2 = (1 << 7) + (1 << 6); // binary: 1100 0000

  public boolean validUtf8(int[] data) {
    int index = 0;
    while (index < data.length) {
      int n = getBytes(data[index]);
      if (n < 0 || index + n > data.length)
        return false;
      ++index;
      --n;
      while (n > 0) {
        if (!isValid(data[index]))
          return false;
        --n;
        ++index;
      }
    }
    return true;
  }

  // @return utf-8 编码占用的字节数; -1 表示不合法.
  public int getBytes(int num) {
    if ((num & MASK1) == 0)
      return 1;
    int mask = MASK1;
    int n = 0;
    while ((num & mask) != 0) {
      ++n;
      mask >>= 1;
    }
    return n >= 2 && n <= 4 ? n : -1; // 合法取值 1, [2,4]
  }

  // @return true 当前字节是 '10' 开头; false 其他.
  public boolean isValid(int byte1) {
    return (byte1 & MASK2) == MASK1;
  }
}