#include "stdafx.h"
#include "Settings.h"


Settings::Settings()
{
	doubleSettings[EDS_MOUSE_SENS] = 100.0f;
	
	boolSettings[EBS_AUTOSWITCH] = true;
}


Settings::~Settings()
{
}
