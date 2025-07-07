class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def removeNthFromEnd(head: ListNode, n: int) -> ListNode:
    dummy = ListNode(0)
    dummy.next = head

    fast = dummy  #快慢指针
    for _ in range(n + 1):
        fast = fast.next

    slow = dummy
    while fast:
        fast = fast.next
        slow = slow.next

    slow.next = slow.next.next

    return dummy.next

def create_linked_list(vals):
    if not vals:
        return None
    head = ListNode(vals[0])
    current = head
    for val in vals[1:]:
        current.next = ListNode(val)
        current = current.next
    return head


def print_linked_list(head):
    vals = []
    while head:
        vals.append(head.val)
        head = head.next
    print("->".join(map(str, vals)))

head = create_linked_list([1, 2, 3, 4, 5])
n = 2
new_head = removeNthFromEnd(head, n)
print_linked_list(new_head)  # 输出: 1->2->3->5