#define _CRT_SECURE_NO_WARNINGS
#include "openai_chat.hpp"
#include <iostream>
#include <vector>

std::string api_key = "YOUR_API_KEY";
std::string url = "YOUR_URL";
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
