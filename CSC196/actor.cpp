#include "actor.h"

void Actor::Update(float dt)
{
	//
}

void Actor::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(m_color);
	for (size_t i = 0; i < m_vertices.size() - 1; i++) {
		vector2 v1 = m_transform.translation + vector2::rotate(m_vertices[i], m_transform.rotation) * m_transform.scale;
		vector2 v2 = m_transform.translation + vector2::rotate(m_vertices[i + 1], m_transform.rotation) * m_transform.scale;
		graphics.DrawLine(v1.x, v1.y, v2.x, v2.y);
	}
}

bool Actor::Load(const rapidjson::Value& value)
{
	json::get_string(value, "name", m_name);

	const rapidjson::Value& tvalue = value["transform"];
	if (tvalue.IsObject()) {
		m_transform.Load(tvalue);
	}

	json::get_color(value, "color", m_color);
	const rapidjson::Value& vvalue = value["vertex"];
	if (vvalue.IsArray()) {
		json::get_vector2(vvalue, "v", m_vertices);
	}

	return true;
}
