import 'flutter_cpp_python_platform_interface.dart';

class FlutterCppPython {
  Future<String?> getPlatformVersion() {
    return FlutterCppPythonPlatform.instance.getPlatformVersion();
  }

  Future demoTest() async {
    return FlutterCppPythonPlatform.instance.demoTest();
  }
}
