import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_cpp_python/flutter_cpp_python.dart';
import 'package:flutter_cpp_python/flutter_cpp_python_platform_interface.dart';
import 'package:flutter_cpp_python/flutter_cpp_python_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFlutterCppPythonPlatform
    with MockPlatformInterfaceMixin
    implements FlutterCppPythonPlatform {
  @override
  Future<String?> getPlatformVersion() => Future.value('42');

  @override
  Future demoTest() {
    // TODO: implement demoTest
    throw UnimplementedError();
  }
}

void main() {
  final FlutterCppPythonPlatform initialPlatform =
      FlutterCppPythonPlatform.instance;

  test('$MethodChannelFlutterCppPython is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFlutterCppPython>());
  });

  test('getPlatformVersion', () async {
    FlutterCppPython flutterCppPythonPlugin = FlutterCppPython();
    MockFlutterCppPythonPlatform fakePlatform = MockFlutterCppPythonPlatform();
    FlutterCppPythonPlatform.instance = fakePlatform;

    expect(await flutterCppPythonPlugin.getPlatformVersion(), '42');
  });
}
