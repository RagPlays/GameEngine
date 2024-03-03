#ifndef SCENE_H
#define SCENE_H

#include "SceneManager.h"

class GameObject;

class Scene final
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	~Scene() = default;

	void Add(std::shared_ptr<GameObject> object);

	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render() const;

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private:
	explicit Scene(const std::string& name);

	void Remove(std::shared_ptr<GameObject> object);
	void RemoveAllObjects();

	std::string m_Name;
	std::vector<std::shared_ptr<GameObject>> m_Objects;

	static unsigned int m_IdCounter;
};

#endif // !SCENE_H