

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "StreetsDatabaseAPI.h"
#include <iostream>
#include "m1.h"
#include "m2.h"
#include "m3.h"
#include "m4.h"
#include "structure.h"
#include <readline/readline.h>
#include <readline/history.h>

#define INITIAL_AREA 3.10775E9

using namespace std;

double cos_factor;
float initial_area = 0;
float frame_factor = 0;
bool show_libraries = false;
bool show_recreation_centers = false;
bool show_POIs = false;
int num_clicks = 0;

//function for demonstration, automatically loads required databases with input of a city name

void load_milestone2() {
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
            draw_map();
            close_map();
        } else if (map_name == "cairo") {
            cout << "Loading the map of Cairo" << endl << endl;
            load_map("/cad2/ece297s/public/maps/cairo_egypt.streets.bin");
            draw_map();
            close_map();
        } else if (map_name == "hamilton") {
            cout << "Loading the map of Hamilton" << endl << endl;
            load_map("/cad2/ece297s/public/maps/hamilton_canada.streets.bin");
            draw_map();
            close_map();
        } else if (map_name == "moscow") {
            cout << "Loading the map of Moscow" << endl << endl;
            load_map("/cad2/ece297s/public/maps/moscow.streets.bin");
            draw_map();
            close_map();
        } else if (map_name == "newyork") {
            cout << "Loading the map of New York" << endl << endl;
            load_map("/cad2/ece297s/public/maps/newyork.streets.bin");
            draw_map();
            close_map();
        } else if (map_name == "saint_helena") {
            cout << "Loading the map of Saint Helena" << endl << endl;
            load_map("/cad2/ece297s/public/maps/saint_helena.streets.bin");
            draw_map();
            close_map();
        } else if (map_name == "toronto_canada") {
            cout << "Loading the map of Toronto, Canada" << endl << endl;
            load_map("/cad2/ece297s/public/maps/toronto_canada.streets.bin");
            draw_map();
            close_map();
        } else if (map_name == "london") {
            cout << "Loading the map of London" << endl << endl;
            load_map("/cad2/ece297s/public/maps/london_england.streets.bin");
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

void draw_map() {

    t_bound_box initial_frame = dataStructureSingleton::dataStructures()->initial_frame;

    initial_area = initial_frame.area();


    //initialize the background color and windows name
    init_graphics(city, t_color(0xE0, 0xDB, 0xD0));

    //set the  frame
    set_visible_world(initial_frame);

    create_button("Window", "Find", act_on_find_button_func_m3);
    create_button("Find", "POIs", act_on_POI_button_func);
    create_button("POIs", "Library", act_on_library_button_func);
    create_button("Library", "Health", act_on_recreation_button_func);
    create_button("Health", "Help", act_on_help_button_func);
    create_button("Help", "Travel Points", act_on_travel_points_button_func);
    event_loop(act_on_mousebutton, NULL, act_on_keypress, drawscreen);

    close_graphics();
}

//function to draw the screen

void drawscreen() {

    t_bound_box current_frame = get_visible_world();

    //calculate current frame area
    float current_frame_area = current_frame.area();

    //calculate current frame ratio
    frame_factor = current_frame_area / initial_area;

    clearscreen();

    draw_subway_routes(frame_factor);

    //in this level only draw main road  features with no name
    if ((frame_factor < 1)&&(frame_factor >= 0.05)) {

        draw_features();
        draw_street(60.0, frame_factor);
        draw_feature_names();

    }//in this level only draw 50 + road with no name 
    else if ((frame_factor < 0.05) && (frame_factor >= 0.01)) {

        draw_features();
        draw_street(50.0, frame_factor);
        draw_feature_names();
    }//in this level only draw 50 + road with names
    else if ((frame_factor < 0.01) && (frame_factor >= 0.001)) {

        draw_features();
        draw_street(50.0, frame_factor);
        draw_street_name(50.0);
        draw_feature_names();
    }//in this level only draw 30  + road with names
    else if ((frame_factor < 0.001) && (frame_factor >= 0.0001)) {

        draw_features();
        draw_street(30.0, frame_factor);
        draw_street_name(30.0);
        draw_feature_names();
        draw_oneway_sign();
    }//in this level draw all roads and names 
    else if ((frame_factor < 0.0001)) {

        draw_features();
        draw_street(0.0, frame_factor);
        draw_street_name(0.0);
        draw_feature_names();
        draw_oneway_sign();
    }//in the top level only draw features and highway
    else {

        draw_street(70.0, frame_factor);
        draw_features();

    }

    draw_subway_routes(frame_factor);
    if (show_POIs == true)
        draw_POI(frame_factor);
    if (show_libraries == true)
        draw_library(frame_factor);
    if (show_recreation_centers == true)
        draw_recreation_center(frame_factor);
    if (dataStructureSingleton::dataStructures()->pop != NULL)
        draw_spec_bubble(frame_factor, dataStructureSingleton::dataStructures()->pop->color,
            dataStructureSingleton::dataStructures()->pop->location,
            dataStructureSingleton::dataStructures()->pop->name);

    draw_closest_path(frame_factor);
    draw_start_end_point_icons(frame_factor);
    draw_clicked_intersection();

    draw_search_bar();
    highlight_POI(dataStructureSingleton::dataStructures()->proceed_name);

    draw_direction_arrows();
}

//function to draw all the features

void draw_features() {
    //print layer 1
    for (auto feature_vector1_itr = dataStructureSingleton::dataStructures()->features_layer1_vector.begin();
            feature_vector1_itr != dataStructureSingleton::dataStructures()->features_layer1_vector.end();
            feature_vector1_itr++) {
        //all the features in this layer is closed
        //this layer includes shorelines, beaches, islands and lakes
        FeatureType current_type = getFeatureType(*feature_vector1_itr);
        if (current_type == Shoreline || current_type == Beach)
            draw_closed_feature(*feature_vector1_itr, KHAKI);
        else if (current_type == Island)
            draw_closed_feature(*feature_vector1_itr, t_color(0xF2, 0xED, 0xE3));
        else//draw lake
            draw_closed_feature(*feature_vector1_itr, t_color(0xAB, 0xD3, 0xFF));
    }
    //print layer 2
    for (auto feature_vector2_itr = dataStructureSingleton::dataStructures()->features_layer2_vector.begin();
            feature_vector2_itr != dataStructureSingleton::dataStructures()->features_layer2_vector.end();
            feature_vector2_itr++) {
        //this layer includes parks, greenspaces, golfcourses, buildings and both open and closed unknown features
        FeatureType current_type = getFeatureType(*feature_vector2_itr);
        if (is_closed_feature(*feature_vector2_itr)) {
            if (current_type == Park || current_type == Greenspace || current_type == Golfcourse)
                draw_closed_feature(*feature_vector2_itr, t_color(0xC9, 0xE1, 0xA5));
            else if (current_type == Building)
                draw_closed_feature(*feature_vector2_itr, t_color(0xF2, 0xF0, 0xE6));
            else//draw closed unknown 
                draw_closed_feature(*feature_vector2_itr, DARKKHAKI);
        } else //draw open unknown
            draw_open_feature(*feature_vector2_itr, 3, DARKKHAKI);
    }
    //print layer 3
    for (auto feature_vector3_itr = dataStructureSingleton::dataStructures()->features_layer3_vector.begin();
            feature_vector3_itr != dataStructureSingleton::dataStructures()->features_layer3_vector.end();
            feature_vector3_itr++) {
        //this layer includes all the rivers and streams
        FeatureType current_type = getFeatureType(*feature_vector3_itr);
        if (current_type == River)
            draw_open_feature(*feature_vector3_itr, 4, t_color(0xAB, 0xD3, 0xFF));
        else if (current_type == Stream)
            draw_open_feature(*feature_vector3_itr, 2, t_color(0xAB, 0xD3, 0xFF));
    }
}

//function to determine if a feature is closed or not

bool is_closed_feature(unsigned feature_id) {
    //find the LatLon for the first and the last feature point
    LatLon start = getFeaturePoint(feature_id, 0);
    LatLon end = getFeaturePoint(feature_id, getFeaturePointCount(feature_id) - 1);

    //if both points share the same position, it is a closed feature
    //otherwise, it is open
    if ((start.lat == end.lat)&&(start.lon == end.lon))
        return true;
    else
        return false;
}

//function to draw a closed feature

void draw_closed_feature(unsigned feature_id, t_color color) {
    //set the drawing parameters
    setcolor(color);
    setlinestyle(SOLID);
    unsigned point_num = getFeaturePointCount(feature_id);

    //change all the feature points from LatLon to t_point one by one
    //stores the t_point into an array to draw the polygon
    t_point feature_points[point_num];
    for (unsigned point_idx = 0; point_idx < point_num; point_idx++) {
        feature_points[point_idx] = to_xycoordinate(getFeaturePoint(feature_id, point_idx));
    }
    fillpoly(feature_points, point_num);
}

//function to draw an open feature

void draw_open_feature(unsigned feature_id, int width, t_color color) {
    //set the drawing parameters
    setlinewidth(width);
    setcolor(color);
    setlinestyle(SOLID);
    unsigned point_num = getFeaturePointCount(feature_id);

    //draw line segments between every two feature points
    for (unsigned point_idx = 1; point_idx < point_num; point_idx++) {
        LatLon start = getFeaturePoint(feature_id, point_idx - 1);
        LatLon end = getFeaturePoint(feature_id, point_idx);
        draw_seg_latlon(start, end);
    }
}

//function to draw a line segment between two LatLon point

void draw_seg_latlon(LatLon start, LatLon end) {
    //change the coordinate system into xy coordinates
    t_point xystart = to_xycoordinate(start);
    t_point xyend = to_xycoordinate(end);

    drawline(xystart, xyend);

}

//function to change a LatLon point to a t_point in xy coordinates

t_point to_xycoordinate(LatLon location) {
    t_point xycoordinate;
    //calculate the x and y coordinate respectively
    xycoordinate.x = EARTH_RADIUS_IN_METERS * location.lon * DEG_TO_RAD * cos_factor;
    xycoordinate.y = EARTH_RADIUS_IN_METERS * location.lat * DEG_TO_RAD;

    return xycoordinate;
}

//function to draw a single street segment

void draw_street_seg(unsigned streetseg_id, float speedlimit, float frame_factor) {
    StreetSegmentInfo current_segment = getStreetSegmentInfo(streetseg_id);

    //get the start and the end of the street segment
    LatLon onset = getIntersectionPosition(current_segment.from);
    LatLon offset = getIntersectionPosition(current_segment.to);


    t_point start = to_xycoordinate(onset);
    t_point end = to_xycoordinate(offset);

    //case 1: a straight street segment
    if (current_segment.curvePointCount == 0) {
        color_width_for_draw_streetseg(speedlimit, frame_factor);
        drawline(start, end);
    }//case 2: a street segment with a single curve point
    else if (current_segment.curvePointCount == 1) {
        LatLon current_curve_point = getStreetSegmentCurvePoint(streetseg_id, 0);
        t_point now = to_xycoordinate(current_curve_point);
        color_width_for_draw_streetseg(speedlimit, frame_factor);
        drawline(start, now);
        drawline(now, end);

    }//case 3: a street segment with more than one curve point
    else {

        LatLon first_curve_point = getStreetSegmentCurvePoint(streetseg_id, 0);
        LatLon last_curve_point = getStreetSegmentCurvePoint(streetseg_id, current_segment.curvePointCount - 1);

        t_point first = to_xycoordinate(first_curve_point);
        t_point last = to_xycoordinate(last_curve_point);

        color_width_for_draw_streetseg(speedlimit, frame_factor);
        drawline(start, first);
        drawline(last, end);

        // draw each sub-street segments
        for (unsigned i = 0, j = 1; i < current_segment.curvePointCount - 1; i++, j++) {

            LatLon current = getStreetSegmentCurvePoint(streetseg_id, i);
            LatLon next = getStreetSegmentCurvePoint(streetseg_id, j);

            t_point former = to_xycoordinate(current);
            t_point latter = to_xycoordinate(next);

            color_width_for_draw_streetseg(speedlimit, frame_factor);
            drawline(former, latter);
        }
    }
}

//function to choose the color and width for the draw_streetseg function
//by the speedLimit and the current zoom level

void color_width_for_draw_streetseg(float speedlimit, float frame_factor) {
    //streets with speed limit larger than 70kmh are in color orange and are wider than the other streets
    if (speedlimit >= 70) {
        if (frame_factor < 1 && frame_factor >= 0.05)
            setlinewidth(4);
        else if (frame_factor < 0.05 && frame_factor >= 0.01)
            setlinewidth(5);
        else if (frame_factor < 0.01 && frame_factor >= 0.001)
            setlinewidth(4);
        else if (frame_factor < 0.001 && frame_factor >= 0.0001)
            setlinewidth(10);
        else if (frame_factor < 0.0001 && frame_factor >= 0.00001)
            setlinewidth(15);
        else if (frame_factor < 0.00001)
            setlinewidth(25);
        else
            setlinewidth(3);
        setcolor(t_color(0xFF, 0x96, 0x07));
        setlinestyle(SOLID);
    }//streets with speed limit smaller than 70kmh are in color white and are narrower
    else {
        if (frame_factor < 1 && frame_factor >= 0.05)
            setlinewidth(2);
        else if (frame_factor < 0.05 && frame_factor >= 0.01)
            setlinewidth(2);
        else if (frame_factor < 0.01 && frame_factor >= 0.001)
            setlinewidth(3);
        else if (frame_factor < 0.001 && frame_factor >= 0.0001)
            setlinewidth(6);
        else if (frame_factor < 0.0001 && frame_factor >= 0.00001)
            setlinewidth(10);
        else if (frame_factor < 0.00001)
            setlinewidth(20);

        setcolor(WHITE);
        setlinestyle(SOLID);
    }
}

//function to draw all the streets on the map

void draw_street(float SpeedLimit, float frame_factor) {
    unsigned num_of_street = getNumberOfStreets();
    //loop through all the streets
    for (unsigned idx = 0; idx < num_of_street; idx++) {
        vector<unsigned> street_seg = find_street_street_segments(idx);
        unsigned num_of_seg = street_seg.size();
        //loop through each street segment
        for (unsigned i = 0; i < num_of_seg; i++) {
            StreetSegmentInfo current_seg = getStreetSegmentInfo(street_seg[i]);

            //if it is larger the speed limit we set, draw the segment
            if (current_seg.speedLimit >= SpeedLimit) {
                draw_street_seg(street_seg[i], current_seg.speedLimit, frame_factor);
            }
        }
    }

}

//function to draw all the name tags for streets

void draw_street_name(float SpeedLimit) {
    unsigned num_of_street = getNumberOfStreets();

    //loop through all the streets
    for (unsigned idx = 0; idx < num_of_street; idx++) {

        vector<unsigned> street_seg = find_street_street_segments(idx);
        string street_name = getStreetName(idx);
        unsigned num_of_seg = street_seg.size();

        // the case when the street has a name
        if (street_name != "<unknown>") {
            for (unsigned i = 0; i < num_of_seg; i++) {
                StreetSegmentInfo current_seg = getStreetSegmentInfo(street_seg[i]);
                //decide if to print the name in the current zoom level
                if (current_seg.speedLimit > SpeedLimit) {
                    if (current_seg.curvePointCount < 10) {
                        LatLon start = getIntersectionPosition(current_seg.from);
                        LatLon end = getIntersectionPosition(current_seg.to);
                        t_point onset = to_xycoordinate(start);
                        t_point offset = to_xycoordinate(end);
                        t_bound_box wordsbound = find_words_box(onset, offset);
                        //find the center for the name to print
                        t_point center;
                        center.x = (onset.x + offset.x) / 2;
                        center.y = (onset.y + offset.y) / 2;

                        double degree = RAD_TO_DEG * atan((offset.y - onset.y) / (offset.x - onset.x));

                        settextrotation(degree);
                        setcolor(t_color(0x00, 0x00, 0x00));
                        setfontsize(11);
                        setlinestyle(SOLID);
                        drawtext(center, street_name, wordsbound);

                    }
                }
            }
        }
    }
}

//draw all the name tags for features

void draw_feature_names() {
    for (unsigned feature_idx = 0; feature_idx < getNumberOfFeatures(); feature_idx++) {
        string name = getFeatureName(feature_idx);
        //only print the name if the feature has a name
        if (name != "<noname>") {
            //if the feature is closed, print the name at its center
            if (is_closed_feature(feature_idx)) {

                unsigned point_num = getFeaturePointCount(feature_idx);

                t_point feature_points[point_num];

                for (unsigned point_idx = 0; point_idx < point_num; point_idx++) {
                    feature_points[point_idx] = to_xycoordinate(getFeaturePoint(feature_idx, point_idx));
                }

                t_point center = find_center_of_polygon(feature_points, point_num);

                t_bound_box featurebound = find_features_box(feature_points, point_num);

                if (featurebound.intersects(center)) {
                    setcolor(t_color(0x00, 0x00, 0x00));

                    setfontsize(11);
                    setlinestyle(SOLID);

                    settextrotation(0);
                    drawtext(center, name, featurebound);
                }


            }//if the feature is open, print the name at the average coordinate
            else {
                unsigned point_num = getFeaturePointCount(feature_idx);

                for (unsigned point_idx = 1; point_idx < point_num; point_idx++) {
                    LatLon start = getFeaturePoint(feature_idx, point_idx - 1);
                    LatLon end = getFeaturePoint(feature_idx, point_idx);
                    t_point onset = to_xycoordinate(start);
                    t_point offset = to_xycoordinate(end);

                    t_bound_box wordsbound = find_words_box(onset, offset);

                    t_point center;
                    center.x = (onset.x + offset.x) / 2;
                    center.y = (onset.y + offset.y) / 2;
                    double degree = RAD_TO_DEG * atan((offset.y - onset.y) / (offset.x - onset.x));

                    settextrotation(degree);
                    setfontsize(11);
                    setcolor(t_color(0x00, 0x00, 0x00));
                    setlinestyle(SOLID);
                    drawtext(center, name, wordsbound);

                }
            }
        }
    }

}

//function to draw name given the name and the position of a POI

void draw_POI_name(string name, t_point position) {
    //the text will be shown slightly below the POI itself
    t_point center = t_point(position.x, position.y - 1.3);
    t_point on_set = t_point(center.x - 100, center.y + 100);
    t_point off_set = t_point(center.x + 100, center.y - 100);
    t_bound_box wordsbound = find_words_box(on_set, off_set);

    settextrotation(0);
    setfontsize(10);
    setcolor(t_color(0x00, 0x00, 0x00));
    setlinestyle(SOLID);
    drawtext(center, name, wordsbound);
}

//function to return the center of a polygon with a vectors of all the points
//making up the polygon and the number of points

t_point find_center_of_polygon(const t_point *polygon, unsigned num) {
    t_point center;
    center.x = 0;
    center.y = 0;

    for (unsigned idx = 0; idx < num; idx++) {

        center.x += polygon[idx].x;
        center.y += polygon[idx].y;

    }
    center.x /= num;
    center.y /= num;

    return center;

}

//function to return a box containing all the feature points

t_bound_box find_features_box(const t_point *polygon, unsigned num) {
    float right = -10000000;
    float left = 10000000;
    float top = -10000000;
    float bottom = 10000000;

    for (unsigned idx = 0; idx < num; idx++) {

        if (polygon[idx].x >= right) {
            right = polygon[idx].x;
        }
        if (polygon[idx].x <= left) {
            left = polygon[idx].x;
        }
        if (polygon[idx].y >= top) {
            top = polygon[idx].y;
        }
        if (polygon[idx].y <= bottom) {
            bottom = polygon[idx].y;
        }

    }

    return t_bound_box(left, bottom, right, top);
}

//function to return a box with point A and B on its diagonal

t_bound_box find_words_box(t_point A, t_point B) {
    float right, left, top, bottom;

    if (A.x > B.x) {
        right = A.x;
        left = B.x;
    } else {
        right = B.x;
        left = A.x;
    }

    if (A.y > B.y) {
        top = A.y;
        bottom = B.y;
    } else {
        top = B.y;
        bottom = A.y;
    }

    return t_bound_box(left, bottom, right, top);

}

//function to respond to user's mouse clicks

void act_on_mousebutton(float x, float y, t_event_buttonPressed event) {

    /* Called whenever event_loop gets a button press in the graphics *
     * area.  Allows the user to do whatever he/she wants with button *
     * clicks.                                                        */

    bool get_travel_points = dataStructureSingleton::dataStructures()->get_travel_points_from_map_clicks;

    bool keyboard_active = dataStructureSingleton::dataStructures()->keyboard_active;

    // get travel points from mouse clicks on map
    if (get_travel_points) {
        t_bound_box current_frame = get_visible_world();

        //calculate current frame area
        float current_frame_area = current_frame.area();

        //calculate current frame ratio
        float frame_factor = current_frame_area / initial_area;

        unsigned num_of_intersection = getNumberOfIntersections();
        for (unsigned idx = 0; idx < num_of_intersection; idx++) {
            LatLon current_intersection = getIntersectionPosition(idx);
            float intersection_x = EARTH_RADIUS_IN_METERS * current_intersection.lon * DEG_TO_RAD * cos_factor;
            float intersection_y = EARTH_RADIUS_IN_METERS * current_intersection.lat * DEG_TO_RAD;

            float x_error = abs(intersection_x - x);
            float y_error = abs(intersection_y - y);

            if ((x_error < 20)&&(y_error < 20) && num_clicks == 0) {
                dataStructureSingleton::dataStructures()->first_intersection_clicked_ID = idx;
                LatLon target1 = getIntersectionPosition(idx);
                dataStructureSingleton::dataStructures()->first_LatLon_clicked = target1;
                num_clicks++;
                draw_start_end_point_icons(frame_factor);
                break;
            } else if ((x_error < 20)&&(y_error < 20) && num_clicks == 1) {
                dataStructureSingleton::dataStructures()->second_intersection_clicked_ID = idx;
                LatLon target2 = getIntersectionPosition(idx);
                dataStructureSingleton::dataStructures()->second_LatLon_clicked = target2;
                num_clicks = 0; // reset counter
                dataStructureSingleton::dataStructures()->get_travel_points_from_map_clicks = false; // reset bool 
                dataStructureSingleton::dataStructures()->path = find_path_between_intersections(dataStructureSingleton::dataStructures()->first_intersection_clicked_ID, dataStructureSingleton::dataStructures()->second_intersection_clicked_ID);
                cout << "-------------------------------------------------------------------" << endl;
                cout << "This path is going to take " << compute_path_travel_time(dataStructureSingleton::dataStructures()->path) << " minutes" << endl;
                draw_closest_path(frame_factor);
                draw_start_end_point_icons(frame_factor);
                draw_path_direction(frame_factor);
                break;
            }
        }
    } else {

        t_bound_box current_frame = get_visible_world();

        //calculate current frame area
        float current_frame_area = current_frame.area();

        //calculate current frame ratio
        float frame_factor = current_frame_area / initial_area;

        cout << "User clicked a mouse button at coordinates ("
                << x << "," << y << ")" << endl;

        if (show_libraries == false && show_recreation_centers == false) {
            unsigned num_of_intersection = getNumberOfIntersections();
            //loop through all the intersection, compare the coordinates with the clicked position
            for (unsigned idx = 0; idx < num_of_intersection; idx++) {
                LatLon current_intersection = getIntersectionPosition(idx);
                float intersection_x = EARTH_RADIUS_IN_METERS * current_intersection.lon * DEG_TO_RAD * cos_factor;
                float intersection_y = EARTH_RADIUS_IN_METERS * current_intersection.lat * DEG_TO_RAD;

                float x_error = abs(intersection_x - x);
                float y_error = abs(intersection_y - y);

                //if the position clicked is less than 20 unit away from the location, the intersection is selected
                if ((x_error < 20)&&(y_error < 20)) {

                    dataStructureSingleton::dataStructures()->clicked_intersection_ID = idx;

                    //highlight the intersection itself
                    setcolor(RED);
                    t_point intersection_xy = to_xycoordinate(current_intersection);
                    fillarc(intersection_xy.x, intersection_xy.y, 2, 0, 360);

                    //output the information of the intersection selected
                    string intersection_name = getIntersectionName(idx);
                    cout << "Found the intersection: " << intersection_name << endl;
                    vector<string> street_name = find_intersection_street_names(idx);
                    cout << "This intersection consists of :" << endl;
                    for (unsigned num = 0; num < street_name.size(); num++) {
                        cout << " " << street_name[num] << endl;
                    }

                    //find the intersected street segment at the intersection
                    vector<unsigned> intersection_seg = find_intersection_street_segments(idx);

                    //highlight all the street segments with the same street name(s) on the map.
                    //which is highlighting the intersected streets
                    for (unsigned num = 0; num < intersection_seg.size(); num++) {
                        StreetSegmentInfo current_seg = getStreetSegmentInfo(intersection_seg[num]);

                        //find all the street segments corresponding to the street ID
                        vector<unsigned> street_seg = find_street_street_segments(current_seg.streetID);
                        unsigned num_of_seg = street_seg.size();
                        for (unsigned i = 0; i < num_of_seg; i++) {

                            draw_street_segR(street_seg[i]);

                        }
                    }
                }
            }
        }


        //output the information for the entrance if applicable
        for (unsigned idx = 0; idx < dataStructureSingleton::dataStructures()->subway_station_vector.size(); idx++) {
            //convert the location of the selected subway station to xy coordinates
            LatLon current_intersection = (dataStructureSingleton::dataStructures()->subway_station_vector[idx]).position;
            float intersection_x = EARTH_RADIUS_IN_METERS * current_intersection.lon * DEG_TO_RAD * cos_factor;
            float intersection_y = EARTH_RADIUS_IN_METERS * current_intersection.lat * DEG_TO_RAD;

            //find the distance between location of the subway entrance and the clicked position 
            float x_error = abs(intersection_x - x);
            float y_error = abs(intersection_y - y);

            if ((x_error < 20)&&(y_error < 20)) {
                cout << "This is a subway entrance to " << (dataStructureSingleton::dataStructures()->subway_station_vector[idx]).name << " station" << endl;
            }
        }

        //output the information for the library if applicable
        if (show_libraries == true)
            for (unsigned idx = 0; idx < dataStructureSingleton::dataStructures()->library_vector.size(); idx++) {
                //convert the location of the selected library to xy coordinates
                LatLon current_intersection = (dataStructureSingleton::dataStructures()->library_vector[idx]).position;
                float intersection_x = EARTH_RADIUS_IN_METERS * current_intersection.lon * DEG_TO_RAD * cos_factor;
                float intersection_y = EARTH_RADIUS_IN_METERS * current_intersection.lat * DEG_TO_RAD;

                //find the distance between location of the library and the clicked position 
                float x_error = abs(intersection_x - x);
                float y_error = abs(intersection_y - y);
                int torlarence;
                if (frame_factor >= 0.5)
                    torlarence = 300;
                else if (frame_factor < 0.05 && frame_factor >= 0.001)
                    torlarence = 150;
                else if (frame_factor < 0.001 && frame_factor >= 0.0001) {
                    torlarence = 60;
                } else {
                    torlarence = 8;
                }
                if ((x_error < torlarence / 2)&&(y_error < torlarence)) {
                    point_info current_info = dataStructureSingleton::dataStructures()->library_vector[idx];
                    t_point current_location = to_xycoordinate(current_info.position);

                    if (dataStructureSingleton::dataStructures()->pop == NULL) {
                        dataStructureSingleton::dataStructures()->pop = new spec_bubble_info(current_location, YELLOW, current_info.name);
                        draw_spec_bubble(frame_factor, dataStructureSingleton::dataStructures()->pop->color,
                                dataStructureSingleton::dataStructures()->pop->location,
                                dataStructureSingleton::dataStructures()->pop->name);
                        cout << "This is " << dataStructureSingleton::dataStructures()->pop->name << endl;
                    } else {
                        if (current_info.name == dataStructureSingleton::dataStructures()->pop->name) {
                            delete dataStructureSingleton::dataStructures()->pop;
                            dataStructureSingleton::dataStructures()->pop = NULL;
                        } else {
                            delete dataStructureSingleton::dataStructures()->pop;
                            dataStructureSingleton::dataStructures()->pop = new spec_bubble_info(current_location, YELLOW, current_info.name);

                            draw_spec_bubble(frame_factor, dataStructureSingleton::dataStructures()->pop->color,
                                    dataStructureSingleton::dataStructures()->pop->location,
                                    dataStructureSingleton::dataStructures()->pop->name);
                            cout << "This is " << dataStructureSingleton::dataStructures()->pop->name << endl;
                        }
                    }
                }
            }

        //output the information for the recreation center if applicable
        if (show_recreation_centers == true)
            for (unsigned idx = 0; idx < dataStructureSingleton::dataStructures()->recreation_vector.size(); idx++) {
                //convert the location of the selected recreation center to xy coordinates
                LatLon current_intersection = (dataStructureSingleton::dataStructures()->recreation_vector[idx]).position;
                float intersection_x = EARTH_RADIUS_IN_METERS * current_intersection.lon * DEG_TO_RAD * cos_factor;
                float intersection_y = EARTH_RADIUS_IN_METERS * current_intersection.lat * DEG_TO_RAD;

                //find the distance between location of the recreation center and the clicked position 
                float x_error = abs(intersection_x - x);
                float y_error = abs(intersection_y - y);
                int torlarence;
                if (frame_factor >= 0.5)
                    torlarence = 300;
                else if (frame_factor < 0.05 && frame_factor >= 0.001)
                    torlarence = 150;
                else if (frame_factor < 0.001 && frame_factor >= 0.0001) {
                    torlarence = 60;
                } else {
                    torlarence = 8;
                }
                if ((x_error < torlarence / 2)&&(y_error < torlarence)) {
                    point_info current_info = dataStructureSingleton::dataStructures()->recreation_vector[idx];
                    t_point current_location = to_xycoordinate(current_info.position);

                    if (dataStructureSingleton::dataStructures()->pop == NULL) {
                        dataStructureSingleton::dataStructures()->pop = new spec_bubble_info(current_location, PINK, current_info.name);
                        draw_spec_bubble(frame_factor, dataStructureSingleton::dataStructures()->pop->color,
                                dataStructureSingleton::dataStructures()->pop->location,
                                dataStructureSingleton::dataStructures()->pop->name);
                        cout << "This is " << dataStructureSingleton::dataStructures()->pop->name << endl;
                    } else {
                        if (current_info.name == dataStructureSingleton::dataStructures()->pop->name) {
                            delete dataStructureSingleton::dataStructures()->pop;
                            dataStructureSingleton::dataStructures()->pop = NULL;
                            drawscreen();
                        } else {
                            delete dataStructureSingleton::dataStructures()->pop;
                            dataStructureSingleton::dataStructures()->pop = new spec_bubble_info(current_location, PINK, current_info.name);

                            draw_spec_bubble(frame_factor, dataStructureSingleton::dataStructures()->pop->color,
                                    dataStructureSingleton::dataStructures()->pop->location,
                                    dataStructureSingleton::dataStructures()->pop->name);
                            cout << "This is " << dataStructureSingleton::dataStructures()->pop->name << endl;
                        }
                    }

                    cout << endl;
                }
            }

        if (!keyboard_active) {
            dataStructureSingleton::dataStructures()->proceed_name = string("/");
            t_bound_box current_view = get_visible_world();
            t_bound_box search_area = t_bound_box(current_view.left(), current_view.top() - current_view.get_height() / 12, current_view.left() + current_view.get_width() / 5, current_view.top());
            t_point click_point = t_point(x, y);
            if (search_area.intersects(click_point)) {
                dataStructureSingleton::dataStructures()->keyboard_active = true;
                set_keypress_input(true);
                draw_search_bar();
            }
        }
    }
}

//function to pop up name tag bubble

void draw_spec_bubble(float frame_factor, t_color color, t_point location, string name) {
    if (frame_factor >= 1) {
        setcolor(DARKGREY);
        fillellipticarc(location, 100, 50, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 100, location.y + 200);
        t_point point3 = t_point(location.x + 100, location.y + 200);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 200, 200, 0, 360);
    } else if (frame_factor < 1 && frame_factor >= 0.05) {
        setcolor(DARKGREY);
        fillellipticarc(location, 100, 50, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 300, location.y + 600);
        t_point point3 = t_point(location.x + 300, location.y + 600);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 600, 300, 0, 360);

    } else if (frame_factor < 0.05 && frame_factor >= 0.01) {
        setcolor(DARKGREY);
        fillellipticarc(location, 50, 25, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 100, location.y + 200);
        t_point point3 = t_point(location.x + 100, location.y + 200);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);

        t_point center = t_point(location.x, location.y + 200);
        fillellipticarc(center, 200, 100, 0, 360);

        //draw name
        t_point on_set = t_point(center.x - 400, center.y + 400);
        t_point off_set = t_point(center.x + 400, center.y - 400);
        t_bound_box wordsbound = find_words_box(on_set, off_set);

        settextrotation(0);
        setfontsize(3);
        setcolor(t_color(0x00, 0x00, 0x00));
        setlinestyle(SOLID);
        drawtext(center, name, wordsbound);

    } else if (frame_factor < 0.01 && frame_factor >= 0.001) {
        setcolor(DARKGREY);
        fillellipticarc(location, 50, 25, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 200, location.y + 200);
        t_point point3 = t_point(location.x + 200, location.y + 200);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);


        t_point center = t_point(location.x, location.y + 200);
        fillellipticarc(center, 200, 100, 0, 360);

        //draw name
        t_point on_set = t_point(center.x - 200, center.y + 200);
        t_point off_set = t_point(center.x + 200, center.y - 200);
        t_bound_box wordsbound = find_words_box(on_set, off_set);

        settextrotation(0);
        setfontsize(6);
        setcolor(t_color(0x00, 0x00, 0x00));
        setlinestyle(SOLID);
        drawtext(center, name, wordsbound);
    } else if (frame_factor < 0.001 && frame_factor >= 0.0001) {
        setcolor(DARKGREY);
        fillellipticarc(location, 20, 10, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 100, location.y + 100);
        t_point point3 = t_point(location.x + 100, location.y + 100);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);

        t_point center = t_point(location.x, location.y + 100);
        fillellipticarc(center, 100, 50, 0, 360);

        //draw name
        t_point on_set = t_point(center.x - 100, center.y + 100);
        t_point off_set = t_point(center.x + 100, center.y - 100);
        t_bound_box wordsbound = find_words_box(on_set, off_set);

        settextrotation(0);
        setfontsize(8);
        setcolor(t_color(0x00, 0x00, 0x00));
        setlinestyle(SOLID);
        drawtext(center, name, wordsbound);
    } else {
        setcolor(DARKGREY);
        fillellipticarc(location, 2, 1, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 20, location.y + 20);
        t_point point3 = t_point(location.x + 20, location.y + 20);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);

        t_point center = t_point(location.x, location.y + 20);
        fillellipticarc(center, 20, 10, 0, 360);

        //draw name
        t_point on_set = t_point(center.x - 20, center.y + 20);
        t_point off_set = t_point(center.x + 20, center.y - 20);
        t_bound_box wordsbound = find_words_box(on_set, off_set);

        settextrotation(0);
        setfontsize(8);
        setcolor(t_color(0x00, 0x00, 0x00));
        setlinestyle(SOLID);
        drawtext(center, name, wordsbound);
    }
}

