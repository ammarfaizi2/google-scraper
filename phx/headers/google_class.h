
#ifndef __GOOGLE_CLASS_H
#define __GOOGLE_CLASS_H

#include <phpcpp.h>

class Google
{
public:

	Google(std::string);
	~Google();

	void setPage(int);
	Php::Value get();
	Php::Value getImage();
	void setProxy(std::string, std::string);

private:

	void exec();
	void buildUrl();
	void imageExec();
	void descriptionParser(std::string*);

	int page = 0;

	std::string getCwd();
	std::string getEncodedQuery();
	std::string phpStr(Php::Value);
	std::string strip_tags(std::string);
	std::string ch_proxy;
	std::string ch_proxyauth;
	int useProxy = 0;
	std::string html_entity_decode(char *);
	std::vector<std::vector<std::string>> parse();
	std::vector<std::vector<std::string>> imageParse();

	std::string body;
	std::string query;	
	std::string url = "https://www.google.com/search?q=";
};

#endif