#include "TeaCurl.h"

size_t TeaCurl::__teaCurlWriteFunc(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)contents, size*nmemb);
	return size*nmemb;
}

TeaCurl::TeaCurl(std::string url) {
	this->url = url;
	this->ch = curl_easy_init();
	this->setUp();
}

CURL *TeaCurl::getCurlResource() {
	return this->ch;
}

void TeaCurl::exec() {
	this->res = curl_easy_perform(ch);
	if(this->res == CURLE_OK) {
		curl_easy_getinfo(this->ch, CURLINFO_RESPONSE_CODE, &this->httpCode);
	} else {
		this->error = curl_easy_strerror(this->res);
	}
}

CURLcode TeaCurl::getInfo(CURLINFO infoOpt, void *ptr) {
	return curl_easy_getinfo(this->ch, infoOpt, ptr);
}

CURLcode TeaCurl::getRes() {
	return this->res;
}

std::string TeaCurl::getError() {
	return this->error;
}

std::string TeaCurl::getResponseHeader() {
	return this->responseHeader;
}

std::string TeaCurl::getBody() {
	return this->out;
}

long TeaCurl::getHttpCode() {
	return this->httpCode;
}

void TeaCurl::setOpt(CURLoption opt, const void *val) {
	curl_easy_setopt(this->ch, opt, val);
}

void TeaCurl::setUp() {
	curl_easy_setopt(this->ch, CURLOPT_URL, this->url.c_str());
	curl_easy_setopt(this->ch, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(this->ch, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(this->ch, CURLOPT_FOLLOWLOCATION, 1);
	
	curl_easy_setopt(this->ch, CURLOPT_WRITEFUNCTION, TeaCurl::__teaCurlWriteFunc);	
	curl_easy_setopt(this->ch, CURLOPT_WRITEDATA, &this->out);

	curl_easy_setopt(this->ch, CURLOPT_HEADERFUNCTION, TeaCurl::__teaCurlWriteFunc);
	curl_easy_setopt(this->ch, CURLOPT_WRITEHEADER, &this->responseHeader);
}

void TeaCurl::setProxy(std::string chp, std::string auth) {
	curl_easy_setopt(this->ch, CURLOPT_PROXY, chp.c_str());
	curl_easy_setopt(this->ch, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
	curl_easy_setopt(this->ch, CURLOPT_PROXYUSERPWD, auth.c_str());
}

void TeaCurl::close() {
	this->cleanUp();
	this->closed = 1;
}

void TeaCurl::cleanUp() {
	curl_easy_cleanup(this->ch);
}

TeaCurl::~TeaCurl() {
	if (!this->closed)
	{
		cleanUp();
	}
}