//function to highlight a street segment

void draw_street_segR(unsigned streetseg_id) {
    StreetSegmentInfo current_segment = getStreetSegmentInfo(streetseg_id);

    //get the begin and the end for a street segment
    LatLon onset = getIntersectionPosition(current_segment.from);
    LatLon offset = getIntersectionPosition(current_segment.to);

    t_point start = to_xycoordinate(onset);
    t_point end = to_xycoordinate(offset);

    //case 1: a straight segment
    if (current_segment.curvePointCount == 0) {
        setlinewidth(2);
        setcolor(t_color(0xFF, 0x00, 0x00));
        setlinestyle(SOLID);
        drawline(start, end);

    }//case 2: one curve point on the segment
    else if (current_segment.curvePointCount == 1) {

        LatLon current_curve_point = getStreetSegmentCurvePoint(streetseg_id, 0);
        t_point now = to_xycoordinate(current_curve_point);

        setlinewidth(2);
        setcolor(t_color(0xFF, 0x00, 0x00));
        setlinestyle(SOLID);
        drawline(start, now);
        drawline(now, end);

    }//case 3: more than one curve point on the segment
    else {

        LatLon first_curve_point = getStreetSegmentCurvePoint(streetseg_id, 0);
        LatLon last_curve_point = getStreetSegmentCurvePoint(streetseg_id, current_segment.curvePointCount - 1);

        t_point first = to_xycoordinate(first_curve_point);
        t_point last = to_xycoordinate(last_curve_point);

        setlinewidth(2);
        setcolor(t_color(0xFF, 0x00, 0x00));
        setlinestyle(SOLID);
        drawline(start, first);
        drawline(last, end);

        //loop through all the points, connect each two adjacent curve points
        for (unsigned i = 0, j = 1; i < current_segment.curvePointCount - 1; i++, j++) {

            LatLon current = getStreetSegmentCurvePoint(streetseg_id, i);
            LatLon next = getStreetSegmentCurvePoint(streetseg_id, j);

            t_point former = to_xycoordinate(current);
            t_point latter = to_xycoordinate(next);

            setlinewidth(8);
            setcolor(t_color(0xFF, 0xFF, 0xFF));
            setlinestyle(SOLID);
            drawline(former, latter);

        }
    }
}

