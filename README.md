# stage2

## dll说明

调用的四个接口样例在Wordlist.cpp中，与dll中其余文件不要放在一个项目中运行，其余应该是基于vs动态库建立基础上放进去。

**其中代码存在两处警告，需要改进**

几个动态库生成需要注意的点

- vs配置和平台的选择，debug x86还是debug x64。
- 生成时是否需要预编译头pch.h（如果完全从零开始造可以先忽略，如果不是，.h文件的顺序可能需要调整）
- 生成的名称，如果是函数，尤其是通用的函数，可以通过extern"C"来保证函数名就是dll生成的名字，如果是类的方法（emm..想来好像确实是我没有加，但是网上有帖子说对extern"C"对类的方法无效，但是我也不知道，再斟酌一下吧）

用动态库时

- 有两轮获取指针，一个是	`HMODULE hModule = LoadLibrary(_T("core.dll"));`,动态库dllmain中定义的一个入口，一个是`functionC C = (functionC)GetProcAddress(hModule,"gen_chain_char");`，functionC是参数“元组”？指针类型，这两个其中一个得到了NULL的值，都会导致dll调用失败
- `HMODULE hModule`失败，是vs平台选错了= =，或者传入地址错了，或者和Unicode、string等格式类型有关
  - x86 or x64 ? ：error = 173(好像是，不想复现了)
  - 传入地址错了
  - Unicode、string : _T("core.dll");   _T是#include "tchar.h"中的宏定义 ，如果没有 _T转化也会导致错误，如果没有include直接无法编译
- GetProcAddress
  - 返回NULL：error = 127
  - dll生成函数名已经出现错误了，不是你自己写的那个函数名，查看dll函数名工具：[*Dependency Walker*](http://www.dependencywalker.com/)

## bin说明

bin中是由dll生成的core.dll以及Wordlist.cpp调用该dll所生成的exe简易样例，测试仍需进一步进行。

