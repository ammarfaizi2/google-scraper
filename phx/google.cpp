
#include "headers/google.h"
#include "headers/google_class.h"

Php::Value google_search(Php::Parameters &p) {
	Google *g = new Google(p[0]);
	g->setPage(p[1]);
	Php::Value r = g->get();
	delete g;
	return r;
}

Php::Value google_image(Php::Parameters &p) {
	Google *g = new Google(p[0]);
	g->setPage(p[1]);
	Php::Value r = g->getImage();
	delete g;
	return r;
}
