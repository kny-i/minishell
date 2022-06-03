#ifndef ASTREE_H
#define ASTREE_H

typedef enum{
	NODE_PIPE	 		= (1 << 0),
	NODE_BACKGRND 		= (1 << 1),
	NODE_SEQ	 		= (1 << 2),
	NODE_REDIRECT_IN	= (1 << 3),
	NODE_REDIRECT_OUT   = (1 << 4),
	NODE_CMD_PATH		= (1 << 5),
	NODE_ARGUMENT	    = (1 << 6),
	NODE_DATA	 		= (1 <<7),
}; NodeType;

