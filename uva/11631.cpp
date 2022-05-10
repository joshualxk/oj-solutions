#include <cstdio>
#include <queue>
#include <cstring>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>

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
		do {
			if (ch == EOF) {
				return 0;
			}
			if (ch >= '0' && ch <= '9') {
				break;
			}
			ch = getchar();
		} while (1);

		ival = 0;
		do {
			ival = 10 * ival + ch - '0';
			ch = getchar();
		} while (ch >= '0' && ch <= '9');

		return 1;
	}


	int readStr(char* str) {
		while (ch == '\n' || ch == ' ') {
			ch = getchar();
		}

		int i;
		for (i = 0; ch != EOF && ch != ' ' && ch != '\n'; ++i) {
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

int M, N;
int P[200010];
int R[200010];
int ans;

struct edge {
	int u, v, w;

	bool operator<(const struct edge& o) const {
		return w > o.w;
	}
};

int getP(int u) {
	return P[u] == u ? u : P[u] = getP(P[u]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, selected, pu, pv;
	struct edge ed;
	io.init();
	while (1) {
		io.readI(M);
		io.readI(N);

		if (!M && !N) {
			break;
		}
		ans = 0;

		for (i = 0; i < M; ++i) {
			P[i] = i;
			R[i] = 1;
		}

		priority_queue<struct edge> pq;
		for (i = 0; i < N; ++i) {
			io.readI(ed.u);
			io.readI(ed.v);
			io.readI(ed.w);
			pq.push(ed);
			ans += ed.w;
		}

		for (selected = 0; selected != M - 1; ) {
			ed = pq.top();
			pq.pop();

			pu = getP(ed.u);
			pv = getP(ed.v);

			if (pu != pv) {
				++selected;
				ans -= ed.w;

				if (R[pu] > R[pv]) {
					P[pv] = pu;
				}
				else if (R[pu] < R[pv]) {
					P[pu] = pv;
				}
				else {
					P[pv] = pu;
					++R[pu];
				}
			}
		}

		io.i2s(ans);
		io.buff[io.ix++] = '\n';
		io.flush(0);
	}
	io.flush(1);

	return 0;
}
