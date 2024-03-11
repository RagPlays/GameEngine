#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

#include <memory>
#include <vector>
#include "Singleton.h"
#include "ImGuiComponent.h"

class ImGuiRenderer final : public Singleton<ImGuiRenderer>
{
public:

	ImGuiRenderer() = default;
	~ImGuiRenderer() = default;

	ImGuiRenderer(const ImGuiRenderer& other) = delete;
	ImGuiRenderer(ImGuiRenderer&& other) noexcept = delete;
	ImGuiRenderer& operator=(const ImGuiRenderer& other) = delete;
	ImGuiRenderer& operator=(ImGuiRenderer&& other) = delete;

	void Render();

	void AddImGuiComponent(std::unique_ptr<ImGuiComponent> component);

private:
	void StartImGuiRender();
	void EndImGuiRender();

private:

	std::vector<std::unique_ptr<ImGuiComponent>> m_ImGuiComponents;
};

#endif // !IMGUIRENDERER_H