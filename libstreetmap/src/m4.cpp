/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "m4.h"

#define DEPOT 3
#define BOTH 2 
#define PICKUP  1
#define DROPOFF 0

vector<DeliveryNode> InterSecOrder;

std::vector<unsigned> traveling_courier(const std::vector<DeliveryInfo>& deliveries, const std::vector<unsigned>& depots) {

    return greedy_algorithm(deliveries, depots);
}

std::vector<unsigned> greedy_algorithm(const std::vector<DeliveryInfo> deliveries, const std::vector<unsigned> depots) {
    vector<unsigned> CurrLoad;
    vector<unsigned> pickedInt;
    vector<unsigned> path;
    int NumOfVisitedNode = 0;
    int NumOfNode = deliveries.size() * 2;
    int NumOfDepots = depots.size();
    int idx;
    if (NumOfDepots < 5) {
        idx = NumOfDepots - 1;
    } else {
        idx = NumOfDepots % 5;
    }
    unsigned tempo_start = depots[idx];
    while (NumOfVisitedNode != NumOfNode) {
        vector<unsigned> tempo_path = find_path_between_two_ints(tempo_start, deliveries, CurrLoad, pickedInt, NumOfVisitedNode);

        auto iter = path.end();
        path.insert(iter, tempo_path.begin(), tempo_path.end());
    }

    vector <unsigned> tempo_path = find_path_between_delivery_and_depot(tempo_start, depots, CurrLoad, pickedInt);
    auto iter = path.end();
    path.insert(iter, tempo_path.begin(), tempo_path.end());


    return path;
}

//return street segment path from starting point to terminal point
vector<unsigned> find_path_between_two_ints(unsigned &intersect_id_start,
        const std::vector<DeliveryInfo>& deliveries, std::vector<unsigned> &CurrLoad,
        std::vector<unsigned> &pickedInt, int &NumOfVisitedNode) {


    int lastIntID = -1;

    int NumOfGood = deliveries.size();

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

        // -1 means initialized
        // 0 means dropoff
        // 1 means pickup
        // 2 means both
        // 3 means depot
        int status = -1;

        bool got = false;
        for (int idx = 0; idx < NumOfGood; idx++) {

            bool pickup = false;
            bool dropoff = false;


            if (curr.IntSecID == deliveries[idx].pickUp) {
                if (find(pickedInt.begin(), pickedInt.end(), curr.IntSecID) == pickedInt.end()) {
                    CurrLoad.push_back(idx);
                    lastIntID = deliveries[idx].pickUp;
                    NumOfVisitedNode++;
                    found = true;
                    pickup = true;
                    got = true;
                }
            }

            if (curr.IntSecID == deliveries[idx].dropOff) {
                auto iter = find(CurrLoad.begin(), CurrLoad.end(), idx);
                if (iter != CurrLoad.end()) {
                    CurrLoad.erase(iter);
                    lastIntID = deliveries[idx].dropOff;
                    NumOfVisitedNode++;
                    found = true;
                    dropoff = true;
                }
            }

            if (status != 2) {
                if (pickup) {
                    if (dropoff) {
                        status = 2;
                    } else {
                        status = 1;
                    }
                } else {
                    if (dropoff) {
                        status = 0;
                    }
                }
            }

            if (got && (idx == (NumOfGood - 1))) {
                pickedInt.push_back(curr.IntSecID);
            }

        }

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

            DeliveryNode info(curr.IntSecID, status, CurrLoad, target);
            InterSecOrder.push_back(info);
            intersect_id_start = lastIntID;
            return target;

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

    vector <unsigned> emptyVector;
    return emptyVector;


}

//return street segment path from starting point to terminal point
vector<unsigned> find_path_between_delivery_and_depot(unsigned intersect_id_start,
        const std::vector<unsigned> depots, std::vector<unsigned> &CurrLoad,
        std::vector<unsigned> &pickedInt) {


    int lastIntID = -1;

    int NumOfDepots = depots.size();

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


        for (int idx = 0; idx < NumOfDepots; idx++) {


                       
            if (curr.IntSecID == depots[idx]) {
                if (find(pickedInt.begin(), pickedInt.end(), curr.IntSecID) == pickedInt.end()) {
                    
                    lastIntID = depots[idx];

                    found = true;

                    break;
                }
            }

           
        }

        if (found) {
            vector<unsigned> SegIDs;
            unsigned tempoInt = lastIntID;
            int prevSeg = IntersectionNode[tempoInt].lastSeg;
            while (prevSeg != -1) {
                SegIDs.push_back(prevSeg);
                StreetSegmentInfo tempo_seg = getStreetSegmentInfo(prevSeg);
                tempoInt = GetLastIntID(tempo_seg, tempoInt);
                prevSeg = IntersectionNode[tempoInt].lastSeg;
            }
            vector<unsigned> target;
            int IntNum = SegIDs.size();
            for (int i = 0; i < IntNum; i++) {
                unsigned tempoID = SegIDs.back();
                SegIDs.pop_back();
                target.push_back(tempoID);
            }

            DeliveryNode info(curr.IntSecID, DEPOT, CurrLoad, target);
            InterSecOrder.push_back(info);
            return target;

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
                            IntersectionNode[tempo_intID].travelTime = time;
                            IntersectionNode[tempo_intID].lastSeg = adjacent_segs[i];
                            IntersectionNode[tempo_intID].lastStreet = currSt;

                            //push_back the tempoID
                            tempoList.push_back(InterSec(tempo_intID, adjacent_segs[i], time));
                            push_heap(tempoList.begin(), tempoList.end(), &timeComparator);
                        }
                    }
                }
            }
        }
    }
    
    vector <unsigned> emptyVector;
    return emptyVector;


}

