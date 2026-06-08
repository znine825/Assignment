/*
GraphAlgorithms.h
Date : 2026-06-08
Author : Lee Jong Kwang
 - 클래스 GraphAlgorithms의 구현을 위한 헤더 파일
 - 알고리즘 구현을 위한 구조체 정의
*/

#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H
#include "Graph.h"
#include <queue>
#include <stack>
#include <functional>
#include <numeric>

/* PathResult 구조체 정의 */
struct PathResult {
	bool found{};  
	double distance{ INF };
	std::vector<int> path;
};

/* MSTResult 구조체 정의 */
struct MSTResult {
	bool connected{};
	double totalWeight{};  
	std::vector<Edge> edges;
};

/* GraphAlgorithms 클래스 정의 */
class GraphAlgorithms {
public:
	/* 깊이 우선 탐색 */
	static PathResult dfsPath(const Graph& graph, const std::string& startName, const std::string& targetName);
	/* 너비 우선 탐색 */
	static PathResult bfsPath(const Graph& graph, const std::string& startName, const std::string& targetName);
	/* 다익스트라 알고리즘 */
	static PathResult dijkstraPath(const Graph& graph, const std::string& startName, const std::string& targetName);
	/* 플로이드-워셜 알고리즘 */
	static std::vector<std::vector<double>> floydWarshall(const Graph& graph);
	/* 크루스칼 알고리즘 */
	static MSTResult kruskalMST(const Graph& graph);
	/* 프림 알고리즘 */
	static MSTResult primMST(const Graph& graph, const std::string& startName);
private:
	/* 경로를 구성하는 함수 */
	static std::vector<int> buildPath(int start, int target, const std::vector<int>& previous);
};
#endif