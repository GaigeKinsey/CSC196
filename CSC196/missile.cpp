#include "missile.h"
#include "scene.h"

void Missile::Update(float dt) {
	vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
	m_transform.translation += forward * m_speed * dt;

	//if (m_transform.translation.x > 800.0f) m_transform.translation.x = 0.0f;
	//if (m_transform.translation.x < 0.0f) m_transform.translation.x = 800.0f;
	//if (m_transform.translation.y > 600.0f) m_transform.translation.y = 0.0f;
	//if (m_transform.translation.y < 0.0f) m_transform.translation.y = 600.0f;

	if (m_transform.translation.x > 800.0f || m_transform.translation.x < 0.0f ||
		m_transform.translation.y > 600.0f || m_transform.translation.y < 0.0f) destroy = true;
}

bool Missile::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}
