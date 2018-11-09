#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct prefix_t;
struct tree_t;

#define N 4000
#define M 4
struct prefix_t {
	int val;
	int index;
	int count;
	struct tree_t *subtree;
};
struct tree_t {
	int val;
	struct prefix_t *prefix;
	int num_prefix;
	int is_leaf;
};

int traverse_tree_for_prefix(struct tree_t *t, int prefix_index)
{
	int i;
	int count = 0;
	
	if (t->prefix[prefix_index -1].count != -1)
		return t->prefix[prefix_index -1].count;
	for (i = 0; i < prefix_index; i++) {
		if (!t->prefix[i].subtree)
			continue;
		if (t->prefix[i].subtree->is_leaf) {
			count++;
			t->prefix[i].count = count;
		}
		else {	
			count+=traverse_tree_for_prefix(t->prefix[i].subtree, i + 1);  		
			t->prefix[i].count = count;
		}
	}
	return count;
}

void main()
{
	struct tree_t tree[N];
	int i,j;
	int set[M] = {2,5,3,6};
	int count = 0;

	for (i = 0; i < N; i++) {
		tree[i].val = i + 1;
		tree[i].prefix = malloc(M * sizeof (struct prefix_t));
		tree[i].num_prefix = M;
		tree[i].is_leaf = 0;
		for (j = 0; j < tree[i].num_prefix; j++) {
			tree[i].prefix[j].count = -1;	
			tree[i].prefix[j].val = set[j];		
			tree[i].prefix[j].index = j;		
			if (tree[i].val == tree[i].prefix[j].val) {
				struct tree_t *subtree = malloc(sizeof (struct tree_t));
				subtree->val = tree[i].val;
				subtree->is_leaf = 1;
				subtree->num_prefix = 0;
				subtree->prefix = NULL;
				tree[i].prefix[j].subtree = subtree;
				continue;
			}
			if (tree[i].val > tree[i].prefix[j].val) {
				int diff = tree[i].val - tree[i].prefix[j].val;
				tree[i].prefix[j].subtree = &tree[diff - 1]; 			
			}
		}
	}

	count = traverse_tree_for_prefix(&tree[N-1], M);
	printf("N = %d, count = %d\n", N, count);

	/* free */
	for (i = 0; i < N; i++) {
		for (j = 0; j < tree[i].num_prefix; j++) {
			if (tree[i].prefix[j].subtree &&
			    tree[i].prefix[j].subtree->is_leaf)
				free(tree[i].prefix[j].subtree);
		}
		if (tree[i].prefix) {
			free(tree[i].prefix);
			tree[i].prefix = NULL;
		}
	}
}
