#ifndef FILESYSTEM_H
# define FILESYSTEM_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_FSNode
{
    char             *name;
    int              size;
    struct s_FSNode  *childrens;
    struct s_FSNode  *parent;
    struct s_FSNode  *next;
}   FSNode;


FSNode *create_file(const char *name, int size);
FSNode *create_folder(const char *name);
void add_child(FSNode *parent, FSNode *child);
FSNode *get_children(const FSNode *parent);
FSNode *get_sibling(const FSNode *node);
int compute_total_size(const FSNode *node);
void print_structure(const FSNode *node, int indent);
void free_filesystem(FSNode *node);

#endif