//function to draw all the one way signs on the map

void draw_oneway_sign() {

    unsigned num_of_street = getNumberOfStreets();
    //loop through all the streets 
    for (unsigned idx = 0; idx < num_of_street; idx++) {

        vector<unsigned> street_seg = find_street_street_segments(idx);
        string street_name = getStreetName(idx);
        unsigned num_of_seg = street_seg.size();

        //loop through each street segment making up the street
        for (unsigned i = 0; i < num_of_seg; i++) {
            StreetSegmentInfo current_seg = getStreetSegmentInfo(street_seg[i]);

            //loop through each sub-street segment (the portion between each two curve points)
            for (unsigned curve_point_idx = 1; curve_point_idx < current_seg.curvePointCount; curve_point_idx++) {
                LatLon start = getStreetSegmentCurvePoint(street_seg[i], curve_point_idx - 1);
                LatLon end = getStreetSegmentCurvePoint(street_seg[i], curve_point_idx);
                t_point onset = to_xycoordinate(start);
                t_point offset = to_xycoordinate(end);
                t_bound_box wordsbound = find_words_box(onset, offset);

                //find the center and the angle of each sub-street segment
                t_point center;
                center.x = (onset.x + offset.x) / 2;
                center.y = (onset.y + offset.y) / 2;
                double degree = RAD_TO_DEG * atan((offset.y - onset.y) / (offset.x - onset.x));

                if (((offset.y - onset.y) < 0 && (offset.x - onset.x) < 0) || ((offset.y - onset.y) > 0 && (offset.x - onset.x) < 0))
                    degree += 180;

                //draw the arrow on all one way sub-street segment
                settextrotation(degree);
                setfontsize(11);
                setcolor(t_color(0x00, 0x00, 0x00));
                setlinestyle(SOLID);
                drawtext(center, "--->", wordsbound);

            }
        }
    }
}

