#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

bool readInt(int& ival) {
	int ch = getchar();
	bool negative = 0;
	do {
		if (ch == EOF) {
			return 0;
		}
		if (ch == '-') {
			negative = 1;
			ch = getchar();
			break;
		}
		else if (ch >= '0' && ch <= '9') {
			break;
		}
		ch = getchar();
	} while (1);

	ival = 0;
	do {
		ival = 10 * ival + ch - '0';
		ch = getchar();
	} while (ch >= '0' && ch <= '9');

	if (negative) {
		ival = -ival;
	}
	return 1;
}

#define MAXN 1000

struct node {
	int v, next;
} nodes[(MAXN << 1) + 10];
int ix;

int heads[MAXN + 1];
int cnts[MAXN + 1];

int N, K;

inline void addEdge(int u, int v) {
	int i = ++ix;
	nodes[i].v = v;
	nodes[i].next = heads[u];
	heads[u] = i;

	i = ++ix;
	nodes[i].v = u;
	nodes[i].next = heads[v];
	heads[v] = i;

	++cnts[u];
	++cnts[v];
}

int dfs(int fa, int cur) {
	int cnt = 1, v, i;
	--cnts[cur];

	if (cnts[cur] == K) {
		for (i = heads[cur]; i; i = nodes[i].next) {
			v = nodes[i].v;
			if (v == fa) {
				continue;
			}
			cnt += dfs(cur, v);
		}
	}
	else if (cnts[cur] > K) {
		priority_queue<int> q;
		for (i = heads[cur]; i; i = nodes[i].next) {
			v = nodes[i].v;
			if (v == fa) {
				continue;
			}
			q.push(dfs(cur, v));
		}

		for (i = 0; i < K; ++i) {
			cnt += q.top();
			q.pop();
		}
	}

	return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T, kase, i, u, v;

	readInt(T);
	for (kase = 1; kase <= T; ++kase) {
		readInt(N);
		readInt(K);
		ix = 0;
		memset(heads, 0, sizeof(heads));
		memset(cnts, 0, sizeof(cnts));
		cnts[1] = 1;
		for (i = 1; i < N; ++i) {
			readInt(u);
			readInt(v);
			addEdge(u, v);
		}
		printf("Case %d: %d\n", kase, dfs(0, 1));
	}

	return 0;
}
