# GitAskHook
使用某些git工具时，当出现文件被占用(error: unable to unlink old 'xxx': Invalid argument)，
工具没有做任何处理，导致git流程被异常终止，本地工作目录被污染。

本工具用于拦截Git unlink文件失败事件，给出危险提示，避免这种git静默的处理引起不可挽回的错误。

# 注册Windows系统环境变量
1. 下载本工程，用VisualStudio编译，得到GitAsk.exe;
2. 在Windows系统环境变量中增加变量`GIT_ASK_YESNO`，值为GitAsk.exe所在路径.

可以用命令行设置系统环境变量:
```bat
setx GIT_ASK_YESNO GitAsk.exe文件的绝对路径
```
