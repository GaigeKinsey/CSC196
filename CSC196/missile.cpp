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
		m_transform.translation.y > 600.0f || m_transform.translation.y < 0.0f) m_destroy = true;

	std::vector<Actor*> actors = m_scene->GetActorsByTag("Enemy");
	for (Actor* actor : actors) {
		float distance = vector2::distance(actor->m_transform.translation, m_transform.translation);
		if (distance <= m_radius.x + actor->m_radius.x || distance <= m_radius.y + actor->m_radius.y) {
			actor->m_destroy = true;
			m_destroy = true;
			break;
		}
	}
}

bool Missile::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}
