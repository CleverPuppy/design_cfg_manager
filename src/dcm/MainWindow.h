#pragma once

#include "imgui/imgui.h"
#include "imgui/imconfig.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "core.h"

namespace dcm {

// ���ڽ��н�����ʾ
class MainWindow : public BaseGui, public Singleton<MainWindow>
{
public:
	MainWindow() : BaseGui(nullptr) {}
	virtual ~MainWindow() = default;

	virtual void Show() override;
};


}; // namespace dcm
