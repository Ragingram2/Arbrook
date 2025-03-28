#include "guisystem.hpp"

namespace rythe::game
{
	gfx::framebuffer* GUISystem::mainFBO;
	gfx::framebuffer* GUISystem::pickingFBO;
	ImGuizmo::OPERATION GUISystem::currentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGuizmo::MODE GUISystem::currentGizmoMode = ImGuizmo::WORLD;

	void GUISystem::setup()
	{
		log::info("Initializing GUI system");
		gfx::gui_stage::addGuiRender<GUISystem, &GUISystem::guiRender>(this);

		bindEvent<key_input<inputmap::method::MOUSE_LEFT>, &GUISystem::doClick>();

		glfwSetFramebufferSizeCallback(gfx::WindowProvider::activeWindow->getGlfwWindow(), GUISystem::framebuffer_size_callback);
	}

	void GUISystem::update()
	{

	}

	void GUISystem::guiRender(core::transform camTransf, gfx::camera camera)
	{
		pickingFBO = gfx::Renderer::getCurrentPipeline()->getFramebuffer("PickingBuffer");
		mainFBO = gfx::Renderer::getCurrentPipeline()->getFramebuffer("MainBuffer");
		ImGuiIO& io = ImGui::GetIO();
		m_isHoveringWindow = io.WantCaptureMouse;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


		DrawWindow("Editor", window_flags, [=]()
			{
				ImGui::Text(std::format("FPS:{}", ImGui::GetIO().Framerate).c_str());

				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

				//ImGui::ShowDemoWindow();
				//ImGui::ShowMetricsWindow();

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("New"))
					{
						if (ImGui::MenuItem("Entity"))
						{
							createEmptyEntity();
						}
						ImGui::MenuItem("Material");
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}


				DrawWindow("Heirarchy", 0, [=]()
					{
						ImGui::Separator();
						ImGui::Indent();
						drawHeirarchy(m_filter.m_entities);
						ImGui::Unindent();

						if (ImGui::BeginPopupContextWindow())
						{
							if (ImGui::MenuItem("New Empty"))
								createEmptyEntity();

							if (ImGui::MenuItem("New Cube"))
								createCubeEntity();

							if (ImGui::MenuItem("New Sphere"))
								createSphereEntity();
							ImGui::EndPopup();
						}
					});

				DrawWindow("Inspector", 0, [=]()
					{
						if (GUI::selected == invalid_id)
						{
							return;
						}
						else
						{
							auto ent = GUI::selected;
							ImGui::BeginChild(ent->name.c_str(), ImVec2(ImGui::GetWindowWidth(), 30.0f), true);
							ImGui::Checkbox("##", &ent->enabled);
							ImGui::SameLine();
							ImGui::Text(ent->name.c_str());
							ImGui::EndChild();

							ImGui::Indent();
							if (ent.hasComponent<core::transform>())
								componentEditor<core::transform>(ent);

							if (ent.hasComponent<gfx::mesh_renderer>())
								componentEditor<gfx::mesh_renderer>(ent);

							if (ent.hasComponent<gfx::light>())
								componentEditor<gfx::light>(ent);

							if (ent.hasComponent<examplecomp>())
								componentEditor<examplecomp>(ent);

							if (ent.hasComponent<gfx::camera>())
								componentEditor<gfx::camera>(ent);
							ImGui::Unindent();


							if (ImGui::BeginPopupContextItem("ComponentList"))
							{
								static const char* current = "None";
								for (auto& [id, comp] : ecs::Registry::componentFamilies)
								{
									if (ent.hasComponent(id)) continue;
									const bool is_selected = (ecs::Registry::componentNames[id] == current);
									if (ImGui::Selectable(ecs::Registry::componentNames[id].c_str(), is_selected))
									{
										if (!ent.hasComponent(id))
										{
											current = ecs::Registry::componentNames[id].c_str();
											ent.addComponent(id);
										}
									}
								}
								ImGui::EndPopup();
							}

							if (ImGui::Button("Add Component"))
							{
								ImGui::OpenPopup("ComponentList");
							}
						}
					});

				DrawWindow("Console", 0, [=]()
					{
						auto sink = (spdlog::sinks::ringbuffer_sink_mt*)(log::impl::get().logger->sinks()[1].get());
						auto logs = sink->last_raw(128);
						int lines = logs.size();
						ImVec2 scrolling_child_size = ImVec2(0, 0);
						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 1.0f));
						ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(.01f, .05f));
						ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.6f, 0.6f, 0.6f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(0.7f, 0.7f, 0.7f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0.8f, 0.8f, 0.8f, 1.0f));
						ImGui::BeginChild("scrolling", scrolling_child_size, ImGuiChildFlags_Borders);
						for (int line = 0; line < lines; line++)
						{
							auto log = logs[line];
							auto message = fmt::to_string(log.payload).substr(0, log.payload.size());
							ImGui::Button(message.c_str(), ImVec2(ImGui::GetWindowSize().x, 20));
						}
						ImGui::EndChild();
						ImGui::PopStyleVar(3);
						ImGui::PopStyleColor(3);
					});

				DrawWindow("Asset Browser", 0, [=]() {});

				int flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse;
				DrawWindow("Scene", flags, [=]()
					{

						ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
						const float width = viewportPanelSize.x;
						const float height = viewportPanelSize.y;
						math::vec2 windowPos = math::vec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
						gfx::Renderer::RI->setViewport(1, 0, 0, width, height);
						float imageWidth = math::min(1280.0f, width); /*width > 1280.f ? width : 1280.f;*/
						float imageHeight = math::min(720.0f, height);//height > 720.f ? height : 720.f;
						mainFBO->rescale(imageWidth, imageHeight);
						pickingFBO->rescale(imageWidth, imageHeight);

#if RenderingAPI == RenderingAPI_OGL
						auto mainTex = mainFBO->getAttachment(gfx::AttachmentSlot::COLOR0).m_data->getId();
#else
						mainFBO->getAttachment(gfx::AttachmentSlot::COLOR0)->unbind(gfx::TextureSlot::TEXTURE0);
						auto mainTex = mainFBO->getAttachment(gfx::AttachmentSlot::COLOR0).m_data->getInternalHandle();
#endif
						if (!Input::mouseCaptured && m_readPixel && ImGui::IsWindowHovered() && !ImGuizmo::IsOver())
						{
							auto color = gfx::Renderer::RI->readPixels(*pickingFBO, math::ivec2(input::Input::mousePos.x, input::Input::mousePos.y) - windowPos, math::ivec2(1, 1));
							rsl::id_type id = color.x + (color.y * 256) + (color.z * 256 * 256) + (color.w * 256 * 256 * 256);
							if (id != invalid_id)
								GUI::selected = ecs::entity{ &ecs::Registry::entities[id] };
							else
								GUI::selected = ecs::entity();

							m_readPixel = false;
						}
						else
						{
							m_readPixel = false;
						}

						if (mainTex != 0)
							ImGui::Image(static_cast<ImTextureID>(mainTex), ImVec2(imageWidth, imageHeight), ImVec2(0, -1), ImVec2(-1, 0));
						if (GUI::selected != invalid_id)
							drawGizmo(camTransf, camera, math::ivec2(imageWidth, imageHeight));
					});

				ImGui::PopStyleVar(3);
			});
	}

	void GUISystem::drawHeirarchy(ecs::entity_set heirarchy)
	{
		for (auto ent : heirarchy)
		{
			rsl::uint flags = ImGuiTreeNodeFlags_OpenOnArrow;

			if (ent == GUI::selected)
				flags |= ImGuiTreeNodeFlags_Selected;

			if (ent->children.size() == 0)
				flags |= ImGuiTreeNodeFlags_Leaf;

			if (!ent->enabled)
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 1.0));

			if (ImGui::TreeNodeEx(ent->name.c_str(), flags))
			{
				if (ImGui::IsItemClicked())
				{
					GUI::selected = ent;
				}

				//if (ImGui::IsItemToggledOpen())
				//{
				//	drawHeirarchy(ent->children);
				//}

				ImGui::TreePop();
			}

			if (!ent->enabled)
				ImGui::PopStyleColor();
		}
	}

	void GUISystem::setModel(ast::asset_handle<gfx::model> handle)
	{
		auto& renderer = GUI::selected.getComponent<gfx::mesh_renderer>();
		if (handle != &renderer.model)
		{
			renderer.model = handle;
			renderer.dirty = true;
		}
	}
	void GUISystem::setMaterial(ast::asset_handle<gfx::material> handle)
	{
		auto& renderer = GUI::selected.getComponent<gfx::mesh_renderer>();
		if (handle != &renderer.mainMaterial)
		{
			renderer.mainMaterial = handle;
			renderer.dirty = true;
		}
	}

	void GUISystem::createEmptyEntity()
	{
		auto ent = createEntity();
		ent.addComponent<core::transform>();
	}
	void GUISystem::createCubeEntity()
	{
		auto ent = createEntity();
		ent.addComponent<core::transform>();
		ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = gfx::MaterialCache::getMaterial("cube-material"), .model = gfx::ModelCache::getModel("cube"), .castShadows = false });
	}
	void GUISystem::createSphereEntity()
	{
		auto ent = createEntity();
		ent.addComponent<core::transform>();
		ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = gfx::MaterialCache::getMaterial("sphere-material"), .model = gfx::ModelCache::getModel("sphere"), .castShadows = false });
	}

	void GUISystem::drawGizmo(core::transform camTransf, gfx::camera camera, math::ivec2 dims)
	{
		if (GUI::selected == invalid_id || !GUI::selected.hasComponent<core::transform>()) return;

		auto ent = GUI::selected;
		if (!Input::mouseCaptured)
		{
			if (ImGui::IsKeyPressed(ImGuiKey_1))//1 key
				currentGizmoOperation = ImGuizmo::TRANSLATE;
			if (ImGui::IsKeyPressed(ImGuiKey_2))//2 key
				currentGizmoOperation = ImGuizmo::ROTATE;
			if (ImGui::IsKeyPressed(ImGuiKey_3))//3 key
				currentGizmoOperation = ImGuizmo::SCALE;
		}

		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, dims.x, dims.y);

		core::transform& transf = ent.getComponent<core::transform>();
		float* matrix = transf.to_world().data;
		if (ImGuizmo::Manipulate(camera.view.data, camera.projection.data, currentGizmoOperation, currentGizmoMode, matrix))
		{
			math::vec3 rot;
			ImGuizmo::DecomposeMatrixToComponents(matrix, transf.position.data.data, rot.data.data, transf.scale.data.data);
			transf.rotation = math::quat::from_euler(rot * math::deg2rad<float>());
		}
	}

	void GUISystem::doClick(key_input<inputmap::method::MOUSE_LEFT>& action)
	{
		if (Input::mouseCaptured) return;

		if (action.isPressed() && !Input::isPressed)
		{
			Input::isPressed = true;
			m_readPixel = true;
			return;
		}

		if (action.wasPressed())
		{
			Input::isPressed = false;
			return;
		}
	}
	void GUISystem::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		gfx::Renderer::RI->resize(width, height);
		mainFBO->rescale(width, height);
	}
	void GUISystem::pushDisabledInspector()
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 1.0));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.5, 0.5, 0.5, 1.0));
	}
	void GUISystem::popDisabledInspector()
	{
		ImGui::PopStyleColor(2);
	}
}