#pragma once

enum E_DOUBLE_SETTING
{
	EDS_MOUSE_SENS = 0,
	E_DOUBLE_SETTING_COUNT
};

enum E_BOOL_SETTING
{
	EBS_AUTOSWITCH = 0,
	E_BOOL_SETTING_COUNT
};

class Settings
{
public:
	Settings();
	~Settings();

	double queryDouble(E_DOUBLE_SETTING setting) { return doubleSettings[setting]; }
	bool queryBool(E_BOOL_SETTING setting) { return boolSettings[setting]; }

private:

	double doubleSettings[E_DOUBLE_SETTING_COUNT];
	bool boolSettings[E_BOOL_SETTING_COUNT];
};

