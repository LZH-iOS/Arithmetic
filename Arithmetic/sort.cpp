//
//  sort.cpp
//  Arithmetic
//
//  Created by 李振华 on 2018/6/28.
//  Copyright © 2018年 zhenhua21. All rights reserved.
//

#include <stdio.h>

/*
 一趟快速排序的算法是：
 1）设置两个变量i、j，排序开始的时候：i=0，j=N-1；
 2）以第一个数组元素作为关键数据，赋值给key，即key=A[0]；
 3）从j开始向前搜索，即由后开始向前搜索(j--)，找到第一个小于key的值A[j]，将A[j]和A[i]互换；
 4）从i开始向后搜索，即由前开始向后搜索(i++)，找到第一个大于key的A[i]，将A[i]和A[j]互换；
 5）重复第3、4步，直到i=j； (3,4步中，没找到符合条件的值，即3中A[j]不小于key,4中A[i]不大于key的时候改变j、i的值，使得j=j-1，i=i+1，直至找到为止。找到符合条件的值，进行交换的时候i， j指针位置不变。另外，i==j这一过程一定正好是i+或j-完成的时候，此时令循环结束）。
 */


void quickSort(int *num, int left, int right)
{
    if (left >= right) {
        return;
    }
    
    int i = left;
    int j = right;
    
    int key = num[left];
    
    while (i < j) {
        while (i < j && key <= num[j]) {
            j--;
        }
        num[i] = num[j];
        
        while (i < j && key >= num[i]) {
            i++;
        }
        num[j] = num[i];
    }
    
    num[i] = key;
    quickSort(num, left, i-1);
    quickSort(num, i+1, right);
    
}
