#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:

	virtual ~SceneManager() = default;
	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	Scene& CreateScene(const std::string& name);
	void Destroy();

	bool Empty() const;
	void SetCurrentSceneByIndex(unsigned int idx);
	void SetCurrentSceneByName(const std::string& name);

	void GameStart();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render() const;

private:

	friend class Singleton<SceneManager>;
	SceneManager();

private:

	unsigned int m_CurrentSceneIdx;
	std::vector<std::shared_ptr<Scene>> m_Scenes;
};

#endif // !SCENEMANAGER_H