#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlstring.h>

typedef struct gameData{
	xmlChar* title;
	xmlChar* version;
	xmlChar* author;
	xmlChar* icon;
	float volume;
}gameData;

gameData* initData(char* filename);

#endif
