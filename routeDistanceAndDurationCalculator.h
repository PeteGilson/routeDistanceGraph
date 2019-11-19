// Declare required includes
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Define statics used, including operating modes.
static const int MAX_STOPS_MODE = 100;
static const int EXACT_STOPS_ONLY_MODE = 101;
static const int SHORTEST_TRIP_MODE = 102;
static const int DIFFERENT_ROUTES_MODE = 103;
static const int DURATION_CHECK_MODE = 104;
static const int QUICKEST_ROUTE_MODE = 105;
static const int DISTANCE_CHECK_MODE = 106;
static const int TRAVEL_UNIT_TIME = 1;
static const int PER_STOP_TIME = 2;
static const int NO_INPUT_FILE_FOUND = -1;
static const int OK = 1;
static const int ROUTE_NOT_FOUND = -1;

// Define the towns structure.
struct towns
{
    char townName;
    std::map<towns*, int> connections;
};

class routeDistanceAndDurationCalculator
{
    public:
        int populateInputGraph(std::string inputGraph, std::vector<towns>* completedGraph);
        int checkDistanceOrDuration(std::vector<towns>* routesGraph, std::string desiredRoute, int operatingMode);
        int numberOfTrips(std::vector<towns>* routesGraph, char* startTown, char* endTown, int numberOfStops, int operatingMode);
        int traverseThisRoute(std::vector<towns>* routesGraph,std::map<towns*, int> route, char* endTown, int maxStopsOrDuration, std::string routeTaken, std::map<std::string, int> &routeDistances, int operatingMode);
};
