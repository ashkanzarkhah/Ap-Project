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
			cntwall.pb(5);
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

	bool Move(int i, char move){
		pii tmp;
		if(move == 'U') tmp = {-1, 0};
		if(move == 'D') tmp = {1, 0};
		if(move == 'R') tmp = {0, 1};
		if(move == 'L') tmp = {0, -1};
		tmp.F += pl[i].F, tmp.S += pl[i].S;
		if(tmp.F < 0 || tmp.S < 0) return false;
		if(tmp.F >= sz || tmp.S >= sz) return false;
		if(mp[tmp.F + pl[i].F][tmp.S + pl[i].S] != 'E') return false;
		mp[2 * tmp.F][2 * tmp.S] = mp[2 * pl[i].F][2 * pl[i].S];
		mp[2 * pl[i].F][2 * pl[i].S] = 'o';
		pl[i] = tmp;
		return true;
	}

	int Get_Wall_Num(int i){
		return cntwall[i];
	}

	bool Add_Wall(int i, int x, int y, char T){
		if(x < 0 || x >= sz) return false;
		if(y < 0 || y >= sz) return false;
		if(cntwall[i] == 0) return false;
		if(T == 'V'){
			if(y - 1 < 0 || y + 1 >= sz || x == 0) return false;
			for(int i = 2 * y - 2; i <= 2 * y + 2; i++) if(mp[2 * x - 1][i] == 'W') return false;
			cntwall[i] --;
			for(int i = 2 * y - 2; i <= 2 * y + 2; i++) mp[2 * x - 1][i] = 'W';
		}
		else{
			if(x - 1 < 0 || x + 1 >= sz || y == sz - 1) return false;
			for(int i = 2 * x - 2; i <= 2 * x + 2; i++) if(mp[i][2 * y + 1] == 'W') return false;
			cntwall[i] --;
			for(int i = 2 * x - 2; i <= 2 * x + 2; i++) mp[i][2 * y + 1] = 'W';
		}
		return true;
	}

	bool Check(int i){
		if(pl[i].F == sz / 2 && pl[i].S == sz / 2) return true;
		return false;
	}


private:
	int sz;
	int cnt;
	char ** mp;
	vector <pii> pl;
	vector <int> cntwall;
	vector <pii> tot;
};
