#include<iostream>
using namespace std;

#define INF 10000000   // ���Ѵ�. 10000000(õ��)���� ǥ��


// ���� ������ node ã�� �Լ�.
int findAdjacentVertex(int vertex_num, bool *check, int *dis) { 
	int min = INF;
	int index = 0;   
	for (int i = 0; i < vertex_num; i++) {
		if (dis[i] < min && !check[i]) { // check[]�� ���� ���õ� vertex�� ����. 
			min = dis[i];
			index = i;
		}
	}
	return index;  // ���� ������ node�� index ��ȯ. ��, �� vertex���� ����� ���� ���� ��� ������ node ã�Ƽ� index return
}

//Dijkstra algorithm
void Dijkstra(int start, int vertex_num, int **graph, bool *check, int *dis) { // start�� ó�� ���õ� vertex.

	for (int i = 0; i < vertex_num; i++) {  //���õ� node�������� �ٸ� node�� ���� �Ÿ� ���� ����.
		dis[i] = graph[start][i];
	}

	check[start] = true; // ���õ� node�� true�� ��ȯ. 

	for (int i = 0; i < vertex_num - 2; i++) { // edge ������ vertex-1�� �ε�, vertex���� �ڱ��ڽ� ���Ƿ� vertex-2���� edge�� ���� �ȴ�. (�ʿ� Edge�� ����ŭ �ݺ�)
		int current = findAdjacentVertex(vertex_num, check, dis); // ���� ���� vertex �����ͼ� index current�� ����. (���õ�)
		check[current] = true; // ���õ� node true�� ��ȯ.
		for (int j = 0; j < vertex_num; j++) {
			if ( !check[j] && (dis[current] + graph[current][j] < dis[j])) // ���õ� node�� �������� ���� �׷��� ���� �� ���ؼ� ���ڰ� �� ������ �Ÿ����� update �������.
				dis[j] = dis[current] + graph[current][j]; // �Ÿ� ���� update. ��, dis[]�� �׻� �� ��Ȳ���� shortest path�� �����Ѵ�.
		}
	}
}

int main() {
	int vertex_num;
	int start;

	cout << "======== Graph ���� �Է� ========\n";
	cout << "vertex ��: ";
	cin >> vertex_num;

	bool *check = new bool[vertex_num]; // �湮�� ��� check. true: �̹� check�� node�̰�, false: ���� check���� ���� node
	int *dis = new int[vertex_num]; // �Ÿ�. ���õ� node�������� �ٸ� node�� ������ �Ÿ� ���� ����ִ� �迭.
									// ��, 0�� vertex ���õǾ����� dis[i] = a[0][i] 
									// �׸��� vertex ���õɶ����� ��� update �Ǿ� ����ȴ�. (������� ���õ� vertex�� �����ؼ� ���� shortest path)
	
	for (int i = 0; i < vertex_num; i++) // check �ʱⰪ false�� ����
		check[i] = false;

	int** graph = new int* [vertex_num];

	for (int i = 0; i < vertex_num; i++) {
		graph[i] = new int[vertex_num];
	}
	cout << "�Է��� �׷��� ������� ������� �Է��մϴ�.\n";
	cout << "EX) vertex �� = 6�ϋ� \n ";
	cout << " \"0 1 5 2 10000000 3\" �Է��ϸ� vertex0���� 0������ ���� weight 0, vertex 0���� 1������ ���� weigth1, ... \n";
	cout << "(Infinite�� 100000000���� �Է�)\n";
	cout << "======================================\n";
	cout << "�׷��� ������� �Է� (2���� �迭 ����)\n";
	for (int i = 0; i < vertex_num; i++) {
		for (int j = 0; j < vertex_num; j++) {
			cin >> graph[i][j];
		}
	}
	cout << "������ vertex index �Է� ( 0 ~ vertex �� -1 ) : ";
	cin >> start;

	Dijkstra(start, vertex_num, graph, check, dis); 


	// Result ( ���õ� node�������� �� node������ shortest path )
	cout << "\n======== Result ========\n";
	for (int i = 0; i < vertex_num; i++) {
		cout << '[' << i << ']';
	}
	cout << '\n';
	for (int i = 0; i < vertex_num; i++)
		cout << dis[i]<<"  ";

	return 0;

}