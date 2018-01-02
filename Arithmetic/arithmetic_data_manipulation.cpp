//
//  arithmetic_data_manipulation.cpp
//  Arithmetic
//
//  Created by zhenhua21 on 2017/10/27.
//  Copyright © 2017年 zhenhua21. All rights reserved.
//

#include <stdio.h>
#include <string.h>

/***********递归和循环*************/

/*
 题目：求斐波拉契数列的第n项
      写一个函数，输入n，求斐波拉契(Fibonacci)数列的第n项。斐波拉契数列的定义如下：
            | 0                     n = 0
      f(n) =| 1                     n = 1
            | f(n - 1) + f(n - 2)   n > 1
 */

//这种递归会有很多重复计算
long long Fibonacci(unsigned int n)
{
    if (n <= 0) {
        return 0;
    }
    
    if (n == 1) {
        return 1;
    }
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

//先根据f(0)和f(1)算出f(2),再根据f(1)和f(2)算出f(3),时间复杂度为O(n)
long long Fibonacci_(unsigned int n)
{
    if (n <= 0) {
        return 0;
    }
    
    if (n == 1) {
        return 1;
    }
    
    long long fibNMinusOne = 1;
    long long fibNMinusTwo = 0;
    long long fibN = 0;
    for (int i = 2; i<= n; i++) {
        fibN = fibNMinusOne + fibNMinusTwo;
        fibNMinusTwo = fibNMinusOne;
        fibNMinusOne = fibN;
    }
    return fibN;
}


/**
 对年龄0～99排序

 @param ages <#ages description#>
 @param length <#length description#>
 */
void SortAges(int ages[], int length)
{
    if (ages == nullptr || length <= 0) {
        return;
    }
    const int oldestAge = 99;
    int timesOfAge[oldestAge + 1];
    for (int i=0; i<=oldestAge; i++) {
        timesOfAge[i] = 0;
    }
    
    for (int i=0; i<length; i++) {
        int age = ages[i];
        if (age < 0 || age > 99) {
            throw "error";
        }
        ++timesOfAge[age];
    }
    
    int index = 0;
    for (int i=0; i<oldestAge; i++) {
        for (int j=0; j<timesOfAge[i]; j++) {
            ages[index] = i;
            ++index;
        }
    }
}

/***********位运算*************/

/*
 题目：实现一个函数，输入一个整数，输出该数二进制表示中1的个数。例如把9表示成二进制时1001，有2位是1.因此如果输入9，该函数输出2.
 */

int NumberOf1_1(int n)
{
    int count = 0;
    if (n < 0) {
        n = -n;
    }
    while (n) {
        if (n & 1) {
            count ++;
        }
       n = n >> 1;
    }
    return  count;
}

int NumberOf1_2(int n)
{
    int count = 0;
    unsigned int flag = 1;
    while (flag) {
        if (n & flag) {
            count ++;
        }
       flag = flag << 1;
    }
    return count;
}

int NumberOf1_3(int n)
{
    int count = 0;
    while (n) {
        n = n & (n - 1);
        count ++;
    }
    return count;
}


/*
 题目：实现函数 double Power(double base, int exponent), 求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。
 */

bool equal(double num1, double num2)
{
    if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001)) {
        return true;
    } else {
        return false;
    }
}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    double result = 1.0;
    for (int i=0; i<= exponent; ++i) {
        result *= base;
    }
    return result;
}

double PowerWithUnsignedExponent_better(double base, unsigned int exponent)
{
    if (exponent == 0) {
        return 1;
    }
    if (exponent == 1) {
        return base;
    }
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result;
    if ((exponent & 0x1) == 1) {
        result *= base;
    }
    return result;
}

bool g_InvalidInput = false;
double Power(double base, int exponent)
{
    g_InvalidInput = false;
    if (equal(base, 0.0) && exponent < 0) {
        g_InvalidInput = true;
        return 0.0;
    }
    
    unsigned int absExponet = (unsigned int )(exponent);
    if (exponent < 0) {
        absExponet = (unsigned int)(-exponent);
    }
    
    double result = PowerWithUnsignedExponent(base, absExponet);
    if (exponent < 0) {
        return 1.0 / result;
    }
    
    return result;
}

/*
 题目：输入数字n, 按顺序打印出从1最大的n位十进制数。比如输入3，则打印出1、2、3一直到最大的3位数即999.
 */



/***********回溯法*************/
/*
 题目：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3*4的矩阵中包含一条字符串“bfce”的路径。但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格之之后，路径不能再次进入这个格之。
     a  b   t   g
     c  f   c   s
     j  d   e   h
 */

bool hasPathCore(const char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* visited)
{
    if (str[pathLength] == '\0') {
        return true;
    }
    bool hasPath = false;
    if (row >= 0 && row < rows && col >=0 && col < cols && matrix[row * cols + row] == str[pathLength] && !visited[row * cols + col]) {
        ++pathLength;
        visited[row * cols + col] = false;
        hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited)
        || hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
        || hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
        || hasPathCore(matrix, rows, cols, row + 1, col , str, pathLength, visited);
        
        if (!hasPath) {
            --pathLength;
            visited[row * cols + col] = false;
        }
    }
    return hasPath;
}

bool hasPath(char* matrix, int rows, int cols, char* str)
{
    if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr) {
        return false;
    }
    bool *visited = new bool[rows * cols];
    memset(visited, 0, rows * cols);
    int pathLength = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col ++) {
            if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited)) {
                return true;
            }
        }
    }
    delete[] visited;
    return false;
}

/*
 题目：地上有一个m行n列的方格。一个机器人从坐标（0，0）的格子开始移动，它每次可以向左、右、上、下移动一格，但不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格（35，37），因为3+5+3+7=18.但它不能进入方格（35，38），因为3+5+3+8=19.请问该机器人能够到达多少个格子？
 */

