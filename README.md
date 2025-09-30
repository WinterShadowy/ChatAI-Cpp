## Hint:
This project is no longer under maintenance.

If you want to implement C++and AI interaction, you can refer to my new project: [ALL-AI-Cpp](https://github.com/WinterShadowy/ALL-AI-Cpp), which has richer and more powerful features.

If it's helpful to you, you can point out a star for my project. Your star is the driving force behind my updates.

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

## !!!
This project is no longer under maintenance. You can take a look at my new related project: [ALL AI Cpp](https://github.com/WinterShadowy/ALL-AI-Cpp)
