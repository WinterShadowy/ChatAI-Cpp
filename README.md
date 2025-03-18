1. A lightweight C++library for interacting with OpenAI, which only supports chatting with AI.
2. He is based on the Github project: [openai-cpp](https://github.com/olrea/openai-cpp) for secondary development.

## Installation

The library consists of three files: include/openai/openai.hpp,include/openai/nlohmann/json.hpp, include/openai/openai-chat.hpp. 
Just copy the [include/openaicpp](https://github.com/olrea/openai-cpp/tree/main/include/openai) folder in your project and you can use `#include "openai-chat.hpp"` in your code. That is all.  

> Note: **OpenAI-CPP** uses [Nlohmann Json](https://github.com/nlohmann/json) which is available in `include/json.hpp`. Feel free to use your own copy for faster compile time build. 

## Usage

Please refer to the demo in the reference example folder.
