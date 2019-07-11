#pragma once

#include "..\\core\core.h"
#include "vector2.h"

struct transform {
	vector2 translation;
	float rotation;
	vector2 scale;

	transform() : rotation(0.0f) {}
	transform(vector2& translation, float rotation, vector2 scale) :
		translation(translation),
		rotation(rotation),
		scale(scale) {}

	bool Load(const rapidjson::Value& value);
};