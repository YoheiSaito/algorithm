#include <stdio.h>
#include <stdlib.h>
#define BTREE_DIM 4
#define BTREE_MAX_KEY (BTREE_DIM*2-1)
#define False 0
#define True  1

// when read the integer listed file 
// READ_TYPE_SET_CHAR flag is 0
#define READ_TYPE_SET_CHAR 0

#if TYPE_SET_CHAR
#define READ_TYPE char
#define PRINT_FMT "%c\n"
#else
#define READ_TYPE int
#define PRINT_FMT "%d\n"
#endif


// bt_tree structures
typedef struct _Bt_node{
	int n;
	// use 1 to n of array
	READ_TYPE key[BTREE_MAX_KEY+1];
	struct _Bt_node* c[BTREE_MAX_KEY+2];
	_Bool leaf;
}Bt_node;

typedef struct{
	Bt_node* node;
	int i;
} Bt_search_result;


// proto type decs 
Bt_search_result bt_search(Bt_node* node, READ_TYPE key);
void bt_insert_nonfull(Bt_node *x, READ_TYPE k);
void bt_insert(Bt_node **node, READ_TYPE key);
void bt_split_child(Bt_node *x, int i);
void bt_print(Bt_node* node, int depth);
void bt_delete(Bt_node* root);


int main(int argc, char* argv[]){
	FILE *fp;
	Bt_node* root;
	// btree create
	root = (Bt_node*)malloc(sizeof(Bt_node));
	root->leaf = True;
	root->n = 0;
	
	// file open
	if( (fp = fopen((argc<2)?"data.txt":argv[1], "r")) == NULL){
		printf("failed to open the file.\n");
		exit(EXIT_FAILURE);
	}

	bt_print(root, 1);
	// file read and insert
	char s[256];
	while(fgets(s, 256, fp) != NULL){
		#if TYPE_SET_CHAR
		bt_insert(&root, s[0]);
		#else
		bt_insert(&root, atoi(s));
		#endif
	}
	fclose(fp);

	// print result
	bt_print(root, 0);
	printf("\n");
	Bt_search_result ret;
	int k = 98;
	ret = bt_search(root, k);
	if( ret.node != NULL){
		printf( "%d is %dth elem in this node: ", k, ret.i);
		for( int i = 1; i <= ret.node->n; i++){
			printf("%d ", ret.node->key[i]);
		}
		printf("\n");
	}else{
		printf("bt_search return NIL\n");
	}

	k = 35;
	ret = bt_search(root, k);
	if( ret.node != NULL){
		printf( "%d is %dth elem in this node: ", k, ret.i);
		for( int i = 1; i <= ret.node->n; i++){
			printf("%d ", ret.node->key[i]);
		}
		printf("\n");
	}else{
		printf("bt_search return NIL\n");
	}
	

	bt_delete(root);
	return 0;
}

// implelemt of B-TREE-SEARCH(x, k)
Bt_search_result bt_search(Bt_node* node, READ_TYPE key){
	int i = 1; 
	while( i <= node->n && key > node->key[i]){
		i++;
	}
	if( i <= node->n && key == node->key[i]){
		Bt_search_result ret;
		ret.node = node;
		ret.i = i;
		return ret;
	}else if(node->leaf){
		Bt_search_result ret;
		ret.node = NULL;
		ret.i = 0;
		return ret;
	}else{
		return bt_search(node->c[i], key);
	}
}


// node is double pointer 
// to rewrite new root
void bt_insert(Bt_node **node, READ_TYPE key){
	Bt_node* r = *node;
	if( r->n == BTREE_MAX_KEY){
		//create new root:s and swap
		Bt_node* s;
		s = (Bt_node*)malloc(sizeof(Bt_node));
		*node = s;
		s->leaf = False; 
		s->n = 0;
		s->c[1] = r;
		bt_split_child(s, 1);
		bt_insert_nonfull(s, key);
	}else{
		bt_insert_nonfull(r, key);
	}
}

void bt_insert_nonfull(Bt_node *x, READ_TYPE k){
	int i = x->n;
	if( x->leaf){
		while( i >= 1 && k < x->key[i]){
			x->key[i+1] = x->key[i];
			i--;
		}
		x->key[i+1] = k;
		x->n = x->n+1;
		// DISK-WRITE
	}else {
		while(i >= 1 && k < x->key[i]){
			i--;
		}
		i++;
		//DISK-READ
		if(x->c[i]->n == BTREE_MAX_KEY){
			bt_split_child(x, i);
			if( k > x->key[i])
				i++;
		}
		bt_insert_nonfull(x->c[i], k);
	}
}
void bt_split_child(Bt_node *x, int i){
	int j;

	// x
	//y z
	// allocate node
	Bt_node *y, *z;
	z = (Bt_node*)malloc(sizeof(Bt_node));

	// saturation child is x->c[i]
	y = x->c[i];
	z->leaf = y->leaf; 
	z->n = BTREE_DIM - 1;
	for(j = 1; j <= BTREE_DIM-1; j++){
		z->key[j] = y->key[j+BTREE_DIM];
	}
	if( !y->leaf){
		for(j = 1; j <= BTREE_DIM; j++){
			z->c[j] = y->c[j+BTREE_DIM];
		}
	}
	// this method execute, when node  x->c[i] is full (= 2*t-1)
	// because of conncatinated y and z is equal to x->c[i] and x[i],
	// y->n and z->n must be t-1;
	y->n = BTREE_DIM - 1;

	for(j = x->n+1; j >= i+1; j--){
		x->c[j+1] = x->c[j];
	}
	x->c[i+1] = z;
	for(j = x->n; j >= i; j--){
		x->key[j+1] = x->key[j];
	}
	x->key[i] = y->key[BTREE_DIM];
	x->n++;
	//disk write

}

void bt_print(Bt_node* node, int depth){
	if(node == NULL)
		return;
	for(int i = 1; i <= node->n; i++){
		bt_print(node->c[i], depth+1);
		for(int j = 0; j < depth; j++){
			printf("|---");
		}
		printf(PRINT_FMT, node->key[i]);
	}
	bt_print(node->c[node->n+1], depth+1);
}
void bt_delete(Bt_node* root){
	if(!root->leaf){
		for(int i = 1; i < root->n; i++){
			bt_delete(root->c[i]);
		}
	}
	free(root);
}
/*
   実行結果


|---2
|---4
|---5
|---8
|---10
|---13
|---14
15
|---17
|---20
|---23
|---25
|---29
|---31
|---32
36
|---38
|---40
|---46
|---48
49
|---52
|---53
|---56
|---60
|---62
64
|---66
|---72
|---73
76
|---80
|---82
|---83
|---86
88
|---90
|---92
|---93
|---98

98 is 4th elem in this node: 90 92 93 98 
bt_search return NIL

*/
