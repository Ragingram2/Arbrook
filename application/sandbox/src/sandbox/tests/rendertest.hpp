#pragma once
#include <string>

#include <rsl/math>

#include "rendering/interface/definitions.hpp"
#include "rendering/rendering.hpp"



namespace rythe::testing
{
	enum APIType
	{
		Arbrook = 0,
		BGFX = 1,
		Native = 2
	};


	inline std::string getAPIName(APIType type)
	{
		switch (type)
		{
		case APIType::Arbrook:
			return "Arbrook";
			break;
		case APIType::BGFX:
			return  "BGFX";
			break;
		case APIType::Native:
			return  "Native";
			break;
		}
		return "";
	}

	struct rendering_test
	{
		bool initialized = false;
		std::string name;
		virtual ~rendering_test() = default;
		virtual void setup(gfx::camera& cam, core::transform& camTransf) = 0;
		virtual void update(gfx::camera& cam, core::transform& camTransf) = 0;
		virtual void destroy() = 0;
	};
}

namespace std {
	template <> struct hash<rythe::testing::APIType> {
		size_t operator() (const rythe::testing::APIType& t) const { return size_t(t); }
	};
}

