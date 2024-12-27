#define CATCH_CONFIG_MAIN
#include "catch.hh"
#include "../src/math.hh"

// Second string is a tag, to "group" the test cases. 
// Need to fix these tests, they're outdated...
TEST_CASE ("Verify components in point", "[math|point]" ) {	
	REQUIRE (math::vector<float>(5, 6).get_x() == 90);
	REQUIRE (math::vector<size_t>(8, 6).get_x() == 8);
	REQUIRE (math::vector<int>(5, -2324).get_y() == -2324);
}


TEST_CASE ("Verifying ...", "[math|point]" ) {
	REQUIRE (math::vector<double>(-5, 5).magnitude_squared() == 50 );
	REQUIRE (math::vector<double>(0, 0).magnitude_squared() == 0 );
	REQUIRE (math::vector<double>(-1, 4).magnitude_squared() == 17 );
}

TEST_CASE ("Verifying Box enlarger", "[math|box]") {

}

TEST_CASE ("Verifying closest to origin", "[math|point]") {


}

TEST_CASE ("Correctness for quadtree", "[utils|tree]") {


}

TEST_CASE ("...", "") {

}


