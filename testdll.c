
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef void (*sg_filter_func)(double* input, size_t ilen, double* output, size_t olen);

#define MAX_DLL_PATH_LENGTH 256

int main() {
    // 将文件路径转换为宽字符
    const char* dll_path = "C:\\Users\\Administrator\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\externtest.dll";

    // 使用常量定义数组大小
    wchar_t w_dll_path[MAX_DLL_PATH_LENGTH];
    MultiByteToWideChar(CP_ACP, 0, dll_path, -1, w_dll_path, MAX_DLL_PATH_LENGTH);

    // 使用 LoadLibraryW 加载 DLL（宽字符字符串）
    HINSTANCE hDll = LoadLibraryW(w_dll_path);
    if (hDll == NULL) {
        printf("无法加载 DLL!\n");
        return 1;
    }

    // 获取函数指针
    sg_filter_func sg_filter = (sg_filter_func)GetProcAddress(hDll, "sg_filter");
    if (sg_filter == NULL) {
        printf("无法找到 sg_filter 函数!\n");
        FreeLibrary(hDll);
        return 1;
    }

    // 准备输入数据
    double input_data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    size_t input_len = sizeof(input_data) / sizeof(input_data[0]);

    // 准备输出数据
    double output_data[MAX_DLL_PATH_LENGTH];

    // 调用 Rust 函数
    sg_filter(input_data, input_len, output_data, input_len);

    // 打印输出数据
    printf("Filtered Data (DLL):\n");
    for (size_t i = 0; i < input_len; ++i) {
        printf("%lf ", output_data[i]);
    }
    printf("\n");

    // 释放 DLL
    FreeLibrary(hDll);
    return 0;
}
