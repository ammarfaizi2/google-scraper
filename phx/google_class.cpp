
/**
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 *
 */

#include "headers/google_class.h"
#include "tealib/TeaCurl/TeaCurl.h"
#include "tealib/TeaPCRE/TeaPCRE.h"

Google::Google(std::string query) {
	this->query = query;
}

Google::~Google() {
	// Destructor.
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
	
	// printf("URL: %s\n", this->url.c_str());

	TeaCurl *tc = new TeaCurl(this->url);
	tc->setOpt(CURLOPT_COOKIEJAR, (this->getCwd()+"/cookie.txt").c_str());
	tc->setOpt(CURLOPT_COOKIEFILE, (this->getCwd()+"/cookie.txt").c_str());
	tc->setOpt(CURLOPT_USERAGENT, "Mozilla/5.0 (Android 9.0; Mobile; rv:61.0) Gecko/61.0 Firefox/61.0");

	if (this->useProxy) {
		tc->setOpt(CURLOPT_PROXY, this->ch_proxy.c_str());
		tc->setOpt(CURLOPT_PROXYUSERPWD, this->ch_proxyauth.c_str());
		CURL *ch = tc->getCurlResource();
		curl_easy_setopt(ch, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
	}

	tc->exec();

	this->body = tc->getBody();
	
	delete tc;
}

void Google::setProxy(std::string ch_proxy, std::string ch_proxyauth) {
	this->useProxy = 1;
	this->ch_proxy = ch_proxy;
	this->ch_proxyauth = ch_proxyauth;
}

std::string Google::html_entity_decode(char *str) {
	return Php::call("trim", Php::call(
		"html_entity_decode",
		std::string(str),
		Php::call("constant", "ENT_QUOTES"),
		"UTF-8"
	));
}

std::vector<std::vector<std::string>> Google::parse() {

	char ***result = (char***)malloc(10 * sizeof(char*));
	TeaPCRE *tre = new TeaPCRE();
	tre->setSubject(this->body.c_str());
	tre->setPattern(
		"(?:<div class=\"\\w{1,10}\\s\\w{1,10}\\s\\w{1,10}\\s\\w{1,10}\">.+<a href=\"/url\\?q=)(.*)(?:&amp.+\".+<div.+>)(.*)(?:<\\/div>.+<div class=\"\\w{1,10}\\s\\w{1,10}\\s\\w{1,10}\">)(.*)(?:<\\/div>[^\\<\\>]*<\\/div>)",
		PCRE_CASELESS | PCRE_DOTALL | PCRE_UNGREEDY | PCRE_MULTILINE
	);

	unsigned int matchCount, matchCountD2, i
		;//, j;
	tre->multiFindAll(result, &matchCount, &matchCountD2, 10u);

	// 0 = url
	// 1 = title
	// 2 = description

	std::vector<std::vector<std::string>> dresult;
	std::vector<std::string> rTmp = {"", "", ""};

	for (i = 0; i < matchCount; ++i) {
		rTmp[0] = rTmp[1] = rTmp[2] = "";
		
		//
		// // debug only
		//
		// printf("Result %d:\n", i);
		// for (j = 1; j < matchCountD2; j++)
		// {
		// 	printf("\tSub Result %d: \n\t\t%s\n", j, result[i][j]);
		// }
		// printf("======================\n");

		free(result[i][0]);
		rTmp[0] = this->html_entity_decode(result[i][1]);
		free(result[i][1]);
		rTmp[1] = this->html_entity_decode(result[i][2]);
		free(result[i][2]);
		rTmp[2] = this->html_entity_decode(result[i][3]);
		free(result[i][3]);
		free(result[i]);
		result[i][0] = result[i][1] = result[i][2] = result[i][3] = nullptr;
		result[i] = nullptr;

		this->descriptionParser(&rTmp[2]);

		dresult.push_back(rTmp);
	}
	free(result);
	result = nullptr;

	// Php::call("printf", "%s", Php::call("json_encode", this->result, 128));

	delete tre;

	return dresult;
}

void Google::descriptionParser(std::string *desc_str) {
	TeaPCRE *tre = new TeaPCRE();
	tre->setSubject((*desc_str).c_str());
	tre->setPattern(
		"<.*>",
		PCRE_DOTALL | PCRE_UNGREEDY | PCRE_MULTILINE
	);

	unsigned int matchCount, matchCountD2, i, j;

	char ***result = (char***)malloc(10 * sizeof(char*));
	tre->multiFindAll(result, &matchCount, &matchCountD2, 10u);

	std::vector<std::string> r1;
	std::vector<std::string> r2;

	if (matchCount) {
		
		for (j = 0; j < matchCount; ++j) {
			for (i = 0; i < matchCountD2; ++i) {
				r1.push_back(std::string(result[j][i]));
				r2.push_back("");
				free(result[j][i]);
			}
			free(result[j]);
		}

		r1.push_back("\t");
		r2.push_back("");
		r1.push_back("\n\n");
		r2.push_back("\n");
		r1.push_back("  ");
		r2.push_back(" ");
		r1.push_back("\n\n\n");
		r2.push_back("\n");

		*desc_str = this->phpStr(Php::call("trim", Php::call("str_replace", r1, r2, *desc_str)));
	}
	free(result);
	delete tre;
	tre = nullptr;
	result = nullptr;
}

Php::Value Google::get() {
	this->exec();
	return this->parse();
}

void Google::imageExec() {
	this->buildUrl();
	this->url += "&tbm=isch";

	TeaCurl *tc = new TeaCurl(this->url);
	tc->setOpt(CURLOPT_COOKIEJAR, (this->getCwd()+"/cookie.txt").c_str());
	tc->setOpt(CURLOPT_COOKIEFILE, (this->getCwd()+"/cookie.txt").c_str());
	tc->setOpt(CURLOPT_USERAGENT, "Mozilla/5.0 (Android 9.0; Mobile; rv:61.0) Gecko/61.0 Firefox/61.0");
	tc->exec();

	this->body = tc->getBody();
	// Php::call("file_put_contents", "b.tmp", this->body);
	// this->body = this->phpStr(Php::call("file_get_contents", "b.tmp"));
	delete tc;
}

std::vector<std::vector<std::string>> Google::imageParse() {	

	// src="https://encrypted

	char ***result = (char***)malloc(50 * sizeof(char*));
	TeaPCRE *tre = new TeaPCRE();
	tre->setSubject(this->body.c_str());
	tre->setPattern(
		"(?:data-index=\")(\\d+)(?:\".+src=\")(https:\\/\\/encrypted.+)(?:\".+alt=\")(.*)(?:\")",
		PCRE_CASELESS | PCRE_DOTALL | PCRE_UNGREEDY | PCRE_MULTILINE
	);

	unsigned int matchCount, matchCountD2, i;//, j;
	tre->multiFindAll(result, &matchCount, &matchCountD2, 50u);

	// 0 = data-index
	// 1 = image url
	// 2 = description

	std::vector<std::vector<std::string>> dresult;
	std::vector<std::string> rTmp = {"", "", ""};

	for (i = 0; i < matchCount; ++i) {
		rTmp[0] = rTmp[1] = rTmp[2] = "";
		
		
		// debug only
		
		// printf("Result %d:\n", i);
		// for (j = 1; j < matchCountD2; j++)
		// {
		// 	printf("\tSub Result %d: \n\t\t%s\n", j, result[i][j]);
		// }
		// printf("======================\n");

		free(result[i][0]);
		rTmp[0] = this->html_entity_decode(result[i][1]);
		free(result[i][1]);
		rTmp[1] = this->html_entity_decode(result[i][2]);
		free(result[i][2]);
		rTmp[2] = this->html_entity_decode(result[i][3]);
		free(result[i][3]);
		free(result[i]);
		result[i][0] = result[i][1] = result[i][2] = result[i][3] = nullptr;
		result[i] = nullptr;

		this->descriptionParser(&rTmp[2]);

		dresult.push_back(rTmp);
	}
	free(result);
	result = nullptr;

	// Php::call("printf", "%s", Php::call("json_encode", this->result, 128));

	delete tre;
	return dresult;
}

Php::Value Google::getImage() {
	this->imageExec();
	return this->imageParse();
}
