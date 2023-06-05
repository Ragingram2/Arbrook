#pragma once
#include <GL/glew.h>

#include "core/core.hpp"
#include "rendering/rendering.hpp"

namespace rythe::core
{
	//#define IX3(x, y, z) ((x) + (y) * N + (z) * N * N)
#define IX(x, y) ((x) + (y) * N)

	struct FluidCube
	{
		int size;
		float deltaTime;
		float diffusion;
		float viscosity;

		std::vector<float> source;
		std::vector<float> density;

		std::vector<float> Velx;
		std::vector<float> Vely;

		std::vector<float> Velx0;
		std::vector<float> Vely0;

		FluidCube() = default;
		FluidCube(int s, int diff, int visc, float dt)
		{
			size = s;
			deltaTime = dt;
			diffusion = diff;
			viscosity = visc;

			auto N = s * s * s;
			source.resize(N);
			density.resize(N);

			Velx.resize(N);
			Vely.resize(N);

			Velx0.resize(N);
			Vely0.resize(N);
		}
	};

	class TestSystem : public System<transform>
	{
	public:
		gfx::RenderInterface* m_api;
		FluidCube cube;

		TestSystem() = default;
		virtual ~TestSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		void step(int iter, float dt)
		{
			diffuse(1, cube.Velx0.data(), cube.Velx.data(), cube.viscosity, dt, iter);
			diffuse(2, cube.Vely0.data(), cube.Vely.data(), cube.viscosity, dt, iter);
			//diffuse();

			project(cube.Velx0.data(), cube.Vely0.data(), cube.Velx.data(), cube.Vely.data(), iter);

			advect(1, cube.Velx.data(), cube.Velx0.data(), cube.Velx0.data(), cube.Vely0.data(), dt);
			advect(2, cube.Vely.data(), cube.Vely0.data(), cube.Velx0.data(), cube.Vely0.data(), dt);
			//advect();

			project(cube.Velx.data(), cube.Vely.data(), cube.Velx0.data(), cube.Vely0.data(), iter);

			diffuse(0, cube.source.data(), cube.density.data(), cube.diffusion, dt, iter);
			advect(0, cube.density.data(), cube.source.data(), cube.Velx.data(), cube.Vely.data(), dt);
		}

		void diffuse(int b, float* x, float* x0, float diff, float dt, int iter)
		{
			int N = cube.size;
			float a = dt * diff * (N - 2) * (N - 2);
			linearSolve(b, x, x0, a, 1 + 6 * a, iter);
		}

		void advect(int b, float* d, float* d0, float* velX, float* velY, float dt)
		{
			int N = cube.size;

			float i0, i1, j0, j1;

			float dtx = dt * (N - 2);
			float dty = dt * (N - 2);

			float s0, s1, t0, t1;
			float tmp1, tmp2, x, y;

			float Nfloat = N;
			float ifloat, jfloat;
			int i, j;

			for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
				for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
					tmp1 = dtx * velX[IX(i, j)];
					tmp2 = dty * velY[IX(i, j)];
					x = ifloat - tmp1;
					y = jfloat - tmp2;

					if (x < 0.5f) x = 0.5f;
					if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
					i0 = floor(x);
					i1 = i0 + 1.0f;
					if (y < 0.5f) y = 0.5f;
					if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
					j0 = floor(y);
					j1 = j0 + 1.0f;

					s1 = x - i0;
					s0 = 1.0f - s1;
					t1 = y - j0;
					t0 = 1.0f - t1;

					int i0i = int(i0);
					int i1i = int(i1);
					int j0i = int(j0);
					int j1i = int(j1);

					// DOUBLE CHECK THIS!!!
					d[IX(i, j)] =
						s0 * (t0 * d0[IX(i0i, j0i)] + t1 * d0[IX(i0i, j1i)]) +
						s1 * (t0 * d0[IX(i1i, j0i)] + t1 * d0[IX(i1i, j1i)]);
				}
			}
			setBound(b, d);
		}

		void project(float* velX, float* velY, float* p, float* div, int iter)
		{
			int N = cube.size;
			for (int j = 1; j < N - 1; j++)
			{
				for (int i = 1; i < N - 1; i++)
				{
					div[IX(i, j)] = -0.5f *
						(velX[IX(i + 1, j)]
							- velX[IX(i - 1, j)]
							+ velY[IX(i, j + 1)]
							- velY[IX(i, j - 1)]) / N;
					p[IX(i, j)] = 0;
				}
			}
		}

		void linearSolve(int b, float* x, float* x0, float a, float c, int iter)
		{
			int N = cube.size;
			float cRecip = 1.f / c;
			for (int k = 0; k < iter; k++)
			{
				for (int j = 1; j < N - 1; j++)
				{
					for (int i = 1; i < N - 1; i++)
					{
						x[IX(i, j)] = (x0[IX(i, j)] +
							a * (x[IX(i + 1, j)]
								+ x[IX(i - 1, j)]
								+ x[IX(i, j + 1)]
								+ x[IX(i, j - 1)])) * cRecip;
					}
				}
			}
			setBound(b, x);
		}

		void setBound(int b, float* x)
		{
			int N = cube.size;
			for (int i = 1; i < N - 1; i++) {
				x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
				x[IX(i, N - 1)] = b == 2 ? -x[IX(i, N - 2)] : x[IX(i, N - 2)];
			}
			for (int j = 1; j < N - 1; j++) {
				x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
				x[IX(N - 1, j)] = b == 1 ? -x[IX(N - 2, j)] : x[IX(N - 2, j)];
			}

			x[IX(0, 0)] = .5f * (x[IX(1, 0)] + x[IX(0, 1)]);
			x[IX(0, N - 1)] = .5f * (x[IX(1, N - 1)] + x[IX(0, N - 2)]);
			x[IX(N - 1, 0)] = .5f * (x[IX(N - 2, 0)] + x[IX(N - 1, 1)]);
			x[IX(N - 1, N - 1)] = .5f * (x[IX(N - 2, N - 1)] + x[IX(N - 1, N - 2)]);
		}

		void addDensity(int x, int y, float amount)
		{
			int N = cube.size;
			cube.density[IX(x, y)] += amount;
		}

		void addVelocity(int x, int y, float amountX, float amountY)
		{
			int N = cube.size;
			int idx = IX(x, y);

			cube.Velx[idx] += amountX;
			cube.Vely[idx] += amountY;
		}

		void render()
		{

		}
	};
}