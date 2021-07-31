#include <iostream>
#include "httplib.h"
#include "Player.h"

using namespace std;
using namespace httplib;

Player A;

int main(){
	Client cli("localhost", 8080);

	cout << "Please Enter your name :" << endl;
	cin >> A.name;
	MultipartFormDataItems items = {
			{"Register", A.name, "", ""}
	};

	if(auto res = cli.Post("/register", items)){
		if((res -> body) == "Invalid Request"){
			cout << "You can't log in, the game is running" << endl;
			return 0;
		}
		else{
			A.number = (int)(res -> body) [0] - 48;
			cout << "You are player number " << A.number << endl;
		}
	}
	else{
		cout << "Server is off" << endl;
	}

	while(true){
		bool flag = false;
		string tmp = "";
		string mp = "";
		tmp += (char)(A.number + 48);
		items = {
				{"Check", tmp, "", ""}
		};
		while(!flag){
			if(auto res = cli.Post("/check", items)){
				if((res -> body) == "Shutdown") return 0;
				else if((res -> body) != "NO"){
					flag = true;
					mp = res -> body;
				}
			}
		}
		cout << "It's Your turn" << endl;
		cout << mp;
		cout << "Enter your move type :(M to move and W to put a Wall)" << endl;
		cin >> tmp;
		if(tmp == "M"){
			cout << "Enter your move (U, D, R, L) :" << endl;
			cin >> tmp;
			items[0].name = "Move";
			items[0].content_type = tmp;
		}
		else if(tmp == "W"){
			items[0].name = "Wallcnt";
			auto res = cli.Post("/wallcnt", items);
			cout << "You have " << (res -> body) << " walls left !" << endl;
			int x, y;
			cout << "Enter your wall cordinates & type(H, V) :" << endl;
			cin >> x >> y >> tmp;
			items[0].name = "Wall";
			items[0].content_type = tmp;

			tmp = "";
			tmp += (char)(65 + x);
			items[0].content += tmp;

			tmp = "";
			tmp += (char)(65 + y);
			items[0].filename = tmp;
		}
		else{
			cout << "Invalid Move, Try agarin !" << endl;
			continue;
		}
		auto res = cli.Post("/move", items);
		if(res -> body == "Invalid Request"){
			cout << "Invalid Move, Try agarin !" << endl;
		}
		else if(res -> body == "Finish"){
			cout << "You win !" << endl;
		}
		else{
			cout << "Your move is done, wait till it's your turn again !" << endl;
			cout << res -> get_header_value("Content-Type") << endl;
		}
	}
	return 0;
}
