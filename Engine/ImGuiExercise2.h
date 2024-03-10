#ifndef IMGUIEXERCISE2_H
#define IMGUIEXERCISE2_H

#include <imgui_plot.h>

class ImGuiExercise2 final
{
public:

	ImGuiExercise2();
	~ImGuiExercise2() = default;

	ImGuiExercise2(const ImGuiExercise2& other) = delete;
	ImGuiExercise2(ImGuiExercise2&& other) noexcept = delete;
	ImGuiExercise2& operator=(const ImGuiExercise2& other) = delete;
	ImGuiExercise2& operator=(ImGuiExercise2&& other) = delete;

	void Render();

private:

	struct Transform
	{
		float matrix[16]
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		Transform* transform;
		int ID;
	};

private:

	int m_SampleSize;
	bool m_GraphOneLoading;
	bool m_GraphTwoLoading;

	ImGui::PlotConfig m_PlotOneConfig;
	ImGui::PlotConfig m_PlotTwoConfig;


};

#endif // !IMGUIEXERCISE2_H