//function to respond to clicks on the find button

void act_on_find_button_func(void (*drawscreen_ptr) (void)) {
    string street1, street2;
    cout << "Please enter first streets: " << endl;
    getline(cin, street1);
    cout << "Please enter second streets: " << endl;
    getline(cin, street2);
    cout << "Processing" << endl;


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
}

//function to respond to clicks on the library button

void act_on_library_button_func(void (*drawscreen_ptr) (void)) {
    //change the boolean variable to draw or not draw libraries
    if (show_libraries == false) {
        show_libraries = true;
        cout << "show all the libraries on the map" << endl;
    } else {
        show_libraries = false;
        cout << "hide all the libraries on the map" << endl;
        if (dataStructureSingleton::dataStructures()->pop != NULL) {
            delete dataStructureSingleton::dataStructures()->pop;
            dataStructureSingleton::dataStructures()->pop = NULL;
        }
    }

    if (show_recreation_centers == true) {
        show_recreation_centers = false;
        cout << "hide all the recreation centers on the map" << endl;
        if (dataStructureSingleton::dataStructures()->pop != NULL) {
            delete dataStructureSingleton::dataStructures()->pop;
            dataStructureSingleton::dataStructures()->pop = NULL;
        }
    }

    // Re-draw the screen 
    drawscreen_ptr();
}

