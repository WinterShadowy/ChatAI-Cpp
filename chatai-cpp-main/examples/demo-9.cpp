#include "openai_chat.hpp"

std::string api_key = "";
std::string api_base_url = "";
std::string model = "gpt-3.5-turbo";

int main()
{
	// If the fourth parameter is true, the conversation can use context.
	// 第四个参数为true，就可以让对话联系上下文。默认为false
    ChatAI::ChatAI ai(api_key, api_base_url, model, true);
	ai.SetN("4");
	while (true)
	{
		std::string chat;
		std::getline(std::cin, chat);
		std::cout << ai.Ask_AI(chat)[1].reply() << std::endl;
	}
	return 0;
}