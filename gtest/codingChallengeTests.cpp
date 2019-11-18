///////////////////////////////////////////////////////////////////////////////
//
// *** codingChallengeTests.cpp ***
//
// Description:	Tests used in the development of the solutions (TDD approach).
//
// 		The Google GTest framework was used.
//
///////////////////////////////////////////////////////////////////////////////


// Declare required includes
#include <gtest/gtest.h>
#include "../routeDistanceAndDurationCalculator.cpp"

///////////////////////////////////////////////////////////////////////////////
//
// Name:                create_graph_test
//                      
// Description:         Tests that the input data file can be read and used to
// 						populate the input data structure as expected.
// Expectes Outcome:    Structure containing all input data from file.
///////////////////////////////////////////////////////////////////////////////
TEST(create_graph_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);
	
	// Check the return code.
	ASSERT_EQ(OK, errorCode);

	// Check the output (All towns have an entry)
	ASSERT_EQ(5, completedGraph.size());
	std::string comp(1, completedGraph.at(0).townName);
	EXPECT_EQ("A", comp);
	std::string comp1(1, completedGraph.at(1).townName);
	EXPECT_EQ("B", comp1);
	std::string comp2(1, completedGraph.at(2).townName);
	EXPECT_EQ("C", comp2);
	std::string comp3(1, completedGraph.at(3).townName);
	EXPECT_EQ("D", comp3);
	std::string comp4(1, completedGraph.at(4).townName);
	EXPECT_EQ("E", comp4);
	
	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                missing_input_file_test
