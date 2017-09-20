/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <readline/readline.h>
#include <readline/history.h>
#include "m3.h"


vector<InterInfo> IntersectionNode;
int visited = 0;

void load_milestone3() {
    string map_name;
    bool run = 1;
    while (run) {
        cout << "Please enter the map you want to load: (type list to show all maps)" << endl;
        cin >> map_name;
        getchar();
        cout << endl;
        if (map_name == "toronto") {
            cout << "Loading the map of Toronto" << endl << endl;
            load_map("/cad2/ece297s/public/maps/toronto.streets.bin");
            //IntersectionNodeInitialization();
            cout << dataStructureSingleton::dataStructures()->findPOIIDFromName("Tim Hortons").size();
            draw_map();
            close_map();
        } else if (map_name == "cairo") {
            cout << "Loading the map of Cairo" << endl << endl;
            load_map("/cad2/ece297s/public/maps/cairo_egypt.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "hamilton") {
            cout << "Loading the map of Hamilton" << endl << endl;
            load_map("/cad2/ece297s/public/maps/hamilton_canada.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "moscow") {
            cout << "Loading the map of Moscow" << endl << endl;
            load_map("/cad2/ece297s/public/maps/moscow.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "newyork") {
            cout << "Loading the map of New York" << endl << endl;
            load_map("/cad2/ece297s/public/maps/newyork.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "saint_helena") {
            cout << "Loading the map of Saint Helena" << endl << endl;
            load_map("/cad2/ece297s/public/maps/saint_helena.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "toronto_canada") {
            cout << "Loading the map of Toronto, Canada" << endl << endl;
            load_map("/cad2/ece297s/public/maps/toronto_canada.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "london") {
            cout << "Loading the map of London" << endl << endl;
            load_map("/cad2/ece297s/public/maps/london_england.streets.bin");
            //IntersectionNodeInitialization();
            draw_map();
            close_map();
        } else if (map_name == "list") {
            cout << "Type in one of the following to load map: " << endl;
            cout << "toronto, cairo, hamilton, moscow, newyork, saint_helena, toronto_canada, london" << endl << endl;
        } else {
            cout << "Wrong map!" << endl;
            cout << ">>Continue to load another map? y/n" << endl;
            string yn;
            getline(cin, yn);
            if (yn == "y") run = true;
            else if (yn == "n") run = false;

        }
    }
}

//this function works for initializing the global InterInfo vector

void IntersectionNodeInitialization() {
    unsigned IntNUM = getNumberOfIntersections();

    for (unsigned IntIDX = 0; IntIDX < IntNUM; IntIDX++) {
        InterInfo currentInt(IntIDX, -2, -2, -1, 0, 0);
        IntersectionNode.push_back(currentInt);
    }

}

//help function to find last Intersection

unsigned GetLastIntID(StreetSegmentInfo seginfo, unsigned currentID) {
    if (seginfo.from == currentID) {
        return seginfo.to;
    } else {
        return seginfo.from;
    }
}

//Dijsktra shortest path algorithm

bool bfsPath(int startID, int destID) {

    //increment visted 
    visited++;
    //initialize the travel time 
    double time = 0;

    //set the initial intersection's information
    IntersectionNode[startID].travelTime = 0;
    IntersectionNode[startID].lastSeg = -1;
    IntersectionNode[startID].lastStreet = -1;
    IntersectionNode[startID].visitedTime = visited;

    //temporary heap to store dealing information
    vector <InterSec> tempoList;
    make_heap(tempoList.begin(), tempoList.end(), &timeComparator);

    //start from the start point
    tempoList.push_back(InterSec(startID, -1, 0));
    push_heap(tempoList.begin(), tempoList.end(), &timeComparator);

    //found to see whether the 
    bool found = false;

    //initialize current street and previous street
    int prevSt = -1;
    int currSt = -1;

    //if the list is not empty, run the loop
    while (!tempoList.empty()) {

        pop_heap(tempoList.begin(), tempoList.end(), &timeComparator);
        InterSec curr = tempoList.back();
        tempoList.pop_back();


        if (curr.IntSecID == destID) {
            found = true;
            return found;
        }

        prevSt = IntersectionNode[curr.IntSecID].lastStreet;
        vector<unsigned> adjacent_segs = find_intersection_street_segments(curr.IntSecID);
        for (auto i = 0; i < adjacent_segs.size(); i++) {
            //CHECK IF CURRENT NODE FROM WAVEFRONT TAKES LESS TIME TO REACH THAN ORIGINAL TIME !!!!!!!!!!!!!!!!!!!!!!

            //get the information of this street_seg
            StreetSegmentInfo current_seg = getStreetSegmentInfo(adjacent_segs[i]);

            int tempo_intID = -1;

            if (selectSeg(current_seg, curr, tempo_intID)) {
                //find current street ID 
                currSt = current_seg.streetID;

                //figure out current segment's travel time
                //find_street_segment_travel_time returns minutes then transfer it to seconds
                double tempo_time = find_street_segment_travel_time(adjacent_segs[i]) * 60;

                //if the it's not the start point or street are not the same 
                //there will be 15 seconds penalty 
                if ((prevSt != -1)&&(prevSt != currSt)) {
                    tempo_time += 15;
                }

                //current time 
                time = IntersectionNode[curr.IntSecID].travelTime + tempo_time;

                double distance = find_distance_between_two_intersection(tempo_intID, destID);
                double estimatedTime = distance / 25.0;
                double weight = estimatedTime + time;

                if (IntersectionNode[tempo_intID].visitedTime < visited) {
                    IntersectionNode[tempo_intID].visitedTime = visited;
                    IntersectionNode[tempo_intID].travelTime = time;
                    IntersectionNode[tempo_intID].lastSeg = adjacent_segs[i];
                    IntersectionNode[tempo_intID].lastStreet = currSt;
                    IntersectionNode[tempo_intID].weightedTime = weight;

                    //push_back the tempoID
                    tempoList.push_back(InterSec(tempo_intID, adjacent_segs[i], weight));
                    push_heap(tempoList.begin(), tempoList.end(), &timeComparator);
                } else if (IntersectionNode[tempo_intID].visitedTime == visited) {
                    //if (IntersectionNode[tempo_intID].travelTime > time) {
                    if ((IntersectionNode[tempo_intID].weightedTime > weight)&&(IntersectionNode[tempo_intID].travelTime > time)) {
                        IntersectionNode[tempo_intID].travelTime = time;
                        IntersectionNode[tempo_intID].lastSeg = adjacent_segs[i];
                        IntersectionNode[tempo_intID].lastStreet = currSt;
                        IntersectionNode[tempo_intID].weightedTime = weight;

                        //push_back the tempoID
                        tempoList.push_back(InterSec(tempo_intID, adjacent_segs[i], weight));
                        push_heap(tempoList.begin(), tempoList.end(), &timeComparator);
                    }
                }
            }
        }
    }
    //searching the entire map and return the result
    return found;
}

bool selectSeg(StreetSegmentInfo current_seg, InterSec curr, int &tempo_intID) {

    if (!current_seg.oneWay) {
        if (current_seg.from != curr.IntSecID) {
            tempo_intID = current_seg.from;
        } else {
            tempo_intID = current_seg.to;
        }
        return true;
    } else {
        if (current_seg.from == curr.IntSecID) {
            tempo_intID = current_seg.to;
            return true;
        }
    }

    return false;

}

//helper function for minimum heap

bool timeComparator(InterSec first, InterSec second) {
    return first.WeightedTime > second.WeightedTime;
}

vector<unsigned> bfsTraceBack(unsigned destID) {
    vector<unsigned> SegIDs;
    unsigned tempoInt = destID;
    unsigned prevSeg = IntersectionNode[tempoInt].lastSeg;
    while (prevSeg != -1) {
        SegIDs.push_back(prevSeg);
        StreetSegmentInfo tempo_seg = getStreetSegmentInfo(prevSeg);
        tempoInt = GetLastIntID(tempo_seg, tempoInt);
        prevSeg = IntersectionNode[tempoInt].lastSeg;
    }
    vector<unsigned> target;
    unsigned IntNum = SegIDs.size();
    for (auto i = 0; i < IntNum; i++) {
        unsigned tempoID = SegIDs.back();
        SegIDs.pop_back();
        target.push_back(tempoID);
    }
    return target;
}

//a list of possible help command
vector<const char*> command_names = {
    "Button-Find", "Button-POIs", "Button-Library", "Button-Health", "Changing map", "Zooming"
};

vector<string> command_names_s = {
    "Button-Find", "Button-POIs", "Button-Library", "Button-Health", "Changing map", "Zooming"
};

std::vector<unsigned> find_path_between_intersections(unsigned
        intersect_id_start, unsigned intersect_id_end) {

    bool found = bfsPath(intersect_id_start, intersect_id_end);
    if (found) {
        return bfsTraceBack(intersect_id_end);
    } else {
        vector <unsigned> emptyVector;
        return (emptyVector);
    }

}

double compute_path_travel_time(const std::vector<unsigned>& path) {
    unsigned SegNum = path.size();
    double tempoTime = 0;
    double time = 0;
    unsigned currSt = 0;
    unsigned prevSt = 0;
    //if (!path.empty()) {
    for (unsigned i = 0; i < SegNum; i++) {
        StreetSegmentInfo current_seg = getStreetSegmentInfo(path[i]);
        if (i == 0) {
            tempoTime = find_street_segment_travel_time(path[i]);
            time += tempoTime;
            prevSt = current_seg.streetID;
        } else {
            currSt = current_seg.streetID;
            tempoTime = find_street_segment_travel_time(path[i]);
            if (currSt != prevSt) {
                tempoTime += 0.25;
            }
            time += tempoTime;
            prevSt = currSt;
        }
        //  }
    }
    return time;
}

vector<unsigned> find_closest_intersection_vector(vector<unsigned> POIIDs) {
    vector<unsigned> result;
    for (auto itr = POIIDs.begin(); itr != POIIDs.end(); itr++) {
        LatLon current_location = getPointOfInterestPosition(*itr);
        unsigned intersectionID = find_closest_intersection(current_location);
        //unsigned intersectionID = dataStructureSingleton::dataStructures()->cloeset_intersec[*itr];
        result.push_back(intersectionID);
    }
    return result;
}

vector<unsigned> find_path_to_point_of_interest(unsigned intersect_id_start, std::string point_of_interest_name) {

    vector<unsigned> POIIDs = dataStructureSingleton::dataStructures()->findPOIIDFromName(point_of_interest_name);

    vector<unsigned> intersection_ids = find_closest_intersection_vector(POIIDs);

    int lastIntID = -1;

    unsigned NumOfINT = POIIDs.size();

    //increment visted 
    visited++;
    //initialize the travel time 
    double time = 0;

    //set the initial intersection's information
    IntersectionNode[intersect_id_start].travelTime = 0;
    IntersectionNode[intersect_id_start].lastSeg = -1;
    IntersectionNode[intersect_id_start].lastStreet = -1;
    IntersectionNode[intersect_id_start].visitedTime = visited;

    //temporary heap to store dealing information
    vector <InterSec> tempoList;
    make_heap(tempoList.begin(), tempoList.end(), &timeComparator);

    //start from the start point
    tempoList.push_back(InterSec(intersect_id_start, -1, 0));
    push_heap(tempoList.begin(), tempoList.end(), &timeComparator);

    //found to see whether the 
    bool found = false;

    //initialize current street and previous street
    int prevSt = -1;
    int currSt = -1;

    //if the list is not empty, run the loop
    while (!tempoList.empty()) {

        pop_heap(tempoList.begin(), tempoList.end(), &timeComparator);
        InterSec curr = tempoList.back();
        tempoList.pop_back();
        unsigned idx;
        for (idx = 0; idx < NumOfINT; idx++) {
            if (curr.IntSecID == intersection_ids[idx]) {
                found = true;
                lastIntID = intersection_ids[idx];
                break;
            }
        }

        if (found) {
            LatLon poi_latlon = getPointOfInterestPosition(POIIDs[idx]);
            dataStructureSingleton::dataStructures()->second_LatLon_clicked = poi_latlon;
            break;
        } else {
            prevSt = IntersectionNode[curr.IntSecID].lastStreet;
            vector<unsigned> adjacent_segs = find_intersection_street_segments(curr.IntSecID);
            unsigned NumOfAdjacentSeg = adjacent_segs.size();
            for (unsigned i = 0; i < NumOfAdjacentSeg; i++) {
                //CHECK IF CURRENT NODE FROM WAVEFRONT TAKES LESS TIME TO REACH THAN ORIGINAL TIME !!!!!!!!!!!!!!!!!!!!!!

                //get the information of this street_seg
                StreetSegmentInfo current_seg = getStreetSegmentInfo(adjacent_segs[i]);

                int tempo_intID = -1;

                if (selectSeg(current_seg, curr, tempo_intID)) {
                    //find current street ID 
                    currSt = current_seg.streetID;

                    //figure out current segment's travel time
                    //find_street_segment_travel_time returns minutes then transfer it to seconds
                    double tempo_time = find_street_segment_travel_time(adjacent_segs[i]) * 60;

                    //if the it's not the start point or street are not the same 
                    //there will be 15 seconds penalty 
                    if ((prevSt != -1)&&(prevSt != currSt)) {
                        tempo_time += 15;
                    }

                    //current time 
                    time = IntersectionNode[curr.IntSecID].travelTime + tempo_time;
                    //
                    //                double distance = find_distance_between_two_intersection(tempo_intID, destID);
                    //                double estimatedTime = distance / 100.0;
                    //                double weight = estimatedTime + time;

                    if (IntersectionNode[tempo_intID].visitedTime < visited) {
                        IntersectionNode[tempo_intID].visitedTime = visited;
                        IntersectionNode[tempo_intID].travelTime = time;
                        IntersectionNode[tempo_intID].lastSeg = adjacent_segs[i];
                        IntersectionNode[tempo_intID].lastStreet = currSt;


                        //push_back the tempoID
                        tempoList.push_back(InterSec(tempo_intID, adjacent_segs[i], time));
                        push_heap(tempoList.begin(), tempoList.end(), &timeComparator);
                    } else if (IntersectionNode[tempo_intID].visitedTime == visited) {
                        if (IntersectionNode[tempo_intID].travelTime > time) {
                            //if ((IntersectionNode[tempo_intID].weightedTime > weight)&&(IntersectionNode[tempo_intID].travelTime > time)) {
                            IntersectionNode[tempo_intID].travelTime = time;
                            IntersectionNode[tempo_intID].lastSeg = adjacent_segs[i];
                            IntersectionNode[tempo_intID].lastStreet = currSt;
                            //IntersectionNode[tempo_intID].weightedTime = weight;

                            //push_back the tempoID
                            tempoList.push_back(InterSec(tempo_intID, adjacent_segs[i], time));
                            push_heap(tempoList.begin(), tempoList.end(), &timeComparator);
                        }
                    }
                }
            }
        }
    }
    //searching the entire map and return the result
    //return found;
    if (found) {
        vector<unsigned> SegIDs;
        unsigned tempoInt = lastIntID;
        unsigned prevSeg = IntersectionNode[tempoInt].lastSeg;
        while (prevSeg != -1) {
            SegIDs.push_back(prevSeg);
            StreetSegmentInfo tempo_seg = getStreetSegmentInfo(prevSeg);
            tempoInt = GetLastIntID(tempo_seg, tempoInt);
            prevSeg = IntersectionNode[tempoInt].lastSeg;
        }
        vector<unsigned> target;
        unsigned IntNum = SegIDs.size();
        for (auto i = 0; i < IntNum; i++) {
            unsigned tempoID = SegIDs.back();
            SegIDs.pop_back();
            target.push_back(tempoID);
        }
        return target;

    } else {
        vector <unsigned> emptyVector;
        return emptyVector;
    }

}

double find_distance_between_two_intersection(unsigned
        intersect_id_1, unsigned intersect_id_2) {
    LatLon latlon_intersec_1 = getIntersectionPosition(intersect_id_1);
    LatLon latlon_intersec_2 = getIntersectionPosition(intersect_id_2);
    return find_distance_between_two_points(latlon_intersec_1, latlon_intersec_2);
}

void act_on_find_button_func_m3(void (*drawscreen_ptr) (void)) {

    //Use tab for auto completion
    rl_bind_key('\t', rl_complete);
    //Use our function for auto-complete
    rl_attempted_completion_function = command_completion_street;
    //Tell readline to handle double and single quotes for us
    rl_completer_quote_characters = strdup("\"\'");


    char* street1_c;
    char* street2_c;
    cout << "Please enter first streets: " << endl;
    if ((street1_c = readline("> ")) != NULL) {
        if (strcmp(street1_c, "") != 0)
            add_history(street1_c); //Only add to history if user input not empty

        cout << "Please enter second streets: " << endl;
        if ((street2_c = readline("> ")) != NULL) {
            if (strcmp(street2_c, "") != 0)
                add_history(street2_c); //Only add to history if user input not empty
            cout << "Processing" << endl;


            //doesn't need extra space to parse the char array
            string street1 = parse_string(street1_c, true);
            string street2 = parse_string(street2_c, true);

            cout << street1.size();


            //target intersection_ids
            vector <unsigned> target_intersections;
            vector <unsigned> street1ID = find_street_ids_from_name(street1);
            vector <unsigned> street2ID = find_street_ids_from_name(street2);



            vector <unsigned> street1IntersectionID;
            vector <unsigned> street2IntersectionID;

            //store all intersection id in with name1 in a vector
            for (unsigned street_idx = 0; street_idx < street1ID.size(); street_idx++) {
                vector<unsigned> current_intersection_ID = find_all_street_intersections(street1ID[street_idx]);
                for (unsigned intersection_idx = 0; intersection_idx < current_intersection_ID.size(); intersection_idx++) {
                    street1IntersectionID.push_back(current_intersection_ID[intersection_idx]);
                }
            }

            //store all intersection id in with name2 in a vector
            for (unsigned street_idx = 0; street_idx < street2ID.size(); street_idx++) {
                vector<unsigned> current_intersection_ID = find_all_street_intersections(street2ID[street_idx]);
                for (unsigned intersection_idx = 0; intersection_idx < current_intersection_ID.size(); intersection_idx++) {
                    street2IntersectionID.push_back(current_intersection_ID[intersection_idx]);
                }
            }

            //compare is there any duplicate intersection 
            //if duplicated, these streets intersects at that intersection
            for (unsigned compare_idx1 = 0; compare_idx1 < street1IntersectionID.size(); compare_idx1++) {
                for (unsigned compare_idx2 = 0; compare_idx2 < street2IntersectionID.size(); compare_idx2++) {
                    if (street1IntersectionID[compare_idx1] == street2IntersectionID[compare_idx2]) {
                        target_intersections.push_back(street1IntersectionID[compare_idx1]);
                    }
                }
            }

            //check the target intersection vector and report information
            if (target_intersections.size() != 0) {
                cout << street1 << " and " << street2 << " intersects at: " << endl;
                for (unsigned report_idx = 0; report_idx < target_intersections.size(); report_idx++) {
                    string current_intersection_name = getIntersectionName(target_intersections[report_idx]);
                    cout << current_intersection_name << " ";
                }
                cout << endl;
            } else {
                cout << street1 << " and " << street2 << " never intersect!" << endl;
            }
            cout << endl;
            free(street1_c);
            free(street2_c);

        }
    }
}

string parse_string(const char* name_char, bool min_1) {
    int onset, offset;
    //check if the first character ' or ", jump 1 over if it is
    if ((name_char[0] == '\'') || (name_char[0] == '\"'))
        onset = 1;
    else
        onset = 0;
    //check if the second last character ' or ", over take the length index up to the last letter if so
    int length = strlen(name_char);
    if ((name_char[length - 2] == '\'') || (name_char[length - 2] == '\"'))
        offset = length - 3;
    else if (min_1)
        offset = length - 1;
    else offset = length;
    string name_string = string(name_char, onset, offset);

    return name_string;
}

void act_on_help_button_func(void (*drawscreen_ptr) (void)) {

    //Use tab for auto completion
    rl_bind_key('\t', rl_complete);
    //Use our function for auto-complete
    rl_attempted_completion_function = command_completion_command;
    //Tell readline to handle double and single quotes for us
    rl_completer_quote_characters = strdup("\"\'");

    string list = "list";

    char* command;
    bool exit = false;
    cout << "What kind of help do you need?" << endl;
    while (!exit) {

        command = readline("> ");
        if (strcmp(command, "") != 0)
            add_history(command); //Only add to history if user input not empty
        //need one extra space to parse the whole char array
        string command_str = parse_string(command, false);

        if (command_str == command_names_s[0]) {
            //when the user types in "Button-Find"
            cout << "Button-Find: " << endl;
            cout << "You can search for a intersection using this button" << endl;
            cout << "You will be asked to insert two street name to locate the intersection after pressing this button" << endl << endl;
        } else if (command_str == command_names_s[1]) {
            //when the user types in "Button-POIs"
            cout << "Button-POIs: " << endl;
            cout << "You can show all the point of interests on the map using this button" << endl;
            cout << "Icons: " << endl << "Green: financial institutions or ATMs" << endl;
            cout << "Purple: all types of restaurants" << endl;
            cout << "White: car services locations including gas station, car wash and parking" << endl;
            cout << "Plum (light purple): arts centers, museums and cinema" << endl;
            cout << "Magenta: schools (including kindergartens, language schools, colleges)" << endl << endl;
        } else if (command_str == command_names_s[2]) {
            //when the user types in "Button-Library"
            cout << "Button-Library: " << endl;
            cout << "You can show all the Libraries on the map using this button" << endl;
            cout << "To learn more about the location, try to click on it using your mouse!" << endl << endl;
        } else if (command_str == command_names_s[3]) {
            //when the user types in "Button-Health"
            cout << "Button-Health: " << endl;
            cout << "You can show all the hospitals and health centers on the map using this button" << endl;
            cout << "To learn more about the location, try to click on it using your mouse!" << endl << endl;
        } else if (command_str == command_names_s[4]) {
            //when the user types in "Changing map"
            cout << "Changing map" << endl;
            cout << "To show a map for another city, press the Proceed button on the right" << endl << endl;
            ;
        } else if (command_str == command_names_s[5]) {
            //when the user types in "Zooming"
            cout << "Zooming" << endl;
            cout << "There are four buttons on the right you can use to change the view" << endl;
            cout << "Zoom in: enlarge the view" << endl;
            cout << "Zoom out: shrink the view" << endl;
            cout << "Zoom fit: show the complete map" << endl;
            cout << "Window: choose an area on the map to fill the screen" << endl << endl;
        } else if (command_str == list) {
            //list all the possible commands
            for (unsigned idx = 0; idx < command_names_s.size(); idx++) {
                cout << command_names_s[idx] << endl;
            }
            cout << endl;
        } else {
            cout << "Command not found. Type \"list\" for displaying all the help commands" << endl << endl;
        }
        cout << ">>Still need other helps? y/n" << endl;
        string yn;
        getline(cin, yn);
        if (yn == "y") exit = false;
        else if (yn == "n") exit = true;

        //free the character array received to prevent memory leak
        free(command);

    }
}

//Called repeatedly for a given 'stem_text'. Each time it returns a potential
//match.  When there are no more matches it returns NULL.
//
//The 'state' variable is zero the first time it is called with a given
//'stem_text', and positive afterwards.

char* street_name_generator(const char* stem_text, int state) {
    //Static here means a variable's value persists across function invocations
    static int count;

    if (state == 0) {
        //We initialize the count the first time we are called
        //with this stem_text
        count = -1;
    }

    int text_len = strlen(stem_text);

    //Search through intersection_names until we find a match
    while (count < (int) (dataStructureSingleton::dataStructures()->street_names).size() - 1) {
        count++;
        if (strncmp((dataStructureSingleton::dataStructures()->street_names)[count], stem_text, text_len) == 0) {
            //Must return a duplicate, Readline will handle
            //freeing this string itself.
            return strdup((dataStructureSingleton::dataStructures()->street_names)[count]);
        }
    }

    //No more matches
    return NULL;
}


//Given the stem 'stem_text' perform auto completion. 
//It returns an array of strings that are potential completions
//
//Note:
// 'start' and 'end' denote the location of 'stem_text' in the global
// 'rl_line_buffer' variable which contains the users current input line.
// If you need more context information to determine how to complete 'stem_text'
// you could look at 'rl_line_buffer'.

char** command_completion_street(const char* stem_text, int start, int end) {
    char ** matches = NULL;

    if (start != 0) {
        //Only generate completions if stem_text' 
        //is not the first thing in the buffer
        matches = rl_completion_matches(stem_text, street_name_generator);
    }

    return matches;
}


//Called repeatedly for a given 'stem_text'. Each time it returns a potential
//match.  When there are no more matches it returns NULL.
//
//The 'state' variable is zero the first time it is called with a given
//'stem_text', and positive afterwards.

char* POI_name_generator(const char* stem_text, int state) {
    //Static here means a variable's value persists across function invocations
    static int count;

    if (state == 0) {
        //We initialize the count the first time we are called
        //with this stem_text
        count = -1;
    }

    int text_len = strlen(stem_text);

    //Search through intersection_names until we find a match
    while (count < (int) (dataStructureSingleton::dataStructures()->POI_names).size() - 1) {
        count++;
        if (strncmp((dataStructureSingleton::dataStructures()->POI_names)[count], stem_text, text_len) == 0) {
            //Must return a duplicate, Readline will handle
            //freeing this string itself.
            return strdup((dataStructureSingleton::dataStructures()->POI_names)[count]);
        }
    }

    //No more matches
    return NULL;
}


//Given the stem 'stem_text' perform auto completion. 
//It returns an array of strings that are potential completions
//
//Note:
// 'start' and 'end' denote the location of 'stem_text' in the global
// 'rl_line_buffer' variable which contains the users current input line.
// If you need more context information to determine how to complete 'stem_text'
// you could look at 'rl_line_buffer'.

char** command_completion_POI(const char* stem_text, int start, int end) {
    char ** matches = NULL;

    if (start != 0) {
        //Only generate completions if stem_text' 
        //is not the first thing in the buffer
        matches = rl_completion_matches(stem_text, POI_name_generator);
    }

    return matches;
}

//Called repeatedly for a given 'stem_text'. Each time it returns a potential
//match.  When there are no more matches it returns NULL.
//
//The 'state' variable is zero the first time it is called with a given
//'stem_text', and positive afterwards.

char* command_name_generator(const char* stem_text, int state) {
    //Static here means a variable's value persists across function invocations
    static int count;

    if (state == 0) {
        //We initialize the count the first time we are called
        //with this stem_text
        count = -1;
    }

    int text_len = strlen(stem_text);

    //Search through intersection_names until we find a match
    while (count < (int) command_names.size() - 1) {
        count++;

        if (strncmp(command_names[count], stem_text, text_len) == 0) {
            //Must return a duplicate, Readline will handle
            //freeing this string itself.
            return strdup(command_names[count]);
        }
    }

    //No more matches
    return NULL;
}


//Given the stem 'stem_text' perform auto completion. 
//It returns an array of strings that are potential completions
//
//Note:
// 'start' and 'end' denote the location of 'stem_text' in the global
// 'rl_line_buffer' variable which contains the users current input line.
// If you need more context information to determine how to complete 'stem_text'
// you could look at 'rl_line_buffer'.

char** command_completion_command(const char* stem_text, int start, int end) {
    char ** matches = NULL;

    if (start != 0) {
        //Only generate completions if stem_text' 
        //is not the first thing in the buffer
        matches = rl_completion_matches(stem_text, command_name_generator);
    }

    return matches;
}

void act_on_travel_points_button_func(void (*drawscreen_ptr) (void)) {

    string command, mode, street1, street2, street3, street4, POIName;
    int target1 = -1, target2 = -1;
    vector<unsigned> tempoInt1, tempoInt2;

    cout << "What kind of path would you like? " << endl;
    cout << "Enter 'I' to find a path from an intersection to another intersection" << endl;
    cout << "Enter 'P' to find a path from an intersection to a point of interests" << endl;

    cin >> command;
    getchar();

    if (command == "I") {
        cout << "Click(C) or Type(T)?" << endl;
        cin >> mode;
        getchar();

        if (mode == "C") {
            cout << "Click two intersections on the map to get travel paths" << endl;
            dataStructureSingleton::dataStructures()->get_travel_points_from_map_clicks = true;
        } else if (mode == "T") {

            //Use tab for auto completion
            rl_bind_key('\t', rl_complete);
            //Use our function for auto-complete
            rl_attempted_completion_function = command_completion_street;
            //Tell readline to handle double and single quotes for us
            rl_completer_quote_characters = strdup("\"\'");


            bool valid = false;
            while (!valid) {
                cout << "Please insert the two streets for the first intersection: " << endl;
                cout << "Type the first street please:" << endl;
                char* street1_r = readline("> ");
                if (strcmp(street1_r, "") != 0)
                    add_history(street1_r); //Only add to history if user input not empty
                //need one extra space to parse the whole char array
                string street1 = parse_string(street1_r, false);
                cout << street1 << endl;

                cout << "Type the second street please:" << endl;
                char* street2_r = readline("> ");
                if (strcmp(street2_r, "") != 0)
                    add_history(street2_r); //Only add to history if user input not empty
                //need one extra space to parse the whole char array
                string street2 = parse_string(street2_r, false);

                tempoInt1 = find_intersection_ids_from_street_names(street1, street2);
                if (tempoInt1.size() == 0)
                    cout << "Those two street never intersect! Try again" << endl;
                else valid = true;
            }

            valid = false;
            while (!valid) {
                cout << "Please insert the two streets for the second intersection: " << endl;
                cout << "Type the third street please:" << endl;
                char* street3_r = readline("> ");
                if (strcmp(street3_r, "") != 0)
                    add_history(street3_r); //Only add to history if user input not empty
                //need one extra space to parse the whole char array
                string street3 = parse_string(street3_r, false);

                cout << "Type the forth street please:" << endl;
                char* street4_r = readline("> ");
                if (strcmp(street4_r, "") != 0)
                    add_history(street4_r); //Only add to history if user input not empty
                //need one extra space to parse the whole char array
                string street4 = parse_string(street4_r, false);


                tempoInt2 = find_intersection_ids_from_street_names(street3, street4);
                if (tempoInt2.size() == 0)
                    cout << "Those two street never intersect! Try again" << endl;
                else valid = true;
            }

            if ((!tempoInt1.empty())&&(!tempoInt2.empty())) {
                target1 = tempoInt1[0];
                target2 = tempoInt2[0];
            } else {
                cout << "Invalid intersections!" << endl;
                target1 = -1;
                target2 = -1;
            }
        }


    } else if (command == "P") {
        vector<unsigned> tempoInt, tempoPOI;
        bool valid = false;
        while (!valid) {
            //Use tab for auto completion
            rl_bind_key('\t', rl_complete);
            //Use our function for auto-complete
            rl_attempted_completion_function = command_completion_street;
            //Tell readline to handle double and single quotes for us
            rl_completer_quote_characters = strdup("\"\'");
            cout << "Please insert the two streets for the first intersection: " << endl;
            cout << "Type the first street please:" << endl;
            char* street1_r = readline("> ");
            if (strcmp(street1_r, "") != 0)
                add_history(street1_r); //Only add to history if user input not empty
            //need one extra space to parse the whole char array
            string street1 = parse_string(street1_r, false);
            cout << street1 << endl;

            cout << "Type the second street please:" << endl;
            char* street2_r = readline("> ");
            if (strcmp(street2_r, "") != 0)
                add_history(street2_r); //Only add to history if user input not empty
            //need one extra space to parse the whole char array
            string street2 = parse_string(street2_r, false);

            tempoInt = find_intersection_ids_from_street_names(street1, street2);
            if (tempoInt.size() == 0)
                cout << "Those two street never intersect! Try again" << endl;
            else valid = true;
        }

        valid = false;
        while (!valid) {
            //Use tab for auto completion
            rl_bind_key('\t', rl_complete);
            //Use our function for auto-complete
            rl_attempted_completion_function = command_completion_POI;
            //Tell readline to handle double and single quotes for us
            rl_completer_quote_characters = strdup("\"\'");
            //Use tab for auto completion
            rl_bind_key('\t', rl_complete);
            //Use our function for auto-complete
            rl_attempted_completion_function = command_completion_POI;
            //Tell readline to handle double and single quotes for us
            rl_completer_quote_characters = strdup("\"\'");
            cout << "Enter a name of point of interest:" << endl;
            char* POI_name_r = readline("> ");
            if (strcmp(POI_name_r, "") != 0)
                add_history(POI_name_r); //Only add to history if user input not empty
            //need one extra space to parse the whole char array
            POIName = parse_string(POI_name_r, false);
            cout << POIName << endl;

            tempoPOI = dataStructureSingleton::dataStructures()->findPOIIDFromName(POIName);
            if (tempoPOI.size() == 0)
                cout << "Invalid point of interest name! Try again" << endl;
            else valid = true;
        }

        vector<unsigned> tempoPOI_inter = find_closest_intersection_vector(tempoPOI);


        if ((!tempoInt.empty())&&(!tempoPOI.empty())) {
            target1 = tempoInt[0];
            target2 = tempoPOI_inter[0];
        } else {
            cout << "Invalid Input!" << endl;
            target1 = -1;
            target2 = -1;
        }

    }

    if ((target1 != -1)&&(target2 != -1)) {
        if (((command == "I")&&(mode == "T"))) {
            LatLon target1_latlon = getIntersectionPosition(target1);
            dataStructureSingleton::dataStructures()->first_LatLon_clicked = target1_latlon;
            dataStructureSingleton::dataStructures()->first_intersection_clicked_ID = target1;

            LatLon target2_latlon = getIntersectionPosition(target2);
            dataStructureSingleton::dataStructures()->second_LatLon_clicked = target2_latlon;
            dataStructureSingleton::dataStructures()->first_intersection_clicked_ID = target2;

            dataStructureSingleton::dataStructures()->path = find_path_between_intersections(target1, target2);

            //find the suitable view for displaying the path
            t_point start = to_xycoordinate(target1_latlon);
            t_point end = to_xycoordinate(target2_latlon);
            float x1, x2, y1, y2;
            if (start.x > end.x) {
                x1 = end.x - 40;
                x2 = start.x + 40;
            } else {
                x1 = start.x - 40;
                x2 = end.x + 40;
            }
            if (start.y > end.y) {
                y1 = end.y - 40;
                y2 = start.y + 40;
            } else {
                y1 = start.y - 40;
                y2 = end.y + 40;
            }
            t_bound_box draw_frame = t_bound_box(x1, y1, x2, y2);
            set_visible_world(draw_frame);


            float current_frame_area = draw_frame.area();

            float initial_area = dataStructureSingleton::dataStructures()->initial_frame.area();

            float frame_factor = current_frame_area / initial_area;

            draw_closest_path(frame_factor);
            draw_start_end_point_icons(frame_factor);
            draw_path_direction(frame_factor);



        } else if (command == "P") {
            LatLon target1_latlon = getIntersectionPosition(target1);
            dataStructureSingleton::dataStructures()->first_LatLon_clicked = target1_latlon;
            dataStructureSingleton::dataStructures()->first_intersection_clicked_ID = target1;

            dataStructureSingleton::dataStructures()->path = find_path_to_point_of_interest(dataStructureSingleton::dataStructures()->first_intersection_clicked_ID, POIName);
            t_bound_box current_frame = get_visible_world();

            //find the suitable view for displaying the path
            t_point start = to_xycoordinate(target1_latlon);
            float x1, x2, y1, y2;

            x1 = start.x - 500;
            x2 = start.x + 500;
            y1 = start.y - 500;
            y2 = start.y + 500;


            t_bound_box draw_frame = t_bound_box(x1, y1, x2, y2);
            set_visible_world(draw_frame);


            float current_frame_area = draw_frame.area();

            float initial_area = dataStructureSingleton::dataStructures()->initial_frame.area();

            float frame_factor = current_frame_area / initial_area;

            draw_closest_path(frame_factor);
            draw_start_end_point_icons(frame_factor);
            draw_path_direction(frame_factor);
            draw_direction_arrows();
        }
    }
    // locations are then received and stored in the singleton in the
    // event_loop(act_on_mousebutton, NULL, NULL, drawscreen);
    return;
}

void draw_start_end_point_icons(float frame_factor) {

    if ((dataStructureSingleton::dataStructures()->first_LatLon_clicked.lat != 0)&&(dataStructureSingleton::dataStructures()->first_LatLon_clicked.lon != 0)) {
        LatLon start_intersection = dataStructureSingleton::dataStructures()->first_LatLon_clicked;
        t_point start_intersection_t_point = to_xycoordinate(start_intersection);
        setcolor(GREEN);
        settextrotation(0);
        draw_icon_start_end_intersection(frame_factor, "S", start_intersection_t_point);
    }
    if ((dataStructureSingleton::dataStructures()->second_LatLon_clicked.lat != 0)&&(dataStructureSingleton::dataStructures()->second_LatLon_clicked.lat != 0)) {
        LatLon end_intersection = dataStructureSingleton::dataStructures()->second_LatLon_clicked;
        t_point end_intersection_t_point = to_xycoordinate(end_intersection);
        setcolor(RED);
        settextrotation(0);
        draw_icon_start_end_intersection(frame_factor, "E", end_intersection_t_point);
    }

}

void draw_icon_start_end_intersection(float frame_factor, string icon, t_point location) {
    //draw at different zoom levels

    if (frame_factor < 0.5 && frame_factor >= 0.3) {
        fillarc(location.x, location.y, 200, 0, 360);
    } else if (frame_factor < 0.3 && frame_factor >= 0.1) {
        fillarc(location.x, location.y, 80, 0, 360);
    } else if (frame_factor < 0.1 && frame_factor >= 0.01) {
        fillarc(location.x, location.y, 65, 0, 360);
    } else if (frame_factor < 0.01 && frame_factor >= 0.001) {
        fillarc(location.x, location.y, 30, 0, 360);
    } else if (frame_factor < 0.001 && frame_factor >= 0.0001) {
        fillarc(location.x, location.y, 15, 0, 360);
        setcolor(BLACK);
        setfontsize(8);
        t_bound_box text_bound = t_bound_box(location.x - 10, location.y - 10, location.x + 10, location.y + 10);
        drawtext(location, icon, text_bound);
    } else if (frame_factor < 0.0001 && frame_factor >= 0.00005) {
        fillarc(location.x, location.y, 7, 0, 360);
        setcolor(BLACK);
        setfontsize(7.5);
        t_bound_box text_bound = t_bound_box(location.x - 10, location.y - 10, location.x + 10, location.y + 10);
        drawtext(location, icon, text_bound);
    } else if (frame_factor < 0.00005 && frame_factor >= 0.00001) {
        fillarc(location.x, location.y, 4, 0, 360);
        setcolor(BLACK);
        setfontsize(7);
        t_bound_box text_bound = t_bound_box(location.x - 10, location.y - 10, location.x + 10, location.y + 10);
        drawtext(location, icon, text_bound);
    } else {
        fillarc(location.x, location.y, 2, 0, 360);
        setcolor(BLACK);
        setfontsize(6);
        t_bound_box text_bound = t_bound_box(location.x - 3, location.y - 3, location.x + 3, location.y + 3);
        drawtext(location, icon, text_bound);
    }
}

void draw_closest_path(float frame_factor) {
    // get path vector from structure.cpp
    vector<unsigned>path = dataStructureSingleton::dataStructures()->path;

    // if vector is not empty
    if (path.size() != 0) {
        unsigned segment_ID;
        for (unsigned i = 0; i < path.size(); i++) {
            segment_ID = path[i];

            StreetSegmentInfo segment_info = getStreetSegmentInfo(segment_ID);

            LatLon from = getIntersectionPosition(segment_info.from);
            LatLon to = getIntersectionPosition(segment_info.to);

            t_point start_t_point = to_xycoordinate(from);
            t_point end_t_point = to_xycoordinate(to);

            float speed_limit = segment_info.speedLimit;

            // if street segment is straight
            if (segment_info.curvePointCount == 0) {
                set_colour_and_width_of_street_segment(speed_limit, frame_factor);
                drawline(start_t_point, end_t_point);
            }// if street segment has 1 curve point 
            else if (segment_info.curvePointCount == 1) {
                LatLon current_curve_point = getStreetSegmentCurvePoint(segment_ID, 0);
                t_point curve_point = to_xycoordinate(current_curve_point);
                set_colour_and_width_of_street_segment(speed_limit, frame_factor);
                drawline(start_t_point, curve_point);
                drawline(curve_point, end_t_point);

            }// if street segment has more than 1 curve point
            else {

                LatLon first_curve_point = getStreetSegmentCurvePoint(segment_ID, 0);
                LatLon last_curve_point = getStreetSegmentCurvePoint(segment_ID, segment_info.curvePointCount - 1);

                t_point first_curve_point_t_point = to_xycoordinate(first_curve_point);
                t_point last_curve_point_t_point = to_xycoordinate(last_curve_point);

                set_colour_and_width_of_street_segment(speed_limit, frame_factor);
                drawline(start_t_point, first_curve_point_t_point);
                drawline(last_curve_point_t_point, end_t_point);

                // draw each sub-street segments
                for (unsigned i = 0, j = 1; i < segment_info.curvePointCount - 1; i++, j++) {

                    LatLon current = getStreetSegmentCurvePoint(segment_ID, i);
                    LatLon next = getStreetSegmentCurvePoint(segment_ID, j);

                    t_point former = to_xycoordinate(current);
                    t_point latter = to_xycoordinate(next);

                    set_colour_and_width_of_street_segment(speed_limit, frame_factor);
                    drawline(former, latter);
                }
            }
        }
    }
}

void draw_path_direction(float frame_factor) {
    // get path vector from structure.cpp
    vector<unsigned>path = dataStructureSingleton::dataStructures()->path;
    int num_of_seg = path.size();
    unsigned arrow_location, tail_location;
    double cur_angle, next_angle;
    t_point pre_offset, offset;
    vector<string> street_name;
    string cur_str_name, next_str_name;

    string last_direction;

    //find the angle of the first street segment
    StreetSegmentInfo current_seg = getStreetSegmentInfo(path[0]);
    cur_str_name = getStreetName(current_seg.streetID);
    street_name.push_back(cur_str_name);
    StreetSegmentInfo next_seg = getStreetSegmentInfo(path[1]);
    next_str_name = getStreetName(next_seg.streetID);

    //find out the tail and the head of the current segment
    if (current_seg.from == next_seg.from || current_seg.from == next_seg.to) {
        arrow_location = current_seg.from;
        tail_location = current_seg.to;
    } else {
        arrow_location = current_seg.to;
        tail_location = current_seg.from;
    }
    LatLon start = getIntersectionPosition(tail_location);
    LatLon end = getIntersectionPosition(arrow_location);
    t_point onset = to_xycoordinate(start);
    offset = to_xycoordinate(end);


    double degree = RAD_TO_DEG * atan((offset.y - onset.y) / (offset.x - onset.x));

    if (((offset.y - onset.y) < 0)&&((offset.x - onset.x) < 0))
        degree += 180;
    else if (((offset.y - onset.y) > 0)&&((offset.x - onset.x) < 0))
        degree += 180;
    next_angle = degree;


    for (unsigned i = 1; i < num_of_seg - 1; i++) {

        pre_offset = offset;
        cur_angle = next_angle;
        StreetSegmentInfo current_seg = getStreetSegmentInfo(path[i]);
        cur_str_name = getStreetName(current_seg.streetID);
        street_name.push_back(cur_str_name);
        StreetSegmentInfo next_seg = getStreetSegmentInfo(path[i + 1]);
        next_str_name = getStreetName(next_seg.streetID);

        //decide if to print the name in the current zoom level
        if (current_seg.from == next_seg.from || current_seg.from == next_seg.to) {
            arrow_location = current_seg.from;
            tail_location = current_seg.to;
        } else {
            arrow_location = current_seg.to;
            tail_location = current_seg.from;
        }
        LatLon start = getIntersectionPosition(tail_location);
        LatLon end = getIntersectionPosition(arrow_location);
        t_point onset = to_xycoordinate(start);
        offset = to_xycoordinate(end);


        double degree = RAD_TO_DEG * atan((offset.y - onset.y) / (offset.x - onset.x));

        if (((offset.y - onset.y) < 0)&&((offset.x - onset.x) < 0))
            degree += 180;
        else if (((offset.y - onset.y) > 0)&&((offset.x - onset.x) < 0))
            degree += 180;

        string direction;
        if (next_angle >= 0 && next_angle <= 10) {
            direction = "East";
            if (i == num_of_seg - 2)
                last_direction = "East";
        } else if (next_angle > 10 && next_angle <= 80) {
            direction = "North East";
            if (i == num_of_seg - 2)
                last_direction = "North East";
        } else if (next_angle > 80 && next_angle <= 100) {
            direction = "North";
            if (i == num_of_seg - 2)
                last_direction = "North";
        } else if (next_angle > 100 && next_angle <= 170) {
            direction = "North West";
            if (i == num_of_seg - 2)
                last_direction = "North West";
        } else if (next_angle > 170 && next_angle <= 190) {
            direction = "West";
            if (i == num_of_seg - 2)
                last_direction = "West";
        } else if (next_angle > 190 && next_angle <= 260) {
            direction = "South West";
            if (i == num_of_seg - 2)
                last_direction = "South West";
        } else if ((next_angle > 260 && next_angle <= 280) || (next_angle>-100 && next_angle <= -80)) {
            direction = "South";
            if (i == num_of_seg - 2)
                last_direction = "South";
        } else {
            direction = "South East";
            if (i == num_of_seg - 2)
                last_direction = "South East";
        }

        if (cur_str_name != next_str_name)
            cout << "Travel " << direction << " along the " << cur_str_name << endl;



        next_angle = degree;

        settextrotation(cur_angle);
        setcolor(t_color(PURPLE));
        setfontsize(20);
        setlinestyle(SOLID);
        //drawtext(pre_offset, ">>", 200, 200);
        
        if (cur_str_name != next_str_name) {
            //first angle in the first quarter
            if (cur_angle > 0) {
                if (next_angle - cur_angle >= 50)
                    cout << "Turn left to " << next_str_name << endl;
                else if (next_angle - cur_angle <= -50)
                    cout << "Turn right to " << next_str_name << endl;
                else
                    cout << "Turn into " << next_str_name << endl;
            } else {
                if (next_angle < 0)
                    if ((180 - next_angle) - (180 - cur_angle) >= 50)
                        cout << "Turn right to " << next_str_name << endl;
                    else if (next_angle - (180 - cur_angle) >= 50)
                        cout << "Turn right to " << next_str_name << endl;
                    else if (next_angle - (180 - cur_angle) <= -50)
                        cout << "Turn left to " << next_str_name << endl;
                    else
                        cout << "Turn into " << next_str_name << endl;
            }

        }
    }

    cout << "Travel " << last_direction << " along the " << cur_str_name << endl;
}

void set_colour_and_width_of_street_segment(float speedlimit, float frame_factor) {

    // if major street
    if (speedlimit >= 70) {
        if (frame_factor < 1 && frame_factor >= 0.05)
            setlinewidth(4);
        else if (frame_factor < 0.05 && frame_factor >= 0.01)
            setlinewidth(5);
        else if (frame_factor < 0.01 && frame_factor >= 0.001)
            setlinewidth(4);
        else if (frame_factor < 0.001 && frame_factor >= 0.0001)
            setlinewidth(12);
        else if (frame_factor < 0.0001 && frame_factor >= 0.00001)
            setlinewidth(20);
        else if (frame_factor < 0.00001)
            setlinewidth(35);
        else
            setlinewidth(3);
        setcolor(MAGENTA);
        setlinestyle(SOLID);
    }// if minor street
    else {
        if (frame_factor < 1 && frame_factor >= 0.05)
            setlinewidth(2);
        else if (frame_factor < 0.05 && frame_factor >= 0.01)
            setlinewidth(2);
        else if (frame_factor < 0.01 && frame_factor >= 0.001)
            setlinewidth(3);
        else if (frame_factor < 0.001 && frame_factor >= 0.0001)
            setlinewidth(9);
        else if (frame_factor < 0.0001 && frame_factor >= 0.00001)
            setlinewidth(15);
        else if (frame_factor < 0.00001)
            setlinewidth(30);

        setcolor(MAGENTA);
        setlinestyle(SOLID);
    }
}

void draw_direction_arrows() {
    // get path vector from structure.cpp
    vector<unsigned>path = dataStructureSingleton::dataStructures()->path;
    unsigned path_vector_size = path.size();

    // loop through all street segments
    for (unsigned i = 0; i < path_vector_size; i++) {

        StreetSegmentInfo current_seg = getStreetSegmentInfo(path[path_vector_size - 1 - i]);

        unsigned startID, endID;
        startID = current_seg.from;
        endID = current_seg.to;

        LatLon start = getIntersectionPosition(startID);
        LatLon end = getIntersectionPosition(endID);
        t_point onset = to_xycoordinate(start);
        t_point offset = to_xycoordinate(end);
        t_bound_box wordsbound = find_words_box(onset, offset);

        // find the center and the angle 
        t_point center;
        center.x = (onset.x + offset.x) / 2;
        center.y = (onset.y + offset.y) / 2;
        double degree = RAD_TO_DEG * atan((offset.y - onset.y) / (offset.x - onset.x));

        if (((offset.y - onset.y) < 0 && (offset.x - onset.x) < 0)
                || ((offset.y - onset.y) > 0 && (offset.x - onset.x) < 0))
            degree += 180;

        settextrotation(degree);
        setcolor(t_color(PURPLE));
        setfontsize(35);
        drawtext(center, ">>", wordsbound);
    }
}