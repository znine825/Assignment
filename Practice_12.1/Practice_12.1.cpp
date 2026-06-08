/*
Homework_12.2.cpp
Date : 2026-06-04
Author : Lee Jong Kwang
- multimap과 unordered_multimap의 삽입, 검색 성능 비교
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>  
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;
using Clock = chrono::high_resolution_clock;
constexpr int NUM_DATA = 1'000'000;
constexpr int NUM_FIND_TEST = 100'000;

/* 삽입 성능 시간 측정 함수 */
template <typename Container>
long long measureInsertPerformance(Container& container, const vector<pair<string, string>>& kvStr_pairs) {
	auto start = Clock::now();
	for (const auto& kvStr_pair : kvStr_pairs) {
		container.insert(kvStr_pair);
	}

	auto end = Clock::now();
	auto elapsedMicro = chrono::duration_cast<chrono::microseconds>(end - start).count();
	return elapsedMicro;
}

/* 검색 성능 시간 측정 함수 */
template <typename Container>
long long measureFindPerformance(const Container& container, const vector<string>& testKeys) {
	size_t foundCount = 0;
	size_t num_test_words = testKeys.size();
	auto start = Clock::now();

	for (const auto& key : testKeys) {
		auto itr = container.find(key);
		if (itr != container.end()) {
			++foundCount;
		}
	}
	auto end = Clock::now();
	if (num_test_words != foundCount) {
		cout << "Error in find operations : foundCount (" << foundCount;
		cout << ") is different from size of testKeys(" << num_test_words << ")\n";
	}
	auto elapsedMicro = chrono::duration_cast<chrono::microseconds>(end - start).count();
	return elapsedMicro;
}

/* 메인 함수 */
int main() {
	cout << "[Comparison of performance of insert() and find() in std::multimap and std::unordered_multimap]\n";
	cout << "Total num_data = " << NUM_DATA << ", num_find_test = " << NUM_FIND_TEST << '\n';
	multimap<string, string> orderedMultiMap;
	unordered_multimap<string, string> unorderedMultiMap;
	unorderedMultiMap.max_load_factor(0.75);
	unorderedMultiMap.reserve(NUM_DATA);
	cout << "\n[1] Data creations and insertions ...\n";
	vector<pair<string, string>> kv_pairs;
	kv_pairs.reserve(NUM_DATA);

	/* 데이터 생성 */
	for (int i = 0; i < NUM_DATA; i++) { 
		string key = "key_" + to_string(i);
		string value = "value_" + to_string(i);
		kv_pairs.push_back(make_pair(key, value));
	}

	/* 데이터 삽입 성능 측정 */
	long long orderedInsertTime, unorderedInsertTime;
	orderedInsertTime = measureInsertPerformance(orderedMultiMap, kv_pairs);
	cout << "std::multimap insert time : " << orderedInsertTime << "[us]\n";
	unorderedInsertTime = measureInsertPerformance(unorderedMultiMap, kv_pairs);
	cout << "std::unordered_multimap insert time : " << unorderedInsertTime << " [us]\n";
	cout << "\n[2] Information of unordered_multimap hash table\n";

	size_t maxBucketSize = 0; 
	size_t usedBucketCount = 0;

	/* 해시 정보 저장 */
	for (size_t i = 0; i < unorderedMultiMap.bucket_count(); ++i) {
		size_t bucketSize = unorderedMultiMap.bucket_size(i);
		if (bucketSize > 0)
			++usedBucketCount;
		if (bucketSize > maxBucketSize) maxBucketSize = bucketSize;
	}

	/* 해시 정보 출력 */
	double usedBucketRatio = static_cast<double>(usedBucketCount) / unorderedMultiMap.bucket_count() * 100.0;
	cout << "size : " << setw(8) << unorderedMultiMap.size() << '\n';
	cout << "bucket_count : " << setw(8) << unorderedMultiMap.bucket_count() << '\n';
	cout << "used_bucket_count : " << setw(8) << usedBucketCount << '\n';
	cout << "empty_bucket_count : " << setw(8) << unorderedMultiMap.bucket_count() - usedBucketCount << '\n';
	cout << "load_factor : " << unorderedMultiMap.load_factor() << '\n';
	cout << "max_load_factor : " << unorderedMultiMap.max_load_factor() << '\n';
	cout << "max_bucket_size : " << maxBucketSize << '\n';
	cout << "used_bucket_ratio : " << fixed << setprecision(2) << usedBucketRatio << " %\n";

	vector<string> testKeys;
	testKeys.reserve(NUM_FIND_TEST);
	mt19937 gen(12345); /* 랜덤 시드 */
	uniform_int_distribution<int> dist(0, NUM_DATA - 1);

	/* 테스트 키 생성 */
	for (int i = 0; i < NUM_FIND_TEST; ++i) {
		int index = dist(gen);
		testKeys.push_back("key_" + to_string(index));
	}

	/* 데이터 검색 성능 측정 */
	cout << "\n[3] Performance measurement results of find() for " << NUM_FIND_TEST << " test words\n";
	long long orderedFindTime, unorderedFindTime;
	orderedFindTime = measureFindPerformance(orderedMultiMap, testKeys);
	unorderedFindTime = measureFindPerformance(unorderedMultiMap, testKeys);
	cout << "std::multimap find time : " << setw(8) << orderedFindTime << " [us]\n";
	cout << "std::unordered_multimap find time: " << setw(8) << unorderedFindTime << " [us]\n";
	return 0;
}
