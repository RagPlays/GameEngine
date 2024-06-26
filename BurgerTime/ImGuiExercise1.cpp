#include <chrono>
#include <thread>
#include "ImGuiExercise1.h"

ImGuiExercise1::ImGuiExercise1()
	: m_SampleSize{ 10 }
	, m_IsLoading{ false }
	, m_PlotConfig{}
	, m_XData{}
	, m_YData{}
{
	m_XData.clear();
	m_YData.clear();

	// setting defaults

	m_PlotConfig.line_thickness = 2.f;
	m_PlotConfig.values.color = ImGui::ColorConvertFloat4ToU32({1.f, 0.5f, 0.f, 1.f }); // orange
	m_PlotConfig.scale.min = 0;
	m_PlotConfig.skip_small_lines = false;
	m_PlotConfig.overlay_text = "int";
	m_PlotConfig.tooltip.format = "x=%.2f, y=%.2f";
	m_PlotConfig.tooltip.show = true;
	m_PlotConfig.frame_size = ImVec2{ 200, 100 };
}

void ImGuiExercise1::Render()
{
	ImGui::Begin("Exercise 1", nullptr);
	{
		ImGui::InputInt("# samples", &m_SampleSize);

		if (!m_IsLoading)
		{
			if (ImGui::Button("Trash the cache"))
			{
				m_IsLoading = true;
			}
		}
		else
		{
			ImGui::Text("Wait for it...");
			LoadData();
			m_IsLoading = false;
		}

		if (!m_IsLoading && m_PlotConfig.values.ys != nullptr)
		{
			ImGui::Plot("plotInt", m_PlotConfig);
		}
	}
	ImGui::End();
}

void ImGuiExercise1::LoadData()
{
	constexpr int arrSize{ 10'000'000 };
	constexpr int maxStepSize{ 1024 };
	constexpr int dataSize{ 11 };

	// Clear all previous data
	m_XData.clear();
	m_YData.clear();

	// Reserve enough data to minimise data copying and setting all values
	m_XData.resize(dataSize);
	m_YData.resize(dataSize);

	// Make TestVec
	std::vector<int> testVec;
	testVec.resize(arrSize);

	// Get XData
	for (int stepsize{ 1 }; stepsize <= maxStepSize; stepsize *= 2)
	{
		m_XData.emplace_back(static_cast<float>(stepsize));
	}

	for (int sampleIdx{}; sampleIdx < m_SampleSize; ++sampleIdx)
	{
		// Create temp vec for data of 1 sample
		std::vector<float> tempDataVec;
		tempDataVec.reserve(dataSize);

		// Get YData
		for (int stepsize{ 1 }; stepsize <= maxStepSize; stepsize *= 2)
		{
			const auto start{ std::chrono::high_resolution_clock::now() };

			for (int i{}; i < arrSize; i += stepsize)
			{
				testVec[i] *= 2;
			}

			const auto end{ std::chrono::high_resolution_clock::now() };
			const auto casttime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
			tempDataVec.emplace_back(static_cast<float>(casttime));
		}

		// Add Data
		for (int idx{}; idx < dataSize; ++idx)
		{
			m_YData[idx] += tempDataVec[idx];
		}
	}

	// Divide By SampleSize
	for (int idx{}; idx < dataSize; ++idx)
	{
		m_YData[idx] /= m_SampleSize;
	}

	// Set Plot Configs / Values
	m_PlotConfig.scale.max = m_YData.front();
	m_PlotConfig.values.count = dataSize;
	m_PlotConfig.values.xs = m_XData.data();
	m_PlotConfig.values.ys = m_YData.data();
}