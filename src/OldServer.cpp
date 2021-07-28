//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <vector>

using namespace httplib;
#define pb push_back

std :: vector <std :: string> V;

int main(void){
	Server svr;

	svr.Get("/hi", [](const Request &req, Response &res) {
		res.set_content("Hello World!", "mamad");
	});

	svr.Post("/post", [&](const Request &req, Response &res) {
	  auto size = req.files.size();
	  auto ret = req.has_file("name1");
	  const auto& file = req.get_file_value("file2");
	  std :: cout << file.name << " " << file.content << std :: endl;
	  res.set_content("HI", "mamad");
	});

	svr.Post("/register", [&](const Request &req, Response &res){
		const auto& file = req.get_file_value("register");
		V.pb(file.content);
		std :: string tmp = "you are player number ";
		tmp += (char)((int)V.size() + 49);
		res.set_content(tmp, "mamad");
	});

	svr.Get("/stop", [&](const Request &req, Response &res) {
		svr.stop();
	});

	svr.listen("localhost", 8080);
}
