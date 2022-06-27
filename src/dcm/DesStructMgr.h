#pragma once
#include<vector>
#include<string>
#include<variant>
#include<unordered_map>

#include "core.h"

namespace dcm
{
	enum DesType
	{
		BEG,
		STRING = BEG,
		INT32,
		INT64,
		FLOAT,
		DOUBLE,
		DESTYPE_PLUS_ONE
	};

	const char* ToString(DesType eType);

	// ���ñ�ṹ
	struct DesPageCellData
	{
		std::variant<std::string, int32_t, int64_t, float, double> data; // ��Ҫ�ϸ���DesTypeö��ֵ˳��
	};

	// �������Ϣ
	struct DesPageColumnInfo
	{
		std::string strColName;
		std::string strDescription;
		int eType{ DesType::STRING };
		int nColID{ -1 };
	};

	// �������Ϣ
	struct DesRowData
	{
		int nRowID{ -1 };
		std::vector<DesPageCellData> rowData;
	};

	struct DesPage
	{
		std::string strPageName;
		std::string strPageDescription;
		std::vector<DesPageColumnInfo> vecColumnInfo;
		std::vector<DesRowData> vecRowData;
	};

	class DesStructMgr : public BaseMgr
	{
	public:
		DesStructMgr() = default;
		virtual ~DesStructMgr() = default;

		virtual bool Init() override;

		std::unordered_map<std::string, DesPage> mapPage;

		// ======================= imgui ==================
		bool bEditing{ false };
		bool bAddingColumn{ false };

		DesPage curEditPage;
		DesPageColumnInfo currentEditingColumn;
	};

} // namespace dcm

