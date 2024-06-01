
#ifndef IMGUICOMPONENT_H
#define IMGUICOMPONENT_H

#include <imgui_plot.h>

namespace MoE
{
	class ImGuiComponent
	{
	public:

		virtual ~ImGuiComponent() = default;

		ImGuiComponent(const ImGuiComponent& other) = delete;
		ImGuiComponent(ImGuiComponent&& other) noexcept = delete;
		ImGuiComponent& operator=(const ImGuiComponent& other) = delete;
		ImGuiComponent& operator=(ImGuiComponent&& other) = delete;

		virtual void Render() = 0;

	protected:

		ImGuiComponent() = default;

	};
}

#endif // !IMGUICOMPONENT_H