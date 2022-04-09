#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "include/util.hpp"
#include "include/camera.hpp"
#include "include/sphere.hpp"
#include "include/material.hpp"
#include "include/hitablelist.hpp"
#include <chrono>
#include <fstream>

int main(void) {
	int nx = 1920;
	int ny = 1080;
	int ns = 5;

	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);

	float dist_to_focus = 10.0f;
	float aperture = 0.1f;

	hitable *world = random_scene();
	camera cam(lookfrom, lookat,
		   vec3(0.0f, 1.0f, 0.0f),
		   20.0f, float(nx) / float(ny),
		   aperture, dist_to_focus);

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	auto time_start = std::chrono::high_resolution_clock::now();
	for (int j = ny - 1; j >= 0; --j)
		for (int i = 0; i < nx; ++i) {
			vec3 col;
			for (int s = 0; s < ns; ++s) {
				float u = float(i + random_double()) / float(nx);
				float v = float(j + random_double()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			std::cout << ir << " "
				  << ig << " "
				  << ib << '\n';
	}
	auto time_stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = time_stop - time_start;
	std::ofstream myfile;
	myfile.open("res.txt");
	myfile<<time.count()*1000;
	myfile.close();
}
