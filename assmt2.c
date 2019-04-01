#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef char *data_t;

#define MAXCHARS 31
#define PERCENTAGE "%%%%%%%%%%"
#define MAXNAMES 100
#define BS_FOUND 1
#define BS_NOT_FOUND 0

/* designing a struct to represent a name and the probabilities */
typedef struct {
  char name[MAXCHARS];
  int prob_first;
  int prob_second;
  int prob_third;
} name_t;

typedef struct node node_t;

/* designing a struct to represent a node */
struct node {
	data_t data;
	node_t *next;
};

/* designing a struct to represent a list */
typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

/* function prototypes */
list_t *make_empty_list(void);
int is_empty_list(list_t *list);
void free_list(list_t *list);
list_t *insert_at_head(list_t *list, data_t value);
list_t *insert_at_foot(list_t *list, data_t value);

int
main(int argc, char *argv[]) {
  name_t A[MAXNAMES];
  list_t *list;
  char word[MAXCHARS];
  int counter = 0;
  int n;
  int word_count = 0;
  float avg;
  /* reading from the input data*/
  while (scanf("%s", word) == 1) {
      /* cheching if this is the end of the dictionary */
      if (strcmp(word, PERCENTAGE) == 0) {
        break;
      }
      /* read the name and store it's probabilities accordingly in the struct */
      if (scanf("%d%d%d", &A[counter].prob_first, &A[counter].prob_second,
      &A[counter].prob_third) == 3) {
        strcpy(A[counter].name, ((word)+1));
      }
      /* calculating the length of the name being read */
      n = strlen(A[counter].name);
      word_count += n;
      /* counter keeps track of the total number of words read */
      counter++;
  }
  printf("=========================Stage 1=========================\n");
  printf("Name 0: %s\nLabel probabilities: %d%% %d%% %d%%\n", A->name, A->prob_first,
  A->prob_second, A->prob_third);

  /* calculating the average number of characters per name */
  avg = (float)word_count/(float)counter;
  printf("=========================Stage 2=========================\nNumber of names: %d\n", counter);
  printf("Average number of characters per name: %.2f\n", avg);

  printf("=========================Stage 3=========================\n");

  /* creating an empty list to store the words */
  list = make_empty_list();
  while (scanf("%s", word) == 1) {
    strcpy(A[counter].name, word);
    if (isalpha(*A[counter].name)) {
      /* inserting the word being read into the end of the list */
      list = insert_at_foot(list, A[counter].name);
      /* printing the words stored in the list one at a line */
      printf("%s\n", A[counter].name);
    }
  }

  printf("=========================Stage 4=========================\n");
  node_t *current = list->head;
  int i, j;
  /* going through linked list of the words to check */
  for (i = 0; i < list_size; i++) {
    check = current->data;
    /* printing word and number of blanks necessary as per spec */
    int blanks = 32 - strlen(check);
    printf("%s", check);
    for (j = 0; j < blanks; j++) {
      printf(" ");
    }
    /* checking if the current word is a name */
    int locn;
    /* word is a name */
    if (binary_search(A, 0, counter, check, &locn)) {
      /* checking probabilites of it being first or last name */
      name_t data = A[locn];
      if (data.prob_first) {
        printf("FIRST_NAME");
      }
      if (data.prob_second) {
        printf(", LAST_NAME");
      }
      printf("\n");
    }
    /* word is not a name */
    else {
      printf("NOT_NAME\n");
    }
    current = current->next;
  }
  /* freeing the list to free the space in memory */
  free_list(list);
  /* assign list to null after usage */
  list = NULL;
  return 0;
}

/* creating an empty list
code from the file "listops.c" */
list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}
/* cheching that the list is empty
code from the file "listops.c" */
int
is_empty_list(list_t *list) {
	assert(list!=NULL);
	return list->head==NULL;
}

/* freeing the list after using it
code from the file "listops.c" */
void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}

/* populating the list by inserting a word at the end of the list
code from the file "listops.c" */
list_t
*insert_at_foot(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

/* binary search function to find a word */
int binary_search(name_t *A, int lo, int hi, char *key, int *locn) {
  int mid, outcome;
  if (lo >= hi) {
    return BS_NOT_FOUND;
  }
  mid = (lo + hi) / 2;
  if ((outcome = strcmp(key, A[mid].name)) < 0) {
    return binary_search(A, lo, mid, key, locn);
  } else if (outcome > 0) {
    return binary_search(A, mid + 1, hi, key, locn);
  } else {
    *locn = mid;
    return BS_FOUND;
  }
}
