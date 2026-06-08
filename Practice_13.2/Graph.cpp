/*
Graph.h
Date : 2026-06-08
Author : Lee Jong Kwang
 - 클래스 Graph의 구현을 위한 기능 파일
 - 그래프의 구조를 정의, 이쁘게 출력
*/

#include "Graph.h" 

/* 매개변수 생성자 */
Graph::Graph(std::string name, bool directed)
: _graphName(std::move(name)), _directed(directed) {}

/* 기본 생성자 */
const std::string& Graph::name() const noexcept { return _graphName; }

/* 그래프가 Directed 인지 확인 */
bool Graph::isDirected() const noexcept { return _directed; }

/* 그래프의 vertex 수 반환 */
int Graph::vertexCount() const noexcept { return static_cast<int>(_vertices.size()); }

/* 그래프의 edge 수 반환 */
int Graph::edgeCount() const noexcept {
	int count = 0;
	for (const auto& edges : _adj) count += static_cast<int>(edges.size());
	return _directed ? count : count / 2;
}

/* vertex 추가 */
int Graph::addVertex(const std::string& vertexName) {
	auto found = _idByName.find(vertexName);
	if (found != _idByName.end()) return found->second;
	int id = static_cast<int>(_vertices.size());
	_vertices.push_back(Vertex{ id, vertexName });
	_adj.emplace_back();
	_idByName[vertexName] = id; return id;
}

/* Name로 Edge추가 */
void Graph::addEdge(const std::string& fromName, const std::string& toName, double weight) {
	int from = addVertex(fromName);
	int to = addVertex(toName);
	addEdge(from, to, weight);
}

/* id로 Edge추가 */
void Graph::addEdge(int from, int to, double weight) {
	if (from < 0 || from >= vertexCount() || to < 0 || to >= vertexCount()) {
		throw std::out_of_range("Graph::addEdge(): invalid vertex id");
	}
	_adj[from].push_back(Edge{ from, to, weight });
	if (!_directed) {
		_adj[to].push_back(Edge{ to, from, weight });
	}
}

/* vertex 존재 여부 확인 */
bool Graph::hasVertex(const std::string& vertexName) const {
	return _idByName.find(vertexName) != _idByName.end();
}

/* vertexName으로 vertex id 반환 */
int Graph::idOf(const std::string& vertexName) const {
	auto found = _idByName.find(vertexName);
	if (found == _idByName.end()) {
		throw std::invalid_argument("Unknown vertex name: " + vertexName);
	}
	return found->second;
}

/* id로 vertex 반환 */
const Vertex& Graph::vertex(int id) const {
	if (id < 0 || id >= vertexCount()) {
		throw std::out_of_range("Graph::vertex(): invalid vertex id");
	}
	return _vertices[id];
}

/* 모든 vertex 반환 */
const std::vector<Vertex>& Graph::vertices() const noexcept {
	return _vertices;
}

/* id로 인접한 edge 반환 */
const std::vector<Edge>& Graph::adjacentEdges(int id) const {
	if (id < 0 || id >= vertexCount()) {
		throw std::out_of_range("Graph::adjacentEdges(): invalid vertex id");
	}
	return _adj[id];
}

/* 모든 edge 반환 */
std::vector<Edge> Graph::edges(bool uniqueUndirectedEdges) const {
	std::vector<Edge> result;
	for (int u = 0; u < vertexCount(); ++u) {
		for (const Edge& e : _adj[u]) {
			if (!_directed && uniqueUndirectedEdges && e.from > e.to) continue;
			result.push_back(e);
		}
	}
	return result;
}

/* 행렬 반환 */
std::vector<std::vector<double>> Graph::adjacencyMatrix() const {
	int n = vertexCount();
	std::vector<std::vector<double>> matrix(n, std::vector<double>(n, INF));
	for (int i = 0; i < n; ++i) matrix[i][i] = 0.0;
	for (int u = 0; u < n; ++u) {
		for (const Edge& e : _adj[u]) {
			matrix[e.from][e.to] = std::min(matrix[e.from][e.to], e.weight);
		}
	}
	return matrix;
}

/* 그래프 출력 */
void Graph::printAdjacencyList(std::ostream& os) const {
	os << "\nGraph " << _graphName << " (" << vertexCount() << " vertices, " << edgeCount() << " edges)\n";
	for (const Vertex& v : _vertices) {
		os << " " << std::setw(5) << v.name << " : ";
		for (const Edge& e : _adj[v.id]) {
			os << "(" << vertex(e.to).name << ", " << e.weight << ") ";
		}
		os << '\n';
	}
}

/* 이쁘게 그래프 출력 */
void Graph::printAdjacencyMatrix(std::ostream& os) const {
	auto matrix = adjacencyMatrix();
	os << "\nAdjacency Matrix of " << _graphName << "\n      |";
	for (const Vertex& v : _vertices) os << std::setw(7) << v.name;
	os << "\n------+" << std::string(vertexCount() * 7, '-') << '\n';

	for (int i = 0; i < vertexCount(); ++i) {
		os << std::setw(5) << vertex(i).name << " |";
		for (int j = 0; j < vertexCount(); ++j) {
			if (matrix[i][j] == INF) os << std::setw(7) << "+oo";
			else os << std::setw(7) << matrix[i][j];
		}
		os << '\n';
	}
}

/* 파일로 부터 그래프 불러오기 */
Graph Graph::fgetGraph(const std::string& fileName, bool directed) {
	std::ifstream fin(fileName);
	if (!fin) {
		throw std::runtime_error("Failed to open graph input file: " + fileName);
	}
	std::string graphName;
	int declaredVertexCount = 0;
	fin >> graphName >> declaredVertexCount;
	if (!fin) {
		throw std::runtime_error("Invalid graph file header: " + fileName);
	}

	Graph graph(graphName, directed);
	std::string from, to;
	double weight = 0.0;
	while (fin >> from >> to >> weight) {
		graph.addEdge(from, to, weight);
	}

	if (declaredVertexCount != graph.vertexCount()) {
		std::cerr << "Warning: file declares " << declaredVertexCount
			<< " vertices, but " << graph.vertexCount()
			<< " vertices were actually found.\n";
	}

	return graph;
}

/* 경로로부터 vertex 이름 반환 */
std::vector<std::string> namesOfPath(const Graph& g, const std::vector<int>& path) {
	std::vector<std::string> result;
	for (int id : path)
		result.push_back(g.vertex(id).name);
	return result;
}

/* 경로 출력 */
void printPath(std::ostream& os, const Graph& g, const std::vector<int>& path) {
	if (path.empty()) {
		os << "No path";
		return;
	}
	for (std::size_t i = 0; i < path.size(); ++i) {
		if (i > 0) os << " -> ";
		os << g.vertex(path[i]).name;
	}
}