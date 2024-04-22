#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <functional>
#include <SDL.h>

class Engine final
{
public:

	explicit Engine(const std::string& dataPath, int width, int height);
	virtual ~Engine();
	Engine(const Engine& other) = delete;
	Engine(Engine&& other) noexcept = delete;
	Engine& operator=(const Engine& other) = delete;
	Engine& operator=(Engine&& other) noexcept = delete;

	void Run();
	void SetGameTitle(const std::string& title);

private:

	const int m_WindowWidth;
	const int m_WindowHeight;
	SDL_Window* m_Window;

};

#endif // !ENGINE_H