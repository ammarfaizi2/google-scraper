
NAME = google-scraper

PHP_VERSION = 7.2
INI_DIR = /etc/php/${PHP_VERSION}/mods-available

EXTENSION_DIR = $(shell php-config${PHP_VERSION} --extension-dir)

PRIORITY = 20
EXTENSION = ${NAME}.so
INI = ${NAME}.ini

COMPILER = g++
LINKER = g++

COMPILER_FLAGS = -Wall -c -O3 -std=c++11 -fpic -o
LINKER_FLAGS = -shared
LINKER_DEPENDENCIES = -lphpcpp

RM = rm -vf
CP = cp -vf
LN = ln -vsf
MKDIR = mkdir -vp

#SOURCES = $(wildcard src/*.cpp)
SOURCES = $(shell find phx/ -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

SHARED_OBJECT_TO_BE_COMMITED = google-scraper-shared

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

deploy:
						${CP} ${EXTENSION} ${SHARED_OBJECT_TO_BE_COMMITED}

install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${INI} ${INI_DIR}/${PRIORITY}-${INI}
						${LN} ${INI_DIR}/${PRIORITY}-${INI} /etc/php/${PHP_VERSION}/cgi/conf.d
						${LN} ${INI_DIR}/${PRIORITY}-${INI} /etc/php/${PHP_VERSION}/cli/conf.d
						${LN} ${INI_DIR}/${PRIORITY}-${INI} /etc/php/${PHP_VERSION}/fpm/conf.d
						${LN} ${INI_DIR}/${PRIORITY}-${INI} /etc/php/${PHP_VERSION}/embed/conf.d
						${LN} ${INI_DIR}/${PRIORITY}-${INI} /etc/php/${PHP_VERSION}/phpdbg/conf.d
						${RM} ${EXTENSION} ${OBJECTS}


clean:
						${RM} ${OBJECTS} ${EXTENSION}