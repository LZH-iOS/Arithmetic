//
//  regular_matcher.cpp
//  Arithmetic
//
//  Created by 李振华 on 2018/6/28.
//  Copyright © 2018年 zhenhua21. All rights reserved.
//

#include <stdio.h>

int matchstar(int c, char *regexp, char *text);
int matchhere(char* regexp, char *text);

int match(char *regexp, char *text)
{
    if (regexp[0] == '^') {
        return matchhere(regexp + 1, text);
    }
    do {
        if (matchhere(regexp, text)) {
            return 1;
        }
    } while (*text != '\0');
    return 0;
}

int matchhere(char* regexp, char *text)
{
    if (regexp[0] == '\0') {
        return 1;
    }
    if (regexp[0] == '$' && regexp[1] == '\0') {
        return *text == '\0';
    }
    if (regexp[1] == '*') {
        return matchstar(regexp[0], regexp+2, text);
    }
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) {
        return matchhere(regexp + 1, text + 1);
    }
    return 0;
}

int matchstar(int c, char *regexp, char *text)
{
    /*
    do {
        if (matchhere(regexp, text)) {
            return 1;
        }
    } while (*text != '\0' && (*text++ == c || c == '.'));
    */
    
    char *temp;
    for (temp = text; *temp != '\0' && (*temp == c || c == ','); temp++);
    do {
        if (matchhere(regexp, temp)) {
            return 1;
        }
    } while (temp-- > text);
    
    return 0;
}
