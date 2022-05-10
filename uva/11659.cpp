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
	int ix;

	int ch;

	void init() {
		ix = 0;
		ch = getchar();
	}

	bool readI(int& ival) {
		bool negative = 0;
		do {
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
		while (ch == '\n' || ch == ' ') {
			ch = getchar();
		}

		int i;
		for (i = 0; ch != ' ' && ch != '\n'; ++i) {
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
			buff[ix++] = val / 10 + '0';
			buff[ix++] = (val % 10) + '0';
		}
	}

	void flush(bool force) {
		if (ix >= BUFF_SIZE) {
			buff[ix] = 0;

			printf("%s", buff);
			ix = 0;
		}
		else if (force && ix) {
			buff[ix] = 0;
			printf("%s", buff);
			ix = 0;
		}
	}
} io;

int N, M;
int ans;
int masks[21], umasks[21];

int impossible;

#define MAXN (1 << 20)
int dp[MAXN + 10];

int stix[] = {
	0,
	1,
	21,
	211,
	1351,
	6196,
	21700,
	60460,
	137980,
	263950,
	431910,
	616666,
	784626,
	910596,
	988116,
	1026876,
	1042380,
	1047225,
	1048365,
	1048555,
	1048575,
	1048576,
};

void init() {
	int ixs[22];
	int i, j, c;
	memcpy(ixs, stix, sizeof(stix));
	for (i = 0; i < MAXN; ++i) {
		c = 0;
		for (j = i; j; j -= j & -j) {
			++c;
		}
		dp[ixs[c]++] = i;
	}
}

bool check(int n) {
	int i, j, u, lit, pre;
	int m, um;
	lit = 1 << N;
	for (i = stix[n]; i < stix[n + 1]; ++i) {
		u = dp[i];
		if (u >= lit) {
			break;
		}
		if (u & impossible) {
			continue;
		}

		m = u;
		um = 0;
		while (1) {
			pre = m;
			for (j = 0; j < N; ++j) {
				if (m & (1 << j)) {
					m |= masks[j];
					um |= umasks[j];
				}
			}
			if (pre == m) {
				break;
			}
		}
		
		if ((m & u) != m || (m & um)) {
			continue;
		}

		//printf("im:%d,", impossible);
		//for (i = 0; i < N; ++i) {
		//	if (u & (1 << i)) {
		//		printf("%d,", i);
		//	}
		//}
		//printf("\n");
		return 1;
	}

	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int u, v, i;
	io.init();
	init();
	while (1) {
		io.readI(N);
		io.readI(M);

		if (!N && !M) {
			break;
		}
		
		for (i = 0; i < N; ++i) {
			masks[i] = 1 << i;
			umasks[i] = 0;
		}

		for (i = 0; i < M; ++i) {
			io.readI(u);
			io.readI(v);

			--u;
			
			if (v < 0) {
				v = -v - 1;
				umasks[u] |= 1 << v;
			}
			else {
				--v;
				masks[u] |= 1 << v;
			}

		}

		impossible = 0;
		ans = N;
		for (i = 0; i < N; ++i) {
			if (masks[i] & umasks[i]) {
				--ans;
				impossible |= 1 << i;
			}
		}
		if (impossible) {
			for (i = 0; i < N; ++i) {
				umasks[i] |= impossible;
			}
		}

		for (; ans > 0; --ans) {
			if (check(ans)) {
				break;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
