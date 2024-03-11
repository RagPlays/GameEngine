#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

class Controller final
{
public:
	Controller() = default;
	~Controller() = default;

	Controller(const Controller& other) = delete;
	Controller(Controller&& other) noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) noexcept = delete;

private:

};

#endif // !CONTROLLERINPUT_H