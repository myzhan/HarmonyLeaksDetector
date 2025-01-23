# HarmonyLeaksDetector

HarmonyLeaksDetector 尝试将字节跳动开源的 [memory-leak-detector](https://github.com/bytedance/memory-leak-detector) 工具移植到鸿蒙 Next 平台。
目前还在开发中，尚未稳定。 鸿蒙 Next 平台的内存泄露检测，应首选[华为官方的 DevEco Profiler 工具](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ide-insight-session-allocations-memory-V5)。

目前在 Apple Silicon 的模拟器上，初步跑通编译和 demo，报告输出到 HiLog。

```bash
01-22 01:49:39.380   16690-16690   A0ff00/RAPHAEL                  com.githu....raphael  I     0x0000007f73190880, 200, malloc, 1
01-22 01:49:39.380   16690-16690   A0ff00/RAPHAEL                  com.githu....raphael  I     0x0000000000014880 /data/storage/el1/bundle/libs/arm64/libraphael.so (Malloc(napi_env__*, napi_callback_info__*) + 28)
01-22 01:49:39.380   16690-16690   A0ff00/RAPHAEL                  com.githu....raphael  I     0x00000000000393bc /system/lib64/platformsdk/libace_napi.z.so (panda::JSValueRef ArkNativeFunctionCallBack<true>(panda::JsiRuntimeCallInfo*) + 224)
01-22 01:49:39.380   16690-16690   A0ff00/RAPHAEL                  com.githu....raphael  I     0x0000007f6f8b2b70 <unknown>/Users/myzhan/github/HarmonyLeaksDetector/raphael/src/main/cpp/Raphael.cpp:24
```

TODO:
- [ ] 支持发布，并作为模块被其他 app 引用。
- [ ] 报告输出支持写文件。
- [ ] 补充聚合报告堆栈的 Python 脚本。

参考资料：
1. [异常堆栈解析原理](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ide-exception-stack-parsing-principle-V5#section5147812132)
2. [Native Hook 技术，天使还是魔鬼？](https://blog.yorek.xyz/android/paid/master/native_hook/)
3. [OpenHarmony/third_party_musl](https://gitee.com/openharmony/third_party_musl)