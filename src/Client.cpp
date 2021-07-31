#include <iostream>
#include "httplib.h"
#include "Player.h"

using namespace std;
using namespace httplib;

Player A;
bool start = false;

int main(){
	Client cli("localhost", 8080);

	cout << "Please Enter your name :" << endl;
	cin >> A.name;
	MultipartFormDataItems items = {
			{"Register", A.name, "", ""}
	};

	if(auto res = cli.Post("/register", items)){
		if((res -> body) == "Invalid Request"){
			cout << "Server is off" << endl;
			return 0;
		}
		else if((res -> body) == "Server is full"){
			cout << "Server is full" << endl;
			return 0;
		}
		else{
			A.number = (int)(res -> body)[0] - 48;
			cout << "You are player number " << A.number << endl;
			cout << "Waiting for others to join !" << endl;
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
				if((res -> body) == "Shutdown"){
					if((res -> get_header_value("Content-Type")) == "Win") cout << "Congrats, you won !" << endl;
					else cout << "Sorry, you lost !" << endl;
					return 0;
				}
				if((res -> body) == "Still registering") continue;
				if((res -> get_header_value("Content-Type")) == "No"){
					if(!start){
						cout << "Game started !" << endl;
						start = true;
					}
					tmp = res -> body;
					if(tmp != mp){
						mp = tmp;
						cout << "The map is changed, new map is: " << endl;
						cout << mp << endl;
						cout << "It's not your turn !" << endl;
					}
				}
				else{
					if(!start){
						cout << "Game started !" << endl;
						start = true;
					}
					flag = true;
					tmp = res -> body;
					if(tmp != mp){
						mp = tmp;
						cout << "The map is changed, new map is: " << endl;
						cout << mp << endl;
					}
				}
			}
		}
		cout << "It's Your turn" << endl;
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
		else{
			cout << "Your move is done, wait till it's your turn again !" << endl;
		}
	}
	return 0;
}
