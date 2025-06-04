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
	// The fourth parameter must be true to save the conversation with AI, but you can also choose other ways to store your conversation with AI.
	ChatAI::ChatAI ai(api_key, url, model, true);   

	cout << ai.ask(std::string("Can we find a unique answer to the quadratic equation 2x+5y=8. Only answer yes or no")) << endl << endl;

	for (auto i : ai.GetContext())
	{
		cout << "role : " << i.role << "  text: " << i.content << endl;
	}
	cout << ai.ask(std::string("Based on the previous equation, combined with the binary linear equation 3x+5y=7, can we find the specific values of x and y? You can solve for the specific values of x and y, otherwise output NO.")) << endl << endl;
	for (auto i : ai.GetContext())
	{
		cout << "role : " << i.role << "  text: " << i.content << endl;
	}

	return 0;
}
