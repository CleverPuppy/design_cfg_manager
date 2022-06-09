#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<typeinfo>
#include<memory>
#include "utils.h"

namespace dcm
{
	class BaseMgr;
	class Program;
	class BaseGui;

	class BaseMgr
	{
	public:
		virtual bool Init() { return true; };
		virtual void tick() {}
	};

	class Program : 
		public BaseMgr,
		public Singleton<Program>
	{
	public:
		Program() = default;
		virtual ~Program();
		virtual bool Init() override;

		template<typename T>
			bool Register(const std::string& strName)
		{
			if (mapAllMgr.find(strName) == mapAllMgr.end())
			{
				T* pMgr = new T();
				mapAllMgr.insert({ strName, pMgr });
				CheckIfCanTick(pMgr);
				return true;
			}

			return false;
		}

		template<typename T>
			bool Register()
		{
			const std::string& strTypeInfo = typeid(T).name();
			if (mapAllMgr.find(strTypeInfo) == mapAllMgr.end())
			{
				T* pMgr = new T();
				mapAllMgr.insert({ strTypeInfo, pMgr });
				CheckIfCanTick(pMgr);
				return true;
			}

			return false;
		}

			template<typename T, bool bAbort = true>
			T* FindMgr()
			{
				for (auto& [strName, pMgr] : mapAllMgr)
				{
					T* result = dynamic_cast<T*>(pMgr);
					if (result)
					{
						return result;
					}
				}

				if constexpr (bAbort)
				{
					std::abort();
				}
				return nullptr;
			}

			template<typename T>
			void CheckIfCanTick(T* pMgr)
			{
				vecTickableMgr.push_back(pMgr);
			}

	private:
		std::unordered_map<std::string, BaseMgr*> mapAllMgr;
		std::vector<BaseMgr*> vecTickableMgr;
	};

	class  BaseGui : public BaseMgr
	{
	public:
		explicit BaseGui(BaseGui* pParent) : dad(pParent) {}
		~BaseGui() = default;

		virtual void tick() override;
		virtual void Show() = 0;

		template<typename T>
		std::shared_ptr<T> CreateChild();

		// ========== public data =============
		int nFlag = 0;
		bool bShouldRender = true;

	protected:
		BaseGui* dad = nullptr;
		std::vector<std::shared_ptr<BaseGui>> vecChildren;
	};

	template<typename T>
	inline std::shared_ptr<T> BaseGui::CreateChild()
	{
		auto pPtr = std::make_shared<T>(this);
		pPtr->Init();
		vecChildren.emplace_back(pPtr);
		return pPtr;
	}

}// namespace dcm
