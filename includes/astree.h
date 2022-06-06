#ifndef ASTREE_H
#define ASTREE_H

typedef enum	e_NodeType
{
	NODE_PIPE	 		= (1 << 0),
	NODE_BACKGRND 		= (1 << 1),
	NODE_SEQ	 		= (1 << 2),
	NODE_REDIRECT_IN	= (1 << 3),
	NODE_REDIRECT_OUT   = (1 << 4),
	NODE_CMD_PATH		= (1 << 5),
	NODE_ARGUMENT	    = (1 << 6),
	NODE_DATA	 		= (1 << 7),
}	NodeType;

typedef struct s_ASTreeNode t_ASTreeNode;

typedef struct s_ASTreeNode
{
	int type;
	char *szData;
	t_ASTreeNode *left;
	t_ASTreeNode *right;
}	t_ASTreeNode;

#define NODETYPE(a) (a & (~NODE_DATA))	// get the type of the nodes

void ASTreeAttachBinaryBranch (t_ASTreeNode * root , t_ASTreeNode * leftNode , t_ASTreeNode * rightNode);
void ASTreeNodeSetType (t_ASTreeNode * node , NodeType nodetype );
void ASTreeNodeSetData (t_ASTreeNode * node , char * data );
void ASTreeNodeDelete (t_ASTreeNode * node );

#endif
