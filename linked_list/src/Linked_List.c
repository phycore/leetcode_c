#include "Linked_List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

static struct ListNode* NewNode(int set_val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (NULL == node) {
        return NULL;
    }
    node->next = NULL;
    node->val = set_val;

    return node;
}

struct SinglyList* NewList(void) {
    struct SinglyList* p_self = (struct SinglyList*)malloc(sizeof(struct SinglyList));
    if (NULL == p_self) {
        return NULL;
    }
    p_self->p_Head = NULL;
    p_self->length = 0;

    return p_self;
}

void DeleteList(struct SinglyList* p_List) {
    struct ListNode* current = NULL;
    struct ListNode* next = NULL;
    current = p_List->p_Head;
    while (NULL != current) {
        next = current->next;
        free(current);
        current = next;
        p_List->length--;
    }
    free(p_List);
    p_List = NULL;
}

void PushNode(struct SinglyList* p_List, int push_val) {
    struct ListNode* head_node = p_List->p_Head;
    struct ListNode* current_node = head_node;
    if (NULL == head_node) {
        p_List->p_Head = NewNode(push_val);
    } else {
        // current_node = head_node->next;
        while (NULL != current_node->next) {
            current_node = current_node->next;
        }
        current_node->next = NewNode(push_val);
    }
    p_List->length++;
}

void DeleteNode(struct SinglyList* p_List, int del_val) {
    struct ListNode* previous = p_List->p_Head;
    struct ListNode* current = p_List->p_Head;

    while (NULL != current) {
        if (del_val == current->val) {
            // 1st node
            if (current == previous) {
                p_List->p_Head = current->next;
                free(p_List->p_Head);
                p_List->length--;
            } else {
                previous->next = current->next;
                free(current);
                p_List->length--;
            }
        }
        previous = current;
        current = current->next;
    }
}

void TraversePrintNodes(struct SinglyList* p_List) {
    if (NULL != p_List) {
        size_t idx = 0;
        struct ListNode* current = p_List->p_Head;
        while (NULL != current) {
            log_info("%s, node[%d] = %d", __func__, idx, current->val);
            current = current->next;
            idx++;
        }
    }
}

size_t GetListLength(struct SinglyList* p_List) {
    size_t length = 0;
    if (NULL != p_List) {
        struct ListNode* current = p_List->p_Head;
        while (NULL != current) {
            current = current->next;
            length++;
        }
    }

    return length;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    size_t node_size = sizeof(struct ListNode);
    struct ListNode* p_Node1 = l1;
    struct ListNode* p_Node2 = l2;
    struct ListNode* head_node = NULL;
    struct ListNode* tail_node = NULL;

    int val = 0;
    int val1 = 0;
    int val2 = 0;
    int carry = 0;
    do {
        // Get value and calculation from node.
        val1 = (NULL != p_Node1) ? (p_Node1->val) : (0);
        val2 = (NULL != p_Node2) ? (p_Node2->val) : (0);
        val = (val1 + val2 + carry);
        carry = (val / 10);
        val -= (carry * 10);

        // Push node and value.
        struct ListNode* temp_node = (struct ListNode*)malloc(node_size);
        memset(temp_node, 0, node_size);
        temp_node->val = val;
        temp_node->next = NULL;
        // head node not exist.
        if (NULL == head_node) {
            head_node = temp_node;
            tail_node = temp_node;
        } else
        // It had head node.
        {
            tail_node->next = temp_node;
            tail_node = tail_node->next;
        }

        // Update pointer of source node.
        if (NULL != p_Node1) p_Node1 = p_Node1->next;
        if (NULL != p_Node2) p_Node2 = p_Node2->next;
    } while ((NULL != p_Node1) || (NULL != p_Node2) || (carry > 0));

    return head_node;
}