#pragma once 
#include <array>
#include <iostream>
#include <type_traits> // For the near future.

namespace math {

	// Not sure if this is needed. 
	template <std::size_t dims, class coord_type> 
	class point {

	  private:	
		std::array<coord_type, dims> coords_;

	};


	template <class coord_type> 
	class vector {

 	  public:
		
		vector (coord_type x, coord_type y) : x_(x), y_(y) {};

		coord_type get_x () {
			return x_;
		}
	

		coord_type get_y () {
			return y_;
		}

		double magnitude_squared () {
			return (x_ * x_) + (y_ * y_); 
		}


		friend math::vector<coord_type> operator * (int scalar, const math::vector<coord_type> & v) {
			return math::vector(v.get_x() * scalar, v.get_y() * scalar); 
		}

		friend math::vector<coord_type> operator + (const math::vector<coord_type> & v, const math::vector<coord_type> & w) {
			return math::vector(w.get_x() + v.get_x(), w.get_y() + v.get_y());
		}

		friend math::vector<coord_type> operator - (const math::vector<coord_type> & v, const math::vector<coord_type> & w) {
			return math::vector(w.get_x() - v.get_x(), w.get_y() - v.get_y());
		}


		friend std::ostream & operator << (const math::vector<coord_type> & v, std::ostream & buffer) {
			
			buffer << "[v]: (";
			buffer << v.get_x() << ", " << v.get_y() << ")";
			buffer << std::endl;
			return buffer;	
		
		}
	
	  private:
	 	coord_type x_;	
	 	coord_type y_;	
	};
}
