#include <iostream>
#include <vector>
#include "httplib.h"
#include "Player.h"

using namespace std;
using namespace httplib;

#define pb push_back

vector <Player> V;

int main(){
	Server svr;

	svr.Post("/register", [&](const Request &req, Response &res){
		bool flag = req.has_file("Register");
		if(!flag){
			res.set_content("Invalid Input", "Error");
		}
		else{
			const auto& file = req.get_file_value("Register");
			Player tmp;
			tmp.name = file.content;
			tmp.number = (int)V.size() + 1;
			cout << "Player number " << tmp.number << " registered with the name of " << tmp.name << endl;

			V.pb(tmp);
			string tmpres = "";
			tmpres += (char)(tmp.number + 48);
			res.set_content(tmpres, "Success");
		}
	});

	svr.listen("localhost", 8080);
}
