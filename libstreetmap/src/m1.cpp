#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <structure.h>
#define PI 3.14159265358979323846264338327950288419716939937

string city;
//load the map
vector<unsigned>* intersections_segments;
//initialize dataStructureSingleton pointer
dataStructureSingleton* dataStructureSingleton::dataStructure = NULL;

bool load_map(std::string map_name) {

    bool load_success = loadStreetsDatabaseBIN(map_name);

    string name;
    if (map_name == "/cad2/ece297s/public/maps/toronto.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/toronto.osm.bin");
        city = "Toronto";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/cairo_egypt.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/cairo_egypt.osm.bin");
        city = "Cairo";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/hamilton_canada.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/hamilton_canada.osm.bin");
        city = "Hamilton";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/moscow.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/moscow.osm.bin");
        city = "Moscow";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/newyork.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/newyork.osm.bin");
        city = "New York";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/saint_helena.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/saint_helena.osm.bin");
        city = "Saint Helena";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/toronto_canada.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/toronto_canada.osm.bin");
        city = "Toronto Canada";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else if (map_name == "/cad2/ece297s/public/maps/london_england.streets.bin") {
        loadOSMDatabaseBIN("/cad2/ece297s/public/maps/london_england.osm.bin");
        city = "London";
        //initialize the global vector
        IntersectionNodeInitialization();
    } else {
        cout << "Wrong map!";
    }
    //    // create any data structures here to speed up your API functions
    unsigned number_of_intersections;
    number_of_intersections = getNumberOfIntersections();

    dataStructureSingleton::dataStructures(); // load data structure
    intersections_segments = new vector<unsigned> [number_of_intersections];
    for (unsigned i = 0; i < number_of_intersections; i++)
        intersections_segments[i] = dataStructureSingleton::dataStructures()->findIntersectionStreetSeg(i);
    return load_success;
}

//close the map

void close_map() {
    //delete the dynamic array, set pointer to NULL
    delete [] intersections_segments;
    intersections_segments = NULL;
    //call the destructor in dataStructureSingleton class
    dataStructureSingleton::dataStructures()->deleteStruc();

    //close both databases
    closeStreetDatabase();
    closeOSMDatabase();

}

//implement the rest of the functions provided in m1.h
// ...


//function to return street id(s) for a street name
//return a 0-length vector if no street with this name exists.

//using structure StNameToID_instance (Done)

std::vector<unsigned> find_street_ids_from_name(std::string street_name) {
    return dataStructureSingleton::dataStructures()->findStreetIDFromName(street_name);
}

std::vector<unsigned> find_intersection_street_segments(unsigned intersection_id) {
    //return dataStructureSingleton::dataStructures()->findIntersectionStreetSeg(intersection_id);
    return intersections_segments[intersection_id];
}

std::vector<std::string> find_intersection_street_names(unsigned intersection_id) {
    std::vector<std::string> streetNamesVec;

    //use the previous function to find out all the intersected street IDs
    std::vector<unsigned> streetSegIDVec;
    streetSegIDVec = find_intersection_street_segments(intersection_id);

    //use a for loop with iterator to go through the streetSegIDVec and store
    //their names in a streetNamesVector
    for (std::vector<unsigned>::iterator strSegIDItr = streetSegIDVec.begin();
            strSegIDItr != streetSegIDVec.end();
            strSegIDItr++) {
        StreetSegmentInfo tempStreetSegInfo = getStreetSegmentInfo(*strSegIDItr);
        unsigned tempStreetID = tempStreetSegInfo.streetID;
        streetNamesVec.push_back(getStreetName(tempStreetID));
    }

    return streetNamesVec;
}

