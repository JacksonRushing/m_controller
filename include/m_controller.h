#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <string>



//after this loop exits, controllerId will contain the ID of the first connected controller, or -1 if no controllers are connected. 

int getFirstControllerId();
