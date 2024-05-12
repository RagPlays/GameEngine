#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "Singleton.h"

class Scene;
class Engine;

class SceneManager final : public Singleton<SceneManager>
{
public:

	virtual ~SceneManager();

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	Scene& CreateScene(const std::string& name, std::function<void(Scene&)> loadFunc);
	void Destroy();

	bool Empty() const;
	void SetCurrentSceneByIndex(uint8_t idx);
	void SetCurrentSceneByName(const std::string& name);
	void GoNextScene();

	Scene& GetCurrentScene() const;
	uint8_t GetCurrentSceneIndex() const;

	void GameStart();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render() const;

private:

	friend class Singleton<SceneManager>;
	SceneManager();

	void CheckSceneSwap();

private:

	uint8_t m_ToSceneIdx;
	uint8_t m_CurrentSceneIdx;
	std::vector<std::unique_ptr<Scene>> m_Scenes;
};

#endif // !SCENEMANAGER_H