bool are_directly_connected(unsigned intersection_id1, unsigned intersection_id2) {
    if (intersection_id1 == intersection_id2)
        return true;

    std::vector<unsigned> streetSegIDVec1 = find_intersection_street_segments(intersection_id1);
    std::vector<unsigned> streetSegIDVec2 = find_intersection_street_segments(intersection_id2);

    //declare a vector of street segment IDs (to store common segments IDs) and 
    //its iterator
    std::vector<unsigned> commonStreetSegIDVec(10);
    std::vector<unsigned>::iterator commonStreetSegIt;
    commonStreetSegIt = std::set_intersection(streetSegIDVec1.begin(), streetSegIDVec1.end(),
            streetSegIDVec2.begin(), streetSegIDVec2.end(), commonStreetSegIDVec.begin());
    commonStreetSegIDVec.resize(commonStreetSegIt - commonStreetSegIDVec.begin());

    //the commonStreetSegIDVec is empty if those two intersection doesn't have any 
    //street segment in common
    if (commonStreetSegIDVec.size() == 0)
        return false;

    for (commonStreetSegIt = commonStreetSegIDVec.begin();
            commonStreetSegIt != commonStreetSegIDVec.end();
            commonStreetSegIt++) {
        StreetSegmentInfo tempStreetSegInfo = getStreetSegmentInfo(*commonStreetSegIt);
        //if the vector is not empty and the segment is not one way, those two
        //intersections are directly connected
        if (!tempStreetSegInfo.oneWay)
            return true;
        //else check if it is the right way
        if (tempStreetSegInfo.from == intersection_id1
                && tempStreetSegInfo.to == intersection_id2)
            return true;
    }
    return false;
}




//Using structure Intersection_HashTable

std::vector<unsigned> find_adjacent_intersections(unsigned intersection_id) {
    return dataStructureSingleton::dataStructures()->getAllAdjacentIntersections(intersection_id);
}


//Using structure StreetIDStruct_HashTable 

std::vector<unsigned> find_street_street_segments(unsigned street_id) {
    return dataStructureSingleton::dataStructures()->getAllStreetSegForStreet(street_id);
}


//Using structure StreetIDStruct_HashTable

std::vector<unsigned> find_all_street_intersections(unsigned street_id) {
    return dataStructureSingleton::dataStructures()->getStreetIntersectionsVector(street_id);
}


//Doesn't use any structure

std::vector<unsigned> find_intersection_ids_from_street_names(std::string street_name1, std::string street_name2) {


    std::vector<unsigned> intersectionIDs1 = dataStructureSingleton::dataStructures() ->getStreetNameIntersectionsVector(street_name1);
    std::vector<unsigned> intersectionIDs2 = dataStructureSingleton::dataStructures() ->getStreetNameIntersectionsVector(street_name2);

    return find_same_intersections(intersectionIDs1, intersectionIDs2);

}





//get the longitude and latitude of two points
//transfer (lon, lat) into (x,y)
//d = R * sqrt((y2 - y1)^2 + (x2 - x1)^2)
//return the result
//Doesn't use any structure

double find_distance_between_two_points(LatLon point1, LatLon point2) {
    //initialize variables
    double distance = 0;
    double lon1, lat1, lon2, lat2, p1x, p1y, p2x, p2y, latavg;

    //convert the decimal degrees to radians
    lon1 = (double) point1.lon / 180 * PI;
    lon2 = (double) point2.lon / 180 * PI;
    lat1 = (double) point1.lat / 180 * PI;
    lat2 = (double) point2.lat / 180 * PI;
    latavg = (lat1 + lat2) / 2;

    //transfer the points from Lat Lon domain into X Y domain
    p1x = lon1 * cos(latavg);
    p1y = lat1;
    p2x = lon2 * cos(latavg);
    p2y = lat2;

    //use the equation to find out the distance between two points
    distance = EARTH_RADIUS_IN_METERS * sqrt((p2y - p1y)*(p2y - p1y) + (p2x - p1x)*(p2x - p1x));
    return distance;
}

//check the number of curve points of input street segment
//if 1 => use find_distance_between_two_points directly
//else => figure out the distance between each connected curve points and add the distance up

