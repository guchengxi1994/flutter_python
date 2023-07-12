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

#include "utils.cpp"

extern "C"
{
    FUNCTION_ATTRIBUTE
    char *eval(char *statement)
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
        PyRun_SimpleString("sys.path.append('./pymod')");

        pModule = PyImport_ImportModule("pymod.statement_eval"); // Python文件名: demo.py
        if (!pModule)
        {
            cout << "py文件导入失败" << endl;
            Py_Finalize();
        }
        else
        {
            pFunc = PyObject_GetAttrString(pModule, "statement_eval"); // Python文件中的函数名
            if (!pFunc)
            {
                cout << "函数导入失败" << endl;
                Py_Finalize();
            }
            std::string a = statement;
            cout << statement << endl;
            PyObject *pyParams = Py_BuildValue("(s)", a.c_str()); // c++类型转python类型，传入参数

            char *result1;
            // string result1;
            pArg = PyEval_CallObject(pFunc, pyParams); // 调用函数
            PyArg_Parse(pArg, "s", &result1);          // python类型转c++类型
            cout << result1 << endl;
            return result1;
        }

        return "";
    }
}