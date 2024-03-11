#ifndef COMMANDS_H
#define COMMANDS_H

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

#endif // !COMMANDS_H
