#include <stdio.h>
#include <stdlib.h>
#define BTREE_DIM 4
#define BTREE_MAX_KEY (BTREE_DIM*2-1)


// bt_tree structures
typedef struct{
	int n;
	int key[2*BTREE_DIM-1];
	int c[2*BTREE_DIM-1];
	_Bool leaf;
} Bt_node;

typedef struct{
	Bt_node* node;
	int i;
} Bt_search_result;


// proto type decs 
Bt_search_result bt_search(Bt_node* node, int key);
void bt_insert(Bt_node *node, int key);
void bt_split_child(Bt_node *x, int i);
void bt_print(Bt_node* node, int depth);


int main(int argc, char* argv[]){
	FILE *fp;
	Bt_node root;

	// btree create
	root.leaf = 1;
	root.n = 0;
	
	// file open
	if( (fp = fopen((argc<2)?"data.txt":argv[1], "r")) == NULL){
		printf("failed to open the file.\n");
		exit(EXIT_FAILURE);
	}

	// file read and insert
	char s[256];
	while(fgets(s, 256, fp) != NULL){
		bt_insert(&root, atoi(s));
	}
	fclose(fp);

	// print result
	bt_print(&root, 0);

	return 0;
}

// implelemt of B-TREE-SEARCH(x, k)
Bt_search_result bt_search(Bt_node* node, int key){
	int i = 0; 
	while( i < node.n && key > node.key[i]){
		i++;
	}
	if( i < node.n && key == node.key[i]){
		Bt_search_result ret;
		ret.node = node;
		ret.i = i;
		return ret;
	}else if(x.leaf){
		Bt_search_result ret;
		ret.node = NULL;
		ret.i = 0;
		return ret;
	}else{
		return bt_search(node.c[i], key);
	}
}


void bt_insert(Bt_node *node, int key){
	Bt_node* r = node;
	if( r.n == BTREE_MAX_KEY){
		Bt_node* s;
		T.root = s;
		bt_split_child(s, 1);
		bt_insert_nonfull(s, k);
	}else{
		bt_insert_nonfull(node, k);
	}
}
void bt_split_child(Bt_node *x, int i){
	// saturation child is x.c[i]
	Bt_node* y = x.c[i];
	Bt_node* z;
	z->leaf = y->leaf; 
	z->n = t - 1;
	for( int j = 0; j < DIM-1; j++){
		z.key[j] = y.key[j+MAX
	}
}
void bt_print(Bt_node* node, int depth){
	for(int i = 0; i < node.n; i++){
		if( !node.leaf ){
			bt_print(node.c[i], depth+1);
		}
		for(int j = 0; j < depth; j++){
			printf("\t");
		}
		printf("%s\n", node[i]);
	}
	if( !node.leaf ){
		bt_print(node.c[node.n], depth+1);
	}
}
