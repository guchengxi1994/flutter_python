import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_cpp_python_method_channel.dart';

abstract class FlutterCppPythonPlatform extends PlatformInterface {
  /// Constructs a FlutterCppPythonPlatform.
  FlutterCppPythonPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterCppPythonPlatform _instance = MethodChannelFlutterCppPython();

  /// The default instance of [FlutterCppPythonPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterCppPython].
  static FlutterCppPythonPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterCppPythonPlatform] when
  /// they register themselves.
  static set instance(FlutterCppPythonPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future demoTest();
}
