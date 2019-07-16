#include "player.h"
#include "scene.h"


void Player::Update(float dt) {
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) m_transform.rotation -= m_rotate * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) m_transform.rotation += m_rotate * dt;

	vector2 forward = vector2::rotate(vector2(0.0f, 1.0f), m_transform.rotation);

	if (Core::Input::IsPressed(Core::Input::KEY_UP)) m_transform.translation += forward * m_speed * dt;

	if (m_transform.translation.x > 800.0f) m_transform.translation.x = 0.0f;
	if (m_transform.translation.x < 0.0f) m_transform.translation.x = 800.0f;
	if (m_transform.translation.y > 600.0f) m_transform.translation.y = 0.0f;
	if (m_transform.translation.y < 0.0f) m_transform.translation.y = 600.0f;

	if (Core::Input::IsPressed(Core::Input::KEY_SPACE)) {
		Actor* actor = ActorFactory::Instance()->Create("Missile_Spawner");
		actor->m_transform.translation = m_transform.translation;
		actor->m_transform.rotation = m_transform.rotation;

		m_scene->AddActor(actor);
	}
}

bool Player::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}