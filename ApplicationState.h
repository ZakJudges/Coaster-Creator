#pragma once

#include "../DXFramework/imgui.h"
#include "../DXFramework/imgui_impl_dx11.h"

#include "LineController.h"

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
	virtual void OnEnter() = 0;
	virtual APPLICATIONSTATE OnExit() = 0;
	bool Exit();
	bool ApplicationRunning();
	bool GetWireframeState();
	void SetWireframeState(bool state);
	virtual void SetLineController(LineController* line_controller);
	virtual LineController* GetLineController();

	virtual void SetCameraLookAt(float x, float y, float z);
	bool GetFocus();

	virtual void OnWPress();
	virtual void OnSPress();
	virtual void OnDPress();
	virtual void OnAPress();
	virtual void OnEPress();
	virtual void OnQPress();

	virtual ~ApplicationState();
	
protected:
	bool exit_;
	bool application_running_;
	bool wireframe_state_;
	bool in_focus_;

	LineController* line_controller_;

};