class AllOne {

  // Attention: 一定要记得同时更新 head 和 nodes

  // 双向列表，从头到尾按照 cnt 从小到大排序（数值上不一定连续）
  Node head;
  Map<String, Node> nodes;

  public AllOne() {
      head = new Node(); // dummy head
      // Tip: 将 prev 和 next 都指向自己。这样将来插入其他节点之后，head.prev 会指向 tail
      // 这样做还有一个好处就是，不需要判断 prev 和 next 是否为 null，因为一定存在
      head.prev = head;
      head.next = head;
      nodes = new HashMap<>();
  }

  public void inc(String key) {
      if (nodes.containsKey(key)) {
          Node cur = nodes.get(key);
          Node nxt = cur.next;
          // 如果 位于 tail 或 下一个计数不为 cur.cnt + 1
          if (nxt == head || nxt.cnt > cur.cnt + 1) {
              // 此时应该新建一个节点
              nodes.put(key, cur.insert(new Node(key, cur.cnt + 1)));
          } else {
              // 此时应该直接插入到 nxt 中
              nxt.add(key);
              nodes.put(key, nxt);
          }
          // 从 cur 中删除 key
          cur.remove(key);
      } else {
          // 如果 列表为空 或 第一个节点计数不为 1
          if (head.next == head || head.next.cnt > 1) {
              // 此时应该在头部插入新节点，cnt 为 1
              nodes.put(key, head.insert(new Node(key, 1)));
          } else {
              // 此时应该直接插入在第一个节点中
              head.next.add(key);
              nodes.put(key, head.next);
          }
      }
  }

  public void dec(String key) {
      if (nodes.containsKey(key)) {
          Node cur = nodes.get(key);
          Node prv = cur.prev;
          if (cur.cnt - 1 == 0) {
              nodes.remove(key);
          } else if (prv == head || prv.cnt < cur.cnt - 1) {
              nodes.put(key, prv.insert(new Node(key, cur.cnt - 1)));
          } else {
              prv.add(key);
              nodes.put(key, prv);
          }
          cur.remove(key);
      }
  }

  public String getMaxKey() {
      return head.prev == head ? "" : head.prev.keys.iterator().next();
  }

  public String getMinKey() {
      return head.next == head ? "" : head.next.keys.iterator().next();
  }
}

class Node {
  Set<String> keys;
  int cnt;
  Node prev, next;

  public Node() {
      keys = new HashSet<>();
      cnt = 0;
  }

  public Node(String key, int cnt) {
      keys = new HashSet<>();
      keys.add(key);
      this.cnt = cnt;
  }

  public void add(String key) {
      keys.add(key);
  }

  public void remove(String key) {
      keys.remove(key);
      // 如果 keys 为空，那么应该删除 this 节点
      if (keys.isEmpty()) {
          prev.next = next;
          next.prev = prev;
      }
  }

  // 在当前节点之后插入一个节点
  public Node insert(Node node) {
      node.prev = this;
      node.next = next;
      this.next = node;
      node.next.prev = node;
      return node;
  }
}
