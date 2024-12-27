#pragma once 
#include <array>
#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <type_traits> // For the near future.

namespace math {
	
	static constexpr float inf = std::numeric_limits<float>::infinity();

	struct point {
		float x;
		float y;

		float dist () { 
			return (x * x) + (y * y); 
		}

		# if 0
		point operator + (point const& pt) {
			return point {pt.x + this.x, pt.y + this.y};
		}

		# endif

	};

	struct box {
		point bottom_left {inf, inf};
		point top_right {-inf, -inf};
		float velx;
		float vely;

		point middle () {
			return point { 
				(bottom_left.x + top_right.x) / 2, 
				(bottom_left.y + top_right.y) / 2 };
		}

		point closest_to_origin () {
			return (bottom_left.dist() < top_right.dist()) ? bottom_left : top_right; 
		}

		float area () {
			return (top_right.x - bottom_left.x) * (top_right.y - bottom_left.y);
		}	

		box& expand (point const& pt) {
			bottom_left.x  = std::min (bottom_left.x, pt.x);
			bottom_left.y  = std::min (bottom_left.y, pt.y);
			top_right.x  = std::max (top_right.x, pt.x);
			top_right.y  = std::max (top_right.y, pt.y);
			return *this;
		}

		box& expand (box const& bx) {
			bottom_left.x  = std::min (bottom_left.x, bx.bottom_left.x);
			bottom_left.y  = std::min (bottom_left.y, bx.bottom_left.y);
			top_right.x  = std::max (top_right.x, bx.top_right.x);
			top_right.y  = std::max (top_right.y, bx.top_right.y);
			return *this;
		}

		SDL_Rect to_sdl () {

			return SDL_Rect { 
				.x = static_cast<int> (top_right.x - bottom_left.x / 2),
				.y = static_cast<int> (top_right.y - bottom_left.y / 2),
				.w = static_cast<int> (top_right.x - bottom_left.x),
				.h = static_cast<int> (top_right.y - bottom_left.y),
			};
			
		}
	
	};


	# if 0
	// Not sure if this is needed, massive refactor incoming.
	template <std::size_t dims, class coord_type> 
	class point {

	  private:	
		std::array<coord_type, dims> coords_;

	};
	
	template <class coord_type> 
	class vector {

 	  public:
		
		vector (coord_type x, coord_type y) : x_(x), y_(y) {};

		coord_type get_x () const {
			return x_;
		}
	

		coord_type get_y () const {
			return y_;
		}

		double magnitude_squared () {
			return (x_ * x_) + (y_ * y_); 
		}

		
		friend math::vector<coord_type> operator * (coord_type scalar, const math::vector<coord_type> & v) {
			return math::vector(v.get_x() * scalar, v.get_y() * scalar); 
		}

		friend math::vector<coord_type> operator + (const math::vector<coord_type> & v, const math::vector<coord_type> & w) {
			return math::vector(w.get_x() + v.get_x(), w.get_y() + v.get_y());
		}

		friend math::vector<coord_type> operator - (const math::vector<coord_type> & v, const math::vector<coord_type> & w) {
			return math::vector(w.get_x() - v.get_x(), w.get_y() - v.get_y());
		}


		friend std::ostream & operator << (std::ostream & buffer, const math::vector<coord_type> & v )  {
			
			buffer << "[v]: (";
			buffer << v.get_x() << ", " << v.get_y() << ")";
			return buffer;	
		
		}
	
	  private:
	 	coord_type x_;	
	 	coord_type y_;	
	};

	#endif 
}
