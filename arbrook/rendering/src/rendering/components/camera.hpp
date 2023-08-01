#pragma once
#include <rsl/math>

namespace rythe::rendering
{
	struct camera
	{
		math::vec3 pos = math::vec3(0, 0, 5.f);
		math::vec3 front = math::vec3(0.0f, 0.0f, -1.0f);

		math::vec3 target = math::vec3(0, 0, 0);
		math::vec3 direction = math::normalize(pos - target);

		math::vec3 g_up = math::vec3(0, 1, 0);
		math::vec3 right = math::normalize(math::cross(g_up, direction));
		math::vec3 up = math::cross(direction, right);
		
		math::mat4 projection/* = math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f)*/;
		math::mat4 view/* = math::lookAt(cam.pos, cam.pos + cam.front, cam.up)*/;
		//math::mat4 projView = projection * view;
	};
}