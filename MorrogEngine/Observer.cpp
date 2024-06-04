#include "Observer.h"
#include "Subject.h"

namespace MoE
{
	void Observer::ChangeSubject(Subject* const subject)
	{
		if (m_pSubject) m_pSubject->UnRegisterObserver(this);
		if(subject) subject->RegisterObserver(this);
		m_pSubject = subject;
	}

	Observer::Observer(Subject* const subject)
		: m_pSubject{ subject }
	{
		if(m_pSubject) m_pSubject->RegisterObserver(this);
	}

	Observer::~Observer()
	{
		if(m_pSubject) m_pSubject->UnRegisterObserver(this);
		m_pSubject = nullptr;
	}
}