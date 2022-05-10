#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

bool readInt(int& ival) {
	int ch = getchar();
	bool negative = 0;
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

	if (negative) {
		ival = -ival;
	}
	return 1;
}

struct xy {
	int x, y;
};

struct xy dxy[4] = {
	{0, -1},
	{-1, 0},
	{0, 1},
	{1, 0}
};

int N, sqrN;
char maze[8][9];

#define BLOCK 'O'

long long dp[36][4], nMasks[36];
map<long long, long long> m;
int ans[64];
char buff[1024];
int bix;

struct node {
	long long st;
	long long mask;

};

long long calMask(long long mask, long long allMask) {
	long long st = 0;
	int i, j, k, r, c, u, ix = 0, cnt;

	for (i = 1; i < N - 1; ++i) {
		for (j = 1; j < N - 1; ++j) {

			if (mask & (1LL << ix)) {
				cnt = 0;
				for (k = 0; k < 4; ++k) {
					r = i + dxy[k].x;
					c = j + dxy[k].y;

					if (maze[r][c] == BLOCK) {
						continue;
					}

					if (r <= 0 || r >= N - 1 || c <= 0 || c >= N - 1) {
						++cnt;
						continue;
					}

					u = (r - 1) * (N - 2) + c - 1;
					if (allMask & (1LL << u)) {
						continue;
					}

					++cnt;

				}

				if (cnt <= 1) {
					st |= (1LL << ix);
				}
			}

			++ix;
		}
	}

	return st;
}

void printStatus(long long st) {
	int i, j, ix = 0;
	for (i = 1; i < N - 1; ++i) {
		for (j = 1; j < N - 1; ++j) {
			printf("%d ", st & (1LL << ix) ? 1 : 0);
			++ix;
		}
		puts("");
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T, kase, i, j, k, r, c, u;
	long long st, pre, ll, firstStatus;
	node nd;
	readInt(T);
	for (kase = 0; kase < T; ++kase) {
		readInt(N);
		sqrN = N > 2 ? (N - 2) * (N - 2) : 0;
		for (i = 0; i < N; ++i) {
			scanf("%s", maze[i]);
		}

		st = 0;
		memset(dp, 0, sizeof(dp));
		memset(nMasks, 0, sizeof(nMasks));
		m.clear();

		for (i = 1; i < N - 1; ++i) {
			for (j = 1; j < N - 1; ++j) {
				if (maze[i][j] == BLOCK) {
					continue;
				}

				u = (i - 1) * (N - 2) + j - 1;
				st |= 1LL << u;

				for (k = 0; k < 4; ++k) {
					r = i + dxy[k].x;
					c = j + dxy[k].y;

					if (maze[r][c] == BLOCK) {
						dp[u][k] = 1LL << u;
					}
					else {
						if (r > 0 && r < N - 1 && c > 0 && c < N - 1) {
							dp[u][k] = 1LL << ((r - 1) * (N - 2) + c - 1);

							nMasks[u] |= dp[u][k];
						}
					}
				}
			}
		}

		firstStatus = st;

		m[st] = st;
		queue<node> pq;
		pq.push({ st, 0 });
		while (!pq.empty()) {
			nd = pq.front();
			pq.pop();

			for (i = 0; i < 4; ++i) {
				st = 0;
				for (j = 0; j < sqrN; ++j) {
					if (nd.st & (1LL << j)) {
						st |= dp[j][i];
					}
				}

				if (!st) {
					m[st] = nd.st;
					goto _out;
				}

				if (st & nd.mask) {
					continue;
				}

				if (m[st]) {
					continue;
				}
				m[st] = nd.st;

				pre = nd.st & (~st);
				pre = calMask(pre, pre | nd.mask);

				pq.push({ st,  pre | nd.mask });

			}
		}

	_out:
		bix = 0;
		if (kase) {
			buff[bix++] = '\n';
		}

		if (firstStatus) {
			st = 0;
			u = 0;
			for (i = 0; ; ++i) {
				pre = m[st];

				if (pre == st) {
					break;
				}

				for (j = 0; j < 4; ++j) {
					ll = 0;
					for (k = 0; k < sqrN; ++k) {
						if (pre & (1LL << k)) {
							ll |= dp[k][j];
						}
					}
					if (ll == st) {
						ans[u++] = j;
						break;
					}
				}

				st = pre;
			}

			for (i = u - 1; i >= 0; --i) {
				switch (ans[i]) {
				case 0:
					strcpy(buff + bix, "west\n");
					bix += 5;
					break;
				case 1:
					strcpy(buff + bix, "north\n");
					bix += 6;
					break;
				case 2:
					strcpy(buff + bix, "east\n");
					bix += 5;
					break;
				case 3:
					strcpy(buff + bix, "south\n");
					bix += 6;
					break;
				}
			}
		}

		if (bix) {
			buff[bix] = 0;
			printf("%s", buff);
		}
	}

	return 0;
}
