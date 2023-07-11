#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define IS_WIN32
#endif

#ifdef __ANDROID__
#include <android/log.h>
#endif

#ifdef IS_WIN32
#include <windows.h>
#endif

#define MONITOR_ON -1
#define MONITOR_OFF 2
#define MONITOR_STANBY 1

#if defined(__GNUC__)
// Attributes to prevent 'unused' function from being removed and to make it visible
#define FUNCTION_ATTRIBUTE __attribute__((visibility("default"))) __attribute__((used))
#elif defined(_MSC_VER)
// Marking a function for export
#define FUNCTION_ATTRIBUTE __declspec(dllexport)
#endif

#include <iostream>
#include <Python.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

inline string GBK_2_UTF8(string gbkStr)
{
    string outUtf8 = "";
    int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
    WCHAR *str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char *str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    outUtf8 = str2;
    delete[] str1;
    str1 = NULL;
    delete[] str2;
    str2 = NULL;
    return outUtf8;
}

inline string UTF8_2_GBK(string utf8Str)
{
    string outGBK = "";
    int n = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
    WCHAR *str1 = new WCHAR[n];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
    char *str2 = new char[n];
    WideCharToMultiByte(CP_ACP, 0, str1, -1, str2, n, NULL, NULL);
    outGBK = str2;
    delete[] str1;
    str1 = NULL;
    delete[] str2;
    str2 = NULL;
    return outGBK;
}

extern "C"
{
    FUNCTION_ATTRIBUTE
    void demo()
    {
        Py_Initialize();
        if (!Py_IsInitialized())
        {
            cout << "初始化失败" << endl;
            Py_Finalize();
        }

        PyObject *pModule;
        PyObject *pFunc = NULL;
        PyObject *pArg = NULL;
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./')"); // 设置python模块，搜寻位置，文件放在.cpp文件一起

        pModule = PyImport_ImportModule("demo"); // Python文件名: demo.py
        if (!pModule)
        {
            cout << "py文件导入失败" << endl;
            Py_Finalize();
        }
        else
        {
            pFunc = PyObject_GetAttrString(pModule, "run"); // Python文件中的函数名
            if (!pFunc)
            {
                cout << "函数导入失败" << endl;
                Py_Finalize();
            }
            std::string a = "{\"type\": \"文字\", \"wxid\": \"lianghua-2021\", \"wxname\": \"微信聊天机器人\", \"source\": \"好友消息\", \"msgSender\": \"NULL\", \"content\": \"公众号：微聊机器人\"}";
            PyObject *pyParams = Py_BuildValue("(s)", GBK_2_UTF8(a).c_str()); // c++类型转python类型，传入参数

            char *result1;
            // string result1;
            pArg = PyEval_CallObject(pFunc, pyParams); // 调用函数
            PyArg_Parse(pArg, "s", &result1);          // python类型转c++类型
            cout << UTF8_2_GBK(result1) << endl;
        }
    }
}