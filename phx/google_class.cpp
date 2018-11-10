
#include "headers/google_class.h"
#include "tealib/TeaCurl/TeaCurl.h"
#include "tealib/TeaPCRE/TeaPCRE.h"

Google::Google(std::string query) {
	this->query = query;
}

Google::~Google() {
	
}

void Google::setPage(int page) {
	this->page = page;
}

std::string Google::getEncodedQuery() {
	return Php::call("urlencode", this->query);
}

std::string Google::getCwd() {
	return Php::call("getcwd");
}

std::string Google::phpStr(Php::Value phpval) {
	return phpval;
}

void Google::buildUrl() {
	this->url += this->getEncodedQuery() + "&start=" + std::to_string(10 * this->page);
}

void Google::exec() {
	this->buildUrl();
	printf("URL: %s\n", this->url.c_str());
	// TeaCurl *tc = new TeaCurl(this->url);
	// tc->setOpt(CURLOPT_COOKIEJAR, (this->getCwd()+"/cookie.txt").c_str());
	// tc->setOpt(CURLOPT_COOKIEFILE, (this->getCwd()+"/cookie.txt").c_str());
	// tc->setOpt(CURLOPT_USERAGENT, "Mozilla/5.0 (Android 9.0; Mobile; rv:61.0) Gecko/61.0 Firefox/61.0");
	// tc->exec();

	// this->body = tc->getBody();
	this->body = this->phpStr(Php::call("file_get_contents", "a.tmp"));
	// delete tc;
}

std::string Google::html_entity_decode(char *str) {
	return Php::call(
		"html_entity_decode",
		str,
		Php::call("constant", "ENT_QUOTES"),
		"UTF-8"
	);
}

std::string strip_tags(std::string str) {
	return Php::call("strip_tags", str);
}

void Google::parse() {
	char ***result = (char***)malloc(200 * sizeof(char*));

	TeaPCRE *tre = new TeaPCRE();
	tre->setSubject(this->body.c_str());
	tre->setPattern(
		"(?:<div class=\"\\w{1,10}\\s\\w{1,10}\\s\\w{1,10}\\s\\w{1,10}\">.+<a href=\"/url\\?q=)(.*)(?:&amp.+\".+<div.+>)(.*)(?:<\\/div>.+<div class=\"\\w{1,10}\\s\\w{1,10}\\s\\w{1,10}\">)(\\w{5,})(?:<)",
		PCRE_CASELESS | PCRE_DOTALL | PCRE_UNGREEDY | PCRE_MULTILINE
	);

	unsigned int matchCount, matchCountD2, i, j;

	tre->multiFindAll(result, &matchCount, &matchCountD2, 10u);

	// 0 = url
	// 1 = title
	// 2 = description
	std::vector<std::vector<std::string>> r;
	std::vector<std::string> rTmp = {"", "", ""};

	for (i = 0; i < matchCount; ++i) {
		rTmp[0] = rTmp[1] = rTmp[2] = "";
		
		rTmp[0] = this->html_entity_decode(result[i][1]);
		rTmp[1] = this->strip_tags(this->html_entity_decode(result[i][2]));
		rTmp[2] = this->html_entity_decode(result[i][3]);

		r.push_back(rTmp);
	}

	Php::call("var_dump", r);

	delete tre;
}

std::string Google::get() {
	this->exec();
	this->parse();
	return this->body;
}
