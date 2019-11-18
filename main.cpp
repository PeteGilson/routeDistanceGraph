//*************************************************************************************************
//*************************************************************************************************
//
//	File Name:      main.cpp 
//	Description:	Main method for demostrating basic operations.
//*************************************************************************************************
//*************************************************************************************************

// Declare required includes
#include "routeDistanceAndDurationCalculator.cpp"


int main (int argc, char *argv[])
{
	// Create 'routeDistanceAndDurationCalculator' object
        routeDistanceAndDurationCalculator* calculator = new routeDistanceAndDurationCalculator();

	// First, read in input graph
	std::string input = "gtest/codingChallengeInput.txt";

	// Construct routes map
	std::vector<towns> completedGraph;
	calculator->populateInputGraph(input, &completedGraph);
	std::cout << "Graph size = " << completedGraph.size() << "\n";

	// Take input string
	std::string desiredRoute;
	std::cout << "ROUTE DISTANCE TEST - "<< "\n" << "please enter route: ";
	std::cin >> desiredRoute;

	// Check distance
	int distance = calculator->checkDistanceOrDuration(&completedGraph, desiredRoute, DISTANCE_CHECK_MODE);
	if(distance == -1)
	{
		std::cout << "NO SUCH ROUTE"  << "\n";
	}
	else
	{
		std::cout << "Distance = " << distance << "\n";
	}

	// Check route count with max stops
	std::string startTown;
	std::cout << "NUMBER OF TRIPS TEST - " << "\n" << "Enter Start Town: ";
	std::cin >> startTown;
	const char* start = startTown.c_str();

	std::string endTown;
	std::cout << "Enter End Town: ";
	std::cin >> endTown;
	const char* end = endTown.c_str();

	int maxStops;
	std::cout << "Enter Max Stops: ";
	std::cin >> maxStops;

	int exactStopsOnly;
	std::cout << "Exact stops only? (0 or 1): ";
	std::cin >> exactStopsOnly;

	int routeCheck = 0;

	if(exactStopsOnly == 0)
	{
	routeCheck = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxStops, MAX_STOPS_MODE);
	}
	else
	{
	routeCheck = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, maxStops, EXACT_STOPS_ONLY_MODE);
	}

	std::cout << "Number of routes = " << routeCheck << "\n";

	// Check shortest route
	std::string startTownShort;
	std::cout << "SHORTEST ROUTE TEST - " << "\n" << "Enter Start Town: ";
	std::cin >> startTownShort;
	const char* startShort = startTownShort.c_str();

	std::string endTownShort;
	std::cout << "Enter End Town: ";
	std::cin >> endTownShort;
	const char* endShort = endTownShort.c_str();

	int shortestStops = calculator->numberOfTrips(&completedGraph, (char*)start, (char*)end, 100, SHORTEST_TRIP_MODE);
	std::cout << "Shortest Route = " << shortestStops << "\n";
}
