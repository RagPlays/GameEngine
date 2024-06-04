#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "Singleton.h"

namespace MoE
{
	class Scene;
	class Engine;
	class GameObject;

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

		bool IsValidGameObject(GameObject* const gameObject) const;
		bool IsValidSceneName(const std::string& sceneName);
		
		bool Empty() const;
		void SetCurrentSceneByIndex(uint8_t idx);
		void SetCurrentSceneByName(const std::string& name);
		void ReloadScene();

		Scene& GetCurrentScene() const;
		uint8_t GetCurrentSceneIndex() const;

		void GameStart();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

	private:

		friend class MoE::Singleton<SceneManager>;
		SceneManager();

		void CheckSceneSwap();

	private:

		bool m_NeedSceneChange;
		uint8_t m_ToSceneIdx;
		uint8_t m_CurrentSceneIdx;
		std::vector<std::unique_ptr<Scene>> m_Scenes;

	};
}

#endif // !SCENEMANAGER_H