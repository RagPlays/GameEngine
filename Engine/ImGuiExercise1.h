#ifndef IMGUIEXERCISE1_H
#define IMGUIEXERCISE1_H

#include <imgui_plot.h>
#include <vector>

class ImGuiExercise1 final
{
public:

	ImGuiExercise1();
	~ImGuiExercise1() = default;

	ImGuiExercise1(const ImGuiExercise1& other) = delete;
	ImGuiExercise1(ImGuiExercise1&& other) noexcept = delete;
	ImGuiExercise1& operator=(const ImGuiExercise1& other) = delete;
	ImGuiExercise1& operator=(ImGuiExercise1&& other) = delete;

	void Render();

private:
	void LoadData();

private:
	int m_SampleSize;
	bool m_IsLoading;
	ImGui::PlotConfig m_PlotConfig;
	std::vector<float> m_XData;
	std::vector<float> m_YData;
};

#endif // !IMGUIEXERCISE1_H