#pragma once

#include "actor.h"

class Player : public Actor {
public:
	Player();
	virtual ~Player() {};

	const char* GetType() { return "Player"; }

	void Update(float dt) override;

	virtual bool Load(const rapidjson::Value& value);
	virtual Player* Clone() { return new Player(*this); }

private:
	float m_speed = 0.0f;
	float m_rotate = 0.0f;
	float m_fireCooldown = 0.0f;
};