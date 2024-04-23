#include <chrono>
#include "ImGuiExercise2.h"

ImGuiExercise2::ImGuiExercise2()
	: m_SampleSize{ 10 }
	, m_LoadingGameObj3D{ false }
	, m_LoadingGameObj3DAlt{ false }
{
	// setting defaults
	m_PlotConfigGameObj3D.line_thickness = 2.f;
	m_PlotConfigGameObj3D.values.color = ImGui::ColorConvertFloat4ToU32({ 0.f, 1.f, 0.f, 1.0f }); // green
	m_PlotConfigGameObj3D.scale.min = 0;
	m_PlotConfigGameObj3D.skip_small_lines = false;
	m_PlotConfigGameObj3D.overlay_text = "GameObj3D";
	m_PlotConfigGameObj3D.tooltip.format = "x=%.2f, y=%.2f";
	m_PlotConfigGameObj3D.tooltip.show = true;
	m_PlotConfigGameObj3D.frame_size = ImVec2{ 200, 100 };

	m_PlotConfigGameObj3DAlt = m_PlotConfigGameObj3D;
	m_PlotConfigGameObj3DAlt.overlay_text = "GameObj3DAlt";
	m_PlotConfigGameObj3DAlt.values.color = ImGui::ColorConvertFloat4ToU32({ 0.f, 1.f, 1.f, 1.0f }); // lightBlue
}

void ImGuiExercise2::Render()
{
	ImGui::Begin("Exercise 2", nullptr);
	{
		ImGui::InputInt("# samples", &m_SampleSize);

		if (!m_LoadingGameObj3D)
		{
			if (ImGui::Button("Trash the cache with GameObject3D"))
			{
				m_LoadingGameObj3D = true;
			}
		}
		else
		{
			ImGui::Text("Wait for it...");
			LoadDataGameObj3D();
			m_LoadingGameObj3D = false;
		}

		if (!m_LoadingGameObj3DAlt)
		{
			if (ImGui::Button("Trash the cache with GameObject3DAlt"))
			{
				m_LoadingGameObj3DAlt = true;
			}
		}
		else
		{
			ImGui::Text("Wait for it...");
			LoadDataGameObj3DAlt();
			m_LoadingGameObj3DAlt = false;
		}

		if (!m_LoadingGameObj3D && m_PlotConfigGameObj3D.values.ys != nullptr)
		{
			ImGui::Plot("plotGameObj3D", m_PlotConfigGameObj3D);
		}
		if (!m_LoadingGameObj3DAlt && m_PlotConfigGameObj3DAlt.values.ys != nullptr)
		{
			ImGui::Plot("plotGameObj3D", m_PlotConfigGameObj3DAlt);
		}
	}
	ImGui::End();

    // Use conf.values.ys_list for multiple lines
    //ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    //// Draw first plot with multiple sources
    //ImGui::PlotConfig conf;
    //conf.values.xs = x_data;
    //conf.values.count = buf_size;
    //conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
    //conf.values.ys_count = 3;
    //conf.values.colors = colors;
    //conf.scale.min = -1;
    //conf.scale.max = 1;
    //conf.tooltip.show = true;
    //conf.grid_x.show = true;
    //conf.grid_x.size = 128;
    //conf.grid_x.subticks = 4;
    //conf.grid_y.show = true;
    //conf.grid_y.size = 0.5f;
    //conf.grid_y.subticks = 5;
    //conf.selection.show = true;
    //conf.selection.start = &selection_start;
    //conf.selection.length = &selection_length;
    //conf.frame_size = ImVec2(buf_size, 200);
    //ImGui::Plot("plot1", conf);

    //// Draw second plot with the selection
    //// reset previous values
    //conf.values.ys_list = nullptr;
    //conf.selection.show = false;
    //// set new ones
    //conf.values.ys = y_data3;
    //conf.values.offset = selection_start;
    //conf.values.count = selection_length;
    //conf.line_thickness = 2.f;
    //ImGui::Plot("plot2", conf);
}

void ImGuiExercise2::LoadDataGameObj3D()
{
	constexpr int maxStepSize{ 1024 };
	constexpr int dataSize{ 11 };

	// Clear all previous data
	m_XData3D.clear();
	m_YData3D.clear();

	// Reserve enough data to minimise data copying and setting all values
	m_XData3D.resize(dataSize, 1.f);
	m_YData3D.resize(dataSize, 1.f);

	// Make TestVec
	constexpr int arrSize{ 10'000'000 };
	std::vector<GameObject3D> testVec;
	testVec.resize(arrSize);

	// Get XData
	for (int stepsize{ 1 }; stepsize <= maxStepSize; stepsize *= 2)
	{
		m_XData3D.emplace_back(static_cast<float>(stepsize));
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
				testVec[i].ID *= 2;
			}

			const auto end{ std::chrono::high_resolution_clock::now() };
			const auto casttime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
			tempDataVec.emplace_back(static_cast<float>(casttime));
		}

		// Add Data
		for (int idx{}; idx < dataSize; ++idx)
		{
			m_YData3D[idx] += tempDataVec[idx];
		}
	}

	// Divide By SampleSize
	for (int idx{}; idx < dataSize; ++idx)
	{
		m_YData3D[idx] /= m_SampleSize;
	}

	// Set Plot Configs / Values
	m_PlotConfigGameObj3D.scale.max = m_YData3D.front();
	m_PlotConfigGameObj3D.values.count = dataSize;
	m_PlotConfigGameObj3D.values.xs = m_XData3D.data();
	m_PlotConfigGameObj3D.values.ys = m_YData3D.data();
}

void ImGuiExercise2::LoadDataGameObj3DAlt()
{
	constexpr int maxStepSize{ 1024 };
	constexpr int dataSize{ 11 };

	// Clear all previous data
	m_XData3DAlt.clear();
	m_YData3DAlt.clear();

	// Reserve enough data to minimise data copying and setting all values
	m_XData3DAlt.resize(dataSize);
	m_YData3DAlt.resize(dataSize);

	// Make TestVec
	constexpr int arrSize{ 10'000'000 };
	std::vector<GameObject3DAlt> testVec;
	testVec.resize(arrSize);

	// Get XData
	for (int stepsize{ 1 }; stepsize <= maxStepSize; stepsize *= 2)
	{
		m_XData3DAlt.emplace_back(static_cast<float>(stepsize));
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
				testVec[i].ID *= 2;
			}

			const auto end{ std::chrono::high_resolution_clock::now() };
			const auto casttime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
			tempDataVec.emplace_back(static_cast<float>(casttime));
		}

		// Add Data
		for (int idx{}; idx < dataSize; ++idx)
		{
			m_YData3DAlt[idx] += tempDataVec[idx];
		}
	}

	// Divide By SampleSize
	for (int idx{}; idx < dataSize; ++idx)
	{
		m_YData3DAlt[idx] /= m_SampleSize;
	}

	// Set Plot Configs / Values
	m_PlotConfigGameObj3DAlt.scale.max = m_YData3DAlt.front();
	m_PlotConfigGameObj3DAlt.values.count = dataSize;
	m_PlotConfigGameObj3DAlt.values.xs = m_XData3DAlt.data();
	m_PlotConfigGameObj3DAlt.values.ys = m_YData3DAlt.data();
}