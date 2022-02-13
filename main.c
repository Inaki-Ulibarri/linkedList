/*
 * Trying to follow BSD KNF guidelines
 * NULL is replaced with 0 in here because I blindly follow
 * what I read on books :D (Modern C btw)
 * TODO: add history to the commands with readline/history.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

#include <readline/readline.h>

struct anon{
	char name[5]; //it >>has<< to be "anon"
	bool gender;
	uint64_t d_sucked; //may overflow
	uint8_t hugs_in_life;
	/* uint4_t could suffice, but it is not standard */
	size_t animes_seen;
	struct anon *prev_anon;
	struct anon *next_anon;
};
typedef struct anon anon;
enum gender{FEMALE, MALE};

anon*
anonCreate()
{
	anon *somebody = malloc(sizeof(anon));
	return (somebody);
}

void
anonInit(anon *ann,
	 bool gend,
	 uint64_t dcks_suck,
	 uint8_t hugs_in_lf,
	 size_t animes_watch,
	 anon *prev,
	 anon *next)
{
	strcpy(ann->name, "anon");
	ann->gender = gend;
	ann->d_sucked = dcks_suck;
	ann->hugs_in_life = hugs_in_lf;
	ann->animes_seen = animes_watch;
	ann->prev_anon = prev;
	ann->next_anon = next;
}

void
anonGets(anon *ann)
{
	char inp[64];
	bool gnd;
	printf("Male or Female: ");
	fgets(inp, 64, stdin);
	/* probably add regex to this thing */
	if (strcmp(inp, "Female") ||
	    strcmp(inp, "female"))
		gnd = FEMALE;
	else
		gnd = MALE;
	
	printf("Dicks sucked: ");
	fgets(inp, 64, stdin);
        uint64_t d_suck;
	sscanf(inp, "%zu", &d_suck);
	
	printf("Hugs in life: ");
	fgets(inp, 64, stdin);
	uint8_t hgs_in_lf = (uint8_t)atoi(inp);

	printf("Anime Watched (quantity): ");
	fgets(inp, 64, stdin);
	size_t an_seen = atol(inp);

	anonInit(ann,
		 gnd,
		 d_suck,
		 hgs_in_lf,
		 an_seen,
		 0,
		 0);
}

void
anonAppend(anon *node, anon *app)
{
	if (node->next_anon == 0) {
		node->next_anon = app;
		app->prev_anon = node;
		app->next_anon = 0;
	} else {
		anon *tail = node->next_anon;
		node->next_anon = app;
		app->next_anon = tail;
		app->prev_anon = node;
		tail->prev_anon = app;
	}
}

/* Remove an anon from the list */
void
anonRemove(anon *node)
{
	if (node->prev_anon == 0){
		anon *nxt = node->next_anon;
		nxt->prev_anon = 0;
		free (node);
	} else if (node->next_anon == 0) {
		anon *prv = node->prev_anon;
		prv->next_anon = 0;
		free (node);
	} else {
		anon *prv = node->prev_anon;
		anon *nxt = node->next_anon;
		prv->next_anon = node->next_anon;
		nxt->prev_anon = node->prev_anon;
		free (node);
	}
}
	
anon*
listCreate()
{
	anon *head = anonCreate(),
		*node = anonCreate(),
		*tail = anonCreate();
	/* I am hilarious */
	anonInit(head,
		 MALE,
		 69,
		 0,
		 420,
		 0,
		 node);
	anonInit(node,
		 MALE,
		 999999999,
		 0,
		 14,
		 head,
		 tail);
	anonInit(tail,
		 MALE,
		 0,
		 32,
		 0,
		 node,
		 0);
	
	return (head);
}

void
listRemove(anon *node)
{
	while (node->prev_anon != 0)
		node = node->prev_anon;

	anon *tmp;
	while (node->next_anon != 0){
		tmp = node->next_anon;
		free(node);
		node = tmp;
	}
			
}

/* Move pos times in the list, if pos is negative  */
/* it will move backwards in the list */
anon*
anonMove(anon *node, const int pos)
{
	int i = pos;
	if (pos < 0){
		for (; i < 0; ++i){
			if (node->prev_anon == 0)
				break;
			node = node->prev_anon;
		}
	} else if (pos > 0) {
		for (; i > 0; --i){
			if (node->next_anon == 0)
				break;
			node = node->next_anon;
		}
	}
	return (node);
}

void
anonPrint(anon *node)
{
	printf("\nName:\t%s\n"
	       "gender:\t%s\n"
	       "Dicks Sucked:\t%lu\n"
	       "Hugs received:\t%u\n"
	       "Animes seen:\t%zu\n"
	       "\n"
	       ,node->name,
	       (node->gender == FEMALE ? "female":"male"),
	       node->d_sucked,
	       node->hugs_in_life,
	       node->animes_seen);
}

/* the function expects the head of the linked list, */
/* in case it is not, it >>will<< find it */
void
listPrint(anon *node)
{
	while(node->prev_anon != 0){
		node = node->prev_anon;
	}

	/* won't write an overcomplicated for loop */
	for(;;) {
		anonPrint(node);
		if(node->next_anon == 0)
			break;
		node = node->next_anon;
	}
}

