#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:

	Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;

	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;
};

#endif // !COMMAND_H