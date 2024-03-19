//#ifndef CONTROLLERINPUT_H
//#define CONTROLLERINPUT_H
//
//#include <memory>
//#include <unordered_map>
//#include "InputStructs.h"
//#include "Command.h"
//
//class XinputController final
//{
//public:
//
//	XinputController();
//	~XinputController() = default;
//
//	XinputController(const XinputController& other) = delete;
//	XinputController(XinputController&& other) noexcept = delete;
//	XinputController& operator=(const XinputController& other) = delete;
//	XinputController& operator=(XinputController&& other) noexcept = delete;
//
//	void Update();
//	void ProcessInput();
//
//	void AddBind(const XinputControllerInput& input, std::unique_ptr<Command> command);
//
//private:
//
//	bool WasPressedThisFrame(unsigned int button) const;
//	bool WasReleasedThisFrame(unsigned int button) const;
//	bool IsPressed(unsigned int button) const;
//
//private:
//
//	XINPUT_STATE m_CurrentState;
//	XINPUT_STATE m_PreviousState;
//	unsigned int m_ControllerIdx;
//	unsigned int m_ButtonsChangedThisFrame;
//	unsigned int m_ButtonsPressedthisFrame;
//	unsigned int m_ButtonsReleasedthisFrame;
//
//	std::unordered_map<XinputControllerInput, std::unique_ptr<Command>, XinputµControllerInputHash, XinputControllerInputEqual> m_Commands;
//};
//
//#endif // !CONTROLLERINPUT_H