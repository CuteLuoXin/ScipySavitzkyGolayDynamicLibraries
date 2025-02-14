# ScipySavitzkyGolayDynamicLibraries
将python库中的SavitzkyGolay滤波器编译windows的动态链接库(x64)，可供c++等其他不便实现的语言使用。
运行python调用dll的速度会比scipy库的速度略快
因为是测试，所以参数写死了dll中的参数和后面一致savgol_filter(input_data, 5, 2, 1, axis=0)
如果需要其他操作系统的库或者scipy中的其他函数可以联系我wx：Hziee_lxdeweixin
