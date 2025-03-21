#pragma once
#include <filesystem>
#include <tuple>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <rfl/Variant.hpp>
#include <variant>

#include "core/utils/profiler.hpp"

#include "core/core.hpp"
#include "graphics/rendering.hpp"
#include "input/input.hpp"

#include "sandbox/components/camerasettings.hpp"
template<typename T> struct is_variant : std::false_type {};

template<typename ...Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

template<typename T>
inline constexpr bool is_variant_v = is_variant<T>::value;

namespace rythe::game
{
	using namespace rythe::core::events;
	using namespace rythe::core;
	namespace fs = std::filesystem;
	namespace ast = rythe::core::assets;

	template<typename FieldType>
	bool DrawField(int index, FieldType& field);

	bool DrawLabel(const char* label);

	template<typename memberType>
	void DrawInspector(memberType member, auto field, size_t i);


	template<typename T>
	struct remove_first_type {};

	template<typename T, typename... Ts>
	struct remove_first_type<std::tuple<T, Ts...>>
	{
		typedef std::tuple<Ts...> type;
	};

	struct GUI
	{
		inline static ecs::entity selected;
	};

	class GUISystem : public core::System<GUISystem, core::transform>
	{
	private:
		bool m_readPixel = false;
		bool m_isHoveringWindow = false;
		static gfx::framebuffer* mainFBO;
		static gfx::framebuffer* pickingFBO;
		static ImGuizmo::OPERATION currentGizmoOperation;
		static ImGuizmo::MODE currentGizmoMode;
	public:
		void setup();
		void update();
		void guiRender(core::transform, gfx::camera);

		void drawHeirarchy(ecs::entity_set heirarchy);

		void pushDisabledInspector();
		void popDisabledInspector();

		static void setModel(ast::asset_handle<gfx::model>);
		static void setMaterial(ast::asset_handle<gfx::material>);
		void createEmptyEntity();
		void createCubeEntity();
		void createSphereEntity();
		void drawGizmo(core::transform camTransf, gfx::camera camera, math::ivec2 dims);
		void doClick(key_input<inputmap::method::MOUSE_LEFT>& action);

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		template<size_t... indices>
		void unrollFields(auto func, std::index_sequence<indices...>)
		{
			(func.template operator() < indices > (), ...);
		}

		template<typename memberType>
		void DrawInspector(memberType& member, auto field, size_t idx)
		{
			if constexpr (!rfl::internal::is_skip_v <memberType>)
			{
				if constexpr (is_variant_v<memberType>)
				{
					std::visit([&member, this](auto arg)
						{
							using variantType = std::decay_t<decltype(arg)>;
							const auto view = rfl::to_view(std::get<variantType>(member));
							const auto fields = rfl::fields<variantType>();
							unrollFields([&view, &fields, this]<size_t i>()
							{
								DrawInspector(*rfl::get<i>(view), fields[i], i);
							}, std::make_index_sequence<view.size()>{});
						}, member);
				}
				else
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					DrawLabel(field.name().c_str());
					ImGui::TableSetColumnIndex(1);
					DrawField(idx, member);
				}
			}
		}

