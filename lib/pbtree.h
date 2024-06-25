#ifndef PCLIB_BTREE
#define PCLIB_BTREE

/*
 * pbtree.h
 *
 * A binary tree implementation
 */

#ifndef PBTREE_TYPE
#define PBTREE_TYPE int
#endif

typedef struct _pbtree {
	PBTREE_TYPE info;
	struct _pbtree *left, *right;
} pbtree;

#endif
