#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <sstream>
#include <ppl.hh>

// unsigned int Factorial( unsigned int number ) {
//     return number <= 1 ? number : Factorial(number-1)*number;
// }

// TEST_CASE( "Factorials are computed", "[factorial]" ) {
//     REQUIRE( Factorial(1) == 1 );
//     REQUIRE( Factorial(2) == 2 );
//     REQUIRE( Factorial(3) == 6 );
//     REQUIRE( Factorial(10) == 3628800 );
// }

// TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

//     std::vector<int> v( 5 );

//     REQUIRE( v.size() == 5 );
//     REQUIRE( v.capacity() >= 5 );

//     SECTION( "resizing bigger changes size and capacity" ) {
//         v.resize( 10 );

//         REQUIRE( v.size() == 10 );
//         REQUIRE( v.capacity() >= 10 );
//     }
//     SECTION( "resizing smaller changes size but not capacity" ) {
//         v.resize( 0 );

//         REQUIRE( v.size() == 0 );
//         REQUIRE( v.capacity() >= 5 );
//     }
//     SECTION( "reserving bigger changes capacity but not size" ) {
//         v.reserve( 10 );

//         REQUIRE( v.size() == 5 );
//         REQUIRE( v.capacity() >= 10 );
//     }
//     SECTION( "reserving smaller does not change size or capacity" ) {
//         v.reserve( 0 );

//         REQUIRE( v.size() == 5 );
//         REQUIRE( v.capacity() >= 5 );
//     }
// }

// SCENARIO( "vectors can be sized and resized", "[vector]" ) {

//     GIVEN( "A vector with some items" ) {
//         std::vector<int> v( 5 );

//         REQUIRE( v.size() == 5 );
//         REQUIRE( v.capacity() >= 5 );

//         WHEN( "the size is increased" ) {
//             v.resize( 10 );

//             THEN( "the size and capacity change" ) {
//                 REQUIRE( v.size() == 10 );
//                 REQUIRE( v.capacity() >= 10 );
//             }
//         }
//         WHEN( "the size is reduced" ) {
//             v.resize( 0 );

//             THEN( "the size changes but not capacity" ) {
//                 REQUIRE( v.size() == 0 );
//                 REQUIRE( v.capacity() >= 5 );
//             }
//         }
//         WHEN( "more capacity is reserved" ) {
//             v.reserve( 10 );

//             THEN( "the capacity changes but not the size" ) {
//                 REQUIRE( v.size() == 5 );
//                 REQUIRE( v.capacity() >= 10 );
//             }
//         }
//         WHEN( "less capacity is reserved" ) {
//             v.reserve( 0 );

//             THEN( "neither size nor capacity are changed" ) {
//                 REQUIRE( v.size() == 5 );
//                 REQUIRE( v.capacity() >= 5 );
//             }
//         }
//     }
// }

#define L(level, exp) {                         \
        using IO_Operators::operator<<;         \
        std::ostringstream os;                  \
        os << exp << std::endl;                 \
        level( os.str() );                      \
    }

#define C(level, exp) L(level, #exp << ": " << exp )
#define N(level, exp) L(level, "*** " << #exp << " ***" << std::endl << exp )

TEST_CASE( "PPL Simple", "[factorial]" ) {
    using namespace Parma_Polyhedra_Library;

    Variable x(0);
    Variable y(1);

    C_Polyhedron ph1(2);
    ph1.add_constraint(x+y >= 0);
    ph1.add_constraint(y >= 0);
    ph1.add_constraint(x <= 2);
    ph1.add_constraint(y <= 4);

    C_Polyhedron ph2(2);
    ph2.add_constraint(y >= 2);
    ph2.add_constraint(y <= 4);
    ph2.add_constraint(x >= 0);
    ph2.add_constraint(x <= 2);

    std::ostringstream os;

    int i = 1;

    N( WARN, ph1 );
    N( WARN, ph2 );

    L( WARN, "*** after upper_bound_assign ***\n" << ph1 );

    C_Polyhedron known_result(2, EMPTY);
    known_result.add_generator(point());
    known_result.add_generator(point(2*x));
    known_result.add_generator(point(-4*x + 4*y));
    known_result.add_generator(point(2*x + 4*y));

    REQUIRE( ph1 == known_result );
}