//function to respond to clicks on the health button

void act_on_recreation_button_func(void (*drawscreen_ptr) (void)) {
    //change the boolean variable to draw or not draw recreation centers
    if (show_recreation_centers == false) {
        show_recreation_centers = true;
        cout << "show all the recreation centers on the map" << endl;
    } else {
        show_recreation_centers = false;
        cout << "hide all the recreation centers on the map" << endl;
        if (dataStructureSingleton::dataStructures()->pop != NULL) {
            delete dataStructureSingleton::dataStructures()->pop;
            dataStructureSingleton::dataStructures()->pop = NULL;
        }
    }

    if (show_libraries == true) {
        show_libraries = false;
        cout << "hide all the libraries on the map" << endl;
        if (dataStructureSingleton::dataStructures()->pop != NULL) {
            delete dataStructureSingleton::dataStructures()->pop;
            dataStructureSingleton::dataStructures()->pop = NULL;
        }
    }
    // Re-draw the screen 
    drawscreen_ptr();
}

void act_on_POI_button_func(void (*drawscreen_ptr) (void)) {
    //change the boolean variable to draw or not draw recreation centers
    if (show_POIs == false) {
        show_POIs = true;
        cout << "show all the points of interests on the map" << endl;
    } else {
        show_POIs = false;
        cout << "hide all the points of interests on the map" << endl;
    }
    // Re-draw the screen 
    drawscreen_ptr();
}


