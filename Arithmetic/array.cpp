//
//  array.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/9/30.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>


/******数组中重复的数字******/
/*
 题目：在一个长度为n的数组里的所有数字都在0～n-1的范围内。数组中的某些数字是重复的，但是不知道有几个数字重复了，
      也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2,3,1,0,2,5,3},
      那么对应的输出是重复的数字2或者3.
 关键点：根据下标定位对应的元素。
 解法：1.把输入的数组排序，从排序的数组中找出重复的数字
      2.开辟一个新的数组，将输入的数组遍历，把遍历的数据放在对应下标的新数组里（比如2放在新数组下标为2的位置），
        每次放入前和数组里面的元素对比，如果相等，说明已经重复。
      3.利用哈希表解决，从头到尾按顺序扫描数组的每个数字，没扫描到一个数字，判断哈希表里是否已经包含了该数字。
      4.根据下标定位对应的元素。每个数字最多只要交换两次就能找到属于它的位置，因此总的时间复杂度是O(n).不需要额外分配内存，空间复杂度O(1).下面属于这种解法。
 */

bool duplicate(int array[], int length, int* duplicate)
{
    if (array == nullptr || length <= 0) {
        return false;
    }
    
    for (int i=0; i< length; i++) {
        if (array[i] < 0 || array[i] > length - 1) {
            return false;
        }
    }
    
    for (int i=0; i< length; i++) {
        while (array[i] != i) {
            if (array[i] == array[array[i]]) {
                *duplicate = array[i];
                return true;
            }
            
            int temp = array[i];
            array[i] = array[array[i]];
            array[array[i]] = temp;
        }
    }
    
    return false;
}

/*
 题目：在一个长度为n+1的数组里的所有数字都在1～n的范围内，所以数组中至少有一个数字是重复的。请找出数组中任一一个重复的数字，
      但不能修改输入的数组。例如，如果输入长度为8的数组{2,3,5,4,3,2,6,7},那么对应的输出是重复的数字2或者3.
 关键点：按照二分查找的思路，如果输入的长度为n的数组，那么函数countRange将被调用O(logn)次，每次需要O(n)的时间，因此总的时间复杂度是O(nlogn)，空间复杂度O(1).
 */

int countRange(const int* numbers, int length, int start, int end)
{
    if (numbers == nullptr) {
        return 0;
    }
    int count = 0;
    for (int i=0; i<length; i++) {
        if (numbers[i] >= start && numbers[i] <= end) {
            ++count;
        }
    }
    return count;
}

int getDuplication(const int* array, int length)
{
    if (array == nullptr || length <= 0) {
        return -1;
    }
    int  start = 1;
    int  end = length;
    while (end > start) {
        int middle = ((end - start)>>1) + start;
        int count = countRange(array, length, start, middle);
        if (end == start) {
            if (count > 1) {
                return start;
            } else {
                break;
            }
        }
        
        if (count > middle - start + 1) {
            end = middle;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}


/******二维数组中的查找******/
/*
 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排列，每一列都按照从上到下递增的顺序排列。
      请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 关键点： 每次选取数组查找范围内的右上角数字（或者左上角），这样才能每次查找剔除行或者列。
 */

bool find(int *array, int rows, int columns, int number)
{
    bool find = false;
    if (array == nullptr || rows <=0 || columns <= 0) {
        return find;
    }
    int row = 0;
    int column = columns - 1;
    
    while (row < rows && columns > 0) {
        if (array[row * columns + column] == number) {
            find  = true;
            break;
        } else if (array[row * column + column] > number) {
            columns --;
        } else {
            row ++;
        }
    }
    
    return find;
}

/*
 题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1.
 关键点：二分查找，p1指针指向第一个元素，p2指针指向最后一个元素
 */

int Min(int* numbers, int length)
{
    if (nullptr == numbers || length <= 0) {
        throw "输入参数错误";
    }
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1;
    while (numbers[index1] > numbers[index2]) {
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        indexMid = (index1 + index2) / 2;
        
        //如果下表为index1、index2和indexMid指向的三个数字相等，则只能顺序查找
        
        
        
        if (numbers[indexMid] >= numbers[index1]) {
            index1 = indexMid;
        } else if(numbers[indexMid] <= numbers[index2]) {
            index2 = indexMid;
        }
    }
    return numbers[indexMid];
}

int MinInOrder(int* number, int index1, int index2)
{
    int result = number[index1];
    for (int i = index1 + 1; i<= index2; ++i) {
        if (result > number[i]) {
            result = number[i];
        }
    }
    return result;
}













