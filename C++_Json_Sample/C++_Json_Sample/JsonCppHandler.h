#ifndef JSON_CPP_HANDLER_H
#define JSON_CPP_HANDLER_H


#include <sstream> 
#include <iostream>  
#include <fstream>
#include <string>
#include <assert.h>  
#include "json.h"
#include "value.h"


class JsonCppHandler
{
public:

	static bool FiletoValue(const std::string& path, Json::Value& value)
	{
		std::ifstream ifs;
		ifs.open(path);


		Json::CharReaderBuilder builder;
		builder["collectComments"] = false;


		JSONCPP_STRING errs;
		if (!Json::parseFromStream(builder, ifs, &value, &errs))
		{
			std::cout << errs << std::endl;
			ifs.close();
			return false;
		}
		ifs.close();
		return true;
	}


	static bool StringtoValue(const std::string jsonString, Json::Value& value)
	{
		const auto length = static_cast<int>(jsonString.length());
		Json::CharReaderBuilder builder;
		const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());


		JSONCPP_STRING errs;
		if (!reader->parse(jsonString.c_str(), jsonString.c_str() + length, &value, &errs))
		{
			std::cout << errs << std::endl;
			return false;
		}
		return true;
	}


	static bool ValuetoFile(const std::string& path, Json::Value& value)
	{
		std::ofstream ofs(path.c_str());


		if (!ofs)
		{
			ofs.close();
			return false;
		}


		Json::StreamWriterBuilder builder;
		const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());


		writer->write(value, &ofs);
		ofs.close();
		return true;
	}


	static bool ValuetoString(std::string& jsonString, Json::Value& value)
	{
		Json::StreamWriterBuilder builder;
		jsonString = Json::writeString(builder, value);
		return true;
	}
};




#endif // ! JsonCppHandler