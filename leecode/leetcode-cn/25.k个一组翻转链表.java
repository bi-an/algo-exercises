
/**
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode() {}
 * ListNode(int val) { this.val = val; }
 * ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
  public ListNode reverseKGroup(ListNode head, int k) {
      ListNode dummy = new ListNode();
      dummy.next = head;

      ListNode prev = dummy;

      while (prev != null) {
          ListNode left = prev.next;

          // 每次走k-1步，到达right
          ListNode right = left;
          for (int i = 0; i < k - 1 && right != null; i++)
              right = right.next;

          if (right == null)
              break;

          ListNode next = right.next;

          // 截断
          prev.next = null;
          right.next = null;

          reverseList(left);

          // 重新拼接
          prev.next = right;
          left.next = next;

          // 下一次循环
          prev = left;
      }

      return dummy.next;
  }

  public void reverseList(ListNode head) {
      if (head == null || head.next == null)
          return;

      reverseList(head.next);
      head.next.next = head;
      head.next = null;
  }
}
