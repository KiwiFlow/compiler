#!/usr/bin/python 
# -*- encoding: UTF-8 -*-
"""
在这部分中，你将使用图转移算法手工实现一个小型的词法分析器。
* 分析器的输入：存储在文本文件中的字符序列，字符取自ASCII字符集。文件中可能包括四种记号：关键字if、符合C语言标准的标识符、空格符、回车符\n。
* 分析器的输出：打印出所识别的标识符的种类、及行号、列号信息。
【示例】对于下面的文本文件：
ifx if iif       if
iff     if
你的输出应该是：
ID(ifx) (1, 1)
IF        (1, 4)
ID(iif)  (1, 8)
IF       (1, 13)
ID(iff) (2, 1)
IF       (2, 8)
"""
def Lexer(filename):
    row_info = 1
    column_info = 0
    f = open(filename)
    while True:
        c = f.read(1)
        column_info = column_info + 1
        if not c:
          break
        if c == '\n': 
            row_info = row_info + 1
            column_info = 0
        else:
            #转移图
            if c.isalpha() or c=='_':
                token = ''
                token = token + c
                c = f.read(1)
                column_info = column_info + 1
                while c.isalnum() or c=='_':
                    token = token + c
                    c = f.read(1) 
                    column_info = column_info + 1
                if token == "if":
                    print("IF "+"("+str(row_info)+","+str(column_info-len("if"))+")")
                else:
                    print("ID"+"("+token+") "+"("+str(row_info)+","+str(column_info-len(token))+")")
                if c=='\n':
                    row_info = row_info + 1
                    column_info = 0

def Lexer_DFA(filename):
    #确定有限自动机,过滤空格，回车，提取标识符（包括关键字）
    #matrix
    matrix = [ [0,1,0],
               [0,1,1] ]
    cur_state = 0
    token = ''
    f = open(filename)
    while True:
        c = f.read(1)
        if not c:
          break
        input = 0
        if c == ' ' or c=='\n':
            input = 0
        elif c.isalpha() or c=='_':
            input = 1
        else:
            input = 2

        if cur_state == 1 and matrix[cur_state][input] == 1:
            token = token + c
        elif cur_state==0 and matrix[cur_state][input]==1:
            token = ''
            token = token + c
        elif cur_state == 1 and matrix[cur_state][input]==0:
            print(token)
        cur_state = matrix[cur_state][input]

Lexer('d:\\test.txt')
Lexer_DFA('d:\\test.txt')
