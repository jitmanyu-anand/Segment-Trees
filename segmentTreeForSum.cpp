/*
* @Author: jitmanyu
* @Date:   2020-09-13 14:27:27
* @Last Modified by:   jitmanyu
* @Last Modified time: 2020-09-13 14:30:16
*/
#include <bits/stdc++.h>

using namespace std;
#define int long long

struct segmentTree {
	int size;
	vector<int> sums;

	void init(int n) {
		size = 1;
		// size should be next power of 2
		while (size < n) size <<= 1;
		// we add extra zeroes in the array
		sums.resize(2 * size, 0);
	}

	void build(vector<int> &a, int x, int lx, int rx) {
		if (rx - lx == 1) {
			// to ignore the extra zeroes added
			if (lx < a.size()) {
				// notice the 'x' and 'lx'
				sums[x] = a[lx];
			}
			return;
		}

		int m = (lx + rx) / 2;

		build(a, 2 * x + 1, lx, m);
		build(a, 2 * x + 2, m, rx);

		// very important to calculate sum in each call
		sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
	}

	void build(vector<int> &a) {
		build(a, 0, 0, size);
	}

	void set(int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			sums[x] = v;
			return;
		}

		int m = (lx + rx) / 2;

		if (i < m) {
			set(i, v, 2 * x + 1, lx, m);
		} else {
			set(i, v, 2 * x + 2, m, rx);
		}

		// very important to calculate sum in each call
		sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
	}

	void set(int i, int v) {
		set(i, v, 0, 0, size);
	}

	int sum(int l, int r, int x, int lx, int rx) {
		// do not intersect
		if (lx >= r or rx <= l) return 0;

		// completely inside
		if (lx >= l and rx <= r) return sums[x];

		// partial intersection
		int m = (lx + rx) / 2;

		int s1 = sum(l, r, 2 * x + 1, lx, m);
		int s2 = sum(l, r, 2 * x + 2, m, rx);

		return s1 + s2;
	}

	int sum(int l, int r) {
		return sum(l, r, 0, 0, size);
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

	// QUERIES

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
			cout << st.sum(l, r) << "\n";
		}
	}
}
