#pragma once
#include "openai.hpp"
#include <stdlib.h>
#include <windows.h>
#include <strsafe.h>
#include <unordered_map>

namespace __OpenAI {
	namespace character {
		inline std::wstring MultiToWide(const std::string& str, int nCodePage = CP_UTF8)
		{
			int size = MultiByteToWideChar(nCodePage, 0, str.c_str(), -1, NULL, 0);
			std::wstring wstr(size, 0);
			MultiByteToWideChar(nCodePage, 0, str.c_str(), -1, &wstr[0], size);
			return wstr;
		}

		inline void MultiToWide(const std::string& str, std::wstring& targetBuffer, int nCodePage = CP_UTF8)
		{
			int size = MultiByteToWideChar(nCodePage, 0, str.c_str(), -1, NULL, 0);
			std::wstring wstr(size, 0);
			MultiByteToWideChar(nCodePage, 0, str.c_str(), -1, &wstr[0], size);
			targetBuffer = wstr;
			return;
		}

		inline std::string WideToMulti(const std::wstring& str, int nCodePage = CP_UTF8)
		{
			int size = WideCharToMultiByte(nCodePage, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
			std::string mstr(size, 0);
			WideCharToMultiByte(nCodePage, 0, str.c_str(), -1, &mstr[0], size, NULL, NULL);
			return mstr;
		}

		inline void WideToMulti(const std::wstring& str, std::string& targetBuffer, int nCodePage = CP_UTF8)
		{
			int size = WideCharToMultiByte(nCodePage, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
			std::string strA(size, 0);
			WideCharToMultiByte(nCodePage, 0, str.c_str(), -1, &strA[0], size, NULL, NULL);
			targetBuffer = strA;
			return;
		}

		inline int MultiToWide(const char* szSrc, wchar_t* szBuffer, int bufferSize, int nCodePage = CP_UTF8)
		{
			int size = MultiByteToWideChar(nCodePage, 0, szSrc, -1, NULL, 0);
			if (szBuffer == NULL)
				return size;

			if (size > bufferSize)	// 字符串长度大于缓冲区长度
				return -1;
			MultiByteToWideChar(nCodePage, 0, szSrc, -1, szBuffer, bufferSize);
			return size;
		}

		inline int WideToMulti(const wchar_t* szSrc, char* szBuffer, int bufferSize, int nCodePage = CP_UTF8)
		{
			int size = WideCharToMultiByte(nCodePage, 0, szSrc, -1, NULL, 0, NULL, NULL);
			if (szBuffer == NULL)
				return size;
			if (size > bufferSize)
				return -1;
			WideCharToMultiByte(nCodePage, 0, szSrc, -1, szBuffer, bufferSize, NULL, NULL);
			return size;
		}
	}
#define USER		"user"
#define ASSISTANT	"assistant"
#define SYSTEM		"system"

#define USERW		L"user"
#define ASSISTANTW	L"assistant"
#define SYSTEMW		L"system"

	typedef struct JSON_MESSAGESW {
		std::wstring role;
		std::wstring content;
	}JsonMessagesW, * JsonMessageWPtr;

	typedef struct JSON_MESSAGES {
		std::string role;
		std::string content;
	}JsonMessages, * JsonMessagesPtr;

	inline JsonMessages ToJsonMessages(const __OpenAI::JsonMessagesW& json_message)
	{
		JsonMessages json_messageA;
		json_messageA.role = __OpenAI::character::WideToMulti(json_message.role);
		json_messageA.content = __OpenAI::character::WideToMulti(json_message.content);
		return json_messageA;
	}
	inline JsonMessagesW ToJsonMessagesW(const __OpenAI::JsonMessages& json_message)
	{
		JsonMessagesW json_messagesW;
		json_messagesW.role = __OpenAI::character::MultiToWide(json_message.role);
		json_messagesW.content = __OpenAI::character::MultiToWide(json_message.content);
		return json_messagesW;
	}

	typedef struct LOGIT_BIAS {
		std::unordered_map <std::string, int> logit_bias;
		nlohmann::json to_json() const {
			return nlohmann::json(logit_bias);
		}

		static LOGIT_BIAS from_json(const nlohmann::json& json) {
			LOGIT_BIAS _logit_bias;
			_logit_bias.logit_bias = json.get<std::unordered_map<std::string, int>>();
			return _logit_bias;
		}
	}LogitBias, * LogitBiasPtr;

	typedef struct LOGIT_BIASW {
		std::unordered_map <std::wstring, int> logit_bias;
	}LogitBiasW, * LogitBiasWPtr;

	inline LogitBias ToLogitBias(const std::unordered_map <std::wstring, int>& wlogit_bias) {
		LogitBias logit_bias;
		for (const auto& item : wlogit_bias)
		{
			logit_bias.logit_bias.insert(std::make_pair(__OpenAI::character::WideToMulti(item.first), item.second));
		}
		return logit_bias;
	}
	inline LogitBiasW ToLogitBiasW(const std::unordered_map <std::string, int>& logit_bias) {
		LogitBiasW wlogit_bias;
		for (const auto& item : logit_bias)
		{
			wlogit_bias.logit_bias.insert(std::make_pair(__OpenAI::character::MultiToWide(item.first), item.second));
		}
		return wlogit_bias;
	}

	typedef struct JSONDATA_ASK {
		std::string model;              // 要使用的模型 ID
		std::vector<std::string> stop;  // 一个字符串或字符串数组，指定生成停止的条件
		std::string user;               // 可选字段，用于标识用户的 ID，便于跟踪和分析
		std::vector<JsonMessages> messages;			// 一个数组，包含交互的消息。
		LogitBias logit_bias;			// 一个对象，用于调整特定 token 的生成概率。
		float top_p;           // 0-255，控制选择的 token 概率的累积和
		std::string n;                // 0-255，指定生成的回答数量
		float temperature;               // 控制生成文本的随机性
		int max_tokens;                 // 生成回答的最大 token 数
		float frequency_penalty;           // 控制重复出现的词的惩罚
		float presence_penalty;            // 控制新出现的主题的惩罚
		bool stream;                   // 如果设置为 true，则响应将以流的方式返回
	} AskJsonMessage, * AskJsonMessagePtr;

	typedef struct JSONDATA_ASK_W {
		std::wstring model;              // 要使用的模型 ID
		std::vector<std::wstring> stop;  // 一个字符串或字符串数组，指定生成停止的条件
		std::wstring user;               // 可选字段，用于标识用户的 ID，便于跟踪和分析
		std::vector<JsonMessagesW> messages;			// 一个数组，包含交互的消息。
		LogitBiasW logit_bias;			// 一个对象，用于调整特定 token 的生成概率。
		float top_p;           // 0-255，控制选择的 token 概率的累积和
		std::wstring n;                // 0-255，指定生成的回答数量
		float temperature;               // 控制生成文本的随机性
		int max_tokens;                 // 生成回答的最大 token 数
		float frequency_penalty;           // 控制重复出现的词的惩罚
		float presence_penalty;            // 控制新出现的主题的惩罚
		bool stream;                   // 如果设置为 true，则响应将以流的方式返回
	} AskJsonMessageW, * AskJsonMessagePtrW;

	inline AskJsonMessageW ToAskJsonMessageW(const AskJsonMessage& askJsonMessage)
	{
		AskJsonMessageW askJsonMessageW;
		askJsonMessageW.model = __OpenAI::character::MultiToWide(askJsonMessage.model);
		askJsonMessageW.user = __OpenAI::character::MultiToWide(askJsonMessage.user);
		askJsonMessageW.n = __OpenAI::character::MultiToWide(askJsonMessage.n);
		for (const auto& item : askJsonMessage.messages)
		{
			askJsonMessageW.messages.push_back(ToJsonMessagesW(item));
		}
		askJsonMessageW.logit_bias = ToLogitBiasW(askJsonMessage.logit_bias.logit_bias);
		for (const auto& item : askJsonMessage.stop)
		{
			askJsonMessageW.stop.push_back(__OpenAI::character::MultiToWide(item));
		}
		askJsonMessageW.top_p = askJsonMessage.top_p;
		askJsonMessageW.temperature = askJsonMessage.temperature;
		askJsonMessageW.max_tokens = askJsonMessage.max_tokens;
		askJsonMessageW.frequency_penalty = askJsonMessage.frequency_penalty;
		askJsonMessageW.presence_penalty = askJsonMessage.presence_penalty;
		askJsonMessageW.stream = askJsonMessage.stream;
		return askJsonMessageW;
	}
	inline AskJsonMessage ToAskJsonMessage(const AskJsonMessageW& askJsonMessageW)
	{
		AskJsonMessage askJsonMessage;
		askJsonMessage.model = __OpenAI::character::WideToMulti(askJsonMessageW.model);
		askJsonMessage.user = __OpenAI::character::WideToMulti(askJsonMessageW.user);
		askJsonMessage.n = __OpenAI::character::WideToMulti(askJsonMessageW.n);
		for (const auto& item : askJsonMessageW.messages)
		{
			askJsonMessage.messages.push_back(ToJsonMessages(item));
		}
		askJsonMessage.logit_bias = ToLogitBias(askJsonMessageW.logit_bias.logit_bias);
		for (const auto& item : askJsonMessageW.stop)
		{
			askJsonMessage.stop.push_back(__OpenAI::character::WideToMulti(item));
		}
		askJsonMessage.top_p = askJsonMessageW.top_p;
		askJsonMessage.temperature = askJsonMessageW.temperature;
		askJsonMessage.max_tokens = askJsonMessageW.max_tokens;
		askJsonMessage.frequency_penalty = askJsonMessageW.frequency_penalty;
		askJsonMessage.presence_penalty = askJsonMessageW.presence_penalty;
		askJsonMessage.stream = askJsonMessageW.stream;
		return askJsonMessage;
	}
	// 回复
#define STOP "stop"
#define LENGTH "length"
#define CONTENT_FILTER "content_filter"

#define STOPW L"stop"
#define LENGTHW L"length"
#define CONTENT_FILTERW L"content_filter"

	// 保留参数
	typedef struct JSON_MESSAGES_REPLY_Retention_parameter {
	}Retention_Parameter;
	typedef struct JSON_MESSAGES_REPLY_Retention_parameterW {
	}Retention_ParameterW;

	typedef struct JSON_MESSAGES_REPLY {
		std::string id;		// 响应的唯一标识符，通常以 chatcmpl- 开头，用于跟踪请求。
		std::string object;	// 表示返回对象的类型，通常为 "chat.completion"
		std::string model;	// 指定使用的模型 ID
		unsigned long long created;		// 响应生成的时间戳（Unix 时间格式），表示响应创建的时间。
		struct _choices {
			struct _message {
				std::string role;	// 消息的角色
				std::string content;	// AI 生成的回答内容，字符串类型
			}message;
			unsigned int index;		// 选项的索引，通常从 0 开始
			std::string finish_reason;	// 表示生成结束的原因
		}choices;
		struct _usage {
			unsigned int prompt_tokens;  // 输入消息（提示）所使用的 token 数
			unsigned int completion_tokens; // 生成的回答所使用的 token 数
			unsigned int total_tokens;	// 总的 token 数，等于 prompt_tokens 和 completion_tokens 之和
		}usage;
	}ReplyJsonMessage, * ReplyJsonMessagePtr;

	typedef struct JSON_MESSAGES_REPLY_W {
		std::wstring id;
		std::wstring object;
		std::wstring model;
		unsigned long long created;
		struct _choices {
			struct _message {
				std::wstring role;
				std::wstring content;
			}messageW;
			unsigned int index;
			std::wstring finish_reason;
		}choices;
		struct _usage {
			unsigned int prompt_tokens;
			unsigned int completion_tokens;
			unsigned int total_tokens;
		}usage;
	}ReplyJsonMessageW, * ReplyJsonMessagePtrW;

	inline ReplyJsonMessage ToReplyJsonMessage(const ReplyJsonMessageW& replyJsonMessageW)
	{
		ReplyJsonMessage replyJsonMessage;
		replyJsonMessage.id = __OpenAI::character::WideToMulti(replyJsonMessageW.id);
		replyJsonMessage.object = __OpenAI::character::WideToMulti(replyJsonMessageW.object);
		replyJsonMessage.model = __OpenAI::character::WideToMulti(replyJsonMessageW.model);
		replyJsonMessage.created = replyJsonMessageW.created;
		replyJsonMessage.choices.index = replyJsonMessageW.choices.index;
		replyJsonMessage.choices.finish_reason = __OpenAI::character::WideToMulti(replyJsonMessageW.choices.finish_reason);
		replyJsonMessage.choices.message.role = __OpenAI::character::WideToMulti(replyJsonMessageW.choices.messageW.role);
		replyJsonMessage.choices.message.content = __OpenAI::character::WideToMulti(replyJsonMessageW.choices.messageW.content);
		replyJsonMessage.usage.prompt_tokens = replyJsonMessageW.usage.prompt_tokens;
		replyJsonMessage.usage.completion_tokens = replyJsonMessageW.usage.completion_tokens;
		replyJsonMessage.usage.total_tokens = replyJsonMessageW.usage.total_tokens;
		return replyJsonMessage;
	}
	inline ReplyJsonMessageW ToReplyJsonMessageW(const ReplyJsonMessage& replyJsonMessage)
	{
		ReplyJsonMessageW replyJsonMessageW;
		replyJsonMessageW.id = __OpenAI::character::MultiToWide(replyJsonMessage.id);
		replyJsonMessageW.object = __OpenAI::character::MultiToWide(replyJsonMessage.object);
		replyJsonMessageW.model = __OpenAI::character::MultiToWide(replyJsonMessage.model);
		replyJsonMessageW.created = replyJsonMessage.created;
		replyJsonMessageW.choices.index = replyJsonMessage.choices.index;
		replyJsonMessageW.choices.finish_reason = __OpenAI::character::MultiToWide(replyJsonMessage.choices.finish_reason);
		replyJsonMessageW.choices.messageW.role = __OpenAI::character::MultiToWide(replyJsonMessage.choices.message.role);
		replyJsonMessageW.choices.messageW.content = __OpenAI::character::MultiToWide(replyJsonMessage.choices.message.content);
		replyJsonMessageW.usage.prompt_tokens = replyJsonMessage.usage.prompt_tokens;
		replyJsonMessageW.usage.completion_tokens = replyJsonMessage.usage.completion_tokens;
		replyJsonMessageW.usage.total_tokens = replyJsonMessage.usage.total_tokens;
		return replyJsonMessageW;
	}

	typedef struct MODEL {
		int created;
		std::string id;
		std::string object;
		std::string owned_by;
		std::string parent;
		struct _permission {
			bool allow_create_engine;
			bool allow_fine_tuning;
			bool allow_logprobs;
			bool allow_sampling;
			bool allow_search_indices;
			bool allow_view;
			bool is_blocking;
			std::string created;
			std::string group;
			std::string id;
			std::string object;
			std::string organization;
		} permission;
		std::string root;
	}ModelInfo;

	typedef struct MODEL_W {
		int created;
		std::wstring id;
		std::wstring object;
		std::wstring owned_by;
		std::wstring parent;
		struct _permission {
			bool allow_create_engine;
			bool allow_fine_tuning;
			bool allow_logprobs;
			bool allow_sampling;
			bool allow_search_indices;
			bool allow_view;
			bool is_blocking;
			std::wstring created;
			std::wstring group;
			std::wstring id;
			std::wstring object;
			std::wstring organization;
		} permission;
		std::wstring root;
	}ModelInfoW;

	inline ModelInfo ToModelInfo(const ModelInfoW& modelInfoW)
	{
		ModelInfo modelInfo;
		modelInfo.created = modelInfoW.created;
		modelInfo.id = __OpenAI::character::WideToMulti(modelInfoW.id);
		modelInfo.object = __OpenAI::character::WideToMulti(modelInfoW.object);
		modelInfo.owned_by = __OpenAI::character::WideToMulti(modelInfoW.owned_by);
		modelInfo.parent = __OpenAI::character::WideToMulti(modelInfoW.parent);
		modelInfo.permission.allow_create_engine = modelInfoW.permission.allow_create_engine;
		modelInfo.permission.allow_fine_tuning = modelInfoW.permission.allow_fine_tuning;
		modelInfo.permission.allow_logprobs = modelInfoW.permission.allow_logprobs;
		modelInfo.permission.allow_sampling = modelInfoW.permission.allow_sampling;
		modelInfo.permission.allow_search_indices = modelInfoW.permission.allow_search_indices;
		modelInfo.permission.allow_view = modelInfoW.permission.allow_view;
		modelInfo.permission.is_blocking = modelInfoW.permission.is_blocking;
		modelInfo.permission.created = __OpenAI::character::WideToMulti(modelInfoW.permission.created);
		modelInfo.permission.group = __OpenAI::character::WideToMulti(modelInfoW.permission.group);
		modelInfo.permission.id = __OpenAI::character::WideToMulti(modelInfoW.permission.id);
		modelInfo.permission.object = __OpenAI::character::WideToMulti(modelInfoW.permission.object);
		modelInfo.permission.organization = __OpenAI::character::WideToMulti(modelInfoW.permission.organization);
		modelInfo.root = __OpenAI::character::WideToMulti(modelInfoW.root);
		return modelInfo;
	}
	inline ModelInfoW ToModelInfoW(const ModelInfo& modelInfo)
	{
		ModelInfoW modelInfoW;
		modelInfoW.created = modelInfo.created;
		modelInfoW.id = __OpenAI::character::MultiToWide(modelInfo.id);
		modelInfoW.object = __OpenAI::character::MultiToWide(modelInfo.object);
		modelInfoW.owned_by = __OpenAI::character::MultiToWide(modelInfo.owned_by);
		modelInfoW.parent = __OpenAI::character::MultiToWide(modelInfo.parent);
		modelInfoW.permission.allow_create_engine = modelInfo.permission.allow_create_engine;
		modelInfoW.permission.allow_fine_tuning = modelInfo.permission.allow_fine_tuning;
		modelInfoW.permission.allow_logprobs = modelInfo.permission.allow_logprobs;
		modelInfoW.permission.allow_search_indices = modelInfo.permission.allow_search_indices;
		modelInfoW.permission.allow_view = modelInfo.permission.allow_view;
		modelInfoW.permission.is_blocking = modelInfo.permission.is_blocking;
		modelInfoW.permission.created = __OpenAI::character::MultiToWide(modelInfo.permission.created);
		modelInfoW.permission.group = __OpenAI::character::MultiToWide(modelInfo.permission.group);
		modelInfoW.permission.id = __OpenAI::character::MultiToWide(modelInfo.permission.id);
		modelInfoW.permission.object = __OpenAI::character::MultiToWide(modelInfo.permission.object);
		modelInfoW.permission.organization = __OpenAI::character::MultiToWide(modelInfo.permission.organization);
		modelInfoW.root = __OpenAI::character::MultiToWide(modelInfo.root);
		return modelInfoW;
	}

	class ans_ai {
	public:
		ans_ai(){}
		ans_ai(__OpenAI::ReplyJsonMessage& reply)
		{
			this->m_Json_Replys = reply;
			return;
		}
		ans_ai(std::vector<__OpenAI::ReplyJsonMessage> replys)
		{
			this->m_vec_Json_Replys = replys;
			return;
		}
		~ans_ai() {}

	public:
		std::string reply()
		{
			return this->m_Json_Replys.choices.message.content;
		}
		std::wstring replyW()
		{
			return std::move(__OpenAI::character::MultiToWide(this->m_Json_Replys.choices.message.content));
		}

		ans_ai operator[] (const int& index)
		{
			if (index < 0 || index >= this->m_vec_Json_Replys.size())
			{
				return std::move(ans_ai());
			}
			return std::move(ans_ai(this->m_vec_Json_Replys[index]));
		}
	private:
		__OpenAI::ReplyJsonMessage m_Json_Replys;
		std::vector<__OpenAI::ReplyJsonMessage> m_vec_Json_Replys;
	};

	class ChatAI
	{
	public:
		ChatAI() 
		{
			this->m_role = USER;
			this->m_Json_Ask.model = std::string("gpt-3.5-turbo");
			this->m_Json_Ask.max_tokens = 100;
			this->m_Json_Ask.n = std::to_string(1);
			this->m_Json_Ask.temperature = 0.8;
			this->m_Json_Replys.clear();
		}
		ChatAI(std::string& api_key, std::string& url, std::string& model, bool UseContext = false)
		{
			// init_ask
			this->m_role = USER;
			if (model.empty())
				model = std::string("gpt-3.5-turbo");
			this->m_Json_Ask.model = std::move(model);
			this->m_Json_Ask.max_tokens = 100;
			this->m_Json_Ask.n = std::to_string(1);
			this->m_Json_Ask.temperature = 0.8;
			// init_reply
			this->m_Json_Replys.clear();

			// init StartData
			this->m_api_key = std::move(api_key);
			this->m_url = std::move(url);
			this->throw_exceptions = false;
			this->organization_id = "";
			openai::start(this->m_api_key.c_str(), this->organization_id.c_str(), this->throw_exceptions, this->m_url.c_str());

			this->m_SaveContext = UseContext;
		}
		ChatAI(std::wstring api_key, std::wstring url, std::wstring model, bool UseConText = false)
		{
			// init ask
			this->m_role = USER;
			if (model.empty())
				model = L"gpt-3.5-turbo";
			this->m_Json_Ask.model = __OpenAI::character::WideToMulti(model);
			this->m_Json_Ask.max_tokens = 100;
			this->m_Json_Ask.n = std::to_string(1);
			this->m_Json_Ask.temperature = 0.8;
			// init reply
			this->m_Json_Replys.clear();

			// init StartData
			this->m_api_key = std::move(__OpenAI::character::WideToMulti(api_key));
			this->m_url = std::move(__OpenAI::character::WideToMulti(url));
			this->throw_exceptions = false;
			this->organization_id = "";

			openai::start(this->m_api_key.c_str(), this->organization_id.c_str(), this->throw_exceptions, this->m_url.c_str());

			this->m_SaveContext = UseConText;
		}
		ChatAI(char* api_key, char* url, char* model = NULL, bool UseConText = false)
		{
			// init_ask
			this->m_role = USER;
			if (model == NULL)
				this->m_Json_Ask.model = "gpt-3.5-turbo";
			else
				this->m_Json_Ask.model = std::string(model);
			this->m_Json_Ask.max_tokens = 100;
			this->m_Json_Ask.n = std::to_string(1);
			this->m_Json_Ask.temperature = 0.8;

			// init reply
			this->m_Json_Replys.clear();

			// init StartData
			this->m_api_key = api_key;
			this->m_url = url;
			this->throw_exceptions = false;
			this->organization_id = "";
			openai::start(this->m_api_key, this->organization_id, this->throw_exceptions, this->m_url);

			this->m_SaveContext = UseConText;
		}
		ChatAI(wchar_t* api_key, wchar_t* url, wchar_t* model = NULL, bool UseConText = false)
		{
			// init ask
			this->m_role = USER;
			if (model == NULL)
				this->m_Json_Ask.model = "gpt-3.5-turbo";
			else
				this->m_Json_Ask.model = __OpenAI::character::WideToMulti(model);
			this->m_Json_Ask.max_tokens = 100;
			this->m_Json_Ask.n = std::to_string(1);
			this->m_Json_Ask.temperature = 0.8;

			// init reply
			this->m_Json_Replys.clear();

			// init StartData
			this->m_api_key = __OpenAI::character::WideToMulti(std::wstring(api_key));
			this->m_url = __OpenAI::character::WideToMulti(std::wstring(url));
			this->throw_exceptions = false;
			this->organization_id = "";

			openai::start(this->m_api_key, this->organization_id, this->throw_exceptions, this->m_url);

			this->m_SaveContext = UseConText;
		}
		~ChatAI() {}
	private:
		nlohmann::json CreateJsonObj(__OpenAI::AskJsonMessage jsonMessage) const
		{
			nlohmann::json::array_t jsonMsgArr;
			for (const auto& message : jsonMessage.messages)
			{
				jsonMsgArr.push_back({ { "role", message.role }, { "content", message.content } });
			}
			nlohmann::json jsonObj;
			jsonObj["model"] = jsonMessage.model;
			jsonObj["messages"] = jsonMsgArr;
			jsonObj["temperature"] = jsonMessage.temperature;
			jsonObj["n"] = atoi(jsonMessage.n.c_str()) == 0 ? 1 : atoi(jsonMessage.n.c_str());
			jsonObj["top_p"] = jsonMessage.top_p;
			jsonObj["frequency_penalty"] = jsonMessage.frequency_penalty;
			jsonObj["presence_penalty"] = jsonMessage.presence_penalty;
			jsonObj["stop"] = jsonMessage.stop;
			jsonObj["stream"] = jsonMessage.stream;
			jsonObj["logit_bias"] = jsonMessage.logit_bias.logit_bias;
			jsonObj["user"] = jsonMessage.user;
			jsonObj["max_tokens"] = jsonMessage.max_tokens;
			return jsonObj;
		}
		std::vector<__OpenAI::ReplyJsonMessage> JsonToJsonStruct(nlohmann::json jsonRes)
		{
			std::vector<ReplyJsonMessage> replies;
			if (jsonRes.contains("id") &&
				jsonRes.contains("object") &&
				jsonRes.contains("model") &&
				jsonRes.contains("created") &&
				jsonRes.contains("choices") &&
				jsonRes.contains("usage"))
			{
				ReplyJsonMessage reply;
				reply.id = jsonRes.at("id").get<std::string>();
				reply.object = jsonRes.at("object").get<std::string>();
				reply.model = jsonRes.at("model").get<std::string>();
				reply.created = jsonRes.at("created").get<unsigned long long>();

				// 解析 usage
				reply.usage.prompt_tokens = jsonRes.at("usage").at("prompt_tokens").get<unsigned int>();
				reply.usage.completion_tokens = jsonRes.at("usage").at("completion_tokens").get<unsigned int>();
				reply.usage.total_tokens = jsonRes.at("usage").at("total_tokens").get<unsigned int>();

				// 解析 choices
				for (const auto& choice : jsonRes.at("choices"))
				{
					reply.choices.index = choice.at("index").get<unsigned int>();
					reply.choices.finish_reason = choice.at("finish_reason").get<std::string>();
					reply.choices.message.role = choice.at("message").at("role").get<std::string>();
					reply.choices.message.content = choice.at("message").at("content").get<std::string>();

					replies.push_back(reply);
				}

			}
			else
			{
				this->m_Json_Replys.clear();
				this->m_Json_Replys = replies;
				return replies;
			}
			this->m_Json_Replys.clear();
			this->m_Json_Replys = replies;
			return replies;
		}
	public:
		void InitChatAI(std::string& api_key, std::string& url, std::string& model, bool UseContext = false)
		{
			// init_ask
			this->m_role = USER;
			if (model.empty())
				model = std::string("gpt-3.5-turbo");
			this->m_Json_Ask.model = std::move(model);
			this->m_Json_Ask.max_tokens = 100;
			this->m_Json_Ask.n = std::to_string(1);
			this->m_Json_Ask.temperature = 0.8;
			// init_reply
			this->m_Json_Replys.clear();

			// init StartData
			this->m_api_key = std::move(api_key);
			this->m_url = std::move(url);
			this->throw_exceptions = false;
			this->organization_id = "";
			openai::start(this->m_api_key.c_str(), this->organization_id.c_str(), this->throw_exceptions, this->m_url.c_str());

			this->m_SaveContext = UseContext;
		}

		ans_ai Ask_AI(std::string& question)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();

			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, question });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				this->m_Json_Ask.messages.push_back({ this->m_role, question });
			}
			auto res = openai::chat().create(CreateJsonObj(this->m_Json_Ask));
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				for (const auto& reply : this->m_Json_Replys)
				{
					this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
				}
			}
			if (this->m_Json_Replys.size() == 0)
			{
				if (this->m_SaveContext == true)
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
				return std::move(ans_ai());
			}
			return std::move(ans_ai(this->m_Json_Replys));
		}

		std::string ask(std::string question)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();

			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, question });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				this->m_Json_Ask.messages.push_back({ this->m_role, question });
			}
			auto res = openai::chat().create(CreateJsonObj(this->m_Json_Ask));
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				for (const auto& reply : this->m_Json_Replys)
				{
					this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
				}
			}
			if (this->m_Json_Replys.size() == 0)
			{
				if (this->m_SaveContext == true)
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
				return "";
			}
			this->m_Result = this->m_Json_Replys[0].choices.message.content;
			return this->m_Json_Replys[0].choices.message.content;
		}
		std::wstring askW(std::wstring question)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();

			std::string question_str = __OpenAI::character::WideToMulti(question);
			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, question_str });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				this->m_Json_Ask.messages.push_back({ this->m_role, question_str });
			}
			auto res = openai::chat().create(CreateJsonObj(this->m_Json_Ask));
			this->m_Json_Replys = JsonToJsonStruct(res);

			if (this->m_SaveContext == true)
			{
				for (const auto& reply : this->m_Json_Replys)
				{
					this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
				}
			}

			if (this->m_Json_Replys.size() == 0)
			{
				if (this->m_SaveContext == true)
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
				return L"";
			}

			return __OpenAI::character::MultiToWide(this->m_Json_Replys[0].choices.message.content);
		}

		nlohmann::json ask(nlohmann::json json)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();

			return openai::chat().create(json);
		}
		std::vector<__OpenAI::ReplyJsonMessage> ask(__OpenAI::AskJsonMessage json)
		{
			this->m_Json_Ask.messages.clear();
			this->m_Json_Replys.clear();
			if (this->m_SaveContext == true)
			{
				for (const auto& msgBuffer : json.messages)
				{
					this->m_vec_Context.push_back({ USER, msgBuffer.content });
				}
			}
			nlohmann::json jsonBuffer = CreateJsonObj(this->m_Json_Ask);
			auto res = openai::chat().create(jsonBuffer);
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				if (this->m_Json_Replys.size() == 0)
				{
					for (const auto& reply : this->m_Json_Replys)
					{
						this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
					}
				}
				else
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
			}
			return this->m_Json_Replys;
		}
		std::vector<__OpenAI::ReplyJsonMessageW> askW(__OpenAI::AskJsonMessageW json)
		{
			this->m_Json_Ask = ToAskJsonMessage(json);
			if (this->m_SaveContext == true)
			{
				this->m_vec_Context = this->m_Json_Ask.messages;
			}
			else
			{
				openai::start(this->m_api_key, this->organization_id, this->throw_exceptions, this->m_url);
			}
			nlohmann::json jsonBuffer = CreateJsonObj(this->m_Json_Ask);
			auto res = openai::chat().create(jsonBuffer);
			this->m_Json_Replys = JsonToJsonStruct(res);
			std::vector<__OpenAI::ReplyJsonMessageW> vec_ReplyJsonMessageW;
			for (const auto& reply : this->m_Json_Replys)
			{
				vec_ReplyJsonMessageW.push_back(ToReplyJsonMessageW(reply));
			}
			if (this->m_SaveContext == true)
			{
				if (this->m_Json_Replys.size() == 0)
				{
					for (const auto& reply : this->m_Json_Replys)
					{
						this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
					}
				}
				else
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
			}
			return vec_ReplyJsonMessageW;
		}
		void SetRole(std::string szRole)
		{
			if (szRole != "user" && szRole != "assistant" && szRole != "system")
				szRole = "user";
			this->m_role = szRole;
			return;
		}
		void SetRoleW(std::wstring szRole)
		{
			if (szRole != L"user" && szRole != L"assistant" && szRole != L"system")
				szRole = L"user";
			this->m_role = __OpenAI::character::WideToMulti(szRole);
			return;
		}
		void SetJsonMessages(__OpenAI::JsonMessages jsonMsg)
		{
			this->m_Json_Ask.messages.push_back(jsonMsg);
			return;
		}
		void SetJsonMessagesW(__OpenAI::JsonMessagesW jsonMsg)
		{
			this->m_Json_Ask.messages.push_back(ToJsonMessages(jsonMsg));
			return;
		}
		void SetJsonMessages(std::vector<__OpenAI::JsonMessages> vecJsonMessages)
		{
			this->m_Json_Ask.messages.clear();
			this->m_Json_Ask.messages = vecJsonMessages;
			return;
		}
		void SetJsonMessagesW(std::vector<__OpenAI::JsonMessagesW> vecJsonMessages)
		{
			this->m_Json_Ask.messages.clear();
			for (const auto& msgBuffer : vecJsonMessages)
			{
				this->m_Json_Ask.messages.push_back(ToJsonMessages(msgBuffer));
			}
			return;
		}

		void SetModel(std::string szModel)
		{
			this->m_Json_Ask.model = szModel;
			return;
		}
		void SetModelW(std::wstring szModel)
		{
			this->m_Json_Ask.model = __OpenAI::character::WideToMulti(szModel);
			return;
		}

		void SetStop(std::vector<std::string> vec_Stop)
		{
			this->m_Json_Ask.stop = vec_Stop;
			return;
		}
		void SetStopW(std::vector<std::wstring> vec_Stop)
		{
			this->m_Json_Ask.stop.clear();
			for (const auto& msgBuffer : vec_Stop)
			{
				this->m_Json_Ask.stop.push_back(__OpenAI::character::WideToMulti(msgBuffer));
			}
			return;
		}

		void SetTemperature(float fTemperature)
		{
			this->m_Json_Ask.temperature = fTemperature;
			return;
		}
		void SetMaxTokens(int nMaxTokens)
		{
			this->m_Json_Ask.max_tokens = nMaxTokens;
			return;
		}
		void SetTop_p(unsigned int unTop_p)
		{
			this->m_Json_Ask.top_p = unTop_p;
			return;
		}
		void SetFrequencyPenalty(float fFrequency_penalty)
		{
			this->m_Json_Ask.frequency_penalty = fFrequency_penalty;
			return;
		}
		void SetPresencePenalty(float fPresence_penalty)
		{
			this->m_Json_Ask.presence_penalty = fPresence_penalty;
			return;
		}
		void SetN(unsigned int unN)
		{
			if (unN <= 0)
				unN = 1;
			this->m_Json_Ask.n = std::to_string(unN);
			return;
		}
		void SetN(std::string szN)
		{
			this->m_Json_Ask.n = szN;
			return;
		}
		void SetN(std::wstring szN)
		{
			this->m_Json_Ask.n = __OpenAI::character::WideToMulti(szN);
			return;
		}
		void SetStream(bool bStream)
		{
			this->m_Json_Ask.stream = bStream;
			return;
		}
		void SetLogitBias(std::unordered_map<std::string, int> umap_Logit_bias)
		{
			this->m_Json_Ask.logit_bias.logit_bias = umap_Logit_bias;
			return;
		}
		void SetLogitBiasW(std::unordered_map<std::wstring, int> umap_Logit_bias)
		{
			this->m_Json_Ask.logit_bias.logit_bias.clear();
			for (const auto& msgBuffer : umap_Logit_bias)
			{
				this->m_Json_Ask.logit_bias.logit_bias[__OpenAI::character::WideToMulti(msgBuffer.first)] = msgBuffer.second;
			}
			return;
		}
		void SetUser(std::string szUser)
		{
			this->m_Json_Ask.user = szUser;
			return;
		}
		void SetUserW(std::wstring szUser)
		{
			this->m_Json_Ask.user = __OpenAI::character::WideToMulti(szUser);
			return;
		}
		void Ask(const char* question)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();
			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, std::string(question) });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				this->m_Json_Ask.messages.push_back({ USER, std::string(question) });
			}
			this->m_Json_Ask.messages.push_back({ this->m_role, std::string(question) });
			nlohmann::json jsonBuffer = CreateJsonObj(this->m_Json_Ask);
			auto res = openai::chat().create(jsonBuffer);
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				if (this->m_Json_Replys.size() == 0)
				{
					this->m_vec_Context.push_back({ ASSISTANT, std::string("") });
					return;
				}
				for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
				{
					this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
				}
			}
			return;
		}
		void AskW(const wchar_t* question)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();
			std::string ques = __OpenAI::character::WideToMulti(std::wstring(question));
			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, ques });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				this->m_Json_Ask.messages.push_back({ this->m_role, ques });
			}

			nlohmann::json jsonBuffer = CreateJsonObj(this->m_Json_Ask);
			auto res = openai::chat().create(jsonBuffer);
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				if (this->m_Json_Replys.size() == 0)
				{
					this->m_vec_Context.push_back({ ASSISTANT, std::string("") });
					return;
				}
				for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
				{
					this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
				}
			}
			return;
		}
		std::vector<__OpenAI::ReplyJsonMessage> GetReply()
		{
			return this->m_Json_Replys;
		}
		std::vector<__OpenAI::ReplyJsonMessageW> GetReplyW()
		{
			std::vector<__OpenAI::ReplyJsonMessageW> buffer;
			for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
			{
				buffer.push_back(ToReplyJsonMessageW(reply));
			}
			return buffer;
		}

		// 获取所有回复
		std::vector<__OpenAI::ReplyJsonMessage::_choices::_message> GetAllReply()
		{
			std::vector<__OpenAI::ReplyJsonMessage::_choices::_message> buffer;
			for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
			{
				buffer.push_back(reply.choices.message);
			}
			return buffer;
		}
		std::vector<__OpenAI::ReplyJsonMessageW::_choices::_message> GetAllReplyW()
		{
			std::vector<__OpenAI::ReplyJsonMessageW::_choices::_message> buffer;
			for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
			{
				buffer.push_back(ToReplyJsonMessageW(reply).choices.messageW);
			}
			return buffer;
		}
		std::vector<__OpenAI::ReplyJsonMessage> GetAllDetailsReply()
		{
			return this->m_Json_Replys;
		}
		std::vector<__OpenAI::ReplyJsonMessageW> GetAllDetailsReplyW()
		{
			std::vector <__OpenAI::ReplyJsonMessageW> buffer;
			for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
			{
				buffer.push_back(ToReplyJsonMessageW(reply));
			}
			return buffer;
		}
		// 获取第几个回复,从0开始数
		std::string GetReplyText(int index)
		{
			if (index >= this->m_Json_Replys.size())
				return "";
			return this->m_Json_Replys[index].choices.message.content;
		}
		std::wstring GetReplyTextW(int index)
		{
			if (index >= this->m_Json_Replys.size())
				return std::wstring(L"");
			return __OpenAI::character::MultiToWide(this->m_Json_Replys[index].choices.message.content);
		}

		std::vector<__OpenAI::ReplyJsonMessage::_usage> GetReplyUsage()
		{
			std::vector<__OpenAI::ReplyJsonMessage::_usage> buffer;
			for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
			{
				buffer.push_back(reply.usage);
			}
			return buffer;
		}
		std::vector<__OpenAI::ReplyJsonMessageW::_usage> GetReplyUsageW()
		{
			std::vector<__OpenAI::ReplyJsonMessageW::_usage> buffer;
			for (const __OpenAI::JSON_MESSAGES_REPLY reply : this->m_Json_Replys)
			{
				buffer.push_back(ToReplyJsonMessageW(reply).usage);
			}
			return buffer; // std::vector<__OpenAI::ReplyJsonMessageW::_usage>
		}

		std::vector<__OpenAI::ModelInfo> GetModelInfo() {
			auto res = openai::model().list();
			if (res.contains("data"))
			{
				__OpenAI::ModelInfo modelInfo;
				for (auto& buffer : res["data"])
				{
					if (buffer.contains("id"))
					{
						modelInfo.id = buffer.at("id").is_string() ? buffer.at("id").get<std::string>() : "";
					}
					if (buffer.contains("created"))
					{
						modelInfo.created = buffer.at("created").is_number() ? buffer.at("created").get<int>() : 0;
					}
					if (buffer.contains("owned_by"))
					{
						modelInfo.owned_by = buffer.at("owned_by").is_string() ? buffer.at("owned_by").get<std::string>() : "";
					}
					if (buffer.contains("object"))
					{
						modelInfo.object = buffer.at("object").is_string() ? buffer.at("object").get<std::string>() : "";
					}
					if (buffer.contains("parent"))
					{
						modelInfo.parent = buffer.at("parent").is_string() ? buffer.at("parent").get<std::string>() : "";
					}
					if (buffer.contains("root"))
					{
						modelInfo.root = buffer.at("root").is_string() ? buffer.at("root").get<std::string>() : "";
					}

					if (buffer.contains("permission"))
					{
						for (const auto& permission : buffer.at("permission"))
						{
							if (permission.contains("allow_create_engine"))
							{
								modelInfo.permission.allow_create_engine = \
									permission.at("allow_create_engine").is_string() ? permission.at("allow_create_engine").get<bool>() : false;
							}
							if (permission.contains("allow_fine_tuning"))
							{
								modelInfo.permission.allow_fine_tuning =
									permission.at("allow_fine_tuning").is_string() ? permission.at("allow_fine_tuning").get<bool>() : false;
							}
							if (permission.contains("allow_logprobs"))
							{
								modelInfo.permission.allow_logprobs = \
									permission.at("allow_logprobs").is_string() ? permission.at("allow_logprobs").get<bool>() : false;
							}
							if (permission.contains("allow_sampling"))
							{
								modelInfo.permission.allow_sampling = \
									permission.at("allow_sampling").is_string() ? permission.at("allow_sampling").get<bool>() : false;
							}
							if (permission.contains("allow_search_indices"))
							{
								modelInfo.permission.allow_search_indices = \
									permission.at("allow_search_indices").is_string() ? permission.at("allow_search_indices").get<bool>() : false;
							}
							if (permission.contains("allow_view"))
							{
								modelInfo.permission.allow_view = \
									permission.at("allow_view").is_string() ? permission.at("allow_view").get<bool>() : false;
							}
							if (permission.contains("is_blocking"))
							{
								modelInfo.permission.is_blocking = \
									permission.at("is_blocking").is_string() ? permission.at("is_blocking").get<bool>() : false;
							}
							if (permission.contains("created"))
							{
								modelInfo.permission.created = \
									permission.at("created").is_string() ? permission.at("created").get<std::string>() : "";
							}
							if (permission.contains("group"))
							{
								modelInfo.permission.group = \
									permission.at("group").is_string() ? permission.at("group").get<std::string>() : "";
							}
							if (permission.contains("id"))
							{
								modelInfo.permission.id = \
									permission.at("id").is_string() ? permission.at("id").get<std::string>() : "";
							}
							if (permission.contains("object"))
							{
								modelInfo.permission.object = \
									permission.at("object").is_string() ? permission.at("object").get<std::string>() : "";
							}
							if (permission.contains("organization"))
							{
								modelInfo.permission.organization = \
									permission.at("organization").is_string() ? permission.at("organization").get<std::string>() : "";
							}
						}
					}

					this->m_Json_Models.push_back(modelInfo);
				}
			}
			return this->m_Json_Models;
		}
		std::vector<__OpenAI::ModelInfoW> GetModelInfoW()
		{
			auto res = openai::model().list();
			if (res.contains("data"))
			{
				__OpenAI::ModelInfo modelInfo;
				for (auto& buffer : res["data"])
				{
					if (buffer.contains("id"))
					{
						modelInfo.id = buffer.at("id").is_string() ? buffer.at("id").get<std::string>() : "";
					}
					if (buffer.contains("created"))
					{
						modelInfo.created = buffer.at("created").is_number() ? buffer.at("created").get<int>() : 0;
					}
					if (buffer.contains("owned_by"))
					{
						modelInfo.owned_by = buffer.at("owned_by").is_string() ? buffer.at("owned_by").get<std::string>() : "";
					}
					if (buffer.contains("object"))
					{
						modelInfo.object = buffer.at("object").is_string() ? buffer.at("object").get<std::string>() : "";
					}
					if (buffer.contains("parent"))
					{
						modelInfo.parent = buffer.at("parent").is_string() ? buffer.at("parent").get<std::string>() : "";
					}
					if (buffer.contains("root"))
					{
						modelInfo.root = buffer.at("root").is_string() ? buffer.at("root").get<std::string>() : "";
					}

					if (buffer.contains("permission"))
					{
						for (const auto& permission : buffer.at("permission"))
						{
							if (permission.contains("allow_create_engine"))
							{
								modelInfo.permission.allow_create_engine = \
									permission.at("allow_create_engine").is_string() ? permission.at("allow_create_engine").get<bool>() : false;
							}
							if (permission.contains("allow_fine_tuning"))
							{
								modelInfo.permission.allow_fine_tuning =
									permission.at("allow_fine_tuning").is_string() ? permission.at("allow_fine_tuning").get<bool>() : false;
							}
							if (permission.contains("allow_logprobs"))
							{
								modelInfo.permission.allow_logprobs = \
									permission.at("allow_logprobs").is_string() ? permission.at("allow_logprobs").get<bool>() : false;
							}
							if (permission.contains("allow_sampling"))
							{
								modelInfo.permission.allow_sampling = \
									permission.at("allow_sampling").is_string() ? permission.at("allow_sampling").get<bool>() : false;
							}
							if (permission.contains("allow_search_indices"))
							{
								modelInfo.permission.allow_search_indices = \
									permission.at("allow_search_indices").is_string() ? permission.at("allow_search_indices").get<bool>() : false;
							}
							if (permission.contains("allow_view"))
							{
								modelInfo.permission.allow_view = \
									permission.at("allow_view").is_string() ? permission.at("allow_view").get<bool>() : false;
							}
							if (permission.contains("is_blocking"))
							{
								modelInfo.permission.is_blocking = \
									permission.at("is_blocking").is_string() ? permission.at("is_blocking").get<bool>() : false;
							}
							if (permission.contains("created"))
							{
								modelInfo.permission.created = \
									permission.at("created").is_string() ? permission.at("created").get<std::string>() : "";
							}
							if (permission.contains("group"))
							{
								modelInfo.permission.group = \
									permission.at("group").is_string() ? permission.at("group").get<std::string>() : "";
							}
							if (permission.contains("id"))
							{
								modelInfo.permission.id = \
									permission.at("id").is_string() ? permission.at("id").get<std::string>() : "";
							}
							if (permission.contains("object"))
							{
								modelInfo.permission.object = \
									permission.at("object").is_string() ? permission.at("object").get<std::string>() : "";
							}
							if (permission.contains("organization"))
							{
								modelInfo.permission.organization = \
									permission.at("organization").is_string() ? permission.at("organization").get<std::string>() : "";
							}
						}
					}

					this->m_Json_Models.push_back(modelInfo);
				}
			}

			std::vector<__OpenAI::ModelInfoW> vec_ModelInfoW;
			for (const auto& buffer : this->m_Json_Models)
			{
				vec_ModelInfoW.push_back(ToModelInfoW(buffer));
			}
			return vec_ModelInfoW;
		}
		std::vector < __OpenAI::JsonMessages> GetContext()
		{
			return this->m_vec_Context;
		}
		std::vector < __OpenAI::JsonMessagesW> GetContextW()
		{
			std::vector < __OpenAI::JsonMessagesW> vec_ContextW;
			for (const auto& buffer : this->m_vec_Context)
			{
				vec_ContextW.push_back(ToJsonMessagesW(buffer));
			}
			return vec_ContextW;
		}
		// 获取模型列表
		std::vector<std::string> GetModelList()
		{
			std::vector<std::string> vecModelList;
			GetModelInfo();
			for (const __OpenAI::ModelInfo buffer : this->m_Json_Models)
			{
				vecModelList.push_back(buffer.id);
			}
			return vecModelList;
		}
		std::vector<std::wstring> GetModelListW()
		{
			std::vector<std::wstring> vecModelList;
			GetModelInfo();
			for (const __OpenAI::ModelInfo buffer : this->m_Json_Models)
			{
				vecModelList.push_back(__OpenAI::character::MultiToWide(buffer.id));
			}
			return vecModelList;
		}
		void ask(const char* question, char* response, unsigned int response_size)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();

			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, std::string(question) });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				openai::start(this->m_api_key, this->organization_id, this->throw_exceptions, this->m_url);
				this->m_Json_Ask.messages.push_back({ this->m_role, std::string(question) });
			}

			nlohmann::json jsonBuffer = CreateJsonObj(this->m_Json_Ask);
			auto res = openai::chat().create(jsonBuffer);
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				if (this->m_Json_Replys.size() == 0)
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
				else
				{
					for (const auto& reply : this->m_Json_Replys)
					{
						this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
					}
				}
			}
			if (response == NULL)
			{
				return;
			}
			if (this->m_Json_Replys.size() == 0)
			{
				strncpy_s(response, response_size * sizeof(char), "", response_size);
			}
			else
			{
				strncpy_s(response, response_size * sizeof(char), this->m_Json_Replys[0].choices.message.content.c_str(), response_size);
			}
			return;
		}
		void askW(const wchar_t* question, wchar_t* response, unsigned int response_size)
		{
			this->m_Json_Replys.clear();
			this->m_Json_Ask.messages.clear();
			if (this->m_SaveContext == true)
			{
				this->m_vec_Context.push_back({ USER, __OpenAI::character::WideToMulti(std::wstring(question)) });
				this->m_Json_Ask.messages = this->m_vec_Context;
			}
			else
			{
				openai::start(this->m_api_key, this->organization_id, this->throw_exceptions, this->m_url);
				this->m_Json_Ask.messages.push_back({ this->m_role, __OpenAI::character::WideToMulti(std::wstring(question)) });
			}
			nlohmann::json jsonBuffer = CreateJsonObj(this->m_Json_Ask);
			auto res = openai::chat().create(jsonBuffer);
			this->m_Json_Replys = JsonToJsonStruct(res);
			if (this->m_SaveContext == true)
			{
				if (this->m_vec_Context.size() == 0)
				{
					this->m_vec_Context.push_back({ ASSISTANT, "" });
				}
				else
				{
					for (const auto& reply : this->m_Json_Replys)
					{
						this->m_vec_Context.push_back({ ASSISTANT, reply.choices.message.content });
					}
				}
			}
			if (response == NULL)
			{
				return;
			}
			std::wstring szRes;
			if (this->m_Json_Replys.size() == 0)
				szRes = L"";
			else
				szRes = __OpenAI::character::MultiToWide(this->m_Json_Replys[0].choices.message.content);
			wcsncpy_s(response, response_size * sizeof(wchar_t), szRes.c_str(), response_size);

			return;
		}

		friend std::ostream& operator<<(std::ostream& os, const ChatAI& ai)
		{
			os << ai.m_Result;
			return os;
		}
		ans_ai operator[] (const int& index)
		{
			if (index < 0 || index >= m_Json_Replys.size())
			{
				return std::move(ans_ai());
			}
			return std::move(ans_ai(this->m_Json_Replys[index]));
		}
	private:
		std::vector<__OpenAI::JsonMessages> m_vec_Context;
		__OpenAI::AskJsonMessage m_Json_Ask;
		std::vector <__OpenAI::ReplyJsonMessage> m_Json_Replys;
		std::vector <__OpenAI::ModelInfo> m_Json_Models;
		std::string m_api_key;
		std::string m_url;
		std::string organization_id; // 可选
		bool throw_exceptions; // 是否抛出异常
		std::string m_role;
		bool m_SaveContext;
		std::string m_Result;
	};
}

namespace ChatAI = __OpenAI;