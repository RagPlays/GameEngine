#ifndef IMGUIEXERCISE2_H
#define IMGUIEXERCISE2_H

#include "ImGuiComponent.h"

class ImGuiExercise2 final : public MoE::ImGuiComponent
{
public:

	ImGuiExercise2();
	virtual ~ImGuiExercise2() = default;

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
	void LoadDataGameObj3D();
	void LoadDataGameObj3DAlt();

private:

	int m_SampleSize;

	bool m_LoadingGameObj3D;
	bool m_LoadingGameObj3DAlt;

	ImGui::PlotConfig m_PlotConfigGameObj3D;
	ImGui::PlotConfig m_PlotConfigGameObj3DAlt;
	ImGui::PlotConfig m_PlotConfigCombined;

	std::vector<float> m_XData3D;
	std::vector<float> m_YData3D;

	std::vector<float> m_XData3DAlt;
	std::vector<float> m_YData3DAlt;
};

#endif // !IMGUIEXERCISE2_H