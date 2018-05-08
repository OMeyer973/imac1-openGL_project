#include <stdio.h>
#include <stdlib.h>

#include "entity.h"

//functions for handling linked list of entities

EntityList instantiateEntity (
		Point2D anchor,
		BoundingBox spriteBox, 
		int textureID, 
		BoundingBox hitBox,
		int type,
		int subType,
		int hp,
		int bulletType,
		float angle,
		float speed,
		float shootDelay,
		float invDelay,
		int shootAnglesNb,
		float* shootAngles,
		int behaviorsNb,
		int* behaviors
	) {
	//instantiate an entity according to the given parameters and return it's adress
	EntityList list;
	list = (Entity*)malloc(sizeof(Entity));
	if (list != NULL) {
		list->anchor 		= anchor;
		list->spriteBox 	= spriteBox;
		list->textureID 	= textureID;
		list->hitBox 		= hitBox;
		list->type 			= type;
		list->subType 		= subType;
		list->hp 			= hp;
		list->bulletType 	= bulletType;
		list->angle 		= angle;
		list->speed 		= speed;
		list->shootDelay	= shootDelay;
		list->shootTime  	= 0.0;
		list->invDelay		= invDelay;
		list->invTime   	= 0.0;
		list->shootAnglesNb = shootAnglesNb;
		int i = 0;
		for (i=0; i<shootAnglesNb; i++) {
			list->shootAngles[i] = shootAngles[i];
		}
		list->behaviorsNb = behaviorsNb;
		for (i=0; i<behaviorsNb; i++) {
			list->behaviors[i] = behaviors[i];
		}
		list->next 			= NULL;
		list->prev 			= NULL;
	} else printf("malloc error\n");
	return list;
}

EntityList copyEntity (EntityList orig) {
	//instantiate an entity with the same parameters as the one given as argument and return it's adress (except next & prev)
	EntityList list;
	list = (Entity*)malloc(sizeof(Entity));
	if (list != NULL) {
		*list = *orig;

		list->next = NULL;
		list->prev = NULL;		
	} else printf("malloc error\n");
	return list;
}

void addEntityStart(EntityList* list, EntityList entity) {
	//adds the entity at the start of the list (only use with entity->next == NULL or the next entity will be lost in memory)
	entity->next = *list;
	if (*list != NULL)
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

void removeEntity(EntityList* entity, EntityList* list) {
	//remove the entity from the list it belongs to
	if (*entity != NULL) {
		
		int isNext = ((*entity)->next != NULL);
		int isPrev = ((*entity)->prev != NULL);
		EntityList tmpNext = (*entity)->next;
		EntityList tmpPrev = (*entity)->prev;
		
		free(*entity);
		*entity = NULL;
		
		if (isPrev) {
			if (isNext) {
				tmpPrev->next = tmpNext;
				tmpNext->prev = tmpPrev;
			} else
				tmpPrev->next = NULL;
		}

		if (!isPrev) {
			if (isNext) {
				*list = tmpNext;
				(*list)->prev = NULL;
			} else
				*list = NULL;
		}
	}
}

void printEntity(EntityList list) {
	//prints all the parameters of an entity
	printf("=================\nEntity list :\n");
	while(list != NULL) {
		printf("  -----------------\n  anchor ------ : %f, %f\n",
			list->anchor.x, list->anchor.y);
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
		printf("  angle, speed  : %f, %f\n",list->angle, list->speed);
		printf("  bulletType -- : %d\n",list->bulletType);
		printf("  shootDelay -- : %f\n",list->shootDelay);
		printf("  shoot angles  : %d : { ",list->shootAnglesNb);
		int i = 0;
		for (i=0; i<list->shootAnglesNb; i++) {
			printf("%f ", list->shootAngles[i]);
		}
		printf("}\n");
		list = list->next;
	}
}