double find_street_segment_length(unsigned street_segment_id) {
    //initialize the current street
    StreetSegmentInfo current_street = getStreetSegmentInfo(street_segment_id);

    //initialize the starting point and ending point
    LatLon onset = getIntersectionPosition(current_street.from);
    LatLon offset = getIntersectionPosition(current_street.to);

    //initialize the length of current street segment
    double length = 0;

    //no curve point
    //just calculate the distance between starting point and ending point
    if (current_street.curvePointCount == 0) {

        length = find_distance_between_two_points(onset, offset);

    } else if (current_street.curvePointCount == 1) {

        LatLon current_curve_point = getStreetSegmentCurvePoint(street_segment_id, 0);
        length = find_distance_between_two_points(onset, current_curve_point) + find_distance_between_two_points(current_curve_point, offset);

    } else {//a loop to add up every parts length

        LatLon last_curve_point = getStreetSegmentCurvePoint(street_segment_id, current_street.curvePointCount - 1);
        LatLon current_curve_point = getStreetSegmentCurvePoint(street_segment_id, 0);
        length = find_distance_between_two_points(onset, current_curve_point) + find_distance_between_two_points(last_curve_point, offset);

        for (unsigned i = 0, j = 1; i < current_street.curvePointCount - 1; i++, j++) {
            length += find_distance_between_two_points(getStreetSegmentCurvePoint(street_segment_id, i), getStreetSegmentCurvePoint(street_segment_id, j));
        }

        //don't delete the following code

    }
    //jump out of loop && finish calculation
    return length;
}

//check the number of segment of the street
//figure out the distance between each street segments and add the distance up

double find_street_length(unsigned street_id) {

    //find all intersection of this street
    std::vector<unsigned> street_segment_id = find_street_street_segments(street_id);

    //initialize the length of the street
    double length = 0;

    //a loop to calculate the length of the street
    for (std::vector<unsigned>::size_type idx = 0; idx < street_segment_id.size(); idx++) {
        length += find_street_segment_length(*(street_segment_id.begin() + idx));
    }

    return length;
}

// time = distance / speed

double find_street_segment_travel_time(unsigned street_segment_id) {

    //figure out the street segment info first
    StreetSegmentInfo current_street = getStreetSegmentInfo(street_segment_id);

    //find the street_segment_length first
    double length = find_street_segment_length(street_segment_id);

    //T = X / V
    double time = length / (double) current_street.speedLimit * 60.0 / 1000.0;

    return time;
}


//algorithm to get the closest point of interest with O(n)

