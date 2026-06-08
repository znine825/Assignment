/*
GraphAlgorithms.cpp
Date : 2026-06-08
Author : Lee Jong Kwang
 - 클래스 GraphAlgorithms의 구현을 위한 헤더 파일
 - 알고리즘 구현을 위한 구조체 정의
*/

#include "GraphAlgorithms.h"
#include <algorithm>  

std::vector<int>
/* 경로를 구성하는 함수 */
GraphAlgorithms::buildPath(int start, int target, const std::vector<int>& previous) {
	std::vector<int> path;
	if (target < 0 || target >= static_cast<int>(previous.size()))
		return path;
	if (previous[target] == -1 && start != target)
		return path;
	for (int cur = target; cur != -1; cur = previous[cur]) {
		path.push_back(cur);
		if (cur == start)
			break;
	}
	if (path.back() != start)
		return {}; 
	std::reverse(path.begin(), path.end());
	return path;
}

/* 깊이 우선 탐색 */
PathResult GraphAlgorithms::dfsPath(const Graph& graph, const std::string& startName, const std::string& targetName) {
	int start = graph.idOf(startName);
	int target = graph.idOf(targetName);
	int n = graph.vertexCount();
	std::vector<bool> visited(n, false);
	std::vector<int> previous(n, -1);
	std::function<bool(int)> dfs = [&](int u) // 람다 함수 선언 
		{
			visited[u] = true; /* 방문한 노드 표시 */
			if (u == target) return true;
			for (const Edge& e : graph.adjacentEdges(u)) {
				int v = e.to;
				/* 방문하지 않은 노드에 대해 재귀 호출 */
				if (!visited[v]) {
					previous[v] = u;
					if (dfs(v)) return true;  
				}
			}
			return false;
		};  
	PathResult result;
	result.found = dfs(start);
	if (result.found) {  
		result.path = buildPath(start, target, previous);
		result.distance = static_cast<double>(result.path.size() - 1);
	}
	return result;  
}

