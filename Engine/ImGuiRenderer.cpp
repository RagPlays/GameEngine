#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include "ImGuiRenderer.h"

void ImGuiRenderer::Render()
{
	// Start
	StartImGuiRender();

	// ...
	m_Exercise1.Render();
	m_Exercise2.Render();
	// ...

	// End
	EndImGuiRender();
}

void ImGuiRenderer::StartImGuiRender()
{
	// ImGui Rendering
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void ImGuiRenderer::EndImGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}