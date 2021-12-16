// 贪心算法 + 优先队列（最大堆）
// 1. 贪心1：对于两门课程(t1,d1)和(t2,d2)的修习顺序：
// (1) 先修截止日期d较早的，再修较晚的；
// (2) 先修较晚的，再修较早的。
// 可以证明，情况(1)比情况(2)更容易满足。因为情况(2)如果满足，情况(1)一定能够满足，反之不然。
// 证明：假设从第x天开始，
// 情况(1)需要满足：x+t1<=d1 && x+t1+t2<=d2
// 情况(2)需要满足：x+t2<=d2 && x+t2+t1<=d1
// 又因为 d1<=d2，
// 所以，情况(2)满足时，x+t1<=x+t2+t1<=d1<=d2，即情况(1)也满足了。
// 但是由情况(1)不能推导情况(2)，反例：(1,2), (2,4)，可以先修前者，再修后者，但是不能先修后者，再修前者。
// 所以，我们首先对courses按照d正序排列，然后遍历。
// 2. 贪心2：排序之后，修习到第i门课时：
// (1) 第i门课的截止时间 >= 已修课程所花时间 + 第i门课的duration，那么能够修习第i门课，加入；
// (2) 如果 第i门课不能修习 && 第i门课的duration比已修课程中最大的duration小 && 用第i门课换掉已修课程中duration最大的课之后能够修习，
// 那么应该换成第i门课。因为这样相当于在总修课程数不变情况下，把修习课程的总时间缩短了，达到更优。
// 注意到，这里的第3个条件一定满足，假设当前课程用时为total, 当前最大duration为tx, 那么 因为 ti<tx, total<=dmax, dmax<=di,
// 所以 total-tx+ti=total+(ti-tx)<total<=dmax<=di，所以置换之后一定符合要求。
class Solution {
    public int scheduleCourse(int[][] courses) {
        Arrays.sort(courses, (a,b)->a[1] - b[1]); // 按lastDay正序排列
        PriorityQueue<Integer> q = new PriorityQueue<>((a, b)-> b -a); // 最大堆存储duration（与C++构造函数正好相反）
        int total = 0; // 当前duration之和

        for(int[] course : courses) {
            int ti = course[0], di = course[1];
            if(total + ti <= di)
            {
                q.offer(ti);
                total += ti;
            } else if(!q.isEmpty() && q.peek() > ti /* && total - q.peek() + ti <= di */) {
                total += ti - q.poll();
                q.offer(ti);
            }
        }

        return q.size();
    }
}
