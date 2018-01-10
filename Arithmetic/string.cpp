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

/*  字符串的排列
 题目：输入一个字符串，打印出该字符串中字符的所有排列。例如输入字符串abc，则打印出由字符a、b、c所能排列出来的所有字符串abc、acb、bac、bca、cab和cba。
 */

void PermutationCore(char *pStr, char *pBegin)
{
    if (*pBegin == '\0') {
        printf("%s\n", pStr);
    } else {
        for (char *pCh = pBegin; *pCh != '\0'; ++pCh) {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
            
            PermutationCore(pStr, pBegin + 1);
            
            temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
        }
    }
}

void Permutation(char *pStr)
{
    if (pStr == NULL) {
        return;
    }
    PermutationCore(pStr, pStr);
}

/*  字符串的排列扩展
    1.求n个字符串中长度为m的组合。
      分解为分别n-1个字符串中长度为m-1的组合，以及求n-1个字符串的长度为m的组合。
 
    2.在8 * 8的国际象棋上包房8个皇后，使其不能相互攻击，即任意两个皇后不得处于同一行、同一列或者同一对角线上。
 */






