struct dumm_anon{
	char name[5]; //it >>has<< to be "anon"
	bool gender;
	uint64_t d_sucked; //may overflow
	uint8_t hugs_in_life;
	/* uint4_t could suffice, but it is not standard */
	size_t animes_seen;
};
typedef struct dumm_anon dumm_anon;

//copy anon to a dumm_anon for saving purposes
void
anonToDumm(const anon *source, dumm_anon *target)
{
	strcpy(target->name, "anon");
	target->gender = source->gender;
	target->d_sucked = source->d_sucked;
	target->hugs_in_life = source->hugs_in_life;
	target->animes_seen = source->animes_seen;
}

void
dummToAnon(const dumm_anon *source, anon *target, anon *prv, anon *nxt)
{
	strcpy(target->name, "anon");
	target->gender = source->gender;
	target->d_sucked = source->d_sucked;
	target->hugs_in_life = source->hugs_in_life;
	target->animes_seen = source->animes_seen;
	target->prev_anon = prv;
	target->next_anon = nxt;
}

int
listSave(const char *fname, anon *node)
{
	FILE *f;
	f = fopen(fname, "w");
	if(f == 0x0) {
		fprintf(stderr, "Error creating file '%s'.\n",
			fname);
		return (1);
	}
	for (;;) {
		if (node->prev_anon == 0)
			break;
		node = node->prev_anon;
	}
	dumm_anon *foo = malloc(sizeof(dumm_anon));
	for (;;) {	
		anonToDumm(node, foo);
		fwrite(foo, sizeof(dumm_anon), 1, f);
		if (node->next_anon == 0)
			break;
		node = node->next_anon;
	}
	fclose(f);
	free(foo);
	return (0);
}


void
dummPrint(dumm_anon *node)
{
	printf("\nName:\t%s\n"
	       "gender:\t%s\n"
	       "Dicks Sucked:\t%lu\n"
	       "Hugs received:\t%u\n"
	       "Animes seen:\t%zu\n"
	       "\n"
	       ,node->name,
	       (node->gender == FEMALE ? "female":"male"),
	       node->d_sucked,
	       node->hugs_in_life,
	       node->animes_seen);
}

int
listRead(const char *fname, anon *head)
{
	FILE *f;
	f = fopen(fname, "r");
	if (f == 0x0) {
		fprintf(stderr, "Error opening file '%s'\n",
			fname);
		return (1);
	}
	
	dumm_anon dmm;
	anon *node = anonCreate();
	fread(&dmm, sizeof(dumm_anon), 1, f);
	dummToAnon(&dmm, head, 0, 0);
 	while(fread(&dmm, sizeof(dumm_anon), 1, f)) {
		dummToAnon(&dmm, node, head, 0);
		anonAppend(head, node);
		head = node;
		node = anonCreate();
	}
	
	free(node);
	fclose(f);
	return (0);
}

void
helpPrint()
{
	printf("Some help: This is a basic linked list program \n"
	       "The commands of this program are: \n"
	       "\thelp: display this help text \n"
	       "\tlistCreate: create a list with the default values\n"
	       "\tlistPrint: list the current list\n"
	       "\tanonAppend: Append an anon to the list\n"
	       "\tanonPrint: Print the current anon\n"
	       "\tanonUp: Move one anon up the list\n"
	       "\tanonDown: Move one anon down the list\n"
	       "\tlistSave: Save a list to a file\n"
	       "\tlistRead: Read a list from a file\n"
	       "\texit: exit the program\n");
}

void
promptStart(anon* node)
{
	char *cmd = (char *)1;
	while (cmd != 0){
		/* Yanderedeving, some anon told it wasn't that bad */
		/* for simple stuff */
		cmd = readline(">> ");
		if (cmd == 0x0) /* I live for the jank */
			continue;
		
		else if (!strcmp(cmd, "help")) /* help */
			helpPrint();
		
		else if (!strcmp(cmd, "listCreate")){ /* listCreate */
			node = listCreate();
			listPrint(node);
		
		} else if (!strcmp(cmd, "listPrint")) /* listPrint */
			listPrint(node);
		
		else if(!strcmp(cmd, "anonPrint")) /* anonPrint */
			anonPrint(node);
		
		else if (!strcmp(cmd, "anonAppend")) { /* anonAppend */
			anon *tmp = anonCreate();
			anonGets(tmp);
			anonAppend(node, tmp);
			
		} else if (!strcmp(cmd, "anonUp")) /* anonMove */
			node = anonMove(node, 1);

		else if (!strcmp(cmd, "anonDown")) /* anonMove */
			node = anonMove(node, -1);
		
		else if (!strcmp(cmd, "listSave")) { /* listSave */
			printf("Name for the database: ");
			char name[68];
			fgets(name, 68, stdin);
			sscanf(name, " %s", name);
			listSave(name, node);

		} else if (!strcmp(cmd, "listRead")) { /* listRead */
			printf("Name for the database: ");
			char name[68];
			fgets(name, 68, stdin);
			sscanf(name, " %s", name);
			listRead(name, node);
			
		} else if (!strcmp(cmd, "exit")){
			listRemove(node);
			break;
		} else
			printf("I don't recognize that option, try \"help\"\n");	
	}
}

int
main()
{
	anon *lst = listCreate();
	promptStart(lst);
 	return (0);
}
