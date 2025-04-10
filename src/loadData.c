#include <stdio.h>
#include <stdlib.h>
#include "xmlParser.h"


gameData* initData(char* filename){

	/*Tarefa : adicionar leitura de audio driver */

	/*
	   xmlChar* title;
	   xmlChar* version;
	   xmlChar* icon;
	   xmlChar* author;
	   */

	gameData* data = malloc(sizeof(gameData));

	xmlDoc* file = NULL;
	xmlKeepBlanksDefault(0);

	if (! (file = xmlReadFile(filename, NULL, 0)) ){
		fprintf(stderr, "[ERROR] Failed to read game data");
	}


	xmlNode* root = xmlDocGetRootElement(file);

	xmlNode* node = root->children;

	while(node != NULL){

		if(! xmlStrcmp(node->name, (xmlChar*)"title" ) ){
			data->title = xmlNodeGetContent(node);
			fprintf(stdout, "setting game title: %s", (char*)data->title);
		}else if(! xmlStrcmp(node->name, (xmlChar*)"version")) {
			data->version = xmlNodeGetContent(node);

		}else if(! xmlStrcmp(node->name, (xmlChar*)"volume")){
			data->volume = atof((char*)xmlNodeGetContent(node));
		}else if(! xmlStrcmp(node->name, (xmlChar*)"icon")){
			data->icon = xmlNodeGetContent(node);
		}


		node = node->next;
	}

	xmlFreeDoc(file);

	fprintf(stdout, "[DONE] gamedata loaded");


	data->audiodriver = (char*)"pulseaudio";

	return data;

}



