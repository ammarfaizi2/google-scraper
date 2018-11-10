#include <phpcpp.h>

#include "headers/google.h"

extern "C" {
    PHPCPP_EXPORT void *get_module() {
        static Php::Extension extension("teaai", "1.0");
        extension.add<google_search>("google_search", {
        	Php::ByVal("query", Php::Type::String),
        	Php::ByVal("page", Php::Type::Numeric)
        });
        extension.add<google_image>("google_image", {
        	Php::ByVal("query", Php::Type::String),
        	Php::ByVal("page", Php::Type::Numeric)
        });
        return extension;
    }
}
