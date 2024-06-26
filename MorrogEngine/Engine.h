#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <functional>

struct SDL_Window;

namespace MoE
{
	class Engine final
	{
	public:

		explicit Engine(const std::string& dataPath, unsigned int width, unsigned int height);
		virtual ~Engine();
		Engine(const Engine& other) = delete;
		Engine(Engine&& other) noexcept = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) noexcept = delete;

		void Run();

		void SetGameTitle(const std::string& title);
		void SetWindowSize(unsigned int width, unsigned int height);
		void SetWindowPosition(int x, int y);
		void SetShowCursor(bool showCursor);

	private:

		static void PrintSDLVersion();

	private:

		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;
		SDL_Window* m_pWindow;

	};
}

#endif // !ENGINE_H