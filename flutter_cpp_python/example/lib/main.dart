import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_cpp_python/flutter_cpp_python.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';
  final _flutterCppPythonPlugin = FlutterCppPython();

  @override
  void initState() {
    super.initState();
    initPlatformState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    String platformVersion;
    // Platform messages may fail, so we use a try/catch PlatformException.
    // We also handle the message potentially returning null.
    try {
      platformVersion = await _flutterCppPythonPlugin.getPlatformVersion() ??
          'Unknown platform version';
    } on PlatformException {
      platformVersion = 'Failed to get platform version.';
    }

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _platformVersion = platformVersion;
    });
  }

  final TextEditingController controller = TextEditingController();

  @override
  void dispose() {
    controller.dispose();
    super.dispose();
  }

  String evalResult = "";

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Column(
          children: [
            Text('Running on: $_platformVersion\n'),
            ElevatedButton(
                onPressed: () {
                  _flutterCppPythonPlugin.demoTest();
                },
                child: const Text("click")),
            Row(
              children: [
                SizedBox(
                  width: 500,
                  child: TextField(
                    controller: controller,
                  ),
                ),
                ElevatedButton(
                    onPressed: () async {
                      final s =
                          await _flutterCppPythonPlugin.eval(controller.text);
                      // ignore: use_build_context_synchronously
                      setState(() {
                        evalResult = s;
                      });
                    },
                    child: const Text("eval")),
                Text(evalResult)
              ],
            )
          ],
        ),
      ),
    );
  }
}
