#include "openai_chat.hpp"

std::string api_key = "";
std::string api_base_url = "";
std::string model = "gpt-3.5-turbo";

int main()
{
    ChatAI::ChatAI ai(api_key, api_base_url, model);
	ai.SetN("4");
	while (true)
	{
		std::string chat;
		std::cin >> chat;
		ai.ask(chat);
		std::cout << "ai: " << ai[2].reply() << std::endl;
	}
	return 0;
}
