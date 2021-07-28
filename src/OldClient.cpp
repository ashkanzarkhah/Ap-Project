#include "httplib.h"

using namespace httplib;

int main(){
	Client cli("localhost", 8080);

	/*
	MultipartFormDataItems items = {
	  { "text1", "text default", "", "" },
	  { "text2", "aωb", "", "" },
	  { "file1", "h\ne\n\nl\nl\no\n", "hello.txt", "text/plain" },
	  { "file2", "{\n  \"world\", true\n}\n", "world.json", "application/json" },
	  { "file3", "", "", "application/octet-stream" },
	};

	if(auto res = cli.Post("/post", items)){
		std :: cout << res -> body << '\n';
		std :: cout.flush();
	}
	*/

	MultipartFormDataItems items = {
			{"Register", "ashkan zarkhah", "", ""}
	};

	if(auto res = cli.Post("/register", items)){
		std :: cout << res -> body << std :: endl;
	}
	else{
		std :: cout << "Ridim ke !! \n";
		std :: cout.flush();
	}

	if(auto res = cli.Get("/hi")){
		if(res -> status == 200){
			std :: cout << res -> body << '\n';
			std :: cout.flush();
		}
	}
	else{
		std :: cout << "RIDIM KE !! \n";
		std :: cout.flush();
	}
	return 0;
}




