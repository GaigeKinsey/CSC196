#pragma once

#include "..\\core\core.h"
#include "..\\math\transform.h"
#include "..\\renderer\color.h"

#include "..\\external\core\include\core.h"

class Scene;

class Actor {
public:
	Actor() {}
	virtual ~Actor() {}

	virtual const char* GetType() { return "Actor"; }

	virtual void Update(float dt);
	virtual void Draw(Core::Graphics& graphics);

	virtual bool Load(const rapidjson::Value& value);

	void SetScene(Scene* scene) { m_scene = scene; }
	const std::string& GetName() { return m_name; }
	virtual Actor* Clone() { return new Actor(*this); }

public:
	bool destroy = false;
	std::string m_name;
	Scene* m_scene = nullptr;

	transform m_transform;
	color m_color;
	std::vector<vector2> m_vertices;
};