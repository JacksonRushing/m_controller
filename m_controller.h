#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <string>



//after this loop exits, controllerId will contain the ID of the first connected controller, or -1 if no controllers are connected. 

int getFirstControllerId()
{
	int controllerId = -1;
	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE controllerState;
		std::memset(&controllerState, 0, sizeof(controllerState));

		if (XInputGetState(i, &controllerState) == ERROR_SUCCESS)
		{
			controllerId = i;
		}
		return controllerId;
	}
}