//function to draw subway routes and station entrances

void draw_subway_routes(float frame_factor) {
    // loop through all the subway routes
    for (auto subway_route_itr = dataStructureSingleton::dataStructures()->subway_vector.begin();
            subway_route_itr != dataStructureSingleton::dataStructures()->subway_vector.end();
            subway_route_itr++) {
        setlinewidth(3);
        setcolor(RED);
        setlinestyle(DASHED);

        // loop through all subway nodes
        for (auto subway_node_itr = subway_route_itr->position.begin();
                subway_node_itr != subway_route_itr->position.end() - 1; subway_node_itr++) {

            // pass to draw_seg_latlon to draw it on map
            draw_seg_latlon(*subway_node_itr, *(subway_node_itr + 1));
        }
    }

    //loop through all the subway station to draw each of them
    for (auto current_station_itr = dataStructureSingleton::dataStructures()->subway_station_vector.begin();
            current_station_itr != dataStructureSingleton::dataStructures()->subway_station_vector.end();
            current_station_itr++) {
        t_point location = to_xycoordinate(current_station_itr->position);
        setcolor(BLUE);
        settextrotation(0);

        //the icon is a green circle when the frame factor is larger than 0.01
        //"SE" is shown on the icon when the frame factor is smaller than 0.01
        draw_icon_for_POI(frame_factor, "SE", location, current_station_itr->name);

    }
}

