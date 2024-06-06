#include <iostream>

#include "ListSelection.h"
#include "Button.h"
#include "GameObject.h"
#include "GameManager.h"
#include "TextureRenderer.h"
#include "GameManager.h"

ListSelection::ListSelection(MoE::GameObject* const owner, bool looping, int offset, std::shared_ptr<MoE::Texture2D> markerTexture, int startButtonPosY)
	: Component{ owner }
    , m_pMarkerRenderer{}
    , m_MarkerOffset{ offset }
    , m_StartButtonYPos{ startButtonPosY }
	, m_Looping{ looping }
	, m_SelectedIndex{}
{
    if (markerTexture)
    {
        std::unique_ptr<MoE::GameObject> marker{ std::make_unique<MoE::GameObject>() };
        auto markerRenderer{ std::make_unique<MoE::TextureRenderer>(marker.get(), markerTexture) };
        markerRenderer->ScaleTextureDimensions(static_cast<float>(GameManager::Get().GetGameScale()));
        m_pMarkerRenderer = markerRenderer.get();
        marker->AddComponent<MoE::TextureRenderer>(std::move(markerRenderer));
        owner->AddChild(std::move(marker));
    }
}

ListSelection::~ListSelection() = default;

void ListSelection::SceneStart()
{
    const glm::ivec2& windowSize{ GameManager::Get().GetWindowSize() };
    //const glm::ivec2& markerDim{ m_pMarkerRenderer->GetTextureDimentions() };

    for (size_t buttonIdx{}; buttonIdx < m_pButtons.size(); ++buttonIdx)
    {
        MoE::GameObject* const pButtonObj{ m_pButtons[buttonIdx]->GetOwner() };
        if (MoE::TextureRenderer* const renderComp{ pButtonObj->GetComponent<MoE::TextureRenderer>() }; renderComp)
        {
            const glm::ivec2& buttonDim{ renderComp->GetTextureDimentions() };

            glm::ivec2 pos
            {
                (windowSize.x / 2) - ((buttonDim.x /*+ markerDim.x + m_MarkerOffset*/) / 2) /*+ (markerDim.x + m_MarkerOffset)*/,
                m_StartButtonYPos + ((m_MarkerOffset + buttonDim.y) * static_cast<int>(buttonIdx))
            };

            pButtonObj->SetWorldPosition(static_cast<glm::vec2>(pos));
        }
    }
    UpdateMarker();
}

void ListSelection::AddButton(std::unique_ptr<MoE::GameObject>&& buttonObj)
{
    if (Button* buttonComp{ buttonObj->GetComponent<Button>() }; buttonComp)
    {
        GetOwner()->AddChild(std::move(buttonObj));
        m_pButtons.emplace_back(buttonComp);
        if (m_pButtons.size() == 1) m_pButtons[0]->Select();
    }
    else std::cerr << "ERROR::LISTSELECTION::GAMEOBJECT_HAS_NO_BUTTONCOMPONENT\n";
}

void ListSelection::Press()
{
	if (m_pButtons.empty()) return;
	if (m_SelectedIndex < m_pButtons.size())
	{
		m_pButtons[m_SelectedIndex]->Press();
	}
}

void ListSelection::Move(bool up)
{
    const int previousSelected{ m_SelectedIndex };
    const int nrButtons{ static_cast<int>(m_pButtons.size()) };

    if (up) m_SelectedIndex = m_Looping ? (m_SelectedIndex - 1 + nrButtons) % nrButtons : std::max(0, m_SelectedIndex - 1);
    else m_SelectedIndex = m_Looping ? (m_SelectedIndex + 1) % nrButtons : std::min(nrButtons - 1, m_SelectedIndex + 1);

    if (previousSelected != m_SelectedIndex)
    {
        if (previousSelected < nrButtons)
        {
            m_pButtons[previousSelected]->UnSelect();
        }
        if (m_SelectedIndex < nrButtons)
        {
            m_pButtons[m_SelectedIndex]->Select();
        }
        UpdateMarker();
    }
}

void ListSelection::ManualSelect(uint8_t idx)
{
    if (static_cast<size_t>(idx) < m_pButtons.size())
    {
        if (static_cast<int>(idx) != m_SelectedIndex)
        {
            m_pButtons[m_SelectedIndex]->UnSelect();
            m_pButtons[idx]->Select();
            m_SelectedIndex = idx;
            UpdateMarker();
        }
    }
    else std::cerr << "ERROR::LISTSELECTION::MANUAL_BUTTON_SELECTION_IDX_OUT_OF_RANGE\n";
}

void ListSelection::SetLooping(bool looping)
{
	m_Looping = looping;
}

void ListSelection::UpdateMarker()
{
    if (m_pMarkerRenderer)
    {
        Button* const currentButton{ m_pButtons[m_SelectedIndex] };
        if (MoE::TextureRenderer* const renderComp{ currentButton->GetOwner()->GetComponent<MoE::TextureRenderer>()}; renderComp)
        {
            const glm::ivec2& markerDim{ m_pMarkerRenderer->GetTextureDimentions() };
            const glm::ivec2& buttonDim{ renderComp->GetTextureDimentions() };
            const glm::vec2& buttonPos{ currentButton->GetOwner()->GetWorldPosition() };

            const glm::ivec2 markerPos
            {
                buttonPos.x - markerDim.x - m_MarkerOffset,
                buttonPos.y + (buttonDim.y - markerDim.y) / 2
            };

            m_pMarkerRenderer->GetOwner()->SetWorldPosition(static_cast<glm::vec2>(markerPos));
        }
    }
}