//
//  tree.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/10/17.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>

/*
 二叉搜索树：左子节点总小于或等于根节点，而右子节点总是大于或等于根节点
 最大堆：根节点最大
 最小堆：根节点最小
 红黑树：把树中节点定义为红、黑两种颜色，并通过规则确保从根节点到叶子节点的最长路径的长度不超过最短路径的两倍。
 
 */


struct BinaryTreeNode
{
    int m_nvalue;
    BinaryTreeNode*  m_pLeft;
    BinaryTreeNode*  m_pRight;
    BinaryTreeNode*  m_pParent;
};


/**
 题目：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1，2，4，7，3，5，6，8}和中序遍历序列{4，7，2，1，5，3，8，6}，则重建出二叉树并输出它的头节点。

 @param preorder <#preorder description#>
 @param inorder <#inorder description#>
 @param length <#length description#>
 @return <#return value description#>
 */

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    //前序遍历序列的第一个数字是根节点的值
    int rootValue = startPreorder[0];
    BinaryTreeNode* root = new BinaryTreeNode();
    root->m_nvalue = startPreorder[0];
    root->m_pLeft = root->m_pRight = nullptr;
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && *startPreorder != * startInorder) {
            return root;
        } else {
            throw "Invalid input";
        }
    }
    
    //在中序遍历中找到根节点的值
    int* rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue) {
        ++rootInorder;
    }
    
    if (rootInorder == endInorder && *rootInorder != rootValue) {
        throw "Invalid input";
    }
    
    int leftLength = rootInorder - startInorder;
    int* leftPreorderEnd = startPreorder + leftLength;
    
    if (leftLength > 0) {
        //构建左子树
        root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
    }
    
    if (leftLength < endPreorder - startPreorder) {
        //构建右子树
        root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
    }
    
    
    return root;
}

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
    if (preorder == nullptr || inorder == nullptr || length <= 0) {
        return nullptr;
    }
    
    return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}


/*
 题目：给定一颗二叉树和其中的一个节点，如何找出中序遍历序列的下一个节点？树中的节点除了有两个分别指向左、右子节点的指针，还有一个指向父节点的指针。
 如下图：{d, b, h, e, i, a, f, c, g}
 
                [a]
               /   \
            [b]     [c]
           /   \   /   \
        [d]    [e][f]   [g]
               / \
            [h]   [i]
 关键：分为以下几种类型处理：
        1.节点没有右子树
            1.1节点是父节点的左子树，那么下一个节点就是父节点
            1.2节点是父节点的右子树，那么向上查找父节点，直到找到一个是它父节点的左子节点的节点。
        2.节点有右子树，那么下一个节点就是它右子树的最左子节点
 */

BinaryTreeNode* GetNext(BinaryTreeNode *pNode)
{
    if (pNode == nullptr) {
        return nullptr;
    }
    
    BinaryTreeNode* pNext = nullptr;
    if (pNode->m_pRight != nullptr) {
        BinaryTreeNode* pRight = pNode->m_pRight;
        while (pRight->m_pLeft != nullptr) {
            pRight = pRight->m_pLeft;
        }
        pNext = pRight;
    } else if(pNode->m_pParent != nullptr) {
        BinaryTreeNode* pCurrenet = pNode;
        BinaryTreeNode* pParent = pNode->m_pParent;
        while (pParent != nullptr && pCurrenet == pParent->m_pRight) {
            pCurrenet = pParent;
            pParent = pCurrenet->m_pParent;
        }
        pNext = pParent;
        
    }
    return pNext;
}










