#include <stdio.h>
#include <stdlib.h>

#include "entity.h"

//functions for handling linked list of entities

EntityList instantiateEntity (
		Point2D center,
		BoundingBox spriteBox, 
		int textureID, 
		BoundingBox hitBox,
		int type,
		int subType,
		int hp,
		int bulletType,
		float speed,
		float delay,
		int shootAnglesNb,
		float* shootAngles
	) {
	//instantiate an entity according to the given parameters and return it's adress
	EntityList list;
	list = (Entity*)malloc(sizeof(Entity));
	if (list != NULL) {
		list->center = center;
		list->spriteBox = spriteBox;
		list->textureID = textureID;
		list->hitBox = hitBox;
		list->type = type;
		list->subType = subType;
		list->hp = hp;
		list->bulletType = bulletType;
		list->speed = speed;
		list->delay = delay;
		list->shootAnglesNb = shootAnglesNb;
		list->shootAngles = shootAngles;
		list->next = NULL;
		list->prev = NULL;
	} else printf("malloc error\n");
	return list;
}

EntityList copyEntity (EntityList orig) {
	//instantiate an entity with the same parameters as the one given as argument and return it's adress (except next & prev)
	EntityList list;
	list = (Entity*)malloc(sizeof(Entity));
	if (list != NULL) {
		list->center 		= orig->center;
		list->spriteBox 	= orig->spriteBox;
		list->textureID 	= orig->textureID;
		list->hitBox 		= orig->hitBox;
		list->type 			= orig->type;
		list->subType 		= orig->subType;
		list->hp 			= orig->hp;
		list->bulletType 	= orig->bulletType;
		list->speed 		= orig->speed;
		list->delay 		= orig->delay;
		list->shootAnglesNb = orig->shootAnglesNb;
		list->shootAngles 	= orig->shootAngles;
		list->next = NULL;
		list->prev = NULL;		
	} else printf("malloc error\n");
	return list;
}

void addEntityStart(EntityList* list, EntityList entity) {
	//adds the entity at the start of the list (only use with entity->next == NULL or the next entity will be lost in memory)
	entity->next = *list;
	(*list)->prev = entity;
	*list = entity;
}

void addEntityEnd(EntityList* list, EntityList entity) {
	//adds the entity at the end of the list (only use with entity->next == NULL or the next entity will be lost in memory)
	EntityList listTmp = *list;
	if (listTmp != NULL){
		while(listTmp->next != NULL)
			listTmp = listTmp->next;
		listTmp->next = entity;
	}
	entity->prev = listTmp;
	if (listTmp == NULL) {
		*list = entity;
	}
}

void removeEntity(EntityList* entity) {
	//remove the entity from the list it belongs to
	if (*entity != NULL) {
		//printf("not null\n");
		if ((*entity)->next != NULL) {
			//if the entity is not the last in the list
			//printf("not last\n");
			EntityList tmp = (*entity)->prev;
			free(*entity);
			(*entity) = (*entity)->next;
			(*entity)->prev = tmp;
		} else  {
			//if the entity is the lase in the list
			//printf("last\n");
			free(*entity);
			*entity = NULL;
		}
	}
}

void printEntity(EntityList list) {
	//prints all the parameters of an entity
	printf("=================\nEntity list :\n");
	while(list != NULL) {
		printf("  -----------------\n  center ------ : %f, %f\n",
			list->center.x, list->center.y);
		printf("  sprite ------ : %d ( %f, %f - %f, %f )\n",
			list->textureID,
			list->spriteBox.sw.x, 
			list->spriteBox.sw.y, 
			list->spriteBox.ne.x, 
			list->spriteBox.ne.y);
		printf("  hitbox ------ : %f, %f - %f, %f\n",
			list->hitBox.sw.x, 
			list->hitBox.sw.y, 
			list->hitBox.ne.x, 
			list->hitBox.ne.y);
		printf("  type, subtype : %d, %d\n", list->type, list->subType);
		printf("  hp ---------- : %d\n",list->hp);
		printf("  bulletType -- : %d\n",list->bulletType);
		printf("  delay ------- : %f\n",list->delay);
		printf("  shoot angles  : %d : { ",list->shootAnglesNb);
		int i = 0;
		for (i=0; i<list->shootAnglesNb; i++) {
			printf("%f ", list->shootAngles[i]);
		}
		printf("}\n");
		list = list->next;
	}
}