		template<typename Component>
		inline void componentEditor(core::ecs::entity ent)
		{
			Component& comp = ent.getComponent<Component>();
			const std::string& compName = ecs::Registry::componentNames[rsl::type_id<Component>()];
			ImGui::PushID(std::format("Entity_{}##{}", compName.c_str(), ent->id).c_str());
			if constexpr (!std::is_same<Component, core::transform>::value)
			{
				ImGui::Checkbox("", &comp.enabled.get());
				ImGui::SameLine();
			}

			bool open = ImGui::TreeNodeEx(compName.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_NoTreePushOnOpen);
			if (!ent->enabled)
				pushDisabledInspector();

			if (open)
			{
				int tableFlags = ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_RowBg;
				const auto view = rfl::to_view(comp);
				const auto fields = rfl::fields<Component>();
				if (ImGui::BeginTable("Component", 2, tableFlags))
				{
					unrollFields([&view, &fields, this]<size_t i>()
					{
						DrawInspector(*rfl::get<i>(view), fields[i], i);
					}, std::make_index_sequence<view.size()>{});
					ImGui::EndTable();
				}
			}

			if (!ent->enabled)
				popDisabledInspector();
			ImGui::PopID();
		}

	};

	template<typename ItemType>
	inline void createAssetDropDown(int index, ItemType current, std::vector<ast::asset_handle<ItemType>> items, void(*func)(ast::asset_handle<ItemType>))
	{
		if (ImGui::BeginCombo(std::format("##{}", index).c_str(), current.name.c_str()))
		{
			for (auto item : items)
			{
				const bool is_selected = (item == current);
				if (ImGui::Selectable(item.getNameC(), is_selected))
				{
					current = *item.m_data;
					func(item);
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}

	inline void DrawWindow(const char* label, ImGuiWindowFlags flags = 0, std::function<void()> func = nullptr)
	{
		bool b = ImGui::Begin(label, 0, flags);
		if (b)
		{
			func();
		}
		ImGui::End();
	}

	inline bool DrawLabel(const char* label)
	{
		ImGui::Text(label);
		return true;
	}

	template<typename FieldType>
	inline bool DrawField([[maybe_unused]] int index, [[maybe_unused]] FieldType& field)
	{
		return true;
	}

	template<>
	inline bool DrawField<math::vec2>(int index, math::vec2& field)
	{
		return ImGui::InputFloat2(std::format("##{}", index).c_str(), field.data.data);
	}

	template<>
	inline bool DrawField<math::vec3>(int index, math::vec3& field)
	{
		return ImGui::InputFloat3(std::format("##{}", index).c_str(), field.data.data);
	}

	template<>
	inline bool DrawField<math::vec4>(int index, math::vec4& field)
	{
		return ImGui::InputFloat4(std::format("##{}", index).c_str(), field.data.data);
	}

	template<>
	inline bool DrawField<math::quat>(int index, math::quat& field)
	{
		math::vec3 rot = field.euler_angles() * math::rad2deg<float>();
		bool b = ImGui::InputFloat3(std::format("##{}", index).c_str(), rot.data.data);
		if (b) field = math::quat::from_euler(rot * math::deg2rad<float>());
		return b;
	}

	template<>
	inline bool DrawField<bool>(int index, bool& field)
	{
		return ImGui::Checkbox(std::format("##{}", index).c_str(), &field);
	}

	template<>
	inline bool DrawField<float>(int index, float& field)
	{
		return ImGui::InputFloat(std::format("##{}", index).c_str(), &field);
	}

	template<>
	inline bool DrawField<double>(int index, double& field)
	{
		return ImGui::InputDouble(std::format("##{}", index).c_str(), &field);
	}

	template<>
	inline bool DrawField<int>(int index, int& field)
	{
		return ImGui::InputInt(std::format("##{}", index).c_str(), &field);
	}

	template<>
	inline bool DrawField<gfx::model>(int index, gfx::model& field)
	{
		createAssetDropDown<gfx::model>(index, field, gfx::ModelCache::getModels(), &GUISystem::setModel);
		return true;
	}

	template<>
	inline bool DrawField<gfx::material>(int index, gfx::material& field)
	{
		createAssetDropDown<gfx::material>(index, field, gfx::MaterialCache::getMaterials(), &GUISystem::setMaterial);
		return true;
	}

	template<>
	inline bool DrawField<std::unordered_map<rsl::id_type, gfx::material>>(int index, std::unordered_map<rsl::id_type, gfx::material>& field)
	{
		//if (ImGui::BeginTable("", 2))
		//{
		//	for (int row = 0; row < field.size(); row++)
		//	{
		//		ImGui::TableNextRow();
		//		for (int column = 0; column < 2; column++)
		//		{
		//			ImGui::TableSetColumnIndex(column);
		//			ImGui::Text("Row %d Column %d", row, column);
		//		}
		//	}
		//	ImGui::EndTable();
		//}
		(void)index;
		(void)field;
		return true;
	}
}