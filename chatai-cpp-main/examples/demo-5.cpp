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
	// Set the number of AI answers.
	ai.SetN(2);
	ai.Ask("How to design software?");
	// Get the first answer
	cout << "first answer: \n" << ai.GetReplyText(0) << endl;
	// Get the second answer
	cout << "second answer: \n" << ai.GetReplyText(1) << endl;
	// Get the third answer  answer : ""  Because AI does not have a third answer
	cout << "third answer: \n" << ai.GetReplyText(2) << endl;
	return 0;
}
