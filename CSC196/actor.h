#pragma once

#include "..\\core\core.h"
#include "..\\math\transform.h"
#include "..\\renderer\color.h"

#include "..\\external\core\include\core.h"

class Actor {
public:
	Actor() {}

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	bool Load(const rapidjson::Value& value);

private:
	transform m_transform;
	color m_color;
	std::vector<vector2> m_vertices;
};