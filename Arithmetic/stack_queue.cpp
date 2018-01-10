//
//  stack_queue.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/10/24.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>
#include <stack>
#include <queue>

/*
 题目：用两个栈实现一个队列，队列的声明如下，请实现它的两个函数appendTail和deleteHead,分别完成在队列尾部插入节点和在队列头部删除节点的功能
 关键点：插入元素，将元素压栈到stack1; 删除元素，判断stack2是否为空，如果为空，将stack1元素按顺序pop到stack2，然后从stack2中pop出元素即可。
 */

template <typename T>
class CQueue
{
public:
    CQueue();
    ~CQueue();
    void appendTail(const T& node);
    T deleteHead();
    
private:
    std::stack<T> stack1;
    std::stack<T> stack2;
};

template <typename T>
void CQueue<T>::appendTail(const T &node)
{
    stack1.push(node);
}

template <typename T>
T CQueue<T>::deleteHead()
{
    if (stack2.size() <= 0) {
        while (stack1.size() > 0) {
            T& data = stack1.top();
            stack2.push(data);
        }
    }
    
    if (stack2.size() == 0) {
        throw "queue is empty";
    }
    
    T head = stack2.top();
    stack2.pop();
    return head;
}

/*
 题目：用两个队列实现一个栈
 */

template <typename T>
class CStack {
public:
    CStack();
    ~CStack();
    void push(const T& node);
    T pop();
    
private:
    std::queue<T> queue1;
    std::queue<T> queue2;
};

template <typename T>
void CStack<T>::push(const T &node)
{
    if (queue1.size() > 0) {
        queue1.push(node);
    } else {
        queue2.push(node);
    }
}

template <typename T>
T CStack<T>::pop()
{
    if (!queue1.size() && !queue2.size()) {
        throw "stask is empty";
    }
    T node;
    int i = 1;
    if (queue1.size() > 0) {
        while (queue1.size() > 0) {
            node = queue1.pop();
            if (i != queue1.size()) {
                queue2.push(node);
            }
            ++i;
        }
    } else {
        while (queue2.size() > 0) {
            node = queue2.pop();
            if (i != queue2.size()) {
                queue1.push(node);
            }
            ++i;
        }
    }
    return node;
}

/*  包含min函数的栈
 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数。在该栈中，调用min、push及pop的时间复杂度都是O(1).
 */

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();
    void push(const T& node);
    T pop();
    T Min();
    
private:
    std::stack<T> stack1; //主栈
    std::stack<T> stack2; //辅助栈
};

template <typename T>
T Stack<T>::Min()
{
    static_assert(stack1.size() && stack2.size(), "error");
    return stack2.top();
}

template <typename T>
T Stack<T>::pop()
{
    static_assert(stack1.size() && stack2.size(), "error");
    stack1.pop();
    stack2.pop();
}

template <typename T>
void Stack<T>::push(const T& value)
{
    stack1.push(value);
    if (stack2.size() == 0 || value < stack2.top()) {
        stack2.push(value);
    } else {
        stack2.push(stack2.top());
    }
}

/*  栈的压入、弹出序列
 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、5是某栈的压入序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，但4、3、5、1、2就不可能是该压栈序列的弹出序列。
 */

bool IsPopOrder(const int* pPush, const int* pPop, int length)
{
    if (pPush == NULL || pPop == NULL || length == 0) {
        return false;
    }
    
    std::stack<int> stackData;
    int index = 0;
    for (int i = 0; i < length ; ++i) {
        int pop = pPop[i];
        if (stackData.size() && stackData.top() == pop) {
            stackData.pop();
        } else {
            if (index == length) {
                return false;
            } else {
                for (int i = index; i < length; ++i) {
                    index++;
                    if (pPush[i] == pop) {
                        break;
                    } else {
                        stackData.push(pPush[i]);
                    }
                }
            }
        }
    }
    return true;
}

bool isOrderOriginal(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;
    
    if (pPush != NULL && pPop != NULL && nLength > 0) {
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;
        
        std::stack<int>stackData;
        
        while (pNextPop - pPop < nLength) {
            while (stackData.empty() || stackData.top() != *pNextPop) {
                if (pNextPush - pPush == nLength) {
                    break;
                }
                stackData.push(*pNextPush);
                pNextPush++;
            }
            
            if (stackData.top() != *pNextPop) {
                break;
            }
            
            stackData.pop();
            pNextPop++;
        }
        
        if (stackData.empty() && pNextPop - pPop == nLength) {
            bPossible = true;
        }
    }
    
    return bPossible;
}



