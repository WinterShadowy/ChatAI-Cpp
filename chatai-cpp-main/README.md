# 中文概述
## 基本概述
1. 一个轻量级的C++库，用于与OpenAI交互，只支持与AI聊天。
2. 本项目基于Github项目：[openai-cpp](https://github.com/olrea/openai-cpp)的二次开发。
3. 仅支持Windows平台。测试集成开发环境：VS2022（MSVC C++17）
4. 带有“W”后缀的函数用于处理宽字符串，这些函数通常处理Unicode字符串，而不是传统的ANSI字符串。

## 要求
无特殊要求。你应该已经有了这些：
1. C++11/C++14/C++17/C++20兼容编译器
2. [libcurl](https://curl.se/libcurl/)（检查[安装curl](https://everything.curl.dev/get)以确保您拥有开发包）

## 安装
1. 库由三个文件组成：include/openai/openai.hpp、include/opensai/nlohmann/json.hpp、include/openai/opensai-chat.hpp。
2. 只需复制[include/openai](https://gitcode.com/user0x0001/ChatAI-Cpp/tree/main/chatai-cpp-main/include/openai)在项目中的文件夹中，您可以在代码中使用`#include“openai-chat.hpp”`。仅此而已。

## 使用方法
请参阅参考示例文件夹中的演示。
# English overview
## Basic Overview
1. A lightweight C++library for interacting with OpenAI, which only supports chatting with AI.
2. It is based on the Github project: [openai-cpp](https://github.com/olrea/openai-cpp) for secondary development.
3. Only supports the Windows platform. Test IDE: VS2022(MSVC C++17)
4. Functions with the "W" suffix are used to handle wide-character strings, which typically process Unicode strings rather than traditional ANSI strings.

## Requirements
No special requirement. You should already have these :
1. C++11/C++14/C++17/C++20 compatible compiler
2. [libcurl](https://curl.se/libcurl/) (check [Install curl](https://everything.curl.dev/get) to make sure you have the development package)

## Installation
1. The library consists of three files: include/openai/openai.hpp,include/openai/nlohmann/json.hpp, include/openai/openai-chat.hpp. 
2. Just copy the [include/openai](https://github.com/WinterShadowy/ChatAI-Cpp/tree/master/chatai-cpp-main/include/openai)) folder in your project and you can use `#include "openai-chat.hpp"` in your code. That is all.  

## Usage
Please refer to the demo in the reference example folder.