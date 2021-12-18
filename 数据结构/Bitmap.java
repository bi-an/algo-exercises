class Bitmap {
    private byte[] bytes;

    Bitmap(int maxValue) {
        bytes = new byte[maxValue / 8 + 1];
    }

    // 在bytes[]中的index
    // index = num / 8.
    public int getIndex(int num) {
        return num >> 3;
    }

    // 在bytes[index]中的bit位置
    // pos = num % 8.
    public int getPosition(int num) {
        return num & 0x7;
    }

    // 向bitmap中添加一个数
    public void add(int num) {
        bytes[getIndex(num)] |= 1 << getPosition(num);
    }

    // 判断bitmap中是否存在某个数
    public boolean contains(int num) {
        return (bytes[getIndex(num)] & 1 << getPosition(num)) != 0;
    }

    // Test
    public static void main(String[] args) {
        Bitmap bitmap = new Bitmap(1000);
        bitmap.add(14);
        System.out.println(bitmap.contains(14));
        System.out.println(bitmap.contains(15));
    }
}