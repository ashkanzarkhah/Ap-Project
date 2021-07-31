#include <iostream>
#include <vector>
#include "httplib.h"
#include "Player.h"
#include "Ground.h"

using namespace std;
using namespace httplib;

#define pb push_back

int n, sz, cur = 1, blackout = -1;
vector <Player> V;

int main(){
	Server svr;

	cout << "Enter number of players :" << endl;
	cin >> n;
	if(n > 4) return cout << "Invalid Input" << endl, 0;

	cout << "Enter size of ground :" << endl;
	cin >> sz;
	if(sz % 2 == 0 || sz < 3) return cout << "Invalid Input" << endl, 0;

	Ground G(sz, n);

	cout << "Waiting for players to register" << endl;
	svr.Post("/register", [&](const Request &req, Response &res){
		bool Flag = req.has_file("Register");
		if(!Flag){
			res.set_content("Invalid Request", "Error");
		}
		else if((int)V.size() == n){
			res.set_content("Server is full", "Success");
		}
		else{
			const auto& file = req.get_file_value("Register");
			Player TmpPlayer;
			TmpPlayer.name = file.content;
			TmpPlayer.number = (int)V.size() + 1;
			cout << TmpPlayer.name << " registered as player number " << TmpPlayer.number << endl;

			V.pb(TmpPlayer);
			string TmpRes = "";
			TmpRes += (char)(TmpPlayer.number + 48);
			res.set_content(TmpRes, "Success");

			if((int)V.size() == n) cout << "Game started" << endl;
		}
	});

	svr.Post("/check", [&](const Request &req, Response &res){
		bool flag = req.has_file("Check");
		if(!flag){
			res.set_content("Invalid Request", "Error");
		}
		else{
			const auto& file = req.get_file_value("Check");
			int tmp = (int)(file.content[0]) - 48;
			if((int)V.size() != n){
				res.set_content("Still registering", "No");
			}
			else if(tmp != cur){
				res.set_content(G.Get_Map(), "No");
			}
			else{
				if(blackout != -1){
					if(cur != blackout) res.set_content("Shutdown", "Lose");
					else res.set_content("Shutdown", "Win");
					cur = (cur % n) + 1;
					if(cur == blackout) svr.stop();
				}
				else res.set_content(G.Get_Map(), "Yes");
			}
		}
	});

	svr.Post("/wallcnt", [&](const Request &req, Response &res){
		bool flag = req.has_file("Wallcnt");
		if(flag){
			const auto& file = req.get_file_value("Wallcnt");
			int i = (int)(file.content[0]) - 49;
			int cntleft = G.Get_Wall_Num(i);
			string tmp = "";
			tmp += (char)(cntleft + 48);
			res.set_content(tmp, "Success");
		}
		else{
			res.set_content("Invalid Request", "Error");
		}
	});

	svr.Post("/move", [&](const Request &req, Response &res){
		bool flag = req.has_file("Move");
		flag |= req.has_file("Wall");
		if(!flag){
			res.set_content("Invalid Request", "Error");
		}
		else if(req.has_file("Move")){
			const auto& file = req.get_file_value("Move");
			int tmp = (int)(file.content[0]) - 48;
			if((int)V.size() != n || tmp != cur || G.Move(cur - 1, file.content_type[0]) == false){
				res.set_content("Invalid Request", "Error");
			}
			else{
				cout << V[cur - 1].name << " made a move !" << endl;
				if(G.Check(cur - 1)){
					res.set_content("Finish", "Seccess");
					cout << V[cur - 1].name << " won !" << endl;
					blackout = cur;
				}
				else{
					res.set_content("Success", "Success");
					cur = (cur % n) + 1;
				}
			}
		}
		else{
			const auto& file = req.get_file_value("Wall");
			int i = (int)(file.content[0]) - 49;
			int x = (int)(file.content[1]) - 65;
			int y = (int)(file.filename[0]) - 65;
			if((int)V.size() != n || i + 1 != cur || G.Add_Wall(i, x, y, file.content_type[0]) == false){
				res.set_content("Invalid Request", "Error");
			}
			else{
				cout << V[cur - 1].name << " added a wall !" << endl;
				res.set_content("Success", "Success");
				cur = (cur % n) + 1;
			}
		}
	});

	svr.listen("localhost", 8080);
}
