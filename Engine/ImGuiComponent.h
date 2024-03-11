
#ifndef IMGUICOMPONENT_H
#define IMGUICOMPONENT_H

// This is a Blueprint class of a ImGuiComponent

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
	explicit ImGuiComponent() = default;
};

#endif // !IMGUICOMPONENT_H