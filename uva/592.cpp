#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAXN 486
int status[MAXN];

#define NIGHT (1 << 25)
#define DAY   (1 << 26)

#define DIVINE (1<<0)
#define EVIL (1<<1)
#define HUMAN (1<<2)

#define LYING (1<<3)
#define NOT_LYING (1<<4)

#define TIME_MASK (NIGHT | DAY)
#define TYPE_MASK (DIVINE | EVIL | HUMAN)
#define LYING_MASK (LYING|NOT_LYING)

#define INFO_MASK (TYPE_MASK|LYING_MASK)

#define ALL_MASK ((1 << 27) - 1)

void printStatus(int st) {

	for (int i = 0; i < 5; ++i) {
		int info = (st >> (i * 5)) & 0x1f;
		if (!info) {
			printf("[],");
			continue;
		}
		printf("[");
		if (info & LYING) {
			printf("x");
		}
		if (info & NOT_LYING) {
			printf("v");
		}
		if (info & DIVINE) {
			printf("d");
		}
		if (info & EVIL) {
			printf("e");
		}
		if (info & HUMAN) {
			printf("h");
		}

		printf("],");
		
	}
	if (st & TIME_MASK) {
		printf(st & NIGHT ? "night" : "day");
	}
	puts("");
}

void printAns(int st) {
	if (!st) {
		puts("No facts are deducible.");
		return;
	}
	int info, i;
	for (i = 0; i < 5; ++i) {
		info = (st >> (i * 5)) & TYPE_MASK;
		if (!info) {
			continue;
		}
		if (info != DIVINE && info != EVIL && info != HUMAN) {
			goto _out;
		}
	}
	if ((info & TIME_MASK) == TIME_MASK) {
		goto _out;
	}

	for (i = 0; i < 5; ++i) {
		info = (st >> (i * 5)) & TYPE_MASK;
		if (!info) {
			continue;
		}
		printf("%c is ", 'A' + i);
		if (info & DIVINE) {
			printf("divine.\n");
		}
		else if (info & EVIL) {
			printf("evil.\n");
		}
		else {
			printf("human.\n");
		}
	}
	if (st & NIGHT) {
		puts("It is night.");
	}
	if (st & DAY) {
		puts("It is day.");
	}
	return;

_out:
	puts("This is impossible.");
}

void init() {
	int body, lying, st, u;
	bool night;
	for (int i = 0; i < MAXN; ++i) {
		st = 0;
		u = i;
		night = 0;
		if (u & 1) {
			st |= NIGHT;
			night = 1;
		}
		else {
			st |= DAY;
		}
		u >>= 1;
		for (int j = 0; j < 5; ++j) {
			body = 1 << (u % 3);
			if (body == DIVINE) {
				lying = NOT_LYING;
			}
			else if (body == EVIL) {
				lying = LYING;
			}
			else {
				if (night) {
					lying = LYING;
				}
				else {
					lying = NOT_LYING;
				}
			}
			st |= (body | lying) << (j * 5);
			u /= 3;
		}
		status[i] = st;
	}
}

typedef struct {
	int yes;
	int no;
} conv;

vector<conv> cvs[5];

void parseConv(char* str) {
	int from = str[0] - 'A', to;
	int status = 0;
	int ix = 8;
	bool noot = 0;
	int mask = 0;
	if (str[3] == 'I') {
		if (str[4] == 't') {
			if (str[9] == 'd') {
				status = DAY;
			}
			else {
				status = NIGHT;
			}
			mask = TIME_MASK;
			goto _out;
		}
		to = from;
	}
	else {
		to = str[3] - 'A';
	}
	if (str[ix] == 'n') {
		noot = 1;
		ix = 12;
	}

	if (str[ix] == 'l') {
		status = noot ? NOT_LYING : LYING;
		mask = LYING_MASK;
	}
	else {
		if (str[ix] == 'd') {
			status = noot ? (DIVINE ^ TYPE_MASK) : DIVINE;
		}
		else if (str[ix] == 'e') {
			status = noot ? (EVIL ^ TYPE_MASK) : EVIL;
		}
		else {
			status = noot ? (HUMAN ^ TYPE_MASK) : HUMAN;
		}
		mask = TYPE_MASK;
	}
	status <<= (to * 5);
	mask <<= (to * 5);

_out:
	cvs[from].push_back({status, status ^ mask});
}

int getLine(char* str) {
	int ch = getchar();
	while (ch < 'A' || ch > 'E') {
		ch = getchar();
	}
	int ix = 0;
	while (ch != '.') {
		str[ix] = ch;
		ch = getchar();
		++ix;
	}
	str[ix] = 0;
	return ix;
}

bool calStatus(int status) {
	int info, st, i, j;
	bool lying;
	for (i = 0; i < 5; ++i) {
		info = (status >> (i * 5)) & INFO_MASK;
		lying = (info & LYING) ? 1 : 0;
		for (j = 0; j < cvs[i].size(); ++j) {
			st = lying ? cvs[i][j].no : cvs[i][j].yes;
			if (!(status & st)) {
				return 0;
			}
		}
	}
	return 1;
}

int cal() {
	int i, j;
	int mask = ALL_MASK;
	for (i = 0; i < MAXN; ++i) {
		if (calStatus(status[i])) {
			mask &= status[i];
		}
	}

	return mask;
}

int main() {
#ifdef _oj_debug_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	init();
	int T = 0, N, st, i;
	char s[64];
	while (scanf("%d", &N), N) {
		for (i = 0; i < 5; ++i) {
			cvs[i].clear();
		}

		for (i = 0; i < N; ++i) {
			getLine(s);
			parseConv(s);
		}

		st = cal();

		printf("Conversation #%d\n", ++T);
		printAns(st);
		puts("");
	}

	return 0;
}