//
// Description:         Tests that the input interpretation class can handle 
// 						a missing input file and report an error.
// Expectes Outcome:    -1 returned from call
///////////////////////////////////////////////////////////////////////////////
TEST(missing_input_file_test, ZeroAndNegativeNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function, inputfile is invalid (doesnt exist)
	std::string inputFileName = "codingChallengeInput_BLABLABLA.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the return code.
	ASSERT_EQ(NO_INPUT_FILE_FOUND, errorCode);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Route_A_B_C_test
// 						Test 1: The distance of the route A-B-C
// Description:         Tests that the route A-B-C distance is calculated
//                      correctly
// Expectes Outcome:    Result = 9
///////////////////////////////////////////////////////////////////////////////
TEST(Route_A_B_C_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the distance of a given route
	int distance = calculator->checkDistanceOrDuration(&completedGraph, "A-B-C", DISTANCE_CHECK_MODE); 

	// Check the value returned
	ASSERT_EQ(9, distance);	

	// Extension tests
	int duration = calculator->checkDistanceOrDuration(&completedGraph, "A-B-C", DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(11, duration);


	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}

///////////////////////////////////////////////////////////////////////////////
//
// Name:                Route_A_D_test
// 						Test 2: The distance of the route A-D
// Description:         Tests that the route A-D distance is calculated
//                      correctly
// Expectes Outcome:    Result = 5
///////////////////////////////////////////////////////////////////////////////
TEST(Route_A_D_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the distance of a given route
	int distance = calculator->checkDistanceOrDuration(&completedGraph, "A-D", DISTANCE_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(5, distance);

	// Extension test
	int duration = calculator->checkDistanceOrDuration(&completedGraph, "A-D", DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(5, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Route_A_D_C_test
// 						Test 3: The distance of the route A-D-C
// Description:         Tests that the route A-D distance is calculated
//                      correctly
// Expectes Outcome:    Result = 13
///////////////////////////////////////////////////////////////////////////////
TEST(Route_A_D_C_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the distance of a given route
	int distance = calculator->checkDistanceOrDuration(&completedGraph, "A-D-C", DISTANCE_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(13, distance);

	 // Extension test
	int duration = calculator->checkDistanceOrDuration(&completedGraph, "A-D-C", DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(15, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Route_A_E_B_C_D_test
// 						Test 4: The distance of the route A-E-B-C-D
// Description:         Tests that the route A-E-B-C-D distance is calculated
//                      correctly
// Expectes Outcome:    Result = 22
///////////////////////////////////////////////////////////////////////////////
TEST(Route_A_E_B_C_D_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the distance of a given route
	int distance = calculator->checkDistanceOrDuration(&completedGraph, "A-E-B-C-D", DISTANCE_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(22, distance);

	// Extension test
	int duration = calculator->checkDistanceOrDuration(&completedGraph, "A-E-B-C-D", DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(28, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Route_A_E_D_test
// 						Test 5: The distance of the route A-E-D
// Description:         Tests that the route A-E-D distance is calculated
//                      correctly
// Expectes Outcome:    Result = NO SUCH ROUTE
///////////////////////////////////////////////////////////////////////////////
TEST(Route_A_E_D_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the distance of a given route
	int distance = calculator->checkDistanceOrDuration(&completedGraph, "A-E-D", DISTANCE_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(ROUTE_NOT_FOUND, distance);

	// Extension test
	int duration = calculator->checkDistanceOrDuration(&completedGraph, "A-E-D", DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(ROUTE_NOT_FOUND, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Trips_C_C_Max_3_test
// 						Test 6: The number of trips from C-C with max stops
// 						of 3.
// Description:         Tests that the number of trips found from start to
// 						end with a stop count less than the max works as 
// 						expected.
// Expectes Outcome:    Result = With route C-C, max stops 3, expect 2
///////////////////////////////////////////////////////////////////////////////
TEST(Trips_C_C_Max_3_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the number of trips matching the route/max stops.
	const char* start = "C";
	const char* end = "C";
	int maxNumberOfStops = 3;
	int maxStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxNumberOfStops, MAX_STOPS_MODE); 

	// Check the value returned
	ASSERT_EQ(2, maxStops);

	// Extension test
	int maxDuration = 30;
	int duration = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxDuration, DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(4, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Trips_A_C_Exact_4_test
// 						Test 7: The number of trips from A-C with exact stop
//                      count of 4.
// Description:         Tests that the number of trips found from start to
//                      end with a stop count equal to the given value works as
//                      expected.
// Expectes Outcome:    Result = With route A-C, exact stops 4, expect 3
///////////////////////////////////////////////////////////////////////////////
TEST(Trips_A_C_Exact_4_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the number of trips matching the route/max stops.
	const char* start = "A";
	const char* end = "C";
	int maxNumberOfStops = 4;
	int maxStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxNumberOfStops, EXACT_STOPS_ONLY_MODE);

	// Check the value returned
	ASSERT_EQ(3, maxStops);

	// Extension test
	int maxDuration = 30;
	int duration = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxDuration, DURATION_CHECK_MODE + EXACT_STOPS_ONLY_MODE);

	// Check the value returned
	ASSERT_EQ(1, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Shortest_A_C_test
// 						Test 8: The length of the shortest route from A-C
// Description:         Tests that the shortest route between 2 distinct 
// 						destinations works as expected.
// Expectes Outcome:    Result = With route A-C, 9
///////////////////////////////////////////////////////////////////////////////
TEST(Shortest_A_C_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the number of trips matching the route/max stops.
	const char* start = "A";
	const char* end = "C";

	// Set an arbitary max stops value.
	int maxNumberOfStops = 100;
	int shortestStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxNumberOfStops, SHORTEST_TRIP_MODE);

	// Check the value returned
	ASSERT_EQ(9, shortestStops);

	// Extension test
	int maxDuration = 50;
	int duration = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxDuration, QUICKEST_ROUTE_MODE);

	// Check the value returned
	ASSERT_EQ(11, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Shortest_B_B_test
// 						Test 9: The length of the shortest route from B-B
// Description:         Tests that the shortest route between a destination
// 						and itself works as expected.
// Expectes Outcome:    Result = With route B-B, 9
///////////////////////////////////////////////////////////////////////////////
TEST(Shortest_B_B_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the number of trips matching the route/max stops.
	const char* start = "B";
	const char* end = "B";

	// Set an arbitary max stops value.
	int maxNumberOfStops = 100;
	int shortestStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxNumberOfStops, SHORTEST_TRIP_MODE);

	// Check the value returned
	ASSERT_EQ(9, shortestStops);

	// Extension test
	int maxDuration = 50;
	int duration = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxDuration, QUICKEST_ROUTE_MODE);

	// Check the value returned
	ASSERT_EQ(13, duration);

	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}


///////////////////////////////////////////////////////////////////////////////
//
// Name:                Routes_C_C_test
//                      Test 10: The number of routes from C to C with a
//                      distance less than 30.
// Description:         Tests that the number of routes between 2 towns with
// 						a duration less than that given can be found
// Expectes Outcome:    Result = With route C-C, distance < 30, expect 7
///////////////////////////////////////////////////////////////////////////////
TEST(Routes_C_C_test, PositiveNos)
{
	// Create the test graph structure to populate.
	std::vector<towns> completedGraph;

	// Create 'routeDistanceAndDurationCalculator' object
	routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// Call the 'populateInputGraph()' function
	std::string inputFileName = "codingChallengeInput.txt";
	int errorCode = calculator->populateInputGraph(inputFileName, &completedGraph);

	// Check the number of trips matching the route/max stops.
	const char* start = "C";
	const char* end = "C";

	// Set an arbitary max stops value.
	int maxDistance = 30;
	int numberStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxDistance, DIFFERENT_ROUTES_MODE);

	// Check the value returned
	ASSERT_EQ(7, numberStops);

	// Extension test
	int maxDuration = 35;
	numberStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxDuration, DIFFERENT_ROUTES_MODE + DURATION_CHECK_MODE);

	// Check the value returned
	ASSERT_EQ(6, numberStops);


	// Delete the 'routeDistanceAndDurationCalculator' object
	delete calculator;
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
