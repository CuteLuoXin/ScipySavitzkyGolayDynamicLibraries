# ScipySavitzkyGolayDynamicLibraries
将python库中的SavitzkyGolay滤波器编译weiwindows的动态链接库，可供c++等其他不便实现的预言使用。
## python example：
使用python调用dll的例子如下的例子如下：
'''python
import ctypes import os import random import time  from scipy.signal import savgol_filter savgol_filter_lib = ctypes.CDLL("./externtest.dll")  # 定义函数原型，告诉 ctypes 函数的参数类型和返回值类型 # 例如：sg_filter(input: *mut f64, ilen: usize, output: *mut f64, olen: usize) # 对应的 Python 类型是：input 和 output 是指针，ilen 和 olen 是整数。  savgol_filter_lib.sg_filter.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_size_t, ctypes.POINTER(ctypes.c_double), ctypes.c_size_t] savgol_filter_lib.sg_filter.restype = None  # 返回类型是 None  # 准备输入数据 input_data = [random.uniform(0, 10000) for _ in range(10000000)] input_len = len(input_data) # 创建 ctypes 数组来传递给 Rust 函数 input_array = (ctypes.c_double * input_len)(*input_data)  # 准备输出数据 output_len = input_len  # 假设输出长度与输入相同 output_array = (ctypes.c_double * output_len)() start_time_python = time.time() filtered_data = savgol_filter(input_data, 5, 2, 1, axis=0) end_time_python = time.time() # print(filtered_data) python_execution_time = end_time_python - start_time_python start_time_rust = time.time() # 调用 Rust 函数 savgol_filter_lib.sg_filter(input_array, input_len, output_array, output_len) end_time_rust = time.time() rust_execution_time = end_time_rust - start_time_rust output_data = list(output_array) # print(output_data) # 获取输出数据 print(f"rust:{rust_execution_time / 1000:.6f}") print(f"python:{python_execution_time / 1000:.6f}")
'''
运行调用dll的速度会比scipy库的速度略快
