#include <phpcpp.h>

#include "headers/google.h"

extern "C" {
    PHPCPP_EXPORT void *get_module() {
        static Php::Extension extension("google-scraper", "1.0");
        extension.add<google_search>("google_search", {
        	Php::ByVal("query", Php::Type::String),
        	Php::ByVal("page", Php::Type::Numeric),
            Php::ByVal("use_proxy", Php::Type::Numeric),
            Php::ByVal("proxy", Php::Type::String),
            Php::ByVal("proxy_auth", Php::Type::String)
        });
        extension.add<google_image>("google_image", {
        	Php::ByVal("query", Php::Type::String),
        	Php::ByVal("page", Php::Type::Numeric),
            Php::ByVal("use_proxy", Php::Type::Numeric),
            Php::ByVal("proxy", Php::Type::String),
            Php::ByVal("proxy_auth", Php::Type::String)
        });
        return extension;
    }
}
