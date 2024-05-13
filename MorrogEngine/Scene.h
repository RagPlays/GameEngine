#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace MoE
{
	class SceneManager;
	class GameObject;

	class Scene final
	{
	public:

		explicit Scene(const std::string& name, std::function<void(Scene&)> loadFunc);
		~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) noexcept = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) noexcept = delete;

		void Add(std::unique_ptr<GameObject>&& object);
		void Load();
		void UnLoad();
		bool IsLoaded() const;

		void SceneStart();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;
		void SceneEnd();

		const std::string& GetName() const;

	private:

		bool m_IsLoaded;
		std::function<void(Scene&)> m_LoadFunction;
		const std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_Objects;

	};
}

#endif // !SCENE_H