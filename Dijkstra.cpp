#include<iostream>
using namespace std;

#define INF 10000000   // 무한대. 10000000(천만)으로 표현


// 가장 인접한 node 찾는 함수.
int findAdjacentVertex(int vertex_num, bool *check, int *dis) { 
	int min = INF;
	int index = 0;   
	for (int i = 0; i < vertex_num; i++) {
		if (dis[i] < min && !check[i]) { // check[]를 통해 선택된 vertex는 제외. 
			min = dis[i];
			index = i;
		}
	}
	return index;  // 가장 인접한 node의 index 반환. 즉, 현 vertex에서 비용이 가장 적게 드는 인접한 node 찾아서 index return
}

//Dijkstra algorithm
void Dijkstra(int start, int vertex_num, int **graph, bool *check, int *dis) { // start는 처음 선택된 vertex.

	for (int i = 0; i < vertex_num; i++) {  //선택된 node에서부터 다른 node들 까지 거리 정보 저장.
		dis[i] = graph[start][i];
	}

	check[start] = true; // 선택된 node는 true로 변환. 

	for (int i = 0; i < vertex_num - 2; i++) { // edge 연결은 vertex-1개 인데, vertex에서 자기자신 빼므로 vertex-2개가 edge의 수가 된다. (필요 Edge의 수만큼 반복)
		int current = findAdjacentVertex(vertex_num, check, dis); // 가장 인접 vertex 가져와서 index current에 저장. (선택됨)
		check[current] = true; // 선택된 node true로 변환.
		for (int j = 0; j < vertex_num; j++) {
			if ( !check[j] && (dis[current] + graph[current][j] < dis[j])) // 선택된 node를 포함했을 떄와 그렇지 않을 때 비교해서 전자가 더 작으면 거리정보 update 해줘야함.
				dis[j] = dis[current] + graph[current][j]; // 거리 정보 update. 즉, dis[]는 항상 현 상황에서 shortest path를 유지한다.
		}
	}
}

int main() {
	int vertex_num;
	int start;

	cout << "======== Graph 정보 입력 ========\n";
	cout << "vertex 수: ";
	cin >> vertex_num;

	bool *check = new bool[vertex_num]; // 방문한 노드 check. true: 이미 check한 node이고, false: 아직 check하지 않은 node
	int *dis = new int[vertex_num]; // 거리. 선택된 node에서부터 다른 node들 까지의 거리 정보 들어있는 배열.
									// 즉, 0번 vertex 선택되었으면 dis[i] = a[0][i] 
									// 그리고 vertex 선택될때마다 계속 update 되어 저장된다. (현재까지 선택된 vertex를 포함해서 가장 shortest path)
	
	for (int i = 0; i < vertex_num; i++) // check 초기값 false로 설정
		check[i] = false;

	int** graph = new int* [vertex_num];

	for (int i = 0; i < vertex_num; i++) {
		graph[i] = new int[vertex_num];
	}
	cout << "입력은 그래프 수반행렬 방식으로 입력합니다.\n";
	cout << "EX) vertex 수 = 6일떄 \n ";
	cout << " \"0 1 5 2 10000000 3\" 입력하면 vertex0번이 0번으로 갈때 weight 0, vertex 0번이 1번으로 갈때 weigth1, ... \n";
	cout << "(Infinite는 100000000으로 입력)\n";
	cout << "======================================\n";
	cout << "그래프 수반행렬 입력 (2차원 배열 형태)\n";
	for (int i = 0; i < vertex_num; i++) {
		for (int j = 0; j < vertex_num; j++) {
			cin >> graph[i][j];
		}
	}
	cout << "선택할 vertex index 입력 ( 0 ~ vertex 수 -1 ) : ";
	cin >> start;

	Dijkstra(start, vertex_num, graph, check, dis); 


	// Result ( 선택된 node에서부터 각 node까지의 shortest path )
	cout << "\n======== Result ========\n";
	for (int i = 0; i < vertex_num; i++) {
		cout << '[' << i << ']';
	}
	cout << '\n';
	for (int i = 0; i < vertex_num; i++)
		cout << dis[i]<<"  ";

	return 0;

}