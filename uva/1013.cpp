#include <cstdio>
#include <queue>
#include <cstring>
#include <map>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

struct fastio {
#define BUFF_SIZE (1<<12)
	char buff[BUFF_SIZE + 64];
	char digit[16];
	int ix;

	int ch;

	void init() {
		ix = 0;
		ch = getchar();
	}

	bool readI(int& ival) {
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


	int readStr(char* str) {
		while (ch == '\n') {
			ch = getchar();
		}

		int i;
		for (i = 0; ch != '\n' && ch != EOF; ++i) {
			str[i] = ch;
			ch = getchar();
		}
		str[i] = 0;

		return i;
	}

	void concat(const char* str, int len) {
		memmove(buff + ix, str, len);
		ix += len;
	}

	void i2s(int val) {
		if (val < 10) {
			buff[ix++] = val + '0';
		}
		else {
			int i, u = val;
			for (i = 14; u; --i) {
				digit[i] = u % 10 + '0';
				u /= 10;
			}

			for (++i; i <= 14; ++i) {
				buff[ix++] = digit[i];
			}
		}
	}

	void flush(bool force) {
		if (ix >= BUFF_SIZE || (force && ix)) {
			buff[ix] = 0;

			printf("%s", buff);
			ix = 0;
		}
	}

	void shity(bool cond) {
		if (cond) {
			int* p = 0;
			p[0] = 0;
		}
	}
} io;

int N;

struct island {
	int x, y, m;
} islands[50];

int P[50], R[50];


struct edge {
	int u, v;
	double d;

	bool operator<(const struct edge& o) const {
		return d > o.d;
	}
};

int getP(int u) {
	return P[u] == u ? u : P[u] = getP(P[u]);
}

int heads[50];
struct node {
	int v, n;
	double d;
} nodes[100];
int ix;

bool vis[50];

double ans;
int tot;
void cal(int cur, double dis) {
	vis[cur] = 1;
	ans += dis * islands[cur].m;

	int i, v;
	for (i = heads[cur]; i; i = nodes[i].n) {
		v = nodes[i].v;

		if (!vis[v]) {
			if (!cur) {
				cal(v, nodes[i].d);
			}
			else {
				cal(v, max(nodes[i].d, dis));
			}
			
		}
	}

}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int kase, i, j, u, v, n;
	struct edge ed;
	io.init();
	for (kase = 1;;++kase) {
		io.readI(N);
		if (!N) {
			break;
		}
		tot = 0;
		for (i = 0; i < N; ++i) {
			io.readI(islands[i].x);
			io.readI(islands[i].y);
			io.readI(islands[i].m);
			tot += islands[i].m;
		}

		priority_queue<struct edge> pq;

		for (i = 0; i < N; ++i) {
			for (j = i + 1; j < N; ++j) {
				ed.d = sqrt((islands[i].x - islands[j].x) * (islands[i].x - islands[j].x) + (islands[i].y - islands[j].y) * (islands[i].y - islands[j].y));
				ed.u = i;
				ed.v = j;
				pq.push(ed);
			}
		}

		for (i = 0; i < N; ++i) {
			P[i] = i;
			R[i] = 1;
		}

		n = 0;
		memset(heads, 0, sizeof(heads));
		ix = 0;
		while (n != N - 1) {
			ed = pq.top();
			pq.pop();

			u = getP(ed.u);
			v = getP(ed.v);

			if (u != v) {
				if (R[u] < R[v]) {
					P[u] = v;
				}
				else if (R[u] > R[v]) {
					P[v] = u;
				}
				else {
					P[v] = u;
					++R[u];
				}

				++ix;
				nodes[ix].v = ed.v;
				nodes[ix].n = heads[ed.u];
				nodes[ix].d = ed.d;
				heads[ed.u] = ix;

				++ix;
				nodes[ix].v = ed.u;
				nodes[ix].n = heads[ed.v];
				nodes[ix].d = ed.d;
				heads[ed.v] = ix;

				++n;
			}
		}

		memset(vis, 0, sizeof(vis));
		ans = 0;
		cal(0, 0);
		ans /= tot;
		printf("Island Group: %d Average %.2lf\n\n", kase, ans);
	}

	return 0;
}
