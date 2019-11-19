********************************************************
------	   Journey Graphical Node Reader	   -----
********************************************************

-- CONTENTS --

The code was developed in C++, on a Linix system
and built using CMake, you must install GTest in order
to build and run the tests. This can be done as follows:
sudo apt-get install libgtest-dev

The code was developed via TDD anf GTest used to
run the unit tests used during development.

The contents are as follows:

routeDistanceAndDurationCalculator.cpp:
Calculator class

routeDistanceAndDurationCalculator.h:
Calculator class header file

CMakeLists.txt
CMake file used to build the executable

gtest/codingChallengeTests.cpp:
Unit tests used to TDD and validate the code.
Tests use the sugessted test data as input/validation

gtest/codingChallengeInput.txt
Input file containing graph node data

gtest/CMakeLists.txt 
CMake file used to build the unit tests

-- BUILD/RUN INSTRUCTIONS --

This software was built and tested on a Linix system,
Ubuntu 19.04 using CMake. To build using CMake:
1 - Unzip to a chosen location
2 - Navigate to the gtest folder
3 - Run 'cmake .'
4 - Run 'make', output should be:
	[ 50%] Building CXX object CMakeFiles/runTests.dir/codingChallengeTests.cpp.o
	[100%] Linking CXX executable runTests
	[100%] Built target runTests
5 - Run the unit tests using the command './runTests'
6 - The output should show 12 sucessfull test runs

To build the executable without the Gtest run:
1 - Unzip to a chosen location
2 - In root folder, run 'cmake .'
3 - Run 'make'
4 - Run './routeDistanceAndDurationCalculator'
5 - Follow instructions to get output


-- DESIGN & ASSUMPTIONS --

The solution uses a defined structure to store towns and their associated
connections. The connections are stored in a map pair of town name + distance:

struct towns
{
    char townName;
    std::map<towns*, int> connections;
};

A vector of this object type is created and populated with the data contained
within the input text file to construct the graph nodes.

The basic distance check, 'checkDistanceOrDuration', simply traverses the vector 
and each towns connection(s) and sums up the distance to give the total. This distance
will be converted into duration (time) if the DURATION_CHECK_MODE is specified.

Modes, defined in the header file 'routeDistanceAndDurationCalculator.h' as static 
integers, are used to switch the values calculated and rules of the traversal 
algorithm in order to both simplify the code, reduce duplicate code and allow
for future expansion of code operations.

The function 'traverseThisRoute' is responsible for traversing the route graph
data and calculating the number of stops, distance and duration (depending on the
mode selected.

The basic premise is that this function will call itself to traverse node child
routes, until either the end town or duration/distance are found/met. Each node
found is added to the total, and a string + int map is poplated with the traversed
routes nodes and distances, used after traversal in the 'numberOfTrips' function 
to calculate the retuen value required, based on the operating modes:
static const int MAX_STOPS_MODE = 100;
static const int EXACT_STOPS_ONLY_MODE = 101;
static const int SHORTEST_TRIP_MODE = 102;
static const int DIFFERENT_ROUTES_MODE = 103;
static const int DURATION_CHECK_MODE = 104;
static const int QUICKEST_ROUTE_MODE = 105;
static const int DISTANCE_CHECK_MODE = 106;

-- VALIDATION --
The solution was developed in a TDD manner, meaning forst teste were defined,
ran against empty target class/functions and allowed to first fail, before
the function code was added to allow the test to pass.

The GTest output shows 12 tests ran sucessfully, the extended challenge tests were
incorporated into the first test in order to minimise test code required. 

The test input file gtest/codingChallengeInput.txt contains the inout data used for the test.

Below is a list of the tests defined, run and passed, along with the requirement they
satisfy:

create_graph_test		- Checks the graph read functionality - Read input via text file requirement.
missing_input_file_test	- Checks that an invalid input file is reported as an error - Read input via text file requirement.
Route_A_B_C_test		- Checks distance and duration of route A-B-C - Expected output #1 & Assignment extension expected output #1
Route_A_D_test			- Checks distance and duration of route A-D - Expected output #2 & Assignment extension expected output #2
Route_A_D_C_test		- Checks distance and duration of route A-D-C - Expected output #3 & Assignment extension expected output #3
Route_A_E_B_C_D_test	- Checks distance and duration of route A-E-B-C-D - Expected output #4 & Assignment extension expected output #4
Route_A_E_D_test		- Checks distance and duration of route A-E-D - Expected output #5 & Assignment extension expected output #5
Trips_C_C_Max_3_test	- Checks the number of trips from C-C max 3 stops - Expected output #6 & Assignment extension expected output #6
Trips_A_C_Exact_4_test	- Checks the number of trips from A-C exactly 4 stops - Expected output #7 & Assignment extension expected output #7
Shortest_A_C_test		- Checks the shortest route from A-C  - Expected output #8 & Assignment extension expected output #8
Shortest_B_B_test		- Checks the shortest route from B-B  - Expected output #9 & Assignment extension expected output #9
Routes_C_C_test			- Checks the number of routes from C-C - Expected output #10 & Assignment extension expected output #10

The output of the test run is shown in the 'testResult.txt' file
 
