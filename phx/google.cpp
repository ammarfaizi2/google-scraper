
#include "headers/google.h"
#include "headers/google_class.h"

Php::Value google_search(Php::Parameters &p) {
	Google *g = new Google(p[0]);
	g->setPage(p[1]);
	return g->get();
}

Php::Value google_image(Php::Parameters &p) {

}
