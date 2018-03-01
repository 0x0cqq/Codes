#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库


# 这是一个图论题的数据生成器，该题目在洛谷的题号为P1339
for i in range(1, 6): # 即在[1, 4)范围内循环，也就是从1到3
    test_data = IO(file_prefix="zkw", data_id=i) # 生成 heat[1|2|3].in/out 三组测试数据
    n = m = 500000 # 源点，随机选取一个
    test_data.input_writeln(n, m) # 写入到输入文件里，自动以空格分割并换行
    for w in range(1,n+1):
        a = radint()%2
        b = radint(1,100000000)
        c = radint()
        test_data.input_writeln(n, m)
    test_data.output_gen("u20796") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out