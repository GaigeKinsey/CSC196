#include "json.h"
#include "filesystem.h"
#include <iostream>

bool json::load(const char* filename, rapidjson::Document& document)
{
	bool success = false;

	char* buffer;
	size_t size;

	if (filesystem::read_file(filename, (void**)& buffer, size)) {
		std::cout << buffer;
		document.Parse(buffer);
		success = document.IsObject();

		filesystem::free_file(buffer);
	}

	return success;
}

bool json::get_int(const rapidjson::Value& value, const char* property_name, int& _int)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (property.IsInt() == false) {
		return false;
	}

	_int = property.GetInt();

	return true;
}

bool json::get_float(const rapidjson::Value& value, const char* property_name, float& _float)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (property.IsFloat() == false) {
		return false;
	}

	_float = property.GetFloat();

	return true;
}

bool json::get_string(const rapidjson::Value& value, const char* property_name, std::string& _string)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (property.IsString() == false) {
		return false;
	}

	_string = property.GetString();

	return true;
}

bool json::get_bool(const rapidjson::Value& value, const char* property_name, bool& _bool)
{
	return false;
}

bool json::get_vector2(const rapidjson::Value& value, const char* property_name, vector2& _vector2)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (property.IsArray() == false || property.Size() != 2) {
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 2; i++) {
		if (property[i].IsDouble() == false) {
			return false;
		}
	}

	_vector2.x = property[0].GetFloat();
	_vector2.y = property[1].GetFloat();

	return true;
}
