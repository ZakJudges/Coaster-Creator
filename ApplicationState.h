#pragma once

#include "../DXFramework/imgui.h"
#include "../DXFramework/imgui_impl_dx11.h"

class ApplicationState
{
public:
	enum class APPLICATIONSTATE
	{
		BUILDING_STATE = 0,
		SIMULATING_STATE
	};

	ApplicationState();
	virtual void Init(void* ptr) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void RenderUI() = 0;
	virtual APPLICATIONSTATE OnExit() = 0;
	bool Exit();
	virtual ~ApplicationState();
	
protected:
	bool exit_;
};