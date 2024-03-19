#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

#include <memory>
#include <vector>
#include "Singleton.h"
#include "ImGuiComponent.h"

class ImGuiRenderer final : public Singleton<ImGuiRenderer>
{
public:

	ImGuiRenderer();
	~ImGuiRenderer() = default;

	ImGuiRenderer(const ImGuiRenderer& other) = delete;
	ImGuiRenderer(ImGuiRenderer&& other) noexcept = delete;
	ImGuiRenderer& operator=(const ImGuiRenderer& other) = delete;
	ImGuiRenderer& operator=(ImGuiRenderer&& other) = delete;

	void Render();

	void AddImGuiComponent(std::unique_ptr<ImGuiComponent> component);

	void SetEnable(bool enable);
	bool IsEnabled() const;

private:

	void StartImGuiRender();
	void EndImGuiRender();

private:

	bool m_Enabled;
	std::vector<std::unique_ptr<ImGuiComponent>> m_ImGuiComponents;
};

#endif // !IMGUIRENDERER_H