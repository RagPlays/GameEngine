#if defined _DEBUG || defined DEBUG
#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

#include <memory>
#include <vector>

#include "Singleton.h"

namespace MoE
{
	class ImGuiComponent;

	class ImGuiRenderer final : public Singleton<ImGuiRenderer>
	{
	public:

		virtual ~ImGuiRenderer();

		ImGuiRenderer(const ImGuiRenderer& other) = delete;
		ImGuiRenderer(ImGuiRenderer&& other) noexcept = delete;
		ImGuiRenderer& operator=(const ImGuiRenderer& other) = delete;
		ImGuiRenderer& operator=(ImGuiRenderer&& other) = delete;

		void Render();

		void AddImGuiComponent(std::unique_ptr<ImGuiComponent>&& component);

	private:

		friend class Singleton<ImGuiRenderer>;
		ImGuiRenderer();

		void StartImGuiRender();
		void EndImGuiRender();

	private:

		std::vector<std::unique_ptr<ImGuiComponent>> m_ImGuiComponents;

	};
}

#endif // !IMGUIRENDERER_H
#endif // _DEBUG || defined DEBUG