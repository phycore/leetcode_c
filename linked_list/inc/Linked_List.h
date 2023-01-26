#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);
#endif