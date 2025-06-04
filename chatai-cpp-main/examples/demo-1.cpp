#define _CRT_SECURE_NO_WARNINGS
#include "openai_chat.hpp"
#include "iostream"

std::string api_key = "YOUR_API_KEY";
std::string url = "YOUR_URL";
std::string model = "gpt-4o-mini-2024-07-18"; // gpt-3.5-turbo...... 
using namespace std;

int main()
{
	ChatAI::ChatAI ai(api_key, url, model);
	cout << ai.ask(std::string("hello")) << endl;
	return 0;
}