void draw_spec_icon(float frame_factor, t_color color, t_point location) {
    if (frame_factor >= 1) {
        setcolor(DARKGREY);
        fillellipticarc(location, 100, 50, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 100, location.y + 200);
        t_point point3 = t_point(location.x + 100, location.y + 200);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 200, 100, 0, 360);
    } else if (frame_factor < 1 && frame_factor >= 0.05) {
        setcolor(DARKGREY);
        fillellipticarc(location, 100, 50, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 100, location.y + 200);
        t_point point3 = t_point(location.x + 100, location.y + 200);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 200, 100, 0, 360);
    } else if (frame_factor < 0.05 && frame_factor >= 0.01) {
        setcolor(DARKGREY);
        fillellipticarc(location, 50, 25, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 50, location.y + 100);
        t_point point3 = t_point(location.x + 50, location.y + 100);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 100, 50, 0, 360);

    } else if (frame_factor < 0.01 && frame_factor >= 0.001) {
        setcolor(DARKGREY);
        fillellipticarc(location, 50, 25, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 50, location.y + 100);
        t_point point3 = t_point(location.x + 50, location.y + 100);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 100, 50, 0, 360);
    } else if (frame_factor < 0.001 && frame_factor >= 0.0001) {
        setcolor(DARKGREY);
        fillellipticarc(location, 20, 10, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 20, location.y + 40);
        t_point point3 = t_point(location.x + 20, location.y + 40);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 40, 20, 0, 360);
    } else {
        setcolor(DARKGREY);
        fillellipticarc(location, 2, 1, 0, 360);
        setcolor(color);
        t_point point1 = t_point(location.x, location.y);
        t_point point2 = t_point(location.x - 2, location.y + 6);
        t_point point3 = t_point(location.x + 2, location.y + 6);
        t_point points[] = {point1, point2, point3};
        fillpoly(points, 3);
        fillarc(location.x, location.y + 6, 2, 0, 360);
    }
}

//function to draw all the libraries on the map

void draw_library(float frame_factor) {
    //loop through all the library to draw each of them
    for (auto current_lib_itr = dataStructureSingleton::dataStructures()->library_vector.begin();
            current_lib_itr != dataStructureSingleton::dataStructures()->library_vector.end();
            current_lib_itr++) {
        t_point location = to_xycoordinate(current_lib_itr->position);

        draw_spec_icon(frame_factor, YELLOW, location);
    }
}

