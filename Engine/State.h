#ifndef STATE_H
#define STATE_H

class State
{
public:

	virtual ~State() = default;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	// ????

	virtual void Update() = 0;

private:

	State() = default;

};

#endif // !STATE_H