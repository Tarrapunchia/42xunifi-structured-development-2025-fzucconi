#ifndef FILESYSTEM_H
# define FILESYSTEM_H
# include <string.h>
# include <stdlib.h>

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

#endif