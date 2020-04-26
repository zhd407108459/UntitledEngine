#include "Gamepad.h"

// Link the 'Xinput' library - Important!
#pragma comment(lib, "Xinput.lib");

// Default constructor
Gamepad::Gamepad() {}

// Overloaded constructor
Gamepad::Gamepad(int a_iIndex)
{
    // Set gamepad index
    m_iGamepadIndex = a_iIndex - 1;
}

// Return gamepad state
XINPUT_STATE Gamepad::GetState()
{
    // Temporary XINPUT_STATE to return
    XINPUT_STATE GamepadState;

    // Zero memory
    ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

    // Get the state of the gamepad
    XInputGetState(m_iGamepadIndex, &GamepadState);

    // Return the gamepad state
    return GamepadState;
}