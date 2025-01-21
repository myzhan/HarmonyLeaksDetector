# HarmonyLeaksDetector

HarmonyLeaksDetector 尝试将字节跳动开源的 [memory-leak-detector](https://github.com/bytedance/memory-leak-detector) 工具移植到鸿蒙 Next 平台。
目前还在开发中，尚未稳定。 鸿蒙 Next 平台的内存泄露检测，应首选[华为官方的 DevEco Profiler 工具](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ide-insight-session-allocations-memory-V5)。

目前在 Apple Silicon 的模拟器上，初步跑通编译和 demo，报告输出到 HiLog，地址可以使用本地的 llvm-addr2line 翻译。

```bash
01-21 10:46:02.438   27137-27137   A0ff00/RAPHAEL                  com.githu....raphael  I     0x0000007f73183340, 200, malloc, 1
01-21 10:46:02.451   27137-27137   A0ff00/RAPHAEL                  com.githu....raphael  I     0x00000000000128bc /data/storage/el1/bundle/libs/arm64/libraphael.so (unknown)
```

```bash
$ /opt/homebrew/Cellar/llvm/19.1.7/bin/llvm-addr2line -e /Users/myzhan/github/HarmonyLeaksDetector/raphael/build/default/intermediates/libs/default/arm64-v8a/libraphael.so -f -C 0x00000000000128bc
Start(napi_env__*, napi_callback_info__*)
/Users/myzhan/github/HarmonyLeaksDetector/raphael/src/main/cpp/Raphael.cpp:24
```

TODO:
- [ ] 支持发布，并作为模块被其他 app 引用。
- [ ] 支持基于 xHook 的 PLT Hook。
- [ ] 报告输出支持写文件。
- [ ] 补充聚合报告堆栈的 Python 脚本。

参考资料：
1. [异常堆栈解析原理](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ide-exception-stack-parsing-principle-V5#section5147812132)
2. [Native Hook 技术，天使还是魔鬼？](https://blog.yorek.xyz/android/paid/master/native_hook/)