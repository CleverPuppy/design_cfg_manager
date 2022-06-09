#pragma once

#include "DesStructMgr.h"
#include <functional>

namespace dcm
{
	class PagePreviewGui;
	class PageEditGui;
	class PageColumnEditGui;

	class PagePreviewGui : public BaseGui
	{
	public:
		PagePreviewGui(BaseGui* dad);
		virtual ~PagePreviewGui() = default;
		virtual void Show() override;

		DesPage* pPage{ nullptr };
	};

	class PageColumnEditGui : public BaseGui
	{
	public:
		PageColumnEditGui(BaseGui* dad) : BaseGui(dad) {}
		virtual ~PageColumnEditGui() = default;

		virtual void Show() override;
		virtual bool Init() override;

		std::function<bool(const DesPageColumnInfo& editCol)> addBtnCallback;

	private:
		DesPageColumnInfo curEditCol;
	};

	class PageEditGui : public BaseGui
	{
	public:
		PageEditGui(BaseGui* dad) : BaseGui(dad) {}
		virtual ~PageEditGui() = default;
		virtual void Show() override;
		virtual bool Init() override;

		void OnAddNewPage();

	private:
		// ========= owns data ========================
		DesPage curEditPage;
		PageColumnEditGui pageColumnEditGui{ this }; // as compond

		std::shared_ptr < PagePreviewGui> pPagePreviewGui; // as child
	};

	// ====================== helper functions ============================
	void SetupLimits(DesPage& page);
	void SetupLimits(DesPageColumnInfo& col);
	void Clear(DesPageColumnInfo& col);
}