unsigned find_closest_point_of_interest(LatLon my_position) {

    //initialize the beginning ID
    unsigned closestPointOfInterestID = 0;
    int size = 100;

    //set the initial value of closestDis to a arbitrary large number   
    double closestDis = 10000;
    unsigned num_POI = getNumberOfPointsOfInterest();

    //doesn't use 2d array for city with less than 50 points of interests
    if (num_POI <= 50) {
        //go through all the POI IDs to find out the ones with smallest difference
        //in LatLon
        for (unsigned pointOfInterestID = 0; pointOfInterestID < num_POI; pointOfInterestID++) {

            //create the tempo position as a potential position
            LatLon potential_position = getPointOfInterestPosition(pointOfInterestID);

            //store the distance between my position and the current point of interest
            double curDis = find_distance_between_two_points(my_position, potential_position);

            //if it is smaller than the closestDis so far, replace it
            //what the result that I am at a point of interest
            if (curDis < closestDis) {
                closestPointOfInterestID = pointOfInterestID;
                closestDis = curDis;
            }
        }

        return closestPointOfInterestID;
    } else {
        t_point my_position_xy = to_xycoordinate(my_position);

        //extract all the necessary information from the initial frame
        double left = (double) dataStructureSingleton::dataStructures() ->initial_frame.left();
        double top = (double) dataStructureSingleton::dataStructures() ->initial_frame.top();
        double right = (double) dataStructureSingleton::dataStructures() ->initial_frame.right();
        double bottom = (double) dataStructureSingleton::dataStructures() ->initial_frame.bottom();

        double x_interval = abs(right - left + 1) / size;
        double y_interval = abs(top - bottom + 1) / size;

        //find out the interval the my_position is in xy coordinates
        double draft_x_value = (abs(my_position_xy.x - left) / x_interval);
        int x_value = (int) floor(draft_x_value);
        double draft_y_value = (abs(top - my_position_xy.y) / y_interval);
        int y_value = (int) floor(draft_y_value);

        cout << "current x y is " << x_value << " " << y_value << endl;

        //go through the nine intervals surrounding my_position
        pair<double, unsigned> closest_pair(1000000, 0);
        bool found = false;

        int incre_x = 1;
        int incre_y = 1;


        if (x_value > (size - 1))
            x_value = size - 1;
        if (y_value > (size - 1))
            y_value = size - 1;
        //cout<<"the target is "<<x_value<<" "<<y_value<<endl;

        while (!found) {
            //first look at the grid the target is at
            pair<double, unsigned> inter_0 = find_closest_POI_one_interval(my_position, x_value, y_value);
            if (closest_pair > inter_0) {
                closest_pair = inter_0;
                found = true;
            }

            //look at the line on the top
            for (int incr_x_idx = -incre_x + 1; incr_x_idx < incre_x; incr_x_idx++) {
                if (((x_value + incr_x_idx) >= 0)&&((x_value + incr_x_idx) <= (size - 1)&&(y_value - incre_y) >= 0)&&((y_value + incre_y) <= (size - 1))) {
                    pair<double, unsigned> inter_1 = find_closest_POI_one_interval(my_position, x_value + incr_x_idx, y_value + incre_y);
                    if (closest_pair > inter_1) {
                        closest_pair = inter_1;
                        found = true;
                    }
                }
            }

            //look at the line at the bottom
            for (int incr_x_idx = -incre_x + 1; incr_x_idx < incre_x; incr_x_idx++) {
                if (((x_value + incr_x_idx) >= 0)&&((x_value + incr_x_idx) <= (size - 1)&&(y_value - incre_y) >= 0)&&((y_value + incre_y) <= (size - 1))) {
                    pair<double, unsigned> inter_1 = find_closest_POI_one_interval(my_position, x_value + incr_x_idx, y_value - incre_y);
                    if (closest_pair > inter_1) {
                        closest_pair = inter_1;
                        found = true;
                    }
                }
            }

            //look at the line on the left
            for (int incr_y_idx = -incre_y + 1; incr_y_idx < incre_y; incr_y_idx++) {
                if (((x_value - incre_x) >= 0)&&((x_value + incre_x) <= (size - 1)&&(y_value + incr_y_idx) >= 0)&&((y_value + incr_y_idx) <= (size - 1))) {
                    pair<double, unsigned> inter_1 = find_closest_POI_one_interval(my_position, x_value + incre_x, y_value + incr_y_idx);
                    if (closest_pair > inter_1) {
                        closest_pair = inter_1;
                        found = true;
                    }
                }
            }

            //look at the line on the right
            for (int incr_y_idx = -incre_y + 1; incr_y_idx < incre_y; incr_y_idx++) {
                if (((x_value - incre_x) >= 0)&&((x_value + incre_x) <= (size - 1)&&(y_value + incr_y_idx) >= 0)&&((y_value + incr_y_idx) <= (size - 1))) {
                    pair<double, unsigned> inter_1 = find_closest_POI_one_interval(my_position, x_value - incre_x, y_value + incr_y_idx);
                    if (closest_pair > inter_1) {
                        closest_pair = inter_1;
                        found = true;
                    }
                }
            }

            //look at the four corners

            if ((x_value + incre_x) <= (size - 1)&&((y_value + incre_y) <= (size - 1))) {
                pair<double, unsigned> inter_2 = find_closest_POI_one_interval(my_position, x_value + incre_x, y_value + incre_y);
                if (closest_pair > inter_2) {
                    closest_pair = inter_2;
                    found = true;
                }
            }

            if (((x_value - incre_x) >= 0)&&((y_value + incre_y) <= (size - 1))) {
                pair<double, unsigned> inter_3 = find_closest_POI_one_interval(my_position, x_value - incre_x, y_value + incre_y);
                if (closest_pair > inter_3) {
                    closest_pair = inter_3;
                    found = true;
                }
            }

            if (((x_value + incre_x) <= (size - 1)&&(y_value + incre_y) >= 0)) {
                pair<double, unsigned> inter_4 = find_closest_POI_one_interval(my_position, x_value + incre_x, y_value - incre_y);
                if (closest_pair > inter_4) {
                    closest_pair = inter_4;
                    found = true;
                }
            }

            if (((x_value - incre_x) >= 0)&&(y_value + incre_y) >= 0) {
                pair<double, unsigned> inter_5 = find_closest_POI_one_interval(my_position, x_value - incre_x, y_value - incre_y);
                if (closest_pair > inter_5) {
                    closest_pair = inter_5;
                    found = true;
                }
            }
            incre_x++;
            incre_y++;
        }
        return closest_pair.second;

    }
}

//helper function to find the closestPointOfInterestID and its distance to my_position in one interval

