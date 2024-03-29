#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include "ImGuiRenderer.h"

ImGuiRenderer::ImGuiRenderer()
	: m_Enabled{ false }
{
}

void ImGuiRenderer::Render()
{
	// Check
	if (!m_Enabled) return;

	// Start
	StartImGuiRender();

	// ...
	for (auto& imGuiComp : m_ImGuiComponents)
	{
		imGuiComp->Render();
	}
	// ...

	// End
	EndImGuiRender();
}

void ImGuiRenderer::AddImGuiComponent(std::unique_ptr<ImGuiComponent> component)
{
	m_ImGuiComponents.emplace_back(std::move(component));
}

void ImGuiRenderer::SetEnable(bool enable)
{
	m_Enabled = enable;
}

bool ImGuiRenderer::IsEnabled() const
{
	return m_Enabled;
}

void ImGuiRenderer::StartImGuiRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void ImGuiRenderer::EndImGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}