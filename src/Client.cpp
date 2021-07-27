#include "httplib.h"

using namespace httplib;

int main(){
	Client cli("localhost", 8080);
	if(auto res = cli.Get("/stop")){
		std :: cout << "Baste shod ! \n";
		std :: cout.flush();
	}
	else{
		std :: cout << "RIDIM KE !! \n";
		std :: cout.flush();
	}
	return 0;
}




