/*
Graph.h
Date : 2026-06-08
Author : Lee Jong Kwang
 - 클래스 Graph의 구현을 위한 헤더 파일
 - 그래프의 구조를 정의, 이쁘게 출력
*/

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <stdexcept>
#include <algorithm>

constexpr double INF = std::numeric_limits<double>::infinity();
/* Vertex 구조체 정의 */
struct Vertex {
	int id{};  
	std::string name;
};

/* Edge 구조체 정의 */
struct Edge {
	int from{};
	int to{};
	double weight{}; 
};

/* Vertex 출력을 위한 << 오버로딩 */
inline std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << v.name;
}

/* Edge 출력을 위한 << 오버로딩 */
inline std::ostream& operator<<(std::ostream& os, const Edge& e) {
	return os << "Edge(" << e.from << " -> " << e.to
		<< ", w=" << e.weight << ")";
}

/* Graph 클래스 정의 */
class Graph {

private:
	/* 변수 정의 */
	std::string _graphName;
	bool _directed{};
	std::vector<Vertex> _vertices;
	std::vector<std::vector<Edge>> _adj;
	std::unordered_map<std::string, int> _idByName;

public:
	/* 매개변수 생성자 */
	explicit Graph(std::string name = "", bool directed = false);
	/* 기본 생성자 */
	const std::string& name() const noexcept;
	/* 그래프가 Directed 인지 확인 */
	bool isDirected() const noexcept;
	/* 그래프의 vertex 수 반환 */
	int vertexCount() const noexcept;
	/* 그래프의 edge 수 반환 */
	int edgeCount() const noexcept;
	/* vertex 추가 */
	int addVertex(const std::string& vertexName);
	/* Name로 Edge추가 */
	void addEdge(const std::string& fromName, const std::string& toName, double weight = 1.0);
	/* id로 Edge추가 */
	void addEdge(int from, int to, double weight = 1.0);
	/* vertex 존재 여부 확인 */
	bool hasVertex(const std::string& vertexName) const;
	/* vertexName으로 vertex id 반환 */
	int idOf(const std::string& vertexName) const;
	/* id로 vertex 반환 */
	const Vertex& vertex(int id) const;
	/* 모든 vertex 반환 */
	const std::vector<Vertex>& vertices() const noexcept;
	/* id로 인접한 edge 반환 */
	const std::vector<Edge>& adjacentEdges(int id) const;
	/* 모든 edge 반환 */
	std::vector<Edge> edges(bool uniqueUndirectedEdges = true) const;
	/* 행렬 반환 */
	std::vector<std::vector<double>> adjacencyMatrix() const;
	/* 그래프 출력 */
	void printAdjacencyList(std::ostream& os) const;
	/* 이쁘게 그래프 출력 */
	void printAdjacencyMatrix(std::ostream& os) const;
	/* 파일로 부터 그래프 불러오기 */
	static Graph fgetGraph(const std::string& fileName, bool directed = false);
};

/* 경로로부터 vertex 이름 반환 */
std::vector<std::string> namesOfPath(const Graph& g, const std::vector<int>& path);

/* 경로 출력 */
void printPath(std::ostream& os, const Graph& g, const std::vector<int>& path);

#endif