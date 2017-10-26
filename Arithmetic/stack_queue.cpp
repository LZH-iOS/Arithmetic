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



