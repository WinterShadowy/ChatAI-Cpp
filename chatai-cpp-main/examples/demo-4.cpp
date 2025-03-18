#define _CRT_SECURE_NO_WARNINGS
#include "openai_chat.hpp"
#include <iostream>
#include <vector>

std::string api_key = "hk-p9q8f71000035387f6bf91e3e3a4b36a6a9c1b0fcd7edbdc";
std::string url = "https://api.openai-hk.com/v1/";
std::string model = "gpt-4o-mini-2024-07-18"; // gpt-3.5-turbo...... 
using namespace std;

int main()
{
	ChatAI::ChatAI ai(api_key, url, model, true);
	// Implement contextual dialogue
	while (true) 
	{
		cout << " You: ";
		string input;
		getline(cin, input);
		cout << "AI: ";
		cout << ai.ask(input) << endl << endl;
	}
	return 0;
}
