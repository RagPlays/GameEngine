#ifndef LOCATOR_H
#define LOCATOR_H

class ServiceLocator final
{
public:

	ServiceLocator() = default;
	~ServiceLocator() = default;

	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) noexcept = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;


	// Get / Set Audio

private:

#if DEBUG || _DEBUG
	// NullAudioSytem
	// static
#else
	// AudioSystem pointer
	// static
#endif

};

#endif // !LOCATOR_H
