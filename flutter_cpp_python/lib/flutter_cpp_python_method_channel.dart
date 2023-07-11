import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'dart:ffi' as ffi;

import 'flutter_cpp_python_platform_interface.dart';

typedef CFunc = ffi.Void Function();
typedef Func = void Function();

/// An implementation of [FlutterCppPythonPlatform] that uses method channels.
class MethodChannelFlutterCppPython extends FlutterCppPythonPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_cpp_python');

  static final ffi.DynamicLibrary _lib =
      ffi.DynamicLibrary.open("flutter_cpp_python_plugin.dll");

  @override
  Future<String?> getPlatformVersion() async {
    final version =
        await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future demoTest() async {
    Func func = _lib.lookup<ffi.NativeFunction<CFunc>>("demo").asFunction();
    func();
  }
}
