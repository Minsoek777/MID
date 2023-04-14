#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

const int INF = 1e9; // INF ���� 1e9���� ����
const int dx[4] = { -1, 0, 1, 0 };// �����¿� �̵��� ���� �迭
const int dy[4] = { 0, 1, 0, -1 };

class Map {
private:
    int n, m;// ������ ����, ���� ũ��
    vector<vector<int>> board;// ���� ��ġ�� �����ϴ� ���� ����
    vector<vector<int>> dist;// �� ��ǥ������ �ִ� �Ÿ��� �����ϴ� ���� ����

public:
    Map(int n, int m) {// Map ������, ���� ���� ũ�⸦ �޾� �̸� �̿��� ���� �ʱ�ȭ
        this->n = n;
        this->m = m;
        board = vector<vector<int>>(n, vector<int>(m, 0));// n * m ũ���� ���� ���͸� 0���� �ʱ�ȭ
        dist = vector<vector<int>>(n, vector<int>(m, INF));// n * m ũ���� ���� ���͸� INF ������ �ʱ�ȭ
    }

    void setWall(int x, int y) {// (x, y) ��ǥ�� �� ��ġ
        board[x][y] = 1;
    }

    void setRandomWall(int k) {// ������ �� ����
        srand((unsigned int)time(NULL));
        for (int i = 0; i < k; i++) {
            int x = rand() % n; // ���� ũ�� ���� ������ ������ x��ǥ ����
            int y = rand() % m;// ���� ũ�� ���� ������ ������ y��ǥ ����
            setWall(x, y); // �ش� ��ǥ�� �� ��ġ
        }
    }

    int getDistance(int x, int y) {// (0, 0)���� (x, y)������ �ִ� �Ÿ� ���
        queue<pair<int, int>> q;// BFS Ž���� ���� ť

        q.push({ 0, 0 });// �������� (0, 0)�� ť�� �߰�
        dist[0][0] = 0;// �������� �Ÿ��� 0���� ����

        while (!q.empty()) {// ť�� �� ������ �ݺ�
            int cx = q.front().first; // ť�� �� �� ������ x��ǥ
            int cy = q.front().second;// ť�� �� �� ������ y��ǥ
            q.pop();// ť�� �� �� ���� ����

            for (int i = 0; i < 4; i++) {// �����¿� �̵�
                int nx = cx + dx[i]; // �̵��� x��ǥ
                int ny = cy + dy[i]; // �̵��� y��ǥ

                // ���� ����ų� ���� ��� ���� �������� ����
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (board[nx][ny] == 1) continue;

                // ��������� �Ÿ�(dist[cx][cy]) + 1�� �� ª�� ��쿡�� ������Ʈ�ϰ� ť�� �߰�
                if (dist[nx][ny] <= dist[cx][cy] + 1) continue;
                dist[nx][ny] = dist[cx][cy] + 1;
                q.push({ nx, ny });
            }
        }

        return dist[x][y];
    }

    // ���� ����ϴ� �Լ�
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
    cout << "��ǥ �Է�(x, y): ";
    cin >> x >> y;

    cout << "�ִ� �Ÿ� (0, 0) to (" << x << ", " << y << "): " << myMap.getDistance(x, y) << endl;

    return 0;
}