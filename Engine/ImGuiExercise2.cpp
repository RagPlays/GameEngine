#include "ImGuiExercise2.h"

ImGuiExercise2::ImGuiExercise2()
	: m_SampleSize{ 10 }
	, m_GraphOneLoading{ false }
	, m_GraphTwoLoading{ false }
{
	// setting defaults
	//m_PlotConfig 
}

void ImGuiExercise2::Render()
{
	ImGui::Begin("Exercise 2", nullptr);
	{
		ImGui::InputInt("# samples", &m_SampleSize);
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
