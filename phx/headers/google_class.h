
#ifndef __GOOGLE_CLASS_H
#define __GOOGLE_CLASS_H

#include <phpcpp.h>

class Google
{
public:

	Google(std::string);
	~Google();

	void setPage(int);
	// std::vector<std::vector<std::string>> get();
	Php::Value get();

private:

	void exec();
	void buildUrl();
	void parse();
	void descriptionParser(std::string*);

	int page = 0;

	std::string getCwd();
	std::string getEncodedQuery();
	std::string phpStr(Php::Value);
	std::string strip_tags(std::string);
	std::string html_entity_decode(char *);

	std::string body;
	std::string query;	
	std::string url = "https://www.google.com/search?q=";

	std::vector<std::vector<std::string>> result;
};

#endif