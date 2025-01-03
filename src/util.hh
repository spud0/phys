#pragma once 
#include <cstdint>
#include <vector>

#include "math.hh"

#define L 2 
#define W L

namespace util {

	using node_id = std::uint32_t;
	static constexpr node_id empty = -1; 

	// Temporary can store more information in here...
	struct node {	
		node_id children[L][W] = {
			{empty, empty}, {empty, empty}
		};
	};
	

	struct quadtree {
		math::box bbox;	
		node_id root;
		std::vector<node> nodes;
	};
}
