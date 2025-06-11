#include "filesystem.h"


int compute_total_size(const FSNode *node)
{
    FSNode *buf = get_sibling(node);
    int size = 0;

    while (buf)
    {
        if (buf->size == 0)
            size += compute_total_size(buf);
        else
            size += buf->size;
    }

    return size;
}

void print_indent(const char *name, int indent)
{
    for (int i = 0; i < indent; i++)
        printf("\t");
    printf("%s\n", name);
}

void print_structure(const FSNode *node, int indent)
{
    if (!node)
        return ;
    
    print_indent(node->name, indent);
    
    if (node->size != 0)
        return ;

    FSNode *buf = get_children(node);
    while (buf)
    {
        print_structure(buf, indent + 1);
        buf = buf->next;
    }
}

void free_filesystem(FSNode *node)
{
    FSNode *top = node;
    FSNode *children = NULL;
    static int flag = 0;

    if (flag == 0)
    {
        while (top->parent && top != top->parent)
            top = top->parent;
        free(top->name);
        free(top);
        flag = 1;
    }
    children = get_children(top);
    while (children)
    {
        free_filesystem(children);
        free(children->name);
        top = children->next;
        free(children);
        children = top;
    }
}

// TO TEST COMPILE WITH gcc -W -W -W -D TEST
#ifdef TEST

int main()
{
    FSNode *root = create_folder("root");
    FSNode *root_f1 = create_file("root/child.file1", 10);
    FSNode *root_fld = create_folder("root/folder");
    FSNode *root_fld2 = create_folder("root/folder2");
    FSNode *root_fld_f2 = create_file("root/folder/child2.file2", 10);
    add_child(root, root_f1);
    add_child(root, root_fld);
    add_child(root_fld, root_fld_f2);
    add_child(root, root_fld2);
    print_structure(root, 1);
    free_filesystem(root_fld_f2);
}

#endif // TEST