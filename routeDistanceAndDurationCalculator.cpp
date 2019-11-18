//*************************************************************************************************
//*************************************************************************************************
//
//	File Name:		routeDistanceAndDurationCalculator.cpp 
//	Class Name:		routeDistanceAndDurationCalculator
//	Description:	Class for calculating route distances & duration.
//*************************************************************************************************
//*************************************************************************************************

// Declare required includes
#include "routeDistanceAndDurationCalculator.h"

//*************************************************************************************************
//
// Function name:	populateInputGraph
// Description:		Takes the input graph file name as input, atempts to open the file, read the
//					routes and distances, and construct the completed graph which is passed by 
//					reference to this function.
// Input:			inputGraph 		- String representing the file location + name to be processed.
//					completedGraph 	- Completed towns vector populated by this function, passed
//					by reference so it can be interpreted by calling function.
// Output:			The comletedGraph structure is populated and a status code is returned (int)
//*************************************************************************************************
int routeDistanceAndDurationCalculator::populateInputGraph(std::string inputGraph, std::vector<towns>* completedGraph)
{
	// Attempt to open the file specified
	std::ifstream inputFile;
	inputFile.open(inputGraph);

	// Check if it was a success
	if(!inputFile.good())
	{
		// Return appropriate error const.
		return NO_INPUT_FILE_FOUND;
	}
	else if(inputFile.is_open())
	{
		// Read the input (all on one line)
		std::string inputGraph;
		getline(inputFile, inputGraph);

		// For each comma separated path, add to the map if id doesnt exist
		std::stringstream inputFileStream;
		inputFileStream << inputGraph;
		std::string nextRoute;
		char delimiter = ',';

		while (std::getline(inputFileStream, nextRoute, delimiter)) 
		{
			// Strip distance from route start and end towns
			char routeStart = *nextRoute.substr(0, 1).c_str();
			char routeEnd = *nextRoute.substr(1, 1).c_str();
			int distance = std::stoi(nextRoute.substr(2, 1));

			// Store the town location within the vector
			towns firstTown;
			towns* secondTown;

			// Insert into the map - Check if we have this town
			bool firstTownFound = false;
			bool secondTownFound = false;
			if(completedGraph->size() > 0)
			{
				// Traverse the towns vector
				for(std::vector<towns>::iterator vectorCheck = completedGraph->begin(); vectorCheck != completedGraph->end(); vectorCheck++)
				{
					// Does this match our start town?
					if(vectorCheck->townName == routeStart)
					{
						// If so, we already have this start town and can use the existing reference, 
						// set flag so we dont add a new town
						firstTownFound = true;
						firstTown = (*vectorCheck);

						// Add the route..does the connection exist? If not, add 
						for(std::vector<towns>::iterator innerVectorCheck = completedGraph->begin(); innerVectorCheck != completedGraph->end(); innerVectorCheck++)
						{
							// Check if we already have the end town
							if(innerVectorCheck->townName == routeEnd)
							{
								// Then use its reference, set flag so we dont add a new town
								secondTownFound = true;
								secondTown = &(*innerVectorCheck);
							}
						}	 
					}
				}
			}

			// If we dont have the towns already, add them
			// First Town.
			if(firstTownFound == false)
			{
				towns newTown;
				newTown.townName = routeStart;
				completedGraph->push_back(newTown);
				firstTown = completedGraph->back();
			}

			// Second Town - pointer
			if(secondTownFound == false)
			{
				towns* newTown = new towns;
				newTown->townName = routeEnd;
				completedGraph->push_back((*newTown));

				// Store the pointer
				secondTown = newTown;
        	}

			// Construct the pair (destination + distance)
			std::pair<towns*, int> p1(secondTown, distance);
			
			// And add to the first towns connections map
			firstTown.connections.insert(p1);

			// Now update the cmpleted graph vector
			for(std::vector<towns>::iterator vectorIt = completedGraph->begin(); vectorIt != completedGraph->end(); vectorIt++)
			{
				if(vectorIt->townName == firstTown.townName)
				{		   
					vectorIt->connections.insert(p1);
				}
			}
		}
	}
	return OK;
}


