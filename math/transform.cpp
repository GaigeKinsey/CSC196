#include "transform.h"

bool transform::Load(const rapidjson::Value& value)
{
	json::get_vector2(value, "position", translation);
	json::get_float(value, "rotation", rotation);
	json::get_float(value, "speed", speed);
	json::get_vector2(value, "scale", scale);

	return true;
}
