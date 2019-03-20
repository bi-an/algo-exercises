class Solution {
public:
	vector<int> multiply(const vector<int>& A) {
		vector<int> B;

		if (A.empty()) return B;

		vector<int> C;
		vector<int> D;
		int n = A.size();
		int c = 1;
		int d = 1;
		for (size_t i = 0; i <= n-1; i++) {
			C.push_back(c);
			c *= A[i];
		}
		for (int i = n-1; i >= 0; i--) {
			D.push_back(d);
			d *= A[i];
		}

		for (int i = 0; i <= n-1; i++) {
			int tmp = C[i] * D[n - 1 - i];
			B.push_back(tmp);
		}
	
		return B;
	}
};