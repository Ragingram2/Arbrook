#include "rendering/systems/rendersystem.hpp"
#include <GLFW/glfw3.h>
namespace rythe::rendering
{
	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;

		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].addComponent<RenderInterface>();

		m_api->initialize(math::ivec2(600, 600), "Arbrook");

		if (!m_api->getWindow())
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}

		testEnt = createEntity("Test");
		testEnt.addComponent<core::transform>();
		auto& renderer = testEnt.addComponent<sprite_renderer>();
		auto& layout = renderer.layout;
		auto vertexHandle = BufferCache::createBuffer<vertex>(*m_api, "Vertex Buffer", TargetType::VERTEX_BUFFER);
		auto indexHandle = BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", TargetType::INDEX_BUFFER);
		auto shader = ShaderCache::createShader(*m_api, "color", "resources/shaders/color.shader");
		layout.addBuffer(indexHandle);
		layout.addBuffer(vertexHandle);
		layout.bind(m_api->getHwnd(), shader);
		layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, sizeof(vertex), 0, InputClass::PER_VERTEX);
		layout.setAttributePtr("COLOR", 1, FormatType::RGBA32F, sizeof(vertex), 3.0f * sizeof(float), InputClass::PER_VERTEX);
		layout.setAttributePtr("TEXCOORD", 2, FormatType::RG32F, sizeof(vertex), 7.0f * sizeof(float), InputClass::PER_VERTEX);
		layout.submitAttributes();
	}

	void Renderer::update()
	{
		m_api->makeCurrent();

		m_api->setSwapInterval(1);

		if (m_api->shouldWindowClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		//TestDrawArrays();
		//TestDrawArraysInstanced();
		//TestDrawIndexed();
		TestDrawIndexedInstanced();

		//auto colorShader = ShaderCache::getShader("color");
		//m_api->clear(ClearBit::COLOR_DEPTH_STENCIL);
		//m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);

		//for (auto& ent : m_filter)
		//{
		//	auto& renderComp = ent.getComponent<sprite_renderer>();
		//	auto& transf = ent.getComponent<core::transform>();
		//	auto& example = ent.getComponent<core::exampleComp>();

		//	auto& shader = renderComp.shader;
		//	auto& texture = renderComp.texture;

		//	shader->bind();
		//	texture->bind();
		//	renderComp.layout.bind(m_api->getHwnd(), shader);

		//	vtx_constant constant[] = { { transf.position,example.time } };
		//	shader->setData("ConstantBuffer", constant);
		//	colorShader->setData("ConstantBuffer", constant);

		//	m_api->setDepthFunction(DepthFuncs::LESS_EQUAL);
		//	m_api->enableStencilTest();
		//	m_api->setStencilOp(Face::FRONT_BACK, StencilOp::KEEP, StencilOp::KEEP, StencilOp::REPLACE);

		//	m_api->setStencilFunction(Face::FRONT_BACK, DepthFuncs::ALWAYS, 1, 0xFF);
		//	m_api->enableDepthWrite();
		//	m_api->updateDepthStencil();
		//	m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 4, 0, 0);

		//	m_api->setStencilFunction(Face::FRONT_BACK, DepthFuncs::NOT_EQUAL, 1, 0xFF);
		//	m_api->disableDepthWrite();
		//	m_api->disableDepthTest();
		//	m_api->updateDepthStencil();
		//	colorShader->bind();
		//	m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 4, 0, 0);

		//	m_api->enableDepthWrite();
		//	m_api->setStencilFunction(Face::FRONT_BACK, DepthFuncs::ALWAYS, 1, 0xFF);
		//	m_api->enableDepthTest();
		//	m_api->updateDepthStencil();

		//	m_api->clear(ClearBit::STENCIL);
		//}


		m_api->swapBuffers();
		m_api->pollEvents();

		m_api->checkError();

		count += .01f;
		if (count > 1)
		{
			count = -1;
		}
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
		m_api->close();
	}


	void Renderer::TestDrawArrays()
	{
		auto& renderer = testEnt.getComponent<sprite_renderer>();
		auto& layout = renderer.layout;
		buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		shader_handle shader = ShaderCache::getShader("color");
		vertex verticies[6] =
		{	//positions						//colors								//tex coors
			{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
			{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		};

		m_api->clear(ClearBit::COLOR);

		vertexHandle->bufferData(verticies, 6);
		shader->bind();
		layout.bind(m_api->getHwnd(), shader);
		m_api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
	}
	void Renderer::TestDrawArraysInstanced()
	{
		auto& renderer = testEnt.getComponent<sprite_renderer>();
		auto& layout = renderer.layout;
		buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		shader_handle shader = ShaderCache::getShader("color");
		vertex verticies[12] =
		{	//positions									//colors								//tex coors
			{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
			{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } },//3

			{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ {	-0.1f,-0.1f + count, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
			{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		};

		m_api->clear(ClearBit::COLOR);

		vertexHandle->bufferData(verticies, 12);
		shader->bind();
		layout.bind(m_api->getHwnd(), shader);
		m_api->drawArraysInstanced(PrimitiveType::TRIANGLESLIST, 12, 2, 0, 0);
	}

	void Renderer::TestDrawIndexed()
	{
		auto& renderer = testEnt.getComponent<sprite_renderer>();
		auto& layout = renderer.layout;
		buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		buffer_handle indexHandle = BufferCache::getBuffer("Index Buffer");
		shader_handle shader = ShaderCache::getShader("color");
		vertex verticies[4] =
		{	//positions						//colors								//tex coors
			{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
			{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		};

		unsigned int indicies[4] =
		{
			1,2,0,3
		};

		if (count == 0)
		{
			indexHandle->bufferData(indicies, 4);
		}

		m_api->clear(ClearBit::COLOR);

		vertexHandle->bufferData(verticies, 4);

		shader->bind();
		layout.bind(m_api->getHwnd(), shader);
		m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 4, 0, 0);
	}
	void Renderer::TestDrawIndexedInstanced()
	{
		auto& renderer = testEnt.getComponent<sprite_renderer>();
		auto& layout = renderer.layout;
		buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		buffer_handle indexHandle = BufferCache::getBuffer("Index Buffer");
		shader_handle shader = ShaderCache::getShader("color");
		vertex verticies[8] =
		{	//positions									//colors								//tex coors
			{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
			{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } },//3

			{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//4
			{ {	-0.1f, -0.1f + count, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//5
			{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//6
			{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//7
		};

		unsigned int indicies[8] =
		{
			1,2,0,3,
			5,6,4,7,
		};

		int idxCount = sizeof(indicies) / sizeof(unsigned int);
		int vtxCount = sizeof(verticies) / sizeof(vertex);

		if (count == 0)
		{
			indexHandle->bufferData(indicies, idxCount);
		}

		m_api->clear(ClearBit::COLOR);

		vertexHandle->bufferData(verticies, vtxCount);

		shader->bind();
		layout.bind(m_api->getHwnd(), shader);
		m_api->drawIndexedInstanced(PrimitiveType::TRIANGLESTRIP, idxCount, 2, 0, 0, 0);
	}
	void Renderer::TestSetViewport()
	{

	}
	void Renderer::TestDepthTest()
	{

	}
	void Renderer::TestStencilTest()
	{

	}

	void Renderer::TestCreateShader()
	{

	}
	void Renderer::TestCreateTexture()
	{

	}
	void Renderer::TestCreateBuffer()
	{

	}
}