//*************************************************************************************************
//
// Function name:	checkDistanceOrDuration
// Description:		Takes the input route as a string (desiredRoute) and determines either the 
//					distance or duration, which is returned as an integer
// Input:			routesGraph 	- Structure populated with the tows and distances.
//					desiredRoute 	- String representing the desired route to check.
//					operatingMode	- Integer representing one of the operating modes.
// Output:			Integer representing the distance or duration, depending on the mode received.
//*************************************************************************************************
int routeDistanceAndDurationCalculator::checkDistanceOrDuration(std::vector<towns>* routesGraph, std::string desiredRoute, int operatingMode)
{
	// Initatlise the distance/duration counter
   	int distance = 0;

	// For each node journey, get the distance and add to the total.
	// First we remove the town name delimiters
	std::stringstream inputRoute(desiredRoute);
	std::string completeRoute;
	std::string town;
	char delimiter = '-';
	while (std::getline(inputRoute, town, delimiter))
	{
		completeRoute += town;
	}

	// Define the start town attribute.
	towns startTown;

	// Now follow the route and add the distance/duration to the total.
	for(int counter = 0; counter < completeRoute.size(); counter++)
	{
		// Get the town name char
		char town = completeRoute.at(counter);
		
		// If this is the start town, get the object from the input vector.
		if(counter == 0)
		{
			// Get the start town from the vector
			for(int graphIter = 0; graphIter < routesGraph->size(); graphIter++)
			{
				// Is this the start town we require.
				if(routesGraph->at(graphIter).townName == town)
				{
					startTown = routesGraph->at(graphIter);
				}
			}

			// No town found, return -1
			if(startTown.townName != town)
			{
				return ROUTE_NOT_FOUND;
			}
		}
		else
		{
			// Check if this route exists
			int routeDistance = 0;
			towns nextTown;
			for(std::map<towns*, int>::iterator it = startTown.connections.begin();it != startTown.connections.end();it++)
			{
				// have we found the town we are looking for
				if(it->first->townName == town)
				{
					// Add the distance to the total
					routeDistance = it->second;

					// Get the next town so the loop can continue.
					for(int graphIter = 0; graphIter < routesGraph->size(); graphIter++)
					{
						if(routesGraph->at(graphIter).townName == town)
						{
							nextTown = routesGraph->at(graphIter);
						}
					}
				}
			}

			// Set the start town attribute to the next town found.
			startTown = nextTown;

			// Check the route existed
			if(routeDistance != 0)
			{
				distance += routeDistance;
			}
			else
			{
				return distance = ROUTE_NOT_FOUND;
			}
		}
	}

	// If in time mode, calculate and return
	if(operatingMode == DURATION_CHECK_MODE ||
	(operatingMode == DURATION_CHECK_MODE + EXACT_STOPS_ONLY_MODE))
	{
		// We need to add the town stop and travel time
		int timeTaken = (distance * TRAVEL_UNIT_TIME) + ((completeRoute.size() - 2) * PER_STOP_TIME);
		return timeTaken;
	}
	return distance;
}


