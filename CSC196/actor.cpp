#include "actor.h"

void Actor::Update(float dt)
{
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) m_transform.rotation -= .1f;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) m_transform.rotation += .1f;

	vector2 forward = vector2::rotate(vector2::right, m_transform.rotation);

	if (Core::Input::IsPressed(Core::Input::KEY_UP)) {
		m_transform.translation += forward * m_transform.speed;
	}
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) {
		m_transform.translation -= forward * m_transform.speed;
	}

	if (m_transform.translation.x > 800.0f) m_transform.translation.x = 0.0f;
	if (m_transform.translation.x < 0.0f)   m_transform.translation.x = 800.0f;
	if (m_transform.translation.y > 600.0f) m_transform.translation.y = 0.0f;
	if (m_transform.translation.y < 0.0f)   m_transform.translation.y = 600.0f;
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
