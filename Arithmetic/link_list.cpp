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
    pnew->m_pnext = nullptr;
    if (*pHead == nullptr) {
        *pHead = pnew;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pnext != nullptr) {
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
    if (pHead == nullptr || *pHead == nullptr) {
        return;
    }
    
    ListNode* pToBeDeleted = nullptr;
    if ((*pHead)->m_nvalue == value) {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pnext;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pnext != nullptr && pNode->m_pnext->m_nvalue != value) {
            pNode = pNode->m_pnext;
        }
        
        if (pNode->m_pnext != nullptr && pNode->m_pnext->m_nvalue == value) {
            pToBeDeleted = pNode->m_pnext;
            pNode->m_pnext = pToBeDeleted->m_pnext;
        }
        
        if (pToBeDeleted != nullptr) {
            delete pToBeDeleted;
            pToBeDeleted = nullptr;
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
    while (pNode != nullptr) {
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
    if (pHead != nullptr) {
        if (pHead->m_pnext == nullptr) {
            printf("%d\t", pHead->m_nvalue);
        } else {
            printListReversingly_Recursively(pHead->m_pnext);
        }
    }
}



