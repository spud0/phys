#pragma once
#include "math.hh"
#include <cmath>

namespace phys {
	
	constexpr double GRAVITY = 9.81; 
	constexpr double DEL_TIME = 0.1;	

	void apply_gravity (math::vector<int>& v) {
		int y_component = v.get_y()
		y_component += static_cast<int> (phys::GRAVITY * phys::DEL_TIME);
		v.set_y(y_component);
		return;
	}

	void apply_gravity (math::vector<float>& v) {
		v.y += static_cast<float> (phys::GRAVITY * phys::DEL_TIME);
		return;
	}

	void apply_gravity (math::vector<double>& v) {
		v.y += phys::GRAVITY * phys::DEL_TIME;
		return;
	}

}
