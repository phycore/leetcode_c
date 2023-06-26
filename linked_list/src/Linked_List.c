#include "Linked_List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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