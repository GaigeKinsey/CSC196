#include "enemy.h"
#include "scene.h"
#include "game.h"

Enemy::Enemy()
{
	AudioSystem::Instance()->AddSound("damage", "Audio\\damage.wav");
}

void Enemy::Update(float dt) {
	Actor* target = m_scene->GetActorByName("Player");
	if (target) {
		vector2 direction = target->m_transform.translation - m_transform.translation;
		float angle = vector2::get_angle(direction);
		m_transform.rotation = angle - math::HALF_PI;
		vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
		m_transform.translation += forward * m_speed * dt;

		float distance = vector2::distance(target->m_transform.translation, m_transform.translation);
		if (distance <= m_radius.x + target->m_radius.x || distance <= m_radius.y + target->m_radius.y) {
			AudioSystem::Instance()->PlaySounds("damage", false);
			Actor* actor = m_scene->GetActorFactory()->Create("Damage_Spawner");

			//Puts the explosion at the actual point of impact
			if (target->m_transform.translation.x - m_transform.translation.x >= 0) {
				actor->m_transform.translation.x = m_transform.translation.x + m_radius.x;
			}
			else {
				actor->m_transform.translation.x = m_transform.translation.x - m_radius.x;
			}

			if (target->m_transform.translation.y - m_transform.translation.y >= 0) {
				actor->m_transform.translation.y = m_transform.translation.y + m_radius.y;
			}
			else {
				actor->m_transform.translation.y = m_transform.translation.y - m_radius.y;
			}

			actor->m_transform.rotation = m_transform.rotation;
			m_scene->AddActor(actor);

			m_scene->GetGame()->SetLives(m_scene->GetGame()->GetLives() - 1);
			m_destroy = true;
		}
	}
}

bool Enemy::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}