void act_on_keypress(char key_pressed, int keysym) {
    if (keysym == XK_BackSpace) {
        dataStructureSingleton::dataStructures()->keyboard_input.pop_back();
    } else if (keysym == 65293) { // process request
        dataStructureSingleton::dataStructures()->keyboard_active = false;
        set_keypress_input(false);
        string user_input_processed(dataStructureSingleton::dataStructures()->keyboard_input.begin(), dataStructureSingleton::dataStructures()->keyboard_input.end());
        dataStructureSingleton::dataStructures()->proceed_name = user_input_processed;

        highlight_POI(dataStructureSingleton::dataStructures()->proceed_name);
    } else if (keysym == 65505) {
        //do nothing
    } else
        dataStructureSingleton::dataStructures()->keyboard_input.push_back(key_pressed);
    draw_search_bar();
}

void draw_search_bar() {
    t_bound_box current_view = get_visible_world();
    setcolor(0);
    fillrect(current_view.left(), current_view.top() - current_view.get_height() / 12, current_view.left() + current_view.get_width() / 5, current_view.top());
    setcolor(DARKGREY);
    setlinewidth(2);
    setlinestyle(SOLID);
    drawrect(current_view.left() + current_view.get_width() / 40, current_view.top() - current_view.get_height() / 18, current_view.left() + current_view.get_width() *7 / 40, current_view.top() - current_view.get_height() / 36);

    if (!(dataStructureSingleton::dataStructures()->keyboard_active)) {
        settextrotation(0);
        setcolor(LIGHTGREY);
        setfontsize(10);
        float x_coord = current_view.left() + current_view.get_width() / 10;
        float y_coord = current_view.top() - current_view.get_height() / 24;
        drawtext(x_coord, y_coord, "Search map", 10000, 10000);
    } else {
        set_keypress_input(true);

        string user_input(dataStructureSingleton::dataStructures()->keyboard_input.begin(), dataStructureSingleton::dataStructures()->keyboard_input.end());
        float x_coord = current_view.left() + current_view.get_width() / 10;
        float y_coord = current_view.top() - current_view.get_height() / 24;
        setcolor(BLACK);
        drawtext(x_coord, y_coord, user_input, 10000, 10000);
        cout << user_input << endl;
    }
}

void highlight_POI(string name) {
    t_bound_box current_frame = get_visible_world();

    //calculate current frame area
    float current_frame_area = current_frame.area();

    //calculate current frame ratio
    float frame_factor = current_frame_area / dataStructureSingleton::dataStructures()->initial_frame.area();

    //set the drawing parameters
    setcolor(RED);
    vector<unsigned> POIIDs = dataStructureSingleton::dataStructures()->findPOIIDFromName(name);

    //loop through all the library to draw each of them
    for (auto current_poi_itr = POIIDs.begin();
            current_poi_itr != POIIDs.end();
            current_poi_itr++) {

        t_point location = to_xycoordinate(getPointOfInterestPosition(*current_poi_itr));
        settextrotation(0);
        //the icon is a red circle 
        draw_spec_bubble(frame_factor, RED, location, name);
    }

    dataStructureSingleton::dataStructures()->keyboard_input.clear();
}

/* Optimization algorithms*/

/* Because of the limitation of the pick-ups and drop-offs, for 2-opt, we can only swap two 
 pick-ups with same load, two drop-offs with same load and a pick-up and a drop-off that are 
 not related to each other (the pick-up must come before the drop-off) */

void two_opt() {
    for (vector<DeliveryNode>::iterator itr1 = InterSecOrder.begin(); itr1 != InterSecOrder.end(); itr1++) {
        for (vector<DeliveryNode>::iterator itr2 = itr1 + 1; itr2 != InterSecOrder.end(); itr2++) {
            two_opt_pickup(itr1, itr2);
            two_opt_dropoff(itr1, itr2);
            //if itr2== InterSecOrder.end()-1)
            //find the end depot again

            //calculate the new path travel time



            //            if (newPathTime < bestPathTime) {
            //                bestPathTime = newPathTime;
            //            }

        }
    }
}

void two_opt_pickup(vector<DeliveryNode>::iterator element1, vector<DeliveryNode>::iterator element2) {
    if ((element1->load == 1 || element1->load == 2)&&(element2->load == 1 || element2->load == 2)) {
        if (element1->current_load == element2->current_load) {
            // swap the order of the two elements
            swap_elements(element1, element2);

            // reconnect the two path
            vector<DeliveryNode>::iterator second_itr = element1 + 1;
            vector<DeliveryNode>::iterator next_itr = element2 + 1;
            //second_itr->prepath=find_path_between_intersections(element1->IntIDX, second_itr->IntIDX);
            //next_itr->prepath=find_path_between_intersections(element2->IntIDX,next_itr->IntIDX);

            //update current_load

        }
    }
    return;
}

void two_opt_dropoff(vector<DeliveryNode>::iterator element1, vector<DeliveryNode>::iterator element2) {
    if ((element1->load == 0 || element1->load == 2)&&(element2->load == 0 || element2->load == 2)) {
        if (element1->current_load == element2->current_load)
            swap_elements(element1, element2);
    }
    return;
}

void swap_elements(vector<DeliveryNode>::iterator element1, vector<DeliveryNode>::iterator element2) {
    iter_swap(element1, element2);
}

