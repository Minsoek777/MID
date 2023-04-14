#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

const int INF = 1e9; // INF 값을 1e9으로 설정
const int dx[4] = { -1, 0, 1, 0 };// 상하좌우 이동을 위한 배열
const int dy[4] = { 0, 1, 0, -1 };

class Map {
private:
    int n, m;// 지도의 가로, 세로 크기
    vector<vector<int>> board;// 벽의 위치를 저장하는 이중 벡터
    vector<vector<int>> dist;// 각 좌표까지의 최단 거리를 저장하는 이중 벡터

public:
    Map(int n, int m) {// Map 생성자, 가로 세로 크기를 받아 이를 이용해 벡터 초기화
        this->n = n;
        this->m = m;
        board = vector<vector<int>>(n, vector<int>(m, 0));// n * m 크기의 이중 벡터를 0으로 초기화
        dist = vector<vector<int>>(n, vector<int>(m, INF));// n * m 크기의 이중 벡터를 INF 값으로 초기화
    }

    void setWall(int x, int y) {// (x, y) 좌표에 벽 설치
        board[x][y] = 1;
    }

    void setRandomWall(int k) {// 무작위 벽 생성
        srand((unsigned int)time(NULL));
        for (int i = 0; i < k; i++) {
            int x = rand() % n; // 가로 크기 범위 내에서 랜덤한 x좌표 선택
            int y = rand() % m;// 세로 크기 범위 내에서 랜덤한 y좌표 선택
            setWall(x, y); // 해당 좌표에 벽 설치
        }
    }

    int getDistance(int x, int y) {// (0, 0)에서 (x, y)까지의 최단 거리 계산
        queue<pair<int, int>> q;// BFS 탐색을 위한 큐

        q.push({ 0, 0 });// 시작점인 (0, 0)을 큐에 추가
        dist[0][0] = 0;// 시작점의 거리를 0으로 설정

        while (!q.empty()) {// 큐가 빌 때까지 반복
            int cx = q.front().first; // 큐의 맨 앞 원소의 x좌표
            int cy = q.front().second;// 큐의 맨 앞 원소의 y좌표
            q.pop();// 큐의 맨 앞 원소 삭제

            for (int i = 0; i < 4; i++) {// 상하좌우 이동
                int nx = cx + dx[i]; // 이동한 x좌표
                int ny = cy + dy[i]; // 이동한 y좌표

                // 맵을 벗어나거나 벽인 경우 다음 방향으로 진행
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (board[nx][ny] == 1) continue;

                // 현재까지의 거리(dist[cx][cy]) + 1이 더 짧은 경우에만 업데이트하고 큐에 추가
                if (dist[nx][ny] <= dist[cx][cy] + 1) continue;
                dist[nx][ny] = dist[cx][cy] + 1;
                q.push({ nx, ny });
            }
        }

        return dist[x][y];
    }

    // 맵을 출력하는 함수
    void printMap() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 1) cout << "* ";
                else cout << "0 ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n = 10, m = 10;
    Map myMap(n, m);
    myMap.setRandomWall(20);
    myMap.printMap();

    int x, y;
    cout << "좌표 입력(x, y): ";
    cin >> x >> y;

    cout << "최단 거리 (0, 0) to (" << x << ", " << y << "): " << myMap.getDistance(x, y) << endl;

    return 0;
}