/* 너비 우선 탐색 */
PathResult GraphAlgorithms::bfsPath(const Graph& graph, const std::string& startName, const std::string& targetName) {
	int start = graph.idOf(startName);
	int target = graph.idOf(targetName);
	int n = graph.vertexCount();
	std::queue<int> q; /* 큐 선언 */
	std::vector<bool> visited(n, false);
	std::vector<int> previous(n, -1);
	std::vector<int> level(n, -1);
	visited[start] = true; /* 시작 노드 방문 표시 */
	level[start] = 0; /* 시작 노드의 레벨 설정 */
	q.push(start); /* 시작 노드를 큐에 추가 */
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		/* 도착시 종료 */
		if (u == target)
			break;
		for (const Edge& e : graph.adjacentEdges(u)) {
			int v = e.to;
			if (!visited[v]) {
				/* 방문하지 않은 노드에 대해 처리 */
				visited[v] = true;
				previous[v] = u;
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	PathResult result;
	result.found = visited[target];
	if (result.found) {
		result.path = buildPath(start, target, previous);
		result.distance = level[target];
	}
	return result;
}
	
/* 다익스트라 알고리즘 */
PathResult GraphAlgorithms::dijkstraPath(const Graph& graph, const std::string& startName, const std::string& targetName) {
	int start = graph.idOf(startName);
	int target = graph.idOf(targetName);
	int n = graph.vertexCount();
	using Node = std::pair<double, int>; 
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq; /* 큐 선언 */
	std::vector<double> dist(n, INF);
	std::vector<int> previous(n, -1);
	dist[start] = 0.0; /* 시작 가중치 */
	pq.push({ 0.0, start }); /* 시작 노드를 큐에 추가 */

	int round = 0;

	std::cout << "\n             | ";
	for (const Vertex& v : graph.vertices()) std::cout << std::setw(7) << v.name;
	std::cout << "\n-------------+" << std::string(graph.vertexCount() * 7 + 1, '-') << '\n';
	 
	while (!pq.empty()) {
		auto [curDist, u] = pq.top();
		
		pq.pop();
		if (curDist > dist[u])
			continue;
		/* 도착시 종료 */
		if (u == target)
			break;
		for (const Edge& e : graph.adjacentEdges(u)) {
			if (e.weight < 0) {
				throw std::logic_error("Dijkstra cannot be used with negative edge weights.");
			}
			int v = e.to;  
			double nextDist = dist[u] + e.weight;
			/* 새로운 경로가 기존 경로보다 가벼운 경우 */
			if (nextDist < dist[v]) {
				dist[v] = nextDist;
				previous[v] = u;
				pq.push({ nextDist, v });
			}
		}
		std::cout << "round [ " << std::setw(2) << round++ << " ] : ";
		for (int i = 0; i < n; ++i) {
			if (dist[i] == INF)
				std::cout << std::setw(7) << "+oo";
			else
				std::cout << std::setw(7) << dist[i];
		}
		std::cout << " ==> selected vertex : " << graph.vertex(u).name << std::endl;
		
	} 
	PathResult result;
	result.found = dist[target] != INF;
	result.distance = dist[target];
	if (result.found)
		result.path = buildPath(start, target, previous);
	return result;
}

/* 플로이드-워셜 알고리즘 */
std::vector<std::vector<double>>
GraphAlgorithms::floydWarshall(const Graph& graph) {
	auto dist = graph.adjacencyMatrix();
	int n = graph.vertexCount();
	/* 모든 노드쌍의 최단거리 찾기 */
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			if (dist[i][k] == INF)
				continue;
			for (int j = 0; j < n; ++j) {
				if (dist[k][j] == INF)
					continue;
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	return dist;
}

/* 프림 알고리즘 */
MSTResult GraphAlgorithms::primMST(const Graph& graph, const std::string& startName) {
	/* 방향 그래프인지 확인 */
	if (graph.isDirected()) {
		throw std::logic_error("MST is normally defined for undirected graphs.");
	}


	int start = graph.idOf(startName);
	int n = graph.vertexCount();
	int round = 0;
	std::vector<bool> selected(n, false);

	std::cout << "Testing Prim-JarnikMST() with start vertex (" << startName << ")" << std::endl;
	std::cout << "Start node : " << startName;
	std::cout << std::endl;

	/* 간선 구조체 정의 */
	struct Candidate {
		double weight;
		Edge edge;
		bool operator>(const Candidate& other) const {
			return weight > other.weight;
		}
	};
	std::priority_queue<Candidate, std::vector<Candidate>, std::greater<Candidate>> pq;
	const double INF = std::numeric_limits<double>::infinity();

	std::vector<double> dist(n, INF);
	dist[start] = 0;
	auto pushEdges = [&](int u) {
		selected[u] = true;

		for (const Edge& e : graph.adjacentEdges(u)) {
			if (!selected[e.to] && e.weight < dist[e.to]) {
				dist[e.to] = e.weight;
				pq.push(Candidate{ e.weight, e });
			}
		}
	};
	MSTResult result;
	pushEdges(start);
	/* 최소 신장 트리 구성 */
	while (!pq.empty() && static_cast<int>(result.edges.size()) < n - 1) {
		Candidate cur = pq.top();  

		pq.pop();
		if (selected[cur.edge.to])  
			continue;
		result.edges.push_back(cur.edge);
		result.totalWeight += cur.edge.weight;
		pushEdges(cur.edge.to);
		std::cout << "Dist after round [" << std::setw(2) << round++ << "] :";

		for (int i = 0; i < n; i++) {
			if (std::isinf(dist[i]))
				std::cout << std::setw(6) << "+oo";
			else
				std::cout << std::setw(6) << dist[i];
		}
		std::cout << "\n  => min_edge (Edge( " << std::right << std::setw(3) << graph.vertices()[cur.edge.from] << " -> " << std::right << std::setw(3) << graph.vertices()[cur.edge.to] << " : "
			<< std::setw(7) << std::right << cur.edge.weight << ")) is selected" << std::endl;
	}

	std::cout << "\nEnd of finding Minimum Spanning Tree by Prim-Jarnik's Algotithm: selectedEdgeLst_size = " << round << std::endl;
	result.connected = static_cast<int>(result.edges.size()) == n - 1;
	return result;
}

/* 클래스 DisjointSet */
class DisjointSet {
private:
	std::vector<int> parent_;  
	std::vector<int> rank_;  
public:
	explicit DisjointSet(int n) : parent_(n), rank_(n, 0) {
		std::iota(parent_.begin(), parent_.end(), 0);
	}
	/* 집합의 가장 높은 부모 찾기 */
	int find(int x) {
		if (parent_[x] != x)
			parent_[x] = find(parent_[x]);  
		return parent_[x];
	}
	/* 두 집합 합치기 */
	bool unite(int a, int b) {   
		int rootA = find(a);
		int rootB = find(b);
		if (rootA == rootB)  
			return false;
		if (rank_[rootA] < rank_[rootB])
			std::swap(rootA, rootB);
		parent_[rootB] = rootA;
		if (rank_[rootA] == rank_[rootB])
			++rank_[rootA];
		return true;
	}
};

/* 크루스칼 알고리즘 */
MSTResult GraphAlgorithms::kruskalMST(const Graph& graph) {
	/* 방향 그래프인지 확인 */
	if (graph.isDirected()) {
		throw std::logic_error("MST is normally defined for undirected graphs.");
	}
	/* 모든 간선을 가중치 기준으로 정렬 */
	std::vector<Edge> edges = graph.edges(true);
	std::sort(edges.begin(), edges.end(),
		[](const Edge& a, const Edge& b) {
			return a.weight < b.weight;
		}
	);

	DisjointSet ds(graph.vertexCount());
	MSTResult result;
	/* 최소 신장 트리 구성 */
	for (const Edge& e : edges) {
		if (ds.unite(e.from, e.to)) {   
			result.edges.push_back(e);
			result.totalWeight += e.weight;
			if (static_cast<int>(result.edges.size()) == graph.vertexCount() - 1)
				break;
		}
	}
	result.connected =
		static_cast<int>(result.edges.size()) == graph.vertexCount() - 1;
	return result;
}