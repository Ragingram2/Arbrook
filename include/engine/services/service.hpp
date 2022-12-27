#pragma once
#include <memory>
#include <iostream>

namespace rythe::core
{
	class Service
	{
	public:
		Service() = default;
		~Service() = default;

		void initialize();
		void update();
		void kill();
	};
}