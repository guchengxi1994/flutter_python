#ifndef FLUTTER_PLUGIN_FLUTTER_CPP_PYTHON_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_CPP_PYTHON_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_cpp_python {

class FlutterCppPythonPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterCppPythonPlugin();

  virtual ~FlutterCppPythonPlugin();

  // Disallow copy and assign.
  FlutterCppPythonPlugin(const FlutterCppPythonPlugin&) = delete;
  FlutterCppPythonPlugin& operator=(const FlutterCppPythonPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace flutter_cpp_python

#endif  // FLUTTER_PLUGIN_FLUTTER_CPP_PYTHON_PLUGIN_H_
