#pragma once

namespace dcm
{
	template<typename T>
	class Singleton
	{
	public:
		using object_type = T;

		static object_type& Instance()
		{
			static object_type obj;

			return obj;
		}
	};

} // namesapce dcm

