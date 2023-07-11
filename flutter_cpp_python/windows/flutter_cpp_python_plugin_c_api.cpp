#include "include/flutter_cpp_python/flutter_cpp_python_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_cpp_python_plugin.h"

void FlutterCppPythonPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_cpp_python::FlutterCppPythonPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
