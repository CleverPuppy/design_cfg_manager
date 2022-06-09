#include "DesStructMgr.h"

bool dcm::DesStructMgr::Init()
{
	constexpr int PAGE_DESCRIPTION_LIMIT = 150;
	constexpr int PAGE_NAME_LIMIT = 50;

	curEditPage.strPageDescription.reserve(PAGE_DESCRIPTION_LIMIT);
	curEditPage.strPageName.reserve(PAGE_NAME_LIMIT);

	return true;
}

const char* dcm::ToString(DesType eType)
{
	switch (eType)
	{
	case dcm::DesType::STRING:
		return "string";
		break;
	case dcm::DesType::INT32:
		return "int32";
		break;
	case dcm::DesType::INT64:
		return "int64";
		break;
	case dcm::DesType::FLOAT:
		return "float";
		break;
	case dcm::DesType::DOUBLE:
		return "double";
		break;
	default:
		break;
	}
	return "unknow DesType";
}
