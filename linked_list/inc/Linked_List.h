#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stddef.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode* next;
};

struct SinglyList {
    struct ListNode* p_Head;
    size_t length;
};

struct SinglyList* NewList(void);
void DeleteList(struct SinglyList* p_List);

void PushNode(struct SinglyList* p_List, int push_val);
void DeleteNode(struct SinglyList* p_List, int del_val);

void TraversePrintNodes(struct SinglyList* p_List);
size_t GetListLength(struct SinglyList* p_List);

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);
#endif