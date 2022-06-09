#include "DesStructMgrGui.h"
#include "dcm_config.h"
#include "imgui/imgui.h"

#include <string>


dcm::PagePreviewGui::PagePreviewGui(BaseGui* dad)
	:BaseGui(dad)
{
}

void dcm::PagePreviewGui::Show()
{
	// 显示一个Page预览窗口
	if (ImGui::Begin("Page Preview"))
	{
		if (!pPage)
		{
			ImGui::Text("No Page Set");
			ImGui::End();
			return;
		}

		ImGui::Text("Page Preview");
		ImGui::Separator();
		{
			ImGui::Text("Name : %s", pPage->strPageName.c_str());
			ImGui::Text("Description : %s", pPage->strPageDescription.c_str());
			ImGui::Separator();

			if (pPage->vecColumnInfo.empty())
			{
				ImGui::Text("No Columns.");
			}
			else
			{
				const auto& vecAvailRegion = ImGui::GetContentRegionAvail();
				if (ImGui::BeginTable("Test Table", 4,
					ImGuiTableFlags_Resizable
					| ImGuiTableFlags_BordersV
					| ImGuiTableFlags_ScrollX
					| ImGuiTableFlags_ScrollY
					, { 0.0f, std::max(1.0f, vecAvailRegion.y) }))
				{
					// first three rows demonstrate name, descrition and type.

					ImGui::TableSetupColumn(u8"#");
					ImGui::TableSetupColumn(u8"名称");
					ImGui::TableSetupColumn(u8"描述");
					ImGui::TableSetupColumn(u8"类型");
					ImGui::TableHeadersRow();

					for (int i = 0; i < pPage->vecColumnInfo.size(); ++i)
					{
						const auto& colInfo = pPage->vecColumnInfo[i];

						ImGui::TableNextColumn();
						ImGui::Text(u8"#%d", colInfo.nColID == -1 ? (i + 1) : colInfo.nColID);
						ImGui::TableNextColumn();
						ImGui::Text(u8"%s", colInfo.strColName.c_str());
						ImGui::TableNextColumn();
						ImGui::Text(u8"%s", colInfo.strDescription.c_str());
						ImGui::TableNextColumn();
						ImGui::Text(u8"%s", ToString((dcm::DesType)colInfo.eType));
					}

					ImGui::EndTable();
				}
			}

		}
	}
	ImGui::End();
}

void dcm::PageEditGui::Show()
{
	if (ImGui::Begin("Page Editor"))
	{
		ImGui::InputText("Page Name", curEditPage.strPageName.data(),
			curEditPage.strPageName.capacity(), ImGuiInputTextFlags_CharsNoBlank);

		ImGui::InputText("Page Description", curEditPage.strPageDescription.data(),
			curEditPage.strPageDescription.capacity());

		ImGui::Separator();
		ImGui::BulletText("New Column:");
		pageColumnEditGui.Show();
		ImGui::Separator();

		if (ImGui::Button(nFlag & dcm_config::FLAG_EDITING ? "Edit" : "Add"))
		{

		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			bShouldRender = false;
		}
	}
	ImGui::End();
}

bool dcm::PageEditGui::Init()
{
	pageColumnEditGui.addBtnCallback = [this](const dcm::DesPageColumnInfo& xInfo) -> bool {
		// TODO 
		curEditPage.vecColumnInfo.push_back(xInfo);
		return true;
	};

	pPagePreviewGui = CreateChild<PagePreviewGui>();
	pPagePreviewGui->pPage = &curEditPage;
	return true;
}

void dcm::PageEditGui::OnAddNewPage()
{
	bShouldRender = true;
}

void dcm::PageColumnEditGui::Show()
{
	ImGui::InputText("Column Name", curEditCol.strColName.data(), curEditCol.strColName.capacity());
	ImGui::InputText("Column Description", curEditCol.strDescription.data(), curEditCol.strDescription.capacity());
	ImGui::Text("Type:");
	for (int i = DesType::BEG; i < DesType::DESTYPE_PLUS_ONE; ++i)
	{
		ImGui::RadioButton(ToString((DesType)i), &curEditCol.eType, i);
		ImGui::SameLine();
	}
	ImGui::NewLine();
	if (ImGui::Button("Add Column"))
	{
		if (addBtnCallback(curEditCol))
		{
			Clear(curEditCol);
		}
		else
		{
			// TODO error hint
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{
		Clear(curEditCol);
	}
}

bool dcm::PageColumnEditGui::Init()
{
	SetupLimits(curEditCol);
	return true;
}

void dcm::SetupLimits(DesPage& page)
{
	page.strPageName.reserve(dcm_config::COMMON_NAME_LIMIT);
	page.strPageDescription.reserve(dcm_config::COMMON_DESCRIPTION_LIMIT);
}

void dcm::SetupLimits(DesPageColumnInfo& col)
{
	col.strColName.reserve(dcm_config::COMMON_NAME_LIMIT);
	col.strDescription.reserve(dcm_config::COMMON_DESCRIPTION_LIMIT);
}

void dcm::Clear(DesPageColumnInfo& col)
{
	col.strColName.clear();
	col.strDescription.clear();
	col.eType = DesType::STRING;
}
