#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "rendering/data/meshhandle.hpp"
#include "rendering/data/modelhandle.hpp"

namespace rythe::rendering
{
	class ModelCache
	{
	private:
		static std::unordered_map<std::string, std::unique_ptr<model>> m_models;
	public:
		//needs import settings
		static model_handle createModel(const std::string& name, mesh_handle handle);
		static model_handle getModel(const std::string& name);
		static void deleteModel(const std::string& name);
	};
}