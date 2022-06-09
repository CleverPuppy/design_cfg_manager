#include "core.h"
#include "imgui.h"
dcm::Program::~Program()
{
	for (auto& [strName, p] : mapAllMgr)
	{
		delete p;
		p = nullptr;
	}
}

bool dcm::Program::Init()
{
	for (auto& [strName, p] : mapAllMgr)
	{
		if (!p->Init())
		{
			return false;
		}
	}

	return true;
}

void dcm::BaseGui::tick()
{
	if (bShouldRender)
	{
		Show();
		for (auto& child : vecChildren)
		{
			child->tick();
		}
	}
}
