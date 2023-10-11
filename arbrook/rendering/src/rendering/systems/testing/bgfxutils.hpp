#pragma once
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <bx/allocator.h>
#include <bx/file.h>

#include <rsl/logging>


namespace rythe::rendering
{
	inline bgfx::ProgramHandle loadShader(std::string name, std::string fsPath, std::string vsPath)
	{
		char* data = new char[2048];
		std::ifstream file;
		size_t fileSize = 0;
		file.open(fsPath, std::ifstream::in | std::ifstream::binary);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			fileSize = file.tellg();
			file.seekg(0, std::ios::beg);
			file.read(data, fileSize);
			file.close();
		}
		const bgfx::Memory* mem = bgfx::copy(data, fileSize + 1);
		mem->data[mem->size - 1] = '\0';
		bgfx::ShaderHandle fhandle = bgfx::createShader(mem);
		if (fhandle.idx == bgfx::kInvalidHandle)
			log::error("Fragment Shader failed compile");
		bgfx::setName(fhandle, "TestFragment");

		file.open(vsPath, std::ifstream::in | std::ifstream::binary);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			fileSize = file.tellg();
			file.seekg(0, std::ios::beg);
			file.read(data, fileSize);
			file.close();
		}

		mem = bgfx::copy(data, fileSize + 1);
		mem->data[mem->size - 1] = '\0';
		bgfx::ShaderHandle vhandle = bgfx::createShader(mem);
		if (vhandle.idx == bgfx::kInvalidHandle)
			log::error("Vertex Shader failed compile");
		bgfx::setName(vhandle, "TestVertex");

		return bgfx::createProgram(vhandle, fhandle, false);
	}

	struct BgfxCallback : public bgfx::CallbackI
	{
		virtual ~BgfxCallback()
		{
		}

		virtual void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
		{
			//BX_UNUSED(_filePath, _line);

			// Something unexpected happened, inform user and bail out.
			log::error("Fatal error {}:{} [{}]: {}", _filePath, _line, _code, _str);

			//abort();
		}

		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
		{
			//log::debug("%s (%d): ", _filePath, _line);
			//log::debug(_format, _argList);
		}

		virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
		{
		}

		virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
		{
		}

		virtual void profilerEnd() override
		{
		}

		virtual uint32_t cacheReadSize(uint64_t _id) override
		{
			return 0;
		}

		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override
		{
			return false;
		}

		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override
		{

		}

		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) override
		{

		}

		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) override
		{

		}

		virtual void captureEnd() override
		{

		}

		virtual void captureFrame(const void* _data, uint32_t /*_size*/) override
		{
		}
	};
}