//*************************************************************************************************
//
// Function name:	numberOfTrips
// Description:		Function to instigate the route traversal algorithm and format the result.
// Input:			routesGraph 	- Structure populated with the tows and distances.
//					startTown		- Start town character
//					endTown			- End town character
//					numberOfStops	- Integer representing the max stops/duration 
//					operatingMode	- Mode of operation, specified by one of the defined const ints
// Output:			Integer representing the distance or duration, depending on the mode received.
//*************************************************************************************************
int routeDistanceAndDurationCalculator::numberOfTrips(std::vector<towns>* routesGraph, char* startTown, char* endTown, int numberOfStops, int operatingMode)
{
	// Get the start town object.
	int returnValue = 0;
	towns startTownObject;
	std::map<std::string, int> routeDistances;
	int postCheckMode = 0;

	postCheckMode = operatingMode;

	// Check if a combination mode has been selected
	switch(operatingMode)
	{
		case DURATION_CHECK_MODE + DIFFERENT_ROUTES_MODE:
			operatingMode = DURATION_CHECK_MODE;
			postCheckMode = DIFFERENT_ROUTES_MODE;
			break;
		default:
			postCheckMode = operatingMode;
			break;
	}

	for(int graphIter = 0; graphIter < routesGraph->size(); graphIter++)
	{
		// Is this our start town?
        if(routesGraph->at(graphIter).townName == *startTown)
        {
			// Get the town object
            startTownObject = routesGraph->at(graphIter);

			// Follow each route, if child connections are available
			if(startTownObject.connections.size() > 0)
			{
				// Construct a string of the route taken so far.
				std::stringstream ss;
				ss << routesGraph->at(graphIter).townName;
				std::string routeTaken;
				ss >> routeTaken;
				
				// Traverse the route to calculate the distance/stop count or time taken.
				returnValue += traverseThisRoute(routesGraph, startTownObject.connections, endTown, numberOfStops, routeTaken, routeDistances, operatingMode);
			}
		}
	}

	// If we are looking for shortest route, calculate and return this instead
	if(postCheckMode == SHORTEST_TRIP_MODE || postCheckMode == QUICKEST_ROUTE_MODE)
	{
		// Set the return value to 0
		returnValue = 0;
		
		// For all route/distance pairs found, check if this is the first or shortest route.  
		for(std::map<string, int>::iterator it = routeDistances.begin(); it != routeDistances.end(); it++)
		{
			if(returnValue == 0 || (it->second < returnValue))
			{ 
				if(postCheckMode == SHORTEST_TRIP_MODE)
				{
					// Set the return value to the shortest distance found.
					returnValue = it->second;
				}
				else if(postCheckMode == QUICKEST_ROUTE_MODE)
				{
					// Times the distance by time per unit.
					returnValue = it->second * TRAVEL_UNIT_TIME;

					// Add the stops also...if any - Exclude start-end towns.
					returnValue += (it->first.size() - 2) * PER_STOP_TIME; 
				}
			}
		}
	}
	else if(postCheckMode == DIFFERENT_ROUTES_MODE)
	{
		// Just return the siye of the routes container
		returnValue = routeDistances.size();
	}

	return returnValue; 
}


