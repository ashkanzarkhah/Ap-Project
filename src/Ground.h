#include <iostream>
#include <vector>

using namespace std;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define pii pair <int, int>

class Ground{
public:
	Ground(int sztmp, int cnttmp){
		sz = sztmp;
		cnt = cnttmp;

		mp = new char * [2 * sz];
		for(int i = 0; i < 2 * sz - 1; i ++){
			mp[i] = new char [2 * sz];
			for(int j = 0; j < 2 * sz - 1; j++){
				mp[i][j] = 'o';
				if(i % 2 != 0 || j % 2 != 0) mp[i][j] = 'E';
			}
		}

		tot.pb({0, sz / 2});
		tot.pb({sz / 2, 0});
		tot.pb({sz - 1, sz / 2});
		tot.pb({sz / 2, sz - 1});
		for(int i = 0; i < cnt; i++){
			pl.pb(tot[i]);
			mp[pl[i].F * 2][pl[i].S * 2] = (char)(65 + i);
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
	int cnt;
	char ** mp;
	vector <pii> pl;
	vector <pii> tot;
};
