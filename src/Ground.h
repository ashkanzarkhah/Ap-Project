#include <iostream>

using namespace std;

class Ground{
public:
	Ground(int tmp){
		sz = tmp;
		mp = new int * [sz];
		for(int i = 0; i < sz; i ++){
			mp[i] = new int [sz];
			for(int j = 0; j < sz; j++) mp[i][j] = 0;
		}
	}

private:
	int sz;
	int ** mp;
};
