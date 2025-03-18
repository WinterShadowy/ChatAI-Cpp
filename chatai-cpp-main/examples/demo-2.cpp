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
	ChatAI::ChatAI ai(api_key, url, model);
	std::vector < std::string > models = ai.GetModelList();
	cout << "Model List:" << endl;
	for (auto i : models)
		cout << i << endl;

	cout << "\n\nModel Details:\n";
	std::vector <ChatAI::ModelInfo> modelInfo = ai.GetModelInfo();
	for(auto i : modelInfo)
	{
		cout << "created: " << i.created << \
			"  \nid: " << i.id << \
			"  \nobject: " << i.object << \
			"  \nowned_by: " << i.owned_by << \
			"  \nparent: " << i.parent << \
			"  \npermission-allow_create_engine: " << i.permission.allow_create_engine << \
			"  \npermission-allow_fine_tuning: " << i.permission.allow_fine_tuning << \
			"  \npermission-allow_logprobs: " << i.permission.allow_logprobs << \
			"  \npermission-allow_sampling: " << i.permission.allow_sampling << \
			"  \npermission-allow_search_indices: " << i.permission.allow_search_indices << \
			"  \npermission-allow_view: " << i.permission.allow_view << \
			"  \npermission-is_blocking: " << i.permission.is_blocking << \
			"  \npermission-created: " << i.permission.created << \
			"  \npermission-group: " << i.permission.group << \
			"  \npermission-id: " << i.permission.id << \
			"  \npermission-object: " << i.permission.object << \
			"  \npermission-organization: " << i.permission.organization << \
			"  \nroot: " << i.root << endl;
		cout << "==================================================================" << endl;
	}
		    
	return 0;
}