pair<double, unsigned> find_closest_POI_one_interval(LatLon my_position, int x_value, int y_value) {
    //cout<<"value passed into the helper function is "<<x_value<<" "<<y_value<<endl;
    unsigned int num_POI = dataStructureSingleton::dataStructures()->POI_2d_array[x_value][y_value].size();
    double closestDis = 1000000;
    unsigned closestPointOfInterestID = 0;
    for (unsigned checked_POI = 0; checked_POI < num_POI; checked_POI++) {

        //create the tempo position as a potential position
        LatLon potential_position = dataStructureSingleton::dataStructures()->POI_2d_array[x_value][y_value][checked_POI].position;

        //store the distance between my position and the current point of interest
        double curDis = find_distance_between_two_points(my_position, potential_position);

        //if it is smaller than the closestDis so far, replace it
        //what the result that I am at a point of interest
        if (curDis < closestDis) {
            closestPointOfInterestID = dataStructureSingleton::dataStructures()->POI_2d_array[x_value][y_value][checked_POI].POIID;
            closestDis = curDis;
        }
    }
    return pair<double, unsigned> (closestDis, closestPointOfInterestID);
}

//algorithm to get the closest intersection with O(n)

unsigned find_closest_intersection(LatLon my_position) {

    //initialize the intersection id
    unsigned closest_intersection_id = 0;

    //initialize the distance with a large number
    double distance = 99999;

    //to get the number of intersection
    unsigned NumOfInt = getNumberOfIntersections();

    //the average latitude
    double convert_factor = PI / 180.0;


    double my_x = my_position.lon * convert_factor * cos_factor;
    double my_y = my_position.lat * convert_factor;

    //compare the distance between each other section and the target section
    for (unsigned intersection_id = 0; intersection_id < NumOfInt; intersection_id++) {

        //temporary position and distance
        LatLon potential_position = getIntersectionPosition(intersection_id);
        //double tempo_distance = find_distance_between_two_points(my_position, potential_position);

        double _x = potential_position.lon * convert_factor * cos_factor;
        double _y = potential_position.lat * convert_factor;



        double current_distance = pow(_x - my_x, 2) + pow(_y - my_y, 2);
        //compare the distance
        //What is the result that I am in an intersection?
        if (current_distance < distance) {
            distance = current_distance;
            closest_intersection_id = intersection_id;
        }
            }

    //jump out of the loop && return the intersection id
    return closest_intersection_id;
}

pair<double, unsigned> find_closest_Intersection_one_interval(LatLon my_position, int x_value, int y_value) {
    //cout<<"value passed into the helper function is "<<x_value<<" "<<y_value<<endl;
    unsigned int num_inter = dataStructureSingleton::dataStructures()->Inter_2d_array[x_value][y_value].size();
    double closestDis = 1000000;
    unsigned closestIntersecID = 0;
    for (unsigned checked_inter = 0; checked_inter < num_inter; checked_inter++) {

        //create the tempo position as a potential position
        unsigned current_id = dataStructureSingleton::dataStructures()->Inter_2d_array[x_value][y_value][checked_inter];
        LatLon potential_position = getIntersectionPosition(current_id);

        //store the distance between my position and the current point of interest
        double curDis = find_distance_between_two_points(my_position, potential_position);

        //if it is smaller than the closestDis so far, replace it
        //what the result that I am at a point of interest
        if (curDis < closestDis) {
            closestIntersecID = dataStructureSingleton::dataStructures()->Inter_2d_array[x_value][y_value][checked_inter];
            closestDis = curDis;
        }
    }
    return pair<double, unsigned> (closestDis, closestIntersecID);
}

//finds common values to two vectors 
//returns a vector containing all common values
//e.g. same intersections

std::vector<unsigned> find_same_intersections(std::vector<unsigned> & intersections1,
        std::vector<unsigned> & intersections2) {

    std::vector<unsigned> sameIntersections; // vector to store all intersections
    //sort vectors
    std::sort(intersections1.begin(), intersections1.end());
    std::sort(intersections2.begin(), intersections2.end());
    //gets common vales
    std::set_intersection(intersections1.begin(), intersections1.end(),
            intersections2.begin(), intersections2.end(),
            std::back_inserter(sameIntersections));
    return sameIntersections;
}

