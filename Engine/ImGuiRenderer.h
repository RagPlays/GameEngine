#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

#include "Singleton.h"
#include "ImGuiExercise1.h"
#include "ImGuiExercise2.h"

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

private:
	void StartImGuiRender();
	void EndImGuiRender();

private:
	ImGuiExercise1 m_Exercise1;
	ImGuiExercise2 m_Exercise2;
};

#endif // !IMGUIRENDERER_H