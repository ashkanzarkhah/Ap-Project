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
		cout << "Ridim ke !!" << endl;
	}

	while(true){
		bool flag = false;
		string tmp = "";
		string mp = "";
		while(!flag){
			tmp += (char)(A.number + 48);
			items = {
					{"Check", tmp, "", ""}
			};
			if(auto res = cli.Post("/check", items)){
				if((res -> body) != "NO"){
					flag = true;
					mp = res -> body;
				}
			}
		}
		cout << "It's Your turn" << endl;
		cout << mp;
		cout << "Enter your Move :" << endl;
		cin >> tmp;
		items[0].name = "Move";
		items[0].content_type = tmp;
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
