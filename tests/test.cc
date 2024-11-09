#define CATCH_CONFIG_MAIN
#include "catch.hh"
#include "../src/math.hh"

TEST_CASE ("initialization of math::vector", "idk" ) {	
	REQUIRE (math::vector<float>(5, 6).get_x() == 90);
	REQUIRE (math::vector<size_t>(8, 6).get_x() == 8);
	REQUIRE (math::vector<int>(5, -2324).get_y() == -2324);
}


TEST_CASE ("magnitude of vector", "what is this for?" ) {
	REQUIRE (math::vector<double>(-5, 5).magnitude_squared() == 50 );
	REQUIRE (math::vector<double>(0, 0).magnitude_squared() == 0 );
	REQUIRE (math::vector<double>(-1, 4).magnitude_squared() == 17 );
}

TEST_CASE ("vector addition...", "...") {

}

TEST_CASE ("scalar multiplication", "...") {


}


