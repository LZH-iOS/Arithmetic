//
//  stack_queue.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/10/24.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>
#include <stack>

/*
 题目：用两个栈实现一个队列，队列的声明如下，请实现它的两个函数appendTail和deleteHead,分别完成在队列尾部插入节点和在队列头部删除节点的功能
 */

template <typename T> class CQueue
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
