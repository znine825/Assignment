/*
Practice_13.1.cpp
Date : 2026-06-09
Author : Lee Jong Kwang
 - 구현된 알고리즘을 테스트
*/

#include "Graph.h"
#include "GraphAlgorithms.h" 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 메인 함수 */
int main() {
	vector<string> graphFiles = { "", "Mesh_2x3.txt", "Mesh_4x4.txt", "Maze_5x5.txt", "USA_7_cities.txt", "Korea_11.txt" };
	while (true) {
		/* 원하는 그래프 선택 */
		cout << "Input graph file\n" << " 1: Mesh_2x3.txt\n" << " 2: Mesh_4x4.txt\n" << " 3: Maze_5x5.txt\n" << " 4: USA_7_cities.txt\n" << " 5: Korea_11.txt\n" << " 0: quit\n" << "Choice: ";
		int graphNo = 0;
		cin >> graphNo;
		if (graphNo == 0) break;
		/* 옳바른 번호를 선택헀는지 확인 */
		if (graphNo < 0 || graphNo >= static_cast<int>(graphFiles.size())) {
			cout << "Invalid graph file number.\n";
			continue;
		}
		/* 파일 잘 열리는지 확인 */
		Graph graph;
		try {
			graph = Graph::fgetGraph(graphFiles[graphNo], false);
		}
		catch (const exception& ex) {
			cout << ex.what() << '\n';
			continue;
		}
		/* 그래프 출력 */
		graph.printAdjacencyList(cout);
		graph.printAdjacencyMatrix(cout);

		/* 어떤 알고리즘으로 테스트 할지 선택 */
		cout << "\nInput test mode" << endl;
		cout << " 1: DFS path\n" << " 2: BFS path\n" << " 3: Dijkstra path\n" << " 4: Floyd-Warshall\n" << " 5: Prim MST\n" << " 6: Kruskal MST\n" << " 0: select another graph / quit this graph\n" << "Choice: ";
		int testMode = 0;
		cin >> testMode;
		cout << endl;
		if (testMode == 0) continue;

		/* 1 ~ 3은 시작노드와 도착도느 선택 */
		string startName, targetName;
		if (testMode >= 1 && testMode <= 3) {
			cout << "Input start and target vertex names: ";
			cin >> startName >> targetName;
		}
		/* 5는 시작노드 선택 */
		else if (testMode == 5) {
			cout << "Input start vertex name for Prim MST: ";
			cin >> startName;
		}

		/* 테스트 케이스 스위치 */
		switch (testMode){
			/* dfsPath */
			case 1: {
				PathResult result = GraphAlgorithms::dfsPath(graph, startName, targetName);
				if (result.found) {
					cout << "DFS path found with distance " << ": ";
					printPath(cout, graph, result.path);
					cout << " / cost  = " << result.distance << endl;
				} else {
					cout << "DFS path not found.\n";
				}
				cout << endl;
				break;
			}
			/* bfsPath */
			case 2: {
				PathResult result = GraphAlgorithms::bfsPath(graph, startName, targetName);
				if (result.found) {
					cout << "BFS path found with distance " << ": ";
					printPath(cout, graph, result.path);
					cout << " / cost  = " << result.distance << endl;
				}
				else {
					cout << "BFS path not found.\n";
				}
				cout << endl;
				break;
			}
			/* dijkstraPath */
			case 3: {
				PathResult result = GraphAlgorithms::dijkstraPath(graph, startName, targetName);
				if (result.found) {
					cout << "reached to the target node {" << targetName << "} at Least Cost = " << result.distance << endl;
					cout << "Path found by dijkstraShortestPath from " << startName << " to " << targetName << " : " 
						<< "Path found (" << startName << " => " << targetName << ") : ";
					printPath(cout, graph, result.path);
					cout << endl;
				}

				result = GraphAlgorithms::dijkstraPath(graph, targetName, startName);
				if (result.found) {
					cout << "reached to the target node {" << targetName << "} at Least Cost = " << result.distance << endl;
					cout << "Path found by dijkstraShortestPath from " << startName << " to " << targetName << " : "
						<< "Path found (" << startName << " => " << targetName << ") : ";
					printPath(cout, graph, result.path);
					cout << endl;
				}
				else {
					cout << "Dijkstra path not found.\n";
				}
				cout << endl;
				break;
			}
			/* floydWarshall */
			case 4: {	
				vector<vector<double>> result = GraphAlgorithms::floydWarshall(graph);
				 
				cout << "All-pairs shortest distance table by Floyd-Warshall";
				cout << "\n      |";
				for (const Vertex& v : graph.vertices()) cout << std::setw(7) << v.name;
				cout << "\n------+" << std::string(graph.vertexCount() * 7, '-') << '\n';
				for (int i = 0; i < result.size(); ++i) {
					cout << std::setw(5) << graph.vertex(i).name << " |";
					for (int j = 0; j < result[i].size(); ++j) {
						if (result[i][j] == INF) cout << std::setw(7) << "+oo";
						else cout << std::setw(7) << result[i][j];
					}	
					cout << endl;
				}
				cout << endl;
				break;
			}
			/* primMST */
			case 5: {
				MSTResult result = GraphAlgorithms::primMST(graph, startName);
				if (result.connected) {
					cout << "Selected edges : \n";
					for (const Edge& e : result.edges) {
						cout << "Edge(" << std::right << std::setw(3) << graph.vertex(e.from).name << " -> " << std::right << std::setw(3) << graph.vertex(e.to).name << " :" << setw(6) << e.weight << "), ";
					}
					cout << "\n " << endl;
				}
				else {
					cout << "Prim MST not found.\n";
				}
				break;
			}
			/* kruskalMST */
			case 6 : {
				MSTResult result = GraphAlgorithms::kruskalMST(graph);
				if (result.connected) {
					cout << "Selected edges : \n";
					for (const Edge& e : result.edges) {
						cout << std::left << std::setw(3) <<  graph.vertex(e.from).name << " --  " << std::setw(3) <<  graph.vertex(e.to).name << "  weight=" << e.weight << '\n';
					}
					cout << "Total weight = " << result.totalWeight << endl;
					cout << endl;
				}
				else {
					cout << "Kruskal MST not found.\n";
				}
				break;
			}
			default: {
				break;
			}
		}
	}
	return 0;
}
