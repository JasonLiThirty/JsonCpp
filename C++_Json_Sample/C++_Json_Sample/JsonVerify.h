#ifndef JSON_CPP_VERIFY_H
#define JSON_CPP_VERIFY_H
#include <stdexcept>


bool JsonTypeLegal(Json::Value& v, Json::ValueType type)
{
	switch (type)
	{
	case Json::ValueType::intValue:
	case Json::ValueType::uintValue:
	{
		if (v.isInt() || v.isUInt() || v.isInt64() || v.isUInt64()) {
			return true;
		}
		break;
	}
	case Json::ValueType::realValue:
	{
		if (v.isDouble()) {
			return true;
		}
		break;
	}
	case Json::ValueType::stringValue:
	{
		if (v.isString()) {
			return true;
		}
		break;
	}
	case Json::ValueType::booleanValue:
	{
		if (v.isBool()) {
			return true;
		}
		break;
	}
	case Json::ValueType::arrayValue:
	{
		if (v.isArray()) {
			return true;
		}
		break;
	}
	case Json::ValueType::objectValue:
	{
		if (v.isObject()) {
			return true;
		}
		break;
	}
	default:
		break;
	}


	return false;
}


class json_exception : public std::runtime_error
{
public:


	json_exception(const char* msg) :std::runtime_error(msg)
	{}


	json_exception() = default;
	~json_exception() = default;
};


[[noreturn]]
void raise(const char *msg)
{
	throw json_exception(msg);
}


#define JSON_OBJ_VERIFY(json, type) \
	[&](Json::Value& v) \
	{	\
		std::ostringstream strOut; \
		if (!v || v.isNull()) { \
			strOut << "Json Object Non-Exist: " << #json << std::endl; \
			raise(strOut.str().c_str()); } \
		else if (!JsonTypeLegal(v, type)) { \
			strOut << "Json Object's Type is not Legal: " << #json << std::endl; \
			raise(strOut.str().c_str()); } \
		return v; \
	}(json)


#endif