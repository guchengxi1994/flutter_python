import 'flutter_cpp_python_platform_interface.dart';

class FlutterCppPython {
  Future<String?> getPlatformVersion() {
    return FlutterCppPythonPlatform.instance.getPlatformVersion();
  }

  Future demoTest() async {
    return FlutterCppPythonPlatform.instance.demoTest();
  }

  Future<String> eval(String s) async {
    return await FlutterCppPythonPlatform.instance.eval(s);
  }
}
