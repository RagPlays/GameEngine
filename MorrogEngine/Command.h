#ifndef COMMAND_H
#define COMMAND_H

namespace MoE
{
	class Command
	{
	public:

		Command() = default;
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) noexcept = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) noexcept = delete;

		virtual void Execute() = 0;

	};
}

#endif // !COMMAND_H