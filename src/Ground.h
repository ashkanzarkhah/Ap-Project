#include <iostream>

using namespace std;

class Ground{
public:
	Ground(int tmp){
		sz = tmp;
		mp = new char * [2 * sz];
		for(int i = 0; i < 2 * sz - 1; i ++){
			mp[i] = new char [2 * sz];
			for(int j = 0; j < 2 * sz - 1; j++){
				mp[i][j] = 'o';
				if(i % 2 != 0 || j % 2 != 0) mp[i][j] = 'E';
			}
		}
	}

	string Get_Map(){
		string ans = "";
		for(int i = 0; i < 2 * sz - 1; i++){
			for(int j = 0; j < 2 * sz - 1; j++){
				ans += mp[i][j];
				ans += " ";
			}
			ans += '\n';
		}
		return ans;
	}

private:
	int sz;
	char ** mp;
};
