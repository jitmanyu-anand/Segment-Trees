/*
* @Author: jitmanyu
* @Date:   2020-09-13 16:56:30
* @Last Modified by:   jitmanyu
* @Last Modified time: 2020-09-13 16:56:45
*/
#include <bits/stdc++.h>

using namespace std;
#define int long long

struct item {
	int mn, c;
};

struct segmentTree {
	int size;
	vector<item> val;

	item merge(item a, item b) {
		if (a.mn < b.mn) return a;
		if (a.mn > b.mn) return b;
		return {a.mn, a.c + b.c};
	}

	item neutralElement = {INT_MAX, 1};

	void init(int n) {
		size = 1;
		while (size < n) size <<= 1;
		val.resize(2 * size, neutralElement);
	}

	void build(vector<int> &a, int x, int lx, int rx) {
		if (rx - lx == 1) {
			if (lx < a.size()) {
				val[x] = {a[lx], 1};
			}
			return;
		}

		int m = (lx + rx) / 2;

		build(a, 2 * x + 1, lx, m);
		build(a, 2 * x + 2, m, rx);

		val[x] = merge( val[2 * x + 1], val[2 * x + 2]);
	}

	void build(vector<int> &a) {
		build(a, 0, 0, size);
	}

	void set(int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			val[x] = {v, 1};
			return;
		}

		int m = (lx + rx) / 2;

		if (i < m) {
			set(i, v, 2 * x + 1, lx, m);
		} else {
			set(i, v, 2 * x + 2, m, rx);
		}

		val[x] = merge(val[2 * x + 1], val[2 * x + 2]);

	}

	void set(int i, int v) {
		set(i, v, 0, 0, size);
	}

	item calc(int l, int r, int x, int lx, int rx) {
		// do not intersect
		if (lx >= r or rx <= l) return neutralElement;

		// completely inside
		if (lx >= l and rx <= r) return val[x];

		// partial intersection
		int m = (lx + rx) / 2;

		item s1 = calc(l, r, 2 * x + 1, lx, m);
		item s2 = calc(l, r, 2 * x + 2, m, rx);

		return merge(s1, s2);
	}

	item calc(int l, int r) {
		return calc(l, r, 0, 0, size);
	}

};

/* SAMPLE INPUT
5 5
5 4 2 3 5
2 0 3
1 1 1
2 0 3
1 3 1
2 0 5
*/

int32_t main() {
	int n, m;
	cin >> n >> m;

	segmentTree st;
	st.init(n);

	// to create the intial segment tree from the given values
	// we can do two things

	//1. use set function n times O(n.logn)
	//2. create a seperate build function in segment tree o(n)

	// if the number of queries(m) are comparable to n
	// then anyhow, the complexity is going to be O(m.logn) = O(n.logn)
	// so no benifit from creating the seperate build function

	// USING METHOD 1 TO BUILD THE INTITAL SEGMENT TREE

//    for(int i=0;i<n;i++){
//        int x;
//        cin>>x;
//        st.set(i, x);
//    }

	// USING METHOD 2

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	st.build(a);

	while (m--) {
		int op;
		cin >> op;

		if (op == 1) {
			int i, v;
			cin >> i >> v;
			st.set(i, v);
		} else {
			int l, r;
			cin >> l >> r;
			item res = st.calc(l, r);
			cout << res.mn << " " << res.c << "\n";
		}
	}
}