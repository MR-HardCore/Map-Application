#include <algorithm>
#include <unittest++/UnitTest++.h>
#include "unit_test_util.h"
#include "m1.h"
#include "StreetsDatabaseAPI.h"

using ece297test::relative_error;

struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(0);
        rand_intersection = std::uniform_int_distribution<unsigned>(0, getNumberOfIntersections()-1);
        rand_street = std::uniform_int_distribution<unsigned>(1, getNumberOfStreets()-1);
        rand_segment = std::uniform_int_distribution<unsigned>(0, getNumberOfStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<unsigned>(0, getNumberOfPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<float>(43.48, 43.91998);
        rand_lon = std::uniform_real_distribution<float>(-79.78998, -79.00001);
    }

    std::minstd_rand rng;
    std::uniform_int_distribution<unsigned> rand_intersection;
    std::uniform_int_distribution<unsigned> rand_street;
    std::uniform_int_distribution<unsigned> rand_segment;
    std::uniform_int_distribution<unsigned> rand_poi;
    std::uniform_real_distribution<float> rand_lat;
    std::uniform_real_distribution<float> rand_lon;
};

SUITE(intersection_queries_perf) {
    TEST_FIXTURE(MapFixture, intersection_street_segments_perf) {
        //Verify Functionality
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {1, 16172};
        actual = find_intersection_street_segments(2);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8375, 84769, 84770, 84771};
        actual = find_intersection_street_segments(9254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8862, 8863};
        actual = find_intersection_street_segments(9746);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {17156, 17157, 20557};
        actual = find_intersection_street_segments(17927);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {19931, 19939, 92896, 127687};
        actual = find_intersection_street_segments(20645);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {28035, 28036};
        actual = find_intersection_street_segments(28614);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {31750, 62898, 62938};
        actual = find_intersection_street_segments(32001);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {32059, 32060, 32062};
        actual = find_intersection_street_segments(32336);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {44726, 44939, 45136};
        actual = find_intersection_street_segments(43318);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {48699, 48996, 51880};
        actual = find_intersection_street_segments(46370);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {61198, 103871, 103872};
        actual = find_intersection_street_segments(55693);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {61709, 61710, 111210};
        actual = find_intersection_street_segments(56048);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {68960, 69005, 69006};
        actual = find_intersection_street_segments(60991);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {72735, 72739, 123676, 141296};
        actual = find_intersection_street_segments(63368);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {74284, 74286, 123700, 124633};
        actual = find_intersection_street_segments(64423);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {75786, 75790, 75799};
        actual = find_intersection_street_segments(65450);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {84696, 84697, 84745, 84746};
        actual = find_intersection_street_segments(71071);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {97312, 97318, 111785};
        actual = find_intersection_street_segments(79039);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {139854, 139855};
        actual = find_intersection_street_segments(80922);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {113071, 152692};
        actual = find_intersection_street_segments(88111);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {123169, 123172, 123173};
        actual = find_intersection_street_segments(93381);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {126892, 129158, 129159};
        actual = find_intersection_street_segments(95411);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {130041, 130042, 130043, 130044};
        actual = find_intersection_street_segments(97041);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {131859, 131951};
        actual = find_intersection_street_segments(97899);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {132206, 136177};
        actual = find_intersection_street_segments(98121);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {133375, 133394, 133395};
        actual = find_intersection_street_segments(98699);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {146596, 146600, 146601};
        actual = find_intersection_street_segments(104651);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {147664, 147665, 147671};
        actual = find_intersection_street_segments(105204);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {148043, 148046};
        actual = find_intersection_street_segments(105350);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {156200, 156287, 156288};
        actual = find_intersection_street_segments(108303);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        //Generate random inputs
        std::vector<unsigned> intersection_ids;
        for(size_t i = 0; i < 15000000; i++) {
            intersection_ids.push_back(rand_intersection(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1106);
            std::vector<unsigned> result;
            for(size_t i = 0; i < 15000000; i++) {
                result = find_intersection_street_segments(intersection_ids[i]);
            }
        }
    } //intersection_street_segments_perf

    TEST_FIXTURE(MapFixture, intersection_street_names_perf) {
        //Verify Functionality
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        
        expected = {"Highway 401 Eastbound Collectors", "Highway 401 Eastbound Collectors"};
        actual = find_intersection_street_names(2);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Heath Street West", "Heath Street West", "Russell Hill Road", "Russell Hill Road"};
        actual = find_intersection_street_names(9254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Millwood Road", "Millwood Road"};
        actual = find_intersection_street_names(9746);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Lace Fernway", "Rock Fernway", "Rock Fernway"};
        actual = find_intersection_street_names(17927);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Major Mackenzie Drive West", "Major Mackenzie Drive West", "Major Mackenzie Drive West", "Starling Boulevard"};
        actual = find_intersection_street_names(20645);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Bramalea Road", "Bramalea Road"};
        actual = find_intersection_street_names(28614);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Flycatcher Avenue", "Flycatcher Avenue"};
        actual = find_intersection_street_names(32001);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(32336);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Cross Country Boulevard", "English Rose Lane", "English Rose Lane"};
        actual = find_intersection_street_names(43318);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Lagani Avenue", "Strathearn Avenue", "Strathearn Avenue"};
        actual = find_intersection_street_names(46370);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Kingston Road", "Kingston Road"};
        actual = find_intersection_street_names(55693);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Bonis Avenue", "Bonis Avenue"};
        actual = find_intersection_street_names(56048);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Gentian Drive", "Gentian Drive", "Sagamore Crescent"};
        actual = find_intersection_street_names(60991);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"16th Avenue", "16th Avenue", "<unknown>", "Spadina Road"};
        actual = find_intersection_street_names(63368);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Commerce Valley Drive East", "Highway 7", "Highway 7"};
        actual = find_intersection_street_names(64423);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Bankside Drive", "Highbank Road", "Highbank Road"};
        actual = find_intersection_street_names(65450);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Brentwood Road North", "Brentwood Road North", "Lynngrove Avenue", "Lynngrove Avenue"};
        actual = find_intersection_street_names(71071);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Gardiner Expressway", "Gardiner Expressway"};
        actual = find_intersection_street_names(79039);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Church Street", "Church Street"};
        actual = find_intersection_street_names(80922);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Eglinton Avenue East", "Eglinton Avenue East"};
        actual = find_intersection_street_names(88111);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(93381);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Grosvenor Street", "Grosvenor Street"};
        actual = find_intersection_street_names(95411);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(97041);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(97899);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Don Valley Parkway Northbound", "Don Valley Parkway Northbound"};
        actual = find_intersection_street_names(98121);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(98699);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(104651);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(105204);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(105350);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(108303);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        //Generate random inputs
        std::vector<unsigned> intersection_ids;
        for(size_t i = 0; i < 1000000; i++) {
            intersection_ids.push_back(rand_intersection(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1058);
            std::vector<std::string> result;
            for(size_t i = 0; i < 1000000; i++) {
                result = find_intersection_street_names(intersection_ids[i]);
            }
        }
    } //intersection_street_names_perf

    TEST_FIXTURE(MapFixture, directly_connected_perf) {
        //Verify Functionality
        CHECK_EQUAL(1, are_directly_connected(2, 2));
        
        CHECK_EQUAL(0, are_directly_connected(7799, 20881));
        
        CHECK_EQUAL(0, are_directly_connected(9138, 19737));
        
        CHECK_EQUAL(1, are_directly_connected(9254, 9254));
        
        CHECK_EQUAL(1, are_directly_connected(9746, 9747));
        
        CHECK_EQUAL(1, are_directly_connected(17927, 21290));
        
        CHECK_EQUAL(0, are_directly_connected(24337, 84933));
        
        CHECK_EQUAL(1, are_directly_connected(28614, 28615));
        
        CHECK_EQUAL(1, are_directly_connected(32336, 32337));
        
        CHECK_EQUAL(0, are_directly_connected(33571, 56039));
        
        CHECK_EQUAL(0, are_directly_connected(43037, 85958));
        
        CHECK_EQUAL(0, are_directly_connected(47762, 44839));
        
        CHECK_EQUAL(0, are_directly_connected(53589, 84115));
        
        CHECK_EQUAL(1, are_directly_connected(56048, 56049));
        
        CHECK_EQUAL(1, are_directly_connected(63368, 93660));
        
        CHECK_EQUAL(1, are_directly_connected(64423, 64425));
        
        CHECK_EQUAL(0, are_directly_connected(64476, 10190));
        
        CHECK_EQUAL(0, are_directly_connected(65253, 91960));
        
        CHECK_EQUAL(1, are_directly_connected(65450, 65451));
        
        CHECK_EQUAL(0, are_directly_connected(66335, 47046));
        
        CHECK_EQUAL(0, are_directly_connected(67120, 63032));
        
        CHECK_EQUAL(0, are_directly_connected(75004, 59237));
        
        CHECK_EQUAL(1, are_directly_connected(79039, 5921));
        
        CHECK_EQUAL(0, are_directly_connected(80465, 34189));
        
        CHECK_EQUAL(1, are_directly_connected(95411, 95410));
        
        CHECK_EQUAL(1, are_directly_connected(97899, 97904));
        
        CHECK_EQUAL(1, are_directly_connected(98121, 98118));
        
        CHECK_EQUAL(1, are_directly_connected(98699, 5445));
        
        CHECK_EQUAL(1, are_directly_connected(101898, 101892));
        
        CHECK_EQUAL(1, are_directly_connected(105350, 105349));
        
        //Generate random inputs
        std::vector<unsigned> intersection_ids_1;
        std::vector<unsigned> intersection_ids_2;
        for(size_t i = 0; i < 2000000; i++) {
            intersection_ids_1.push_back(rand_intersection(rng));
            intersection_ids_2.push_back(rand_intersection(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1022);
            bool result;
            for(size_t i = 0; i < 2000000; i++) {
                result &= are_directly_connected(intersection_ids_1[i], intersection_ids_2[i]);
            }
        }
    } //directly_connected_perf

    TEST_FIXTURE(MapFixture, adjacent_intersections_perf) {
        //Verify Functionality
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {605, 618};
        actual = find_adjacent_intersections(617);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {1053, 5209, 8613, 12776};
        actual = find_adjacent_intersections(1054);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {5735, 5742, 92588};
        actual = find_adjacent_intersections(5743);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8457, 8473, 97063};
        actual = find_adjacent_intersections(8474);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {11876, 13757};
        actual = find_adjacent_intersections(13734);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_adjacent_intersections(19860);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {23082, 23091, 23095};
        actual = find_adjacent_intersections(23092);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {26128, 26130, 26131};
        actual = find_adjacent_intersections(26129);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_adjacent_intersections(37565);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {38322, 38324, 38331};
        actual = find_adjacent_intersections(38323);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {41473, 41475};
        actual = find_adjacent_intersections(41474);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {43487, 43489};
        actual = find_adjacent_intersections(43486);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {51843, 51851};
        actual = find_adjacent_intersections(51845);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {57090, 57112, 57206};
        actual = find_adjacent_intersections(57089);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {6426, 58400};
        actual = find_adjacent_intersections(58405);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {29375, 58488};
        actual = find_adjacent_intersections(58487);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {64891, 64893, 90122};
        actual = find_adjacent_intersections(64892);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {66844, 66851, 66853};
        actual = find_adjacent_intersections(66852);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {68309, 68373};
        actual = find_adjacent_intersections(68353);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {77580, 77607};
        actual = find_adjacent_intersections(77581);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {79730, 79734};
        actual = find_adjacent_intersections(79729);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {66367, 66374, 85117};
        actual = find_adjacent_intersections(85110);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {86125};
        actual = find_adjacent_intersections(86124);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {89376, 89377};
        actual = find_adjacent_intersections(89375);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {19034, 19035, 19036};
        actual = find_adjacent_intersections(93870);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {9383, 71942};
        actual = find_adjacent_intersections(95282);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {98497};
        actual = find_adjacent_intersections(98500);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {101380, 101384, 101391};
        actual = find_adjacent_intersections(101383);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {102370, 102400, 102404};
        actual = find_adjacent_intersections(102401);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {103270, 103272};
        actual = find_adjacent_intersections(103271);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        //Generate random inputs
        std::vector<unsigned> intersection_ids;
        for(size_t i = 0; i < 1000000; i++) {
            intersection_ids.push_back(rand_intersection(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1005);
            std::vector<unsigned> result;
            for(size_t i = 0; i < 1000000; i++) {
                result = find_adjacent_intersections(intersection_ids[i]);
            }
        }
    } //adjacent_intersections_perf

} //intersection_queries_perf

SUITE(street_queries_perf) {
    TEST_FIXTURE(MapFixture, street_street_segments_perf) {
        //Verify Functionality
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {0, 1, 9539, 9540, 9541, 16160, 16172, 39216, 123617, 153388};
        actual = find_street_street_segments(1);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {6907};
        actual = find_street_street_segments(1804);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {7225, 22779, 22780, 107013, 147968, 147969};
        actual = find_street_street_segments(1900);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {13948, 13949};
        actual = find_street_street_segments(3494);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {15852, 15853, 15854, 15855, 15856, 15857, 15858, 15957, 15958, 15959, 15960, 15961, 85094, 85095, 85097};
        actual = find_street_street_segments(4023);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {21793, 21794, 21795, 21796, 21797};
        actual = find_street_street_segments(5576);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25098};
        actual = find_street_street_segments(6236);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25283};
        actual = find_street_street_segments(6301);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {44114, 64270};
        actual = find_street_street_segments(8441);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {47988};
        actual = find_street_street_segments(9036);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {54213, 54214, 54215};
        actual = find_street_street_segments(10853);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {54397, 54404, 54438, 54442, 54471, 54476, 54495};
        actual = find_street_street_segments(10922);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {58138};
        actual = find_street_street_segments(11885);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {60682};
        actual = find_street_street_segments(12348);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {61520, 61531, 61551};
        actual = find_street_street_segments(12554);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {62382};
        actual = find_street_street_segments(12754);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {67347};
        actual = find_street_street_segments(13849);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {74944};
        actual = find_street_street_segments(15402);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {76683, 76691, 76692, 76694, 76701, 76709, 76726, 76727, 76742, 76743, 76744, 76765, 76783, 76791};
        actual = find_street_street_segments(15769);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {82673};
        actual = find_street_street_segments(17170);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {93006, 93454, 93505, 93621, 93824, 106518, 106519, 106520};
        actual = find_street_street_segments(18197);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {94065};
        actual = find_street_street_segments(18592);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {96821};
        actual = find_street_street_segments(18910);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {100810, 100811};
        actual = find_street_street_segments(19077);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {101150};
        actual = find_street_street_segments(19120);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {101692, 101693, 101694, 101695, 101696};
        actual = find_street_street_segments(19233);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {120018, 120019};
        actual = find_street_street_segments(20393);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {121988, 121989, 121990};
        actual = find_street_street_segments(20500);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {123141, 123142, 123143};
        actual = find_street_street_segments(20529);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {154600, 154601};
        actual = find_street_street_segments(21104);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        //Generate random inputs
        std::vector<unsigned> street_ids;
        for(size_t i = 0; i < 8000000; i++) {
            street_ids.push_back(rand_street(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1087);
            // UnitTest::TimeHelpers::SleepMs(3000);
            std::vector<unsigned> result;
            for(size_t i = 0; i < 8000000; i++) {
                result = find_street_street_segments(street_ids[i]);
            }
        }
    } //street_street_segments_perf

    TEST_FIXTURE(MapFixture, all_street_intersections_perf) {
        //Verify Functionality
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {0, 1, 2, 168, 6138, 10366, 10367, 10368, 10369, 16905, 38486};
        actual = find_all_street_intersections(1);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {7702, 7722};
        actual = find_all_street_intersections(1804);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8044, 8045, 23553, 23554, 23555, 25383, 105316};
        actual = find_all_street_intersections(1900);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {12902, 14751, 14752};
        actual = find_all_street_intersections(3494);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {15235, 15261, 15263, 15269, 15270, 15272, 15275, 15277, 15278, 15281, 15282, 16660, 16661, 16662, 16663, 71269};
        actual = find_all_street_intersections(4023);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {22567, 22568, 22569, 22570, 22571, 22572};
        actual = find_all_street_intersections(5576);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25751, 25762};
        actual = find_all_street_intersections(6236);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25924, 25925};
        actual = find_all_street_intersections(6301);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {42545, 42546, 43046};
        actual = find_all_street_intersections(8441);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {45511, 45525};
        actual = find_all_street_intersections(9036);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {16889, 50975, 50977, 50978};
        actual = find_all_street_intersections(10853);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {13272, 51120, 51144, 51151, 51153, 51161, 51162, 51222};
        actual = find_all_street_intersections(10922);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {53763, 53764};
        actual = find_all_street_intersections(11885);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {55393, 55413};
        actual = find_all_street_intersections(12348);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {46200, 55911, 55920, 55932};
        actual = find_all_street_intersections(12554);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {56498, 56499};
        actual = find_all_street_intersections(12754);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {59911, 59922};
        actual = find_all_street_intersections(13849);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {64740, 65062};
        actual = find_all_street_intersections(15402);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8081, 8091, 66087, 66088, 66093, 66097, 66098, 66109, 66110, 66136, 66137, 66142, 66148, 66149, 66160};
        actual = find_all_street_intersections(15769);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {50707, 69955};
        actual = find_all_street_intersections(17170);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {76215, 76216, 76240, 76241, 76406, 76721, 76741, 84338, 84339};
        actual = find_all_street_intersections(18197);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {76949, 76953};
        actual = find_all_street_intersections(18592);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {78756, 78757};
        actual = find_all_street_intersections(18910);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {34647, 34664, 81074};
        actual = find_all_street_intersections(19077);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {81258, 81259};
        actual = find_all_street_intersections(19120);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {81439, 81440, 81616, 81617, 81618};
        actual = find_all_street_intersections(19233);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {43836, 91582, 91614};
        actual = find_all_street_intersections(20393);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {92650, 92669, 92699, 92700};
        actual = find_all_street_intersections(20500);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {18158, 52275, 93360, 93361};
        actual = find_all_street_intersections(20529);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {84210, 107702, 107703};
        actual = find_all_street_intersections(21104);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        //Generate random inputs
        std::vector<unsigned> street_ids;
        for(size_t i = 0; i < 1600000; i++) {
            street_ids.push_back(rand_street(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1376);
            std::vector<unsigned> result;
            for(size_t i = 0; i < 1600000; i++) {
                result = find_all_street_intersections(street_ids[i]);
            }
        }
    } //all_street_intersections_perf

    TEST_FIXTURE(MapFixture, intersection_ids_from_street_names_perf) {
        //Verify Functionality
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {};
        actual = find_intersection_ids_from_street_names("662 Warden Avenue", "Duplex Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {55393, 55413};
        actual = find_intersection_ids_from_street_names("Blacktoft Drive", "Braymore Boulevard");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {27023, 27024};
        actual = find_intersection_ids_from_street_names("Breckonwood Crescent", "Willowbrook Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {55920, 55932};
        actual = find_intersection_ids_from_street_names("Brigadoon Crescent", "Andes Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Brixham Gate", "Baffin Court");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {68929, 68942};
        actual = find_intersection_ids_from_street_names("Canada Goose Boulevard", "Dolphin Song Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Caradoc Lane", "Manorheights Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Cayley Lane", "Goldpine Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Chartway Boulevard", "Delle Donne Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {51151};
        actual = find_intersection_ids_from_street_names("Craiglee Drive", "Phillip Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {107703};
        actual = find_intersection_ids_from_street_names("Decorso Drive", "Sagebrook Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Deer Hollow Court", "Dime Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {46237, 49483};
        actual = find_intersection_ids_from_street_names("Gells Road", "Skopit Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {0};
        actual = find_intersection_ids_from_street_names("Highway 401 Eastbound Collectors", "Ramp to Highway 404 / Don Valley Parkway");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {78756, 78757};
        actual = find_intersection_ids_from_street_names("Kingsborough Street", "Kingmount Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Lorne Park Road", "Thornhill Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25924, 25925};
        actual = find_intersection_ids_from_street_names("Mantle Crescent", "McCovey Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Nipigon Avenue", "Patron Cove");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Northey Drive", "Garland Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25762};
        actual = find_intersection_ids_from_street_names("Ottewell Crescent", "Maple Ridge Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Port Street West", "Dixington Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {59922};
        actual = find_intersection_ids_from_street_names("Richwood Street", "Wright Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {45996, 49310};
        actual = find_intersection_ids_from_street_names("Romfield Circuit", "Stornoway Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Rose Avenue", "Daniel Court");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Sumner Lane", "Starfire Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Teak Avenue", "Commerce Valley Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {14752};
        actual = find_intersection_ids_from_street_names("Thirty Seventh Street", "Lake Promenade");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8081, 8091};
        actual = find_intersection_ids_from_street_names("White Clover Way", "Mavis Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Wychcrest Avenue", "Aldridge Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Wycliffe Crescent", "Wetherby Circle");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        //Generate random inputs
        std::vector<std::string> street_names_1;
        std::vector<std::string> street_names_2;
        for(size_t i = 0; i < 900000; i++) {
            unsigned street_id1 = rand_street(rng);
            unsigned street_id2 = rand_street(rng);
            street_names_1.push_back(getStreetName(street_id1));
            street_names_2.push_back(getStreetName(street_id2));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(983);
            std::vector<unsigned> result;
            for(size_t i = 0; i < 900000; i++) {
                result = find_intersection_ids_from_street_names(street_names_1[i], street_names_2[i]);
            }
        }
    } //intersection_ids_from_street_names_perf

} //street_queries_perf

SUITE(distance_time_queries_perf) {
    TEST_FIXTURE(MapFixture, distance_between_two_points_perf) {
        //Verify Functionality
        double expected;
        double actual;
        
        expected = 48901.358372445;
        actual = find_distance_between_two_points(LatLon(43.89957, -79.504), LatLon(43.50177, -79.76295));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 21420.02903886264;
        actual = find_distance_between_two_points(LatLon(43.49641, -79.44099), LatLon(43.68565, -79.3917));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 21376.69698715043;
        actual = find_distance_between_two_points(LatLon(43.51353, -79.42992), LatLon(43.55679, -79.68823));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 54931.5136634997;
        actual = find_distance_between_two_points(LatLon(43.51741, -79.78996), LatLon(43.87229, -79.31493));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 16312.28938023908;
        actual = find_distance_between_two_points(LatLon(43.68439, -79.59126), LatLon(43.56063, -79.48255));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 30754.44346434695;
        actual = find_distance_between_two_points(LatLon(43.52221, -79.47686), LatLon(43.75831, -79.27802));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 32599.47236635839;
        actual = find_distance_between_two_points(LatLon(43.68481, -79.4072), LatLon(43.57791, -79.78425));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 39023.60685698516;
        actual = find_distance_between_two_points(LatLon(43.82004, -79.40101), LatLon(43.56441, -79.73337));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 36216.89085942857;
        actual = find_distance_between_two_points(LatLon(43.48414, -79.33807), LatLon(43.70441, -79.66917));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 33893.61559371489;
        actual = find_distance_between_two_points(LatLon(43.49874, -79.36289), LatLon(43.80342, -79.35551));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 11389.84730426912;
        actual = find_distance_between_two_points(LatLon(43.55212, -79.33412), LatLon(43.62733, -79.23817));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 42859.86777600402;
        actual = find_distance_between_two_points(LatLon(43.7766, -79.33257), LatLon(43.50935, -79.71619));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 42289.1208070249;
        actual = find_distance_between_two_points(LatLon(43.6515, -79.13216), LatLon(43.55277, -79.6392));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 44458.96413928206;
        actual = find_distance_between_two_points(LatLon(43.59955, -79.08165), LatLon(43.59901, -79.63361));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 25138.05910348874;
        actual = find_distance_between_two_points(LatLon(43.62518, -79.13019), LatLon(43.61975, -79.44231));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 30568.60793684721;
        actual = find_distance_between_two_points(LatLon(43.56346, -79.02532), LatLon(43.65511, -79.38316));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 44386.71395539412;
        actual = find_distance_between_two_points(LatLon(43.5922, -79.67077), LatLon(43.74093, -79.15884));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 31384.02264981917;
        actual = find_distance_between_two_points(LatLon(43.62439, -79.65219), LatLon(43.6536, -79.2644));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 6010.516174706887;
        actual = find_distance_between_two_points(LatLon(43.73144, -79.6271), LatLon(43.746, -79.69913));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 39835.07710941207;
        actual = find_distance_between_two_points(LatLon(43.66745, -79.55527), LatLon(43.76731, -79.0794));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 14540.15794712581;
        actual = find_distance_between_two_points(LatLon(43.70654, -79.5463), LatLon(43.82749, -79.4776));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 41176.07519816377;
        actual = find_distance_between_two_points(LatLon(43.66126, -79.44331), LatLon(43.9166, -79.07198));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 14589.17096791525;
        actual = find_distance_between_two_points(LatLon(43.83619, -79.33003), LatLon(43.70514, -79.32238));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 20204.57351138864;
        actual = find_distance_between_two_points(LatLon(43.67019, -79.3085), LatLon(43.85175, -79.31635));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 15129.80999032024;
        actual = find_distance_between_two_points(LatLon(43.73481, -79.3028), LatLon(43.61821, -79.20594));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 4189.335030047673;
        actual = find_distance_between_two_points(LatLon(43.77595, -79.29842), LatLon(43.73858, -79.3049));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 10159.97945877936;
        actual = find_distance_between_two_points(LatLon(43.75237, -79.10904), LatLon(43.81199, -79.01318));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 46939.23730974402;
        actual = find_distance_between_two_points(LatLon(43.90305, -79.07779), LatLon(43.8575, -79.65986));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 53828.74092613246;
        actual = find_distance_between_two_points(LatLon(43.91593, -79.03275), LatLon(43.86306, -79.70026));
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 9622.930751213542;
        actual = find_distance_between_two_points(LatLon(43.91782, -79.09747), LatLon(43.90529, -79.21629));
        CHECK(relative_error(expected, actual) < 0.05);
        
        //Generate random inputs
        std::vector<LatLon> latlons_1;
        std::vector<LatLon> latlons_2;
        for(size_t i = 0; i < 30000000; i++) {
            latlons_1.push_back(LatLon(rand_lat(rng), rand_lon(rng)));
            latlons_2.push_back(LatLon(rand_lat(rng), rand_lon(rng)));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1114);
            double result;
            for(size_t i = 0; i < 30000000; i++) {
                result += find_distance_between_two_points(latlons_1[i], latlons_2[i]);
            }
        }
    } //distance_between_two_points_perf

    TEST_FIXTURE(MapFixture, street_segment_length_perf) {
        //Verify Functionality
        double expected;
        double actual;
        
        expected = 674.8669607293826;
        actual = find_street_segment_length(3);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 246.1086537368939;
        actual = find_street_segment_length(13418);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 91.86766496321486;
        actual = find_street_segment_length(14130);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 34.85348565791629;
        actual = find_street_segment_length(25991);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 49.92764455638124;
        actual = find_street_segment_length(29932);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 78.39967337096751;
        actual = find_street_segment_length(41486);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 62.21272659089265;
        actual = find_street_segment_length(46396);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 122.394028684053;
        actual = find_street_segment_length(46882);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 62.94792283465361;
        actual = find_street_segment_length(62805);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 88.79330698835589;
        actual = find_street_segment_length(67230);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 117.1440030680625;
        actual = find_street_segment_length(80747);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 115.4439063519075;
        actual = find_street_segment_length(81262);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 112.7704630804144;
        actual = find_street_segment_length(88428);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 133.6440988156629;
        actual = find_street_segment_length(91875);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 263.551426460903;
        actual = find_street_segment_length(93404);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 21.44858623530901;
        actual = find_street_segment_length(94892);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 49.64933999436872;
        actual = find_street_segment_length(103042);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 15.49511866263699;
        actual = find_street_segment_length(114595);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 74.45864350413386;
        actual = find_street_segment_length(117325);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 108.2830988447954;
        actual = find_street_segment_length(127748);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 13.16748662475364;
        actual = find_street_segment_length(135389);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 63.90268822923701;
        actual = find_street_segment_length(138331);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 52.32645906531687;
        actual = find_street_segment_length(140695);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 117.4620997451055;
        actual = find_street_segment_length(141939);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 60.67941886282961;
        actual = find_street_segment_length(142261);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 6.264595892006245;
        actual = find_street_segment_length(143098);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 104.2114678931176;
        actual = find_street_segment_length(151728);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 20.97509348185989;
        actual = find_street_segment_length(152530);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 87.31789561008861;
        actual = find_street_segment_length(152742);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 18.28536919458546;
        actual = find_street_segment_length(157023);
        CHECK(relative_error(expected, actual) < 0.05);
        
        //Generate random inputs
        std::vector<unsigned> segment_ids;
        for(size_t i = 0; i < 1600000; i++) {
            segment_ids.push_back(rand_segment(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(970);
            double result;
            for(size_t i = 0; i < 1600000; i++) {
                result += find_street_segment_length(segment_ids[i]);
            }
        }
    } //street_segment_length_perf

    TEST_FIXTURE(MapFixture, street_length_perf) {
        //Verify Functionality
        double expected;
        double actual;
        
        expected = 2671.060022501815;
        actual = find_street_length(1);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 319.8031789086556;
        actual = find_street_length(1804);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 991.6345677011659;
        actual = find_street_length(1900);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 535.2300643137936;
        actual = find_street_length(3494);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 1054.537675954481;
        actual = find_street_length(4023);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 433.3307719696763;
        actual = find_street_length(5576);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 326.0544311844756;
        actual = find_street_length(6236);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 389.5037450253016;
        actual = find_street_length(6301);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 675.3605744607062;
        actual = find_street_length(8441);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 436.51379181573;
        actual = find_street_length(9036);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 583.0059102253641;
        actual = find_street_length(10853);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 717.6103388001828;
        actual = find_street_length(10922);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 281.1736417858992;
        actual = find_street_length(11885);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 567.5241681847091;
        actual = find_street_length(12348);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 262.2003198206775;
        actual = find_street_length(12554);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 214.4103690763226;
        actual = find_street_length(12754);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 255.1514430545134;
        actual = find_street_length(13849);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 249.6506933623033;
        actual = find_street_length(15402);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 1905.152600338697;
        actual = find_street_length(15769);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 182.5506950106781;
        actual = find_street_length(17170);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 829.2028208201273;
        actual = find_street_length(18197);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 127.6533101140082;
        actual = find_street_length(18592);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 191.3392717280832;
        actual = find_street_length(18910);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 337.297016290511;
        actual = find_street_length(19077);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 148.3990884714312;
        actual = find_street_length(19120);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 497.7547202116976;
        actual = find_street_length(19233);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 161.8584820097527;
        actual = find_street_length(20393);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 395.2205610016454;
        actual = find_street_length(20500);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 294.2056766867215;
        actual = find_street_length(20529);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 403.8703884698567;
        actual = find_street_length(21104);
        CHECK(relative_error(expected, actual) < 0.05);
        
        //Generate random inputs
        std::vector<unsigned> street_ids;
        for(size_t i = 0; i < 400000; i++) {
            street_ids.push_back(rand_street(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1131);
            double result;
            for(size_t i = 0; i < 400000; i++) {
                result += find_street_length(street_ids[i]);
            }
        }
    } //street_length_perf

    TEST_FIXTURE(MapFixture, street_segment_travel_time_perf) {
        //Verify Functionality
        double expected;
        double actual;
        
        expected = 0.4049201764376296;
        actual = find_street_segment_travel_time(3);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.2953303844842727;
        actual = find_street_segment_travel_time(13418);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1102411979558579;
        actual = find_street_segment_travel_time(14130);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.04182418278949956;
        actual = find_street_segment_travel_time(25991);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.05991317346765749;
        actual = find_street_segment_travel_time(29932);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.09407960804516101;
        actual = find_street_segment_travel_time(41486);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.07465527190907117;
        actual = find_street_segment_travel_time(46396);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1468728344208635;
        actual = find_street_segment_travel_time(46882);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.07553750740158434;
        actual = find_street_segment_travel_time(62805);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1065519683860271;
        actual = find_street_segment_travel_time(67230);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.140572803681675;
        actual = find_street_segment_travel_time(80747);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.138532687622289;
        actual = find_street_segment_travel_time(81262);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1353245556964972;
        actual = find_street_segment_travel_time(88428);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1603729185787954;
        actual = find_street_segment_travel_time(91875);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.3162617117530835;
        actual = find_street_segment_travel_time(93404);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.02573830348237081;
        actual = find_street_segment_travel_time(94892);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.05957920799324248;
        actual = find_street_segment_travel_time(103042);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.01859414239516439;
        actual = find_street_segment_travel_time(114595);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.08935037220496064;
        actual = find_street_segment_travel_time(117325);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1624246482671931;
        actual = find_street_segment_travel_time(127748);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.01580098394970436;
        actual = find_street_segment_travel_time(135389);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.0766832258750844;
        actual = find_street_segment_travel_time(138331);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.06279175087838024;
        actual = find_street_segment_travel_time(140695);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1409545196941266;
        actual = find_street_segment_travel_time(141939);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.07281530263539554;
        actual = find_street_segment_travel_time(142261);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.007517515070407494;
        actual = find_street_segment_travel_time(143098);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1250537614717412;
        actual = find_street_segment_travel_time(151728);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.02517011217823186;
        actual = find_street_segment_travel_time(152530);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.1047814747321063;
        actual = find_street_segment_travel_time(152742);
        CHECK(relative_error(expected, actual) < 0.05);
        
        expected = 0.02194244303350255;
        actual = find_street_segment_travel_time(157023);
        CHECK(relative_error(expected, actual) < 0.05);
        
        //Generate random inputs
        std::vector<unsigned> segment_ids;
        for(size_t i = 0; i < 1600000; i++) {
            segment_ids.push_back(rand_segment(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1014);
            double result;
            for(size_t i = 0; i < 1600000; i++) {
                result += find_street_segment_travel_time(segment_ids[i]);
            }
        }
    } //street_segment_travel_time_perf

} //distance_time_queries_perf

SUITE(spatial_queries_perf) {
    TEST_FIXTURE(MapFixture, closest_poi_perf) {
        //Verify Functionality
        CHECK_EQUAL(316, find_closest_point_of_interest(LatLon(43.51741, -79.78996)));
        
        CHECK_EQUAL(316, find_closest_point_of_interest(LatLon(43.53968, -79.77652)));
        
        CHECK_EQUAL(3696, find_closest_point_of_interest(LatLon(43.54883, -79.76294)));
        
        CHECK_EQUAL(6038, find_closest_point_of_interest(LatLon(43.5564, -79.75731)));
        
        CHECK_EQUAL(3200, find_closest_point_of_interest(LatLon(43.55912, -79.74387)));
        
        CHECK_EQUAL(7469, find_closest_point_of_interest(LatLon(43.56133, -79.73864)));
        
        CHECK_EQUAL(681, find_closest_point_of_interest(LatLon(43.56441, -79.73337)));
        
        CHECK_EQUAL(4870, find_closest_point_of_interest(LatLon(43.57032, -79.68089)));
        
        CHECK_EQUAL(1752, find_closest_point_of_interest(LatLon(43.5922, -79.67077)));
        
        CHECK_EQUAL(3523, find_closest_point_of_interest(LatLon(43.59901, -79.63361)));
        
        CHECK_EQUAL(5844, find_closest_point_of_interest(LatLon(43.60174, -79.57462)));
        
        CHECK_EQUAL(8024, find_closest_point_of_interest(LatLon(43.61377, -79.50719)));
        
        CHECK_EQUAL(1312, find_closest_point_of_interest(LatLon(43.61975, -79.44231)));
        
        CHECK_EQUAL(183, find_closest_point_of_interest(LatLon(43.64908, -79.41658)));
        
        CHECK_EQUAL(7825, find_closest_point_of_interest(LatLon(43.65142, -79.40141)));
        
        CHECK_EQUAL(98, find_closest_point_of_interest(LatLon(43.65511, -79.38316)));
        
        CHECK_EQUAL(8103, find_closest_point_of_interest(LatLon(43.65997, -79.35538)));
        
        CHECK_EQUAL(3009, find_closest_point_of_interest(LatLon(43.73439, -79.34768)));
        
        CHECK_EQUAL(1879, find_closest_point_of_interest(LatLon(43.75162, -79.33743)));
        
        CHECK_EQUAL(6945, find_closest_point_of_interest(LatLon(43.76944, -79.33583)));
        
        CHECK_EQUAL(5431, find_closest_point_of_interest(LatLon(43.7766, -79.33257)));
        
        CHECK_EQUAL(8356, find_closest_point_of_interest(LatLon(43.83619, -79.33003)));
        
        CHECK_EQUAL(8206, find_closest_point_of_interest(LatLon(43.85112, -79.32314)));
        
        CHECK_EQUAL(8206, find_closest_point_of_interest(LatLon(43.85175, -79.31635)));
        
        CHECK_EQUAL(7914, find_closest_point_of_interest(LatLon(43.87229, -79.31493)));
        
        CHECK_EQUAL(6886, find_closest_point_of_interest(LatLon(43.88705, -79.24767)));
        
        CHECK_EQUAL(8455, find_closest_point_of_interest(LatLon(43.89022, -79.24205)));
        
        CHECK_EQUAL(3759, find_closest_point_of_interest(LatLon(43.90529, -79.21629)));
        
        CHECK_EQUAL(3759, find_closest_point_of_interest(LatLon(43.91232, -79.16315)));
        
        CHECK_EQUAL(8312, find_closest_point_of_interest(LatLon(43.91782, -79.09747)));
        
        //Generate random inputs
        std::vector<LatLon> latlons;
        for(size_t i = 0; i < 1000; i++) {
            latlons.push_back(LatLon(rand_lat(rng), rand_lon(rng)));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1344);
            unsigned result;
            for(size_t i = 0; i < 1000; i++) {
                result = find_closest_point_of_interest(latlons[i]);
            }
        }
    } //closest_poi_perf

    TEST_FIXTURE(MapFixture, closest_intersection_perf) {
        //Verify Functionality
        CHECK_EQUAL(96621, find_closest_intersection(LatLon(43.51741, -79.78996)));
        
        CHECK_EQUAL(9362, find_closest_intersection(LatLon(43.53968, -79.77652)));
        
        CHECK_EQUAL(9364, find_closest_intersection(LatLon(43.54883, -79.76294)));
        
        CHECK_EQUAL(65277, find_closest_intersection(LatLon(43.5564, -79.75731)));
        
        CHECK_EQUAL(82856, find_closest_intersection(LatLon(43.55912, -79.74387)));
        
        CHECK_EQUAL(65110, find_closest_intersection(LatLon(43.56133, -79.73864)));
        
        CHECK_EQUAL(65361, find_closest_intersection(LatLon(43.56441, -79.73337)));
        
        CHECK_EQUAL(66169, find_closest_intersection(LatLon(43.57032, -79.68089)));
        
        CHECK_EQUAL(66049, find_closest_intersection(LatLon(43.5922, -79.67077)));
        
        CHECK_EQUAL(24139, find_closest_intersection(LatLon(43.59901, -79.63361)));
        
        CHECK_EQUAL(39366, find_closest_intersection(LatLon(43.60174, -79.57462)));
        
        CHECK_EQUAL(60722, find_closest_intersection(LatLon(43.61377, -79.50719)));
        
        CHECK_EQUAL(96382, find_closest_intersection(LatLon(43.61975, -79.44231)));
        
        CHECK_EQUAL(5670, find_closest_intersection(LatLon(43.64908, -79.41658)));
        
        CHECK_EQUAL(4192, find_closest_intersection(LatLon(43.65142, -79.40141)));
        
        CHECK_EQUAL(98107, find_closest_intersection(LatLon(43.65511, -79.38316)));
        
        CHECK_EQUAL(12539, find_closest_intersection(LatLon(43.65997, -79.35538)));
        
        CHECK_EQUAL(56830, find_closest_intersection(LatLon(43.73439, -79.34768)));
        
        CHECK_EQUAL(52269, find_closest_intersection(LatLon(43.75162, -79.33743)));
        
        CHECK_EQUAL(7217, find_closest_intersection(LatLon(43.76944, -79.33583)));
        
        CHECK_EQUAL(18920, find_closest_intersection(LatLon(43.7766, -79.33257)));
        
        CHECK_EQUAL(4267, find_closest_intersection(LatLon(43.83619, -79.33003)));
        
        CHECK_EQUAL(84020, find_closest_intersection(LatLon(43.85112, -79.32314)));
        
        CHECK_EQUAL(93088, find_closest_intersection(LatLon(43.85175, -79.31635)));
        
        CHECK_EQUAL(63186, find_closest_intersection(LatLon(43.87229, -79.31493)));
        
        CHECK_EQUAL(91973, find_closest_intersection(LatLon(43.88705, -79.24767)));
        
        CHECK_EQUAL(91862, find_closest_intersection(LatLon(43.89022, -79.24205)));
        
        CHECK_EQUAL(78248, find_closest_intersection(LatLon(43.90529, -79.21629)));
        
        CHECK_EQUAL(39281, find_closest_intersection(LatLon(43.91232, -79.16315)));
        
        CHECK_EQUAL(95231, find_closest_intersection(LatLon(43.91782, -79.09747)));
        
        //Generate random inputs
        std::vector<LatLon> latlons;
        for(size_t i = 0; i < 1000; i++) {
            latlons.push_back(LatLon(rand_lat(rng), rand_lon(rng)));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(1347);
            unsigned result;
            for(size_t i = 0; i < 1000; i++) {
                result = find_closest_intersection(latlons[i]);
            }
        }
    } //closest_intersection_perf

} //spatial_queries_perf