//*************************************************************************************************
//
// Function name:	traverseThisRoute
// Description:		Function to instigate the route traversal algorithm and format the result.
// Input:			routesGraph 		- Structure populated with the tows and distances.
//					route				- The route, connections, to be traversed.
//					endTown				- End town character
//					maxStopsOrDuration	- Integer representing the max stops/duration 
//					routeTaken			- String representing the current route being traversed
//					routeDistances		- Structure to store route & distance/duration pairs
//					operatingMode	- Mode of operation, specified by one of the defined const ints
// Output:			Integer representing either number of nodes found.
//*************************************************************************************************
int routeDistanceAndDurationCalculator::traverseThisRoute(std::vector<towns>* routesGraph,std::map<towns*, int> route, char* endTown, int maxStopsOrDuration, std::string routeTaken, std::map<std::string, int> &routeDistances, int operatingMode)
{
	// Define variables used.
	int returnValue = 0;
	bool exit = false;
	int stopsOrDistance = 0;

	// Traverse through all connections
	for(std::map<towns*, int>::iterator it = route.begin(); it != route.end() && exit == false; it++)
	{
		// Get this object from the list
		towns nextObject;
		for(int graphIter = 0; graphIter < routesGraph->size(); graphIter++)
		{
			if(routesGraph->at(graphIter).townName == it->first->townName)
			{
				nextObject = routesGraph->at(graphIter);
			}
		}

		// Store route taken so far as a string.
		std::stringstream ss;
		ss << routeTaken;
		ss << nextObject.townName;
		std::string thisRouteTaken;
		ss >> thisRouteTaken;

		// Format the route string into the format required for the checkDistance function
		std::stringstream routeStringStream;
		for(int stringSize = 0; stringSize < thisRouteTaken.size(); stringSize++)
		{
			routeStringStream << thisRouteTaken.at(stringSize);
			if(stringSize != stringSize -1)
			{
				routeStringStream << "-";
			}
		}
		std::string routeString;
		routeStringStream >> routeString;

		// Update the stops taken or distance/duration count.
		if(operatingMode == DISTANCE_CHECK_MODE || operatingMode == DIFFERENT_ROUTES_MODE || operatingMode == DURATION_CHECK_MODE ||
		(operatingMode == DURATION_CHECK_MODE + EXACT_STOPS_ONLY_MODE) ||
		(operatingMode == QUICKEST_ROUTE_MODE))
		{
			stopsOrDistance = checkDistanceOrDuration(routesGraph, routeString, operatingMode);
		}
		else
		{
			// Stops taken is the string size -1 since start town doesnt count.
			stopsOrDistance = thisRouteTaken.size() - 1;
		}

		// Check if we have reached our limit, for DIFFERENT_ROUTES_MODE this must be less than
		if((operatingMode == DIFFERENT_ROUTES_MODE && (stopsOrDistance < maxStopsOrDuration)) || 
		(operatingMode != DIFFERENT_ROUTES_MODE && (stopsOrDistance <= maxStopsOrDuration)))
		{
			// Is this the end town and are we waiting for a specific number of stops?
			// Each operating mode is checked.
			if((operatingMode == DURATION_CHECK_MODE + EXACT_STOPS_ONLY_MODE && stopsOrDistance == maxStopsOrDuration && nextObject.townName == *endTown) ||
			(operatingMode == DURATION_CHECK_MODE && nextObject.townName == *endTown) ||
			(operatingMode == MAX_STOPS_MODE && nextObject.townName == *endTown) ||
			(operatingMode == EXACT_STOPS_ONLY_MODE && (nextObject.townName == *endTown) && (stopsOrDistance == maxStopsOrDuration)) ||
			(operatingMode == SHORTEST_TRIP_MODE && (nextObject.townName == *endTown)) ||
			(operatingMode == DIFFERENT_ROUTES_MODE && nextObject.townName == *endTown) ||
			(operatingMode == QUICKEST_ROUTE_MODE && nextObject.townName == *endTown))
			{
				// Increment the counter
				returnValue++;
				
				// Get the route distance and add this to the routeDistances container
				int distanceTravelled = checkDistanceOrDuration(routesGraph, routeString, false);
				std::pair<std::string, int> p1(thisRouteTaken, distanceTravelled);
				routeDistances.insert(p1);

				// Duration mode, call the function again since we have not hit the limit.
				if(operatingMode == DURATION_CHECK_MODE || (operatingMode == DIFFERENT_ROUTES_MODE) || (operatingMode == DURATION_CHECK_MODE + EXACT_STOPS_ONLY_MODE) ||
				(operatingMode == QUICKEST_ROUTE_MODE))
				{
					returnValue += traverseThisRoute(routesGraph, nextObject.connections, endTown, maxStopsOrDuration, thisRouteTaken, routeDistances, operatingMode);
				}
				else if (operatingMode == SHORTEST_TRIP_MODE && (nextObject.townName == *endTown))
				{
					// Shortest trip mode, ignore max trips count and exit
					exit = true;
				}
			}
			else if(nextObject.connections.size() >= 1)
            		{
				// Continue to traverse the children
				returnValue += traverseThisRoute(routesGraph, nextObject.connections, endTown, maxStopsOrDuration, thisRouteTaken, routeDistances, operatingMode);
			}
		}
		else
		{
			// End loop
			exit = true;
		}
	}
	return returnValue;
}
