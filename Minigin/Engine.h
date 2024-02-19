#ifndef MINIGIN_H
#define MINIGIN_H

#include <string>
#include <functional>

class Engine
{
public:
	explicit Engine(const std::string& dataPath);
	~Engine();
	void Run(const std::function<void()>& load);

	Engine(const Engine& other) = delete;
	Engine(Engine&& other) = delete;
	Engine& operator=(const Engine& other) = delete;
	Engine& operator=(Engine&& other) = delete;
};

#endif // !MINIGIN_H