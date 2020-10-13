#pragma once

class EditMode
{
public:
	enum class EditModeTag
	{
		MOVE = 0,
		SOFT_CURVE,
		HARD_CURVE,
		FIXED_ENDS,
		MODE_COUNT
	};
	EditMode();
	virtual bool GetP0State() = 0;
	virtual bool GetP1State() = 0;
	virtual bool GetP2State() = 0;
	virtual bool GetP3State() = 0;
	virtual ~EditMode();
};

class EditModeMove : public EditMode
{
public:
	virtual bool GetP0State();
	virtual bool GetP1State();
	virtual bool GetP2State();
	virtual bool GetP3State();
};

class EditModeSoftCurve : public EditMode
{
public:
	virtual bool GetP0State();
	virtual bool GetP1State();
	virtual bool GetP2State();
	virtual bool GetP3State();
};

class EditModeHardCurve : public EditMode
{
public:
	virtual bool GetP0State();
	virtual bool GetP1State();
	virtual bool GetP2State();
	virtual bool GetP3State();
};

class EditModeFixedEnds : public EditMode
{
public:
	virtual bool GetP0State();
	virtual bool GetP1State();
	virtual bool GetP2State();
	virtual bool GetP3State();
};

