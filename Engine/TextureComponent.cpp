#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

TextureComponent::TextureComponent(GameObject* const owner, const std::string& fileName)
	: Component{ owner }
	, m_Texture{ ResourceManager::GetInstance().LoadTexture(fileName) }
{
}

TextureComponent::TextureComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
	, m_Texture{ texture }
{
}

void TextureComponent::Render() const
{
	const glm::vec3& renderPos{ m_Owner->GetTransform().GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_Texture, renderPos.x, renderPos.y);
}