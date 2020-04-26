#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")

// XBOX Controller Class Definition
class XboxInput
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;

public:
	XboxInput(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
    
    // Thumbstick functions
    // - Return true if stick is inside deadzone, false if outside
    bool LStick_InDeadzone();
    bool RStick_InDeadzone();

    float LeftStick_X();  // Return X axis of left stick
    float LeftStick_Y();  // Return Y axis of left stick
    float RightStick_X(); // Return X axis of right stick
    float RightStick_Y(); // Return Y axis of right stick
};

#endif