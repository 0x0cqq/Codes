#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

from cyaron import * # 引入CYaRon的库
from math import *


# 这是一个图论题的数据生成器，该题目在洛谷的题号为P1339
for i in range(1, 3): # 即在[1, 4)范围内循环，也就是从1到3
    test_data = IO(file_prefix="logarithm0", data_id=i) # 生成 heat[1|2|3].in/out 三组测试数据
    T = 20 # 源点，随机选取一个
    maxn = 100
    test_data.input_writeln(T) # 写入到输入文件里，自动以空格分割并换行
    for w in range(1,T+1):
        if(w%2 == 0):
            test_data.input_writeln(randint(1,maxn),randint(1,10))
        else:
            test_data.input_writeln(randint(1,maxn),randint(1,maxn))
    # for w in range(1,n+1):
    #     test_data.input_write(randint(1,100000))
    # for w in range(1,m+1):
    #     a = randint(1,2)
    #     b = abs(randint(1,n/2))
    #     c = randint(b,n)
    #     d = randint(-10000,10000)
    #     if(a == 2):
    #         test_data.input_writeln(a, b, c)
    #     else:
    #         test_data.input_writeln(a, b, c, d)
    test_data.output_gen("./a") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out