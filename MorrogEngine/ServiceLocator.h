#ifndef LOCATOR_H
#define LOCATOR_H

#include <memory>

namespace MoE
{
	class SoundSystem;

	class ServiceLocator final
	{
	public:

		~ServiceLocator();

		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) noexcept = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;

		// Get / Set Audio
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

	private:

		ServiceLocator() = default;

	private:

		static std::unique_ptr<SoundSystem> s_SoundSystemInstance;

	};
}

#endif // !LOCATOR_H