//function to draw all the recreation centers on the map

void draw_recreation_center(float frame_factor) {
    //loop through all the recreation center to draw each of them
    for (auto current_recre_itr = dataStructureSingleton::dataStructures()->recreation_vector.begin();
            current_recre_itr != dataStructureSingleton::dataStructures()->recreation_vector.end();
            current_recre_itr++) {
        t_point location = to_xycoordinate(current_recre_itr->position);

        draw_spec_icon(frame_factor, PINK, location);
    }
}

void draw_icon_for_POI(float frame_factor, string icon, t_point location, string name) {
    /*if (frame_factor < 1 && frame_factor >= 0.05) {
        fillarc(location.x, location.y, 40, 0, 360);
    }
    else */if (frame_factor < 0.05 && frame_factor >= 0.01) {
        fillarc(location.x, location.y, 20, 0, 360);
    } else if (frame_factor < 0.01 && frame_factor >= 0.001) {
        fillarc(location.x, location.y, 10, 0, 360);
    } else if (frame_factor < 0.001 && frame_factor >= 0.0001) {
        fillarc(location.x, location.y, 9, 0, 360);
        setcolor(BLACK);
        setfontsize(8);
        t_bound_box text_bound = t_bound_box(location.x - 10, location.y - 10, location.x + 10, location.y + 10);
        drawtext(location, icon, text_bound);
    } else if (frame_factor < 0.0001 && frame_factor >= 0.00005) {
        fillarc(location.x, location.y, 5, 0, 360);
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
        fillarc(location.x, location.y, 1, 0, 360);
        setcolor(BLACK);
        setfontsize(6);
        t_bound_box text_bound = t_bound_box(location.x - 3, location.y - 3, location.x + 3, location.y + 3);
        drawtext(location, icon, text_bound);
        draw_POI_name(name, location);
    }
}

void draw_POI(float frame_factor) {
    draw_finance(frame_factor);
    draw_restaurant(frame_factor);
    draw_car(frame_factor);
    draw_arts(frame_factor);
    draw_education(frame_factor);

}

void draw_finance(float frame_factor) {
    //loop through all the library to draw each of them
    for (auto current_fin_itr = dataStructureSingleton::dataStructures()->finance_vector.begin();
            current_fin_itr != dataStructureSingleton::dataStructures()->finance_vector.end();
            current_fin_itr++) {
        t_point location = to_xycoordinate(current_fin_itr->position);
        setcolor(GREEN);
        settextrotation(0);
        //the icon is a green circle when the frame factor is larger than 0.01
        //"SE" is shown on the icon when the frame factor is smaller than 0.01
        draw_icon_for_POI(frame_factor, "$", location, current_fin_itr->name);
    }
}

void draw_restaurant(float frame_factor) {
    //loop through all the library to draw each of them
    for (auto current_res_itr = dataStructureSingleton::dataStructures()->restaurant_vector.begin();
            current_res_itr != dataStructureSingleton::dataStructures()->restaurant_vector.end();
            current_res_itr++) {
        t_point location = to_xycoordinate(current_res_itr->position);
        setcolor(MEDIUMPURPLE);
        settextrotation(0);
        //the icon is a green circle when the frame factor is larger than 0.01
        //"SE" is shown on the icon when the frame factor is smaller than 0.01
        draw_icon_for_POI(frame_factor, "FD", location, current_res_itr->name);
    }
}

void draw_car(float frame_factor) {
    //loop through all the library to draw each of them
    for (auto current_car_itr = dataStructureSingleton::dataStructures()->car_vector.begin();
            current_car_itr != dataStructureSingleton::dataStructures()->car_vector.end();
            current_car_itr++) {
        t_point location = to_xycoordinate(current_car_itr->position);
        setcolor(WHITE);
        settextrotation(0);
        //the icon is a green circle when the frame factor is larger than 0.01
        //"SE" is shown on the icon when the frame factor is smaller than 0.01
        draw_icon_for_POI(frame_factor, "CS", location, current_car_itr->name);
    }
}

void draw_arts(float frame_factor) {
    //loop through all the library to draw each of them
    for (auto current_art_itr = dataStructureSingleton::dataStructures()->arts_vector.begin();
            current_art_itr != dataStructureSingleton::dataStructures()->arts_vector.end();
            current_art_itr++) {
        t_point location = to_xycoordinate(current_art_itr->position);
        setcolor(PLUM);
        settextrotation(0);
        //the icon is a green circle when the frame factor is larger than 0.01
        //"SE" is shown on the icon when the frame factor is smaller than 0.01
        draw_icon_for_POI(frame_factor, "arts", location, current_art_itr->name);
    }
}

void draw_education(float frame_factor) {
    //loop through all the library to draw each of them
    for (auto current_edu_itr = dataStructureSingleton::dataStructures()->education_vector.begin();
            current_edu_itr != dataStructureSingleton::dataStructures()->education_vector.end();
            current_edu_itr++) {
        t_point location = to_xycoordinate(current_edu_itr->position);
        setcolor(MAGENTA);
        settextrotation(0);
        //the icon is a green circle when the frame factor is larger than 0.01
        //"SE" is shown on the icon when the frame factor is smaller than 0.01
        draw_icon_for_POI(frame_factor, "edu", location, current_edu_itr->name);
    }
}

spec_bubble_info::spec_bubble_info(t_point _location, t_color _color, std::string _name) {
    location = _location;
    color = _color;
    name = _name;
}

void draw_clicked_intersection() {
    unsigned intersection_ID = dataStructureSingleton::dataStructures()->clicked_intersection_ID;

    if (intersection_ID != 0) {


        LatLon LatLon_clicked_intersection = getIntersectionPosition(intersection_ID);

        //highlight clicked intersection
        setcolor(RED);
        t_point intersection_xy = to_xycoordinate(LatLon_clicked_intersection);
        fillarc(intersection_xy.x, intersection_xy.y, 2, 0, 360);

        //find the intersected street segment at the intersection
        vector<unsigned> intersection_seg = find_intersection_street_segments(intersection_ID);

        //highlight all the street segments with the same street name(s) on the map.
        //which is highlighting the intersected streets
        for (unsigned num = 0; num < intersection_seg.size(); num++) {
            StreetSegmentInfo current_seg = getStreetSegmentInfo(intersection_seg[num]);

            //find all the street segments corresponding to the street ID
            vector<unsigned> street_seg = find_street_street_segments(current_seg.streetID);
            unsigned num_of_seg = street_seg.size();
            for (unsigned i = 0; i < num_of_seg; i++) {

                draw_street_segR(street_seg[i]);

            }
        }
    }
}