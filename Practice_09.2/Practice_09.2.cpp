/*
Practice_09.2.cpp
Date : 2026-05-15
Author : Lee Jong Kwang
- Store 2 cities as a tuple
- Save the stored tuple and the distance between the two cities as a map
- Print the saved map nicely
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>
#include <string>
using namespace std;

/* 도시정보를 tuple로 저장*/
void addInterCityDist(map<pair<string, string>, int>& distanceMap,
	const string& city1, const string& city2, int distance) {
	distanceMap[make_pair(city1, city2)] = distance;
}

// 두 도시 간 거리 조회 함수
bool getDistance(const map<pair<string, string>, int>& distanceMap,
	const string& city1, const string& city2, int& distance) {
	if (city1 == city2) {
		distance = 0;
		return true;
	}
	auto key = make_pair(city1, city2);
	auto it = distanceMap.find(key);
	if (it != distanceMap.end()) {
		distance = it->second;
		return true;
	}
	return false;
}

/* 파일로부터 도시간의 거리를 불러오는 기능 */
int fgetCityPairDistTbl(istream& fin, set<string>& cities, map<pair<string, string>, int>& distMap) {
	string db_name, city1, city2;
	int dist;
	pair<string, string> icd_pair;
	fin >> db_name;
	while (!fin.eof()) {
		fin >> city1 >> city2 >> dist;
		/* a - b, b - a 경로 모두 등록 */
		cities.insert(city1);
		cities.insert(city2);
		addInterCityDist(distMap, city1, city2, dist);
		addInterCityDist(distMap, city2, city1, dist);
	} return distMap.size();
}

/* map 테이블 이뿌게 출력*/
void printDistanceTable(const map<pair<string, string>, int>& distanceMap, const set<string>& cities) {
	const int width = 10;
	cout << "\n[도시 간 거리표 (km)]\n\n";
	/* 제목 출력하기 */
	cout << left << setw(width) << "City" << "| ";
	for (const auto& colCity : cities) {
		cout << right << setw(width) << colCity;
	}
	cout << "\n";
	cout << string(width, '-') << "+";
	cout << string(width * cities.size() + 1, '-') << "\n";
	/* map 내용을 이쁘게 출력 */
	for (const auto& rowCity : cities) {
		cout << left << setw(width) << rowCity << "| ";
		for (const auto& colCity : cities) {
			int dist;
			if (getDistance(distanceMap, rowCity, colCity, dist)) {
				cout << right << setw(width) << dist;
			}
			else {
				cout << right << setw(width) << " - ";
			}
		}
		cout << "\n";
	}
}

/* 메인 함수 */
int main() {
	ifstream fin;
	map<pair<string, string>, int> interCityDistMap;
	set<string> cities;
	fin.open("KR_InterCityDist_11.txt");
	if (fin.fail()) {
		cout << "Error in opening KR_InterCityDist_11.txt !!\n";
		return -1;
	}
	/* 파일로부터 거리 읽어오기 */
	fgetCityPairDistTbl(fin, cities, interCityDistMap);
	/* 이쁘게 출력 */
	printDistanceTable(interCityDistMap, cities);
	return 0;
}