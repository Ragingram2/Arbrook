#include "rendering/systems/rendertestsystem.hpp"

namespace rythe::rendering
{

	void RenderTestSystem::setup()
	{
		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].addComponent<RenderInterface>();

		glfwSetKeyCallback(m_api->getWindow(), key_callback);

		auto ent = createEntity();
		ent.addComponent<core::transform>();

	}
	void RenderTestSystem::TestDrawArrays()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestDrawArrays");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//shader_handle shader = ShaderCache::getShader("color");
		//vertex verticies[6] =
		//{	//positions						//colors								//tex coors
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//m_api->clear(ClearBit::COLOR);

		//vertexHandle->bufferData(verticies, 6);
		//shader->bind();
		//layout.bind(m_api->getHwnd(), shader);
		//m_api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
	}
	void RenderTestSystem::TestDrawArraysInstanced()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestDrawArraysInstanced");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//shader_handle shader = ShaderCache::getShader("color");
		//vertex verticies[12] =
		//{	//positions									//colors								//tex coors
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } },//3

		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f + count, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//m_api->clear(ClearBit::COLOR);

		//vertexHandle->bufferData(verticies, 12);
		//shader->bind();
		//layout.bind(m_api->getHwnd(), shader);
		//m_api->drawArraysInstanced(PrimitiveType::TRIANGLESLIST, 12, 2, 0, 0);
	}

	void RenderTestSystem::TestDrawIndexed()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestDrawIndexed");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//buffer_handle indexHandle = BufferCache::getBuffer("Index Buffer");
		//shader_handle shader = ShaderCache::getShader("color");
		//vertex verticies[4] =
		//{	//positions						//colors								//tex coors
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//unsigned int indicies[4] =
		//{
		//	1,2,0,3
		//};

		//if (count == 0)
		//{
		//	indexHandle->bufferData(indicies, 4);
		//}

		//m_api->clear(ClearBit::COLOR);

		//vertexHandle->bufferData(verticies, 4);

		//shader->bind();
		//layout.bind(m_api->getHwnd(), shader);
		//m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 4, 0, 0);
	}
	void RenderTestSystem::TestDrawIndexedInstanced()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestDrawInstanced");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//buffer_handle indexHandle = BufferCache::getBuffer("Index Buffer");
		//buffer_handle constantHandle = BufferCache::getBuffer("ConstantBuffer");
		//shader_handle shader = ShaderCache::getShader("color");
		//vertex verticies[4] =
		//{	//positions									//colors								//tex coors
		//	{ { -0.1f, 0.1f, 0.0f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f, 0.0f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3

		//	//{ { -0.1f, 0.1f + count, 0.0f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//4
		//	//{ {	-0.1f, -0.1f + count, 0.0f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//5
		//	//{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//6
		//	//{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//7
		//};

		//unsigned int indicies[4] =
		//{
		//	1,2,0,3/*,
		//	5,6,4,7,*/
		//};

		//int idxCount = sizeof(indicies) / sizeof(unsigned int);
		//int vtxCount = sizeof(verticies) / sizeof(vertex);

		//if (count == 0)
		//{
		//	indexHandle->bufferData(indicies, idxCount);
		//	shader->addBuffer(ShaderType::VERTEX, constantHandle);
		//}

		//m_api->clear(ClearBit::COLOR);
		//vtx_constant constant[] = { { math::vec3(count,0,0),0 }, {math::vec3(0,count,0),0} };
		//shader->setData("ConstantBuffer", constant);
		//vertexHandle->bufferData(verticies, vtxCount);

		//shader->bind();
		//layout.bind(m_api->getHwnd(), shader);
		//m_api->drawIndexedInstanced(PrimitiveType::TRIANGLESTRIP, idxCount, 2, 0, 0, 0);
	}
	void RenderTestSystem::TestSetViewport()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestSetViewport");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//shader_handle shader = ShaderCache::getShader("color");
		//vertex verticies[6] =
		//{	//positions						//colors								//tex coors
		//	{ { -0.1f, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//m_api->setViewport(1, 300, 300, 600, 600, 0, 1);


		//m_api->clear(ClearBit::COLOR);

		//vertexHandle->bufferData(verticies, 6);
		//shader->bind();
		//layout.bind(m_api->getHwnd(), shader);
		//m_api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
	}

	void RenderTestSystem::TestDepthTest()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestDepthTest");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//shader_handle shader = ShaderCache::getShader("color");
		//vertex verticies[12] =
		//{	//positions									//colors								//tex coors
		//	{ { -0.1f + count, 0.1f, 0.0f},			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } },//3

		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f + count, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//m_api->clear(ClearBit::COLOR_DEPTH);

		//vertexHandle->bufferData(verticies, 12);
		//shader->bind();
		//layout.bind(m_api->getHwnd(), shader);
		//m_api->depthTest(true);
		//m_api->depthWrite(true);
		//m_api->setDepthFunction(DepthFuncs::LESS);
		//m_api->updateDepthStencil();
		//m_api->drawArraysInstanced(PrimitiveType::TRIANGLESLIST, 12, 2, 0, 0);
		//m_api->clear(ClearBit::DEPTH);
	}
	void RenderTestSystem::TestStencilTest()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestStencilTest");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//shader_handle colorShader = ShaderCache::getShader("color");
		//shader_handle texShader = ShaderCache::getShader("default");
		//texture_handle texture = TextureCache::getTexture2D("Rythe");
		//vertex verticies[12] =
		//{	//positions									//colors								//tex coors
		//	{ { -0.1f + count, 0.1f, 0.0f},			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } },//3

		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f + count, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//vertexHandle->bufferData(verticies, 12);

		//texture->bind();
		//layout.bind(m_api->getHwnd(), texShader);

		//m_api->depthTest(true);
		//m_api->setStencilOp(Face::FRONT, StencilOp::KEEP, StencilOp::KEEP, StencilOp::REPLACE);
		//m_api->updateDepthStencil();
		//m_api->clear(ClearBit::COLOR_DEPTH_STENCIL);

		//m_api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 1, 0xFF);
		//m_api->setStencilMask(0xFF);
		//m_api->updateDepthStencil();
		//texShader->bind();
		//m_api->drawArraysInstanced(PrimitiveType::TRIANGLESTRIP, 12, 2, 0, 0);

		//m_api->setDepthFunction(DepthFuncs::NOT_EQUAL);
		//m_api->setStencilMask(0x00);
		//m_api->depthTest(false);
		//m_api->updateDepthStencil();
		//colorShader->bind();
		//m_api->drawArraysInstanced(PrimitiveType::TRIANGLESTRIP, 12, 2, 0, 0);

		//m_api->setStencilMask(0xFF);
		//m_api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 1, 0xFF);
		//m_api->depthTest(true);
		//m_api->updateDepthStencil();

		//m_api->clear(ClearBit::STENCIL);
	}

	void RenderTestSystem::TestCreateShader()
	{

	}
	void RenderTestSystem::TestCreateTexture()
	{

	}
	void RenderTestSystem::TestCreateBuffer()
	{

	}
}