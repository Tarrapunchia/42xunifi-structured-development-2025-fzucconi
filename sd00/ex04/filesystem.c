#include "filesystem.h"
#include <stdlib.h>

FSNode *create_file(const char *name, int size)
{
    FSNode *new_file;
    new_file = (FSNode *)malloc(sizeof(FSNode));
    if (!new_file) { return (NULL); }
    new_file->name = strdup(name);
    new_file->size = size;
    new_file->childrens = NULL;
    new_file->parent = NULL;
    new_file->next = NULL;
    return new_file;
}

// Quando creo una folder, di base la setto come parent di se stessa, cosi
// se si ritrova ad essere cartella origine di tt il filesystem posso comunque
// utilizzare tutte le funzioni (get_sibiling, soprattutto)
FSNode *create_folder(const char *name)
{
    FSNode *new_folder;
    new_folder = (FSNode *)malloc(sizeof(FSNode));
    if (!new_folder) { return (NULL); }
    new_folder->name = strdup(name);
    new_folder->size = 0;
    new_folder->childrens = NULL;
    new_folder->parent = new_folder;
    new_folder->next = NULL;
    return new_folder;
}

void add_child(FSNode *parent, FSNode *child)
{
    if (!parent || !child || parent->size != 0)
        return;
    child->parent = parent;
    if (parent->childrens == NULL)
    {
        parent->childrens = child;
        return ;
    }

    FSNode *buf = parent->childrens;

    while (buf->next != NULL)
    {
        buf = buf->next;
    }
    buf->next = child;
}

FSNode *get_children(const FSNode *parent)
{
    return parent->childrens;
}

FSNode *get_sibling(const FSNode *node)
{
    return node->parent->childrens;
}

// TO TEST COMPILE WITH gcc -W -W -W -D TEST
#ifdef TEST

int main()
{
    FSNode *root = create_folder("root");
    FSNode *root_f1 = create_file("root/child.file1", 10);
    FSNode *root_fld = create_folder("root/folder");
    FSNode *root_fld_f2 = create_file("root/folder/child2.file2", 10);
    add_child(root, root_f1);
    add_child(root, root_fld);
    add_child(root_fld, root_fld_f2);
    free(root->name);
    free(root);
    free(root_f1->name);
    free(root_f1);
    free(root_fld->name);
    free(root_fld);
    free(root_fld_f2->name);
    free(root_fld_f2);
}

#endif // TEST
