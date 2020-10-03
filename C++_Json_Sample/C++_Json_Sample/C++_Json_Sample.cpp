// C++_Json_Sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "JsonCppHandler.h"
#include "JsonVerify.h"
#include <vector>




void ReadJsonFile(const std::string& path)
{
	Json::Value root;
	if (!JsonCppHandler::FiletoValue(path, root))
	{
		std::cout << "Read Json File Failed" << std::endl;
	}

	try
	{
		//int
		std::cout << JSON_OBJ_VERIFY(root["id"], Json::ValueType::intValue).asInt() << std::endl;


		//string
		std::cout << JSON_OBJ_VERIFY(root["name"], Json::ValueType::stringValue).asString() << std::endl;


		//float
		std::cout << JSON_OBJ_VERIFY(root["team"]["title"]["count"], Json::ValueType::realValue).asFloat() << std::endl;


		//array
		//std::cout << JSON_OBJ_VERIFY(root["team"]["member"], Json::ValueType::arrayValue) << std::endl;
		Json::Value memberArray = JSON_OBJ_VERIFY(root["team"]["member"], Json::ValueType::arrayValue);
		for (auto &it : memberArray)
		{
			std::cout << "member id = " << JSON_OBJ_VERIFY(it["id"], Json::ValueType::intValue).asInt() << ", name = " << JSON_OBJ_VERIFY(it["name"], Json::ValueType::stringValue).asString() << std::endl;
		}


		//map
		std::map<int, std::string> docMap;
		Json::Value docArray = JSON_OBJ_VERIFY(root["documents"], Json::ValueType::arrayValue);
		for (auto &it : docArray)
		{
			std::string itStr = JSON_OBJ_VERIFY(it, Json::ValueType::stringValue).asString();
			std::string::size_type pos = itStr.find_first_of(":", 0);
			if (pos != std::string::npos)
			{
				docMap.emplace(std::atoi(itStr.substr(0, pos).c_str()), itStr.substr(pos + 1, itStr.length() - 1));
			}
		}


		for (auto &it : docMap)
		{
			std::cout << "doc id = " << it.first << ", name = " << it.second << std::endl;
		}

	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}


void ReadJsonString(const std::string& raw)
{
	Json::Value root;


	if (!JsonCppHandler::StringtoValue(raw, root))
	{
		std::cout << "Read Json String Failed" << std::endl;
	}


	try
	{
		std::cout << JSON_OBJ_VERIFY(root["Age"], Json::ValueType::intValue).asInt() << std::endl;
		std::cout << JSON_OBJ_VERIFY(root["Name"], Json::ValueType::stringValue).asString() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}


void JsonFiletoString(const std::string& path)
{
	std::string jsonString;


	Json::Value root;
	if (!JsonCppHandler::FiletoValue(path, root))
	{
		std::cout << "Read Json File Failed" << std::endl;
	}


	jsonString = root.toStyledString();
	std::cout << jsonString << std::endl;
}


void WriteJsonFile(const std::string& path, Json::Value& root)
{
	if (!JsonCppHandler::ValuetoFile(path, root))
	{
		std::cout << "Write Json File Failed" << std::endl;
	}
}


void WriteJsonString(Json::Value& root)
{
	std::string str;


	if (!JsonCppHandler::ValuetoString(str, root))
	{
		std::cout << "Write Json String Failed" << std::endl;
	}


	std::cout << str << std::endl;
}




int main()
{
	std::string readFile("D:\\203 - C++\\C++ Sample\\C++_Json_Sample\\x64\\Debug\\JsonSample.jpd");
	std::string writeFile("D:\\203 - C++\\C++ Sample\\C++_Json_Sample\\x64\\Debug\\JsonSample_Writed.jpd");

	//1
	//ReadJsonFile(readFile);


	//2
	//const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
	//ReadJsonString(rawJson);


	//3
	//JsonFiletoString(readFile);


	//4, 5
	Json::Value sample;
	sample["Name"] = "Robert";
	sample["Age"] = 27;
	std::vector<int> array = { 1, 2, 3 };
	for (const auto &it : array)
	{
		sample["Array"].append(Json::Value(it));
	}


	WriteJsonFile(writeFile, sample);
	WriteJsonString(sample);


	return 0;
}
