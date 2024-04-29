#ifndef SCENE_H
#define SCENE_H

#include "SceneManager.h"
#include "GameObject.h"

class Scene final
{
public:

	~Scene() = default;
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) noexcept = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) noexcept = delete;

	void Add(std::unique_ptr<GameObject>&& object);

	void GameStart();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render() const;

	const std::string& GetName() const;

private:

	explicit Scene(const std::string& name);
	friend Scene& SceneManager::CreateScene(const std::string& name);

private:

	const std::string m_Name;
	std::vector<std::unique_ptr<GameObject>> m_Objects;

};

#endif // !SCENE_H