//
//  link_list.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/10/13.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>
#include <stack>

struct ListNode
{
    int m_nvalue;
    ListNode* m_pnext;
};

/*
 表尾添加节点
 */
void AddToTail(ListNode** pHead, int value)
{
    ListNode* pnew = new ListNode();
    pnew->m_nvalue = value;
    pnew->m_pnext = NULL;
    if (*pHead == NULL) {
        *pHead = pnew;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pnext != NULL) {
            pNode = pNode->m_pnext;
        }
        pNode->m_pnext = pnew;
    }
}


/**
 删除指定值的node节点

 @param pHead <#pHead description#>
 @param value <#value description#>
 */
void RemoveNode(ListNode** pHead, int value)
{
    if (pHead == NULL || *pHead == NULL) {
        return;
    }
    
    ListNode* pToBeDeleted = NULL;
    if ((*pHead)->m_nvalue == value) {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pnext;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pnext != NULL && pNode->m_pnext->m_nvalue != value) {
            pNode = pNode->m_pnext;
        }
        
        if (pNode->m_pnext != NULL && pNode->m_pnext->m_nvalue == value) {
            pToBeDeleted = pNode->m_pnext;
            pNode->m_pnext = pToBeDeleted->m_pnext;
        }
        
        if (pToBeDeleted != NULL) {
            delete pToBeDeleted;
            pToBeDeleted = NULL;
        }
    }
}


/**
 从尾到头打印链表

 @param pHead <#pHead description#>
 
 解法：
    1.栈结构
    2.递归
 */
void PrintListReversingly_Iteratively(ListNode *pHead)
{
    std::stack<ListNode*> nodes;
    ListNode* pNode = pHead;
    while (pNode != NULL) {
        nodes.push(pNode);
        pNode = pNode->m_pnext;
    }
    while (!nodes.empty()) {
        pNode = nodes.top();
        printf("%d\t", pNode->m_nvalue);
        nodes.pop();
    }
}

void printListReversingly_Recursively(ListNode *pHead)
{
    if (pHead != NULL) {
        if (pHead->m_pnext == NULL) {
            printf("%d\t", pHead->m_nvalue);
        } else {
            printListReversingly_Recursively(pHead->m_pnext);
        }
    }
}

/*
    在O(1)时间删除链表结点
 题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点。
 
 */
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (!pListHead || !pToBeDeleted) {
        return;
    }
    
    if (pToBeDeleted->m_pnext != NULL) {
        ListNode* pNext = pToBeDeleted->m_pnext;
        pToBeDeleted->m_nvalue = pNext->m_nvalue;
        pToBeDeleted->m_pnext = pNext->m_pnext;
        delete  pNext;
        pNext = NULL;
    } else if (*pListHead == pToBeDeleted && pToBeDeleted->m_pnext == NULL) {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
        *pListHead = NULL;
    } else {
        ListNode* pNode = *pListHead;
        while (pNode->m_pnext != pToBeDeleted) {
            pNode = pNode->m_pnext;
        }
        pNode->m_pnext = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
    
}

/* 链表中倒数第k个结点
 题目：输入一个链表，输出该链表中倒数第k个结点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾结点是倒数第1个结点。例如一个链表有6个结点，从头结点开始它们的值依次是1、2、3、4、5、6.这个链表的倒数第3个结点是值为4的结点。
 
 */

ListNode* FindKthToTail(ListNode *pListHead, unsigned int k)
{
    if (pListHead == NULL || k <= 0 ) {
        return NULL;
    }
    ListNode *pAhead = pListHead;
    ListNode *pBehind = NULL;
    
    for (int i = 0; i < k - 1; i++) {
        if (pAhead->m_pnext != NULL) {
            pAhead = pAhead->m_pnext;
        } else {
            return NULL;
        }
    }
    
    pBehind = pListHead;
    
    while (pAhead->m_pnext != NULL) {
        pAhead = pAhead->m_pnext;
        pBehind = pBehind->m_pnext;
    }
    return pBehind;
    
}

/* 反转链表
 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。
 */

ListNode* ReverseList(ListNode *pHead)
{
    if (pHead == NULL) {
        return NULL;
    }
    
    ListNode *pReverseHead = NULL;
    ListNode *pRrev = NULL;
    ListNode *pNode = pHead;
    
    while (pNode != NULL) {
        ListNode *pNext = pNode->m_pnext;
        
        if (pNext == NULL) {
            pReverseHead = pNode;
        }
        
        pNode->m_pnext = pRrev;
        
        pRrev = pNode;
        pNode = pNext;
    }
    
    return pReverseHead;
}

/* 合并两个排序的链表
 题目：输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。
 */

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == NULL) {
        return pHead2;
    } else if (pHead2 == NULL){
        return pHead1;
    }
    
    ListNode *pNode1 = pHead1;
    ListNode *pNode2 = pHead2;
    ListNode *pHead = pNode1->m_nvalue > pNode2->m_nvalue ? pNode1 : pNode2;
    ListNode *pNode = pHead;
    
    while (pNode1 && pNode2) {
        if (pNode1->m_nvalue > pNode2->m_nvalue) {
            pNode->m_pnext = pNode2;
            pNode = pNode2;
            pNode2 = pNode2->m_pnext;
        } else {
            pNode->m_pnext = pNode1;
            pNode = pNode1;
            pNode1 = pNode1->m_pnext;
        }
    }
    if (pNode1 == NULL) {
        pNode->m_pnext = pNode2;
    } else {
        pNode->m_pnext = pNode1;
    }
    
    return pHead;
}

ListNode* MergeOriginal(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == NULL) {
        return pHead2;
    } else if (pHead2 == NULL){
        return pHead1;
    }
    
    ListNode *pMergeHeard = NULL;
    
    if (pHead1->m_nvalue < pHead2->m_nvalue) {
        pMergeHeard = pHead1;
        pMergeHeard->m_pnext =  MergeOriginal(pHead1->m_pnext, pHead2);
    } else {
        pMergeHeard = pHead2;
        pMergeHeard->m_pnext = MergeOriginal(pHead2->m_pnext, pHead1);
    }
    
    return pMergeHeard;
}




