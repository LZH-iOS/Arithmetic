//
//  string.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/9/30.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>


/*
 题目：请实现一个函数，把字符串中的每个空格替换成"%20".例如输入"We are happy", 则输出"We%20are%20happy"。
 关键点：考虑从后往前复制，这样就能减少移动的次数，从而提高效率。
 */

void ReplaceBlank(char string[], int length)
{
    if (string == nullptr && length <= 0) {
        return;
    }
    
    int originalLength = 0; //字符串string的实际长度
    int numberOfBlank = 0;
    int i = 0;
    while (string[i] != '\0') {
        ++originalLength;
        if (string[i] == ' ') {
            ++numberOfBlank;
        }
        
        ++i;
    }
    int newLength = originalLength + numberOfBlank * 2;
    if (newLength > length) {
        return;
    }
    
    int indexOfOriginal = originalLength;
    int indexOfNew = newLength;
    while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal) {
        if (string[indexOfOriginal] == ' ') {
            string[indexOfNew --] = '0';
            string[indexOfNew --] = '2';
            string[indexOfNew --] = '%';
        } else {
            string[indexOfNew --] = string[indexOfOriginal];
        }
        --indexOfOriginal;
    }
}
