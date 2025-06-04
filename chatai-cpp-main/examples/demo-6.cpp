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
	// Set the maximum number of tokens
	ai.SetMaxTokens(1024);

	// Ask
	ai.Ask("How to design software?");
	// Get the first answer
	cout << "===== first answer : \n" << ai.GetReplyText(0) << endl;
	// Get the second answer
	cout << "\n===== second answer: \n" << ai.GetReplyText(1) << endl;
	// Get the third answer  == answer : ""  Because AI does not have a third answer ==
	cout << "\n===== third answer: \n" << ai.GetReplyText(2) << endl << endl << endl;
	

	// Get the usage
	cout << "usage: \n";
	vector<ChatAI::ReplyJsonMessage::_usage> usage = ai.GetReplyUsage();
	int cnt = 1;
	for (auto i : usage)
	{
		cout << "  -> usage: " << cnt++ << endl;
		cout << "completion_tokens: " << i.completion_tokens << endl;
		cout << "prompt_tokens: " << i.prompt_tokens << endl;
		cout << "total_tokens: " << i.total_tokens << endl;
	}

	// Obtain the details of the answer.
	vector<ChatAI::ReplyJsonMessage> replys = ai.GetAllDetailsReply();
	cnt = 1;
	for (auto i : replys)
	{
		cout << "  -> reply:" << cnt++ << endl;
		cout << "id:" << i.id << endl;
		cout << "object:" << i.object << endl;
		cout << "model:" << i.model << endl;
		cout << "created:" << i.created << endl;
		cout << "choices.index:" << i.choices.index << endl;
		cout << "choices.finish_reason:" << i.choices.finish_reason << endl;
		cout << "choices.message.role:" << i.choices.message.role << endl;
		cout << "choices.message.content:" << i.choices.message.content << endl;
		cout << "usage.completion_tokens:" << i.usage.completion_tokens << endl;
		cout << "usage.prompt_tokens:" << i.usage.prompt_tokens << endl;
		cout << "usage.total_tokens:" << i.usage.total_tokens << endl;
	}
	return 0;
}
