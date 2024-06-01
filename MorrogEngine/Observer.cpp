#include "Observer.h"
#include "Subject.h"

namespace MoE
{
	Observer::Observer(Subject* const subject)
		: m_pSubject{ subject }
	{
		m_pSubject->RegisterObserver(this);
	}

	Observer::~Observer()
	{
		m_pSubject->UnRegisterObserver(this);
	}
}