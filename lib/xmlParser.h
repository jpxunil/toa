#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlstring.h>

typedef struct gameData{
		xmlChar* title;
		xmlChar* version;
		float volume;
		xmlChar* author;
}gameData;

gameData* initData(char* filename);


#endif
