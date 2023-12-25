#include<bits/stdc++.h>
using namespace std;
queue<pair<int, int>> q; 
int dx[4] = { 0,0,1,-1 }; 
int dy[4] = { 1,-1,0,0 }; 
int maps[100][100]; 
int visited[100][100]; 
int h, w, chk, cnt, lst; 
void bfs() {
	visited[0][0] = 1; 
	while (!q.empty()) {
		int x, y; 		
		tie(y, x) = q.front(); 
		q.pop(); 
		if (maps[y][x] == 0) {
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
				if (visited[ny][nx]) continue;
				if (maps[ny][nx] == 0) {	
					visited[ny][nx] = 1;
					q.push({ ny, nx });
				}
				if (maps[ny][nx] == 1) {
					visited[ny][nx] = 1; 
				}
			}
		}
	}
	int c = 0; 
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (maps[i][j] == 1 && visited[i][j] == 1) {
				maps[i][j] = 0;				
				c++;
			}
		}
	}
	if (c != 0) {
		memset(visited, 0, sizeof(visited));
		lst = c;
		q.push({ 0,0 });
		cnt++;
		bfs();
	}
	else  return; 
}
int main() {
	cin >> h >> w; 
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> maps[i][j]; 
		}
	}
	q.push({ 0,0 }); 
	bfs(); 
	cout << cnt << endl; 
	cout << lst << endl; 	
    return 0;
}
