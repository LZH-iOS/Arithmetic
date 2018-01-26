//
//  tree.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/10/17.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>
#include "deque"
#include "vector"

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

 */

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    //前序遍历序列的第一个数字是根节点的值
    int rootValue = startPreorder[0];
    BinaryTreeNode* root = new BinaryTreeNode();
    root->m_nvalue = startPreorder[0];
    root->m_pLeft = root->m_pRight = nullptr;
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && *startPreorder == * startInorder) {
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

/* 树的子结构
 题目：输入两颗二叉树A和B， 判断B是不是A的子结构。
 
 */

bool DoseTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot2 == NULL) {
        return true;
    }
    
    if (pRoot1 == NULL) {
        return false;
    }
    
    if (pRoot1->m_nvalue != pRoot2->m_nvalue) {
        return false;
    }
    
    return DoseTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoseTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result = false;
    
    if (pRoot1 != NULL && pRoot2 != NULL) {
        if (pRoot1->m_nvalue == pRoot2->m_nvalue) {
            return DoseTree1HaveTree2(pRoot1, pRoot2);
        }
        
        if (!result) {
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        }
        
        if (!result) {
            result =HasSubtree(pRoot1->m_pRight, pRoot2);
        }
    }
    
    return result;
}

/* 二叉树的镜像
 题目：请完成一个函数，输入一个二叉树，该函数输出它的镜像。
 
            8                       8
        6      10               10      6
      5   7  9   11           11   9  7   5
 
 */

void MirrorRecursively(BinaryTreeNode* pNode)
{
    if (pNode == NULL || (pNode->m_pLeft == NULL && pNode->m_pRight == NULL)) {
        return;
    }
    
    BinaryTreeNode* pTemp = pNode->m_pLeft;
    pNode->m_pLeft = pNode->m_pRight;
    pNode->m_pRight = pTemp;
    MirrorRecursively(pNode->m_pLeft);
    MirrorRecursively(pNode->m_pRight);
    
}

/*  从上往下打印二叉树
 题目：从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。例如输入如下二叉树，则依次打印出8、6、10、5、7、9、11.
 
        8
    6      10
  5   7  9   11
 
 */

void PrintFromToBottom(BinaryTreeNode *pTreeRoot)
{
    if (pTreeRoot == NULL) {
        return;
    }
    
    std::deque<BinaryTreeNode *> dequeTreeNode;
    
    dequeTreeNode.push_back(pTreeRoot);
    
    while (dequeTreeNode.size()) {
        BinaryTreeNode *pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();
        printf("%d ", pTreeRoot->m_nvalue);
        
        if (pNode->m_pLeft) {
            dequeTreeNode.push_back(pNode->m_pLeft);
        }
        
        if (pNode->m_pRight) {
            dequeTreeNode.push_back(pNode->m_pRight);
        }
    }
    
}

/*  二叉搜索树的后序遍历序列
 题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则返回true，否则返回false，假设输入的数组的任意两个数字都不相同。
 */

bool VerifySquenceOfBST(int sequence[], int length)
{
    if (sequence == NULL || length <= 0) {
        return false;
    }
    
    int root = sequence[length - 1];
    
    int i = 0;
    
    while (sequence[i] < root) {
        i++;
    }
    
    for (int j = i; j < length - 1; j++) {
        if (sequence[j] < root) {
            return false;
        }
    }
    
    bool left = true;
    if (i > 0) {
        left = VerifySquenceOfBST(sequence, i);
    }
    
    bool right = true;
    
    if (i < length - 1) {
        right  = VerifySquenceOfBST(sequence + i, length - 1 - i);
    }
    
    return left && right;
}

/*  二叉树中和为某一值的路径
 题目：输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。从树的根结点开始往下一直到叶子结点所经过的结点形成一条路径。
 */

struct stackWithSum
{
    std::vector<int> vec;
    int sum;
    
    stackWithSum () {
        sum = 0;
    }
};

void findPathCore(BinaryTreeNode *pRoot, int expectedSum, stackWithSum& stack)
{
    if (pRoot == NULL) {
        if (stack.sum == expectedSum) {
            for (std::vector<int>::iterator iter = stack.vec.begin(); iter != stack.vec.end(); ++iter) {
                printf("%d ", *iter);
            }
        } else {
            stack.vec.pop_back();
        }
        return;
    }
    
    stack.vec.push_back(pRoot->m_nvalue);
    stack.sum += pRoot->m_nvalue;
    
    findPathCore(pRoot->m_pLeft, expectedSum, stack);
    findPathCore(pRoot->m_pRight, expectedSum, stack);
    
    if (stack.vec.size()) {
        stack.sum -= pRoot->m_nvalue;
        stack.vec.pop_back();
    }
}

void FindPath(BinaryTreeNode *pRoot, int expectedSum)
{
    if (pRoot == NULL && expectedSum <= 0) {
        return;
    }
    
    stackWithSum stack;
    
    findPathCore(pRoot, expectedSum, stack);
    
}

/*  二叉搜索树与双向链表
 题目：输入一颗二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。比如输入如下图二叉搜索树，则输出转换之后的排序双向链表。
        10
      6     14   ==》4<==>6<==>8<==>10<==>12<==>14<==>16
    4   8 12  16
 */


void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
    if (pNode == NULL) {
        return;
    }
    
    BinaryTreeNode *pCurrent = pNode;
    if (pCurrent->m_pLeft != NULL) {
        ConvertNode(pCurrent->m_pLeft, pLastNodeInList);
    }
    
    pCurrent->m_pLeft = *pLastNodeInList;
    
    if (*pLastNodeInList != NULL) {
        (*pLastNodeInList)->m_pRight = pCurrent;
    }
    *pLastNodeInList = pCurrent;
    
    if (pNode->m_pRight != NULL) {
        ConvertNode(pNode->m_pRight, pLastNodeInList);
    }
}

BinaryTreeNode* Convert(BinaryTreeNode* pRootofTree)
{
    if (pRootofTree == NULL) {
        return NULL;
    }
    
    BinaryTreeNode *pLastNodeInList = NULL;
    
    ConvertNode(pRootofTree, &pLastNodeInList);
    
    BinaryTreeNode *pHeadOfList = pLastNodeInList;
    
    while (pHeadOfList != NULL && pHeadOfList->m_pLeft != NULL) {
        pHeadOfList = pHeadOfList->m_pLeft;
    }
    
    return pHeadOfList;
}
















