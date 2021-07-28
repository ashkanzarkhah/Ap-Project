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
		A.number = (int)(res -> body) [0] - 48;
		cout << "You are player number " << A.number << endl;
	}
	else{
		cout << "Ridim ke !!" << endl;
	}

	return 0;
}
