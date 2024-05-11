#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap * nuevoMap = (TreeMap *)malloc(sizeof(TreeMap));
    if (nuevoMap == NULL) return NULL;

    nuevoMap->root = NULL;
    nuevoMap->current = NULL;
    nuevoMap->lower_than = lower_than;
    return nuevoMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode * nuevoMap = createTreeNode(key, value);
    if (tree->root == NULL)
    {
        tree->root = nuevoMap;
        tree->current = nuevoMap;
        return;
    }

    TreeNode * parent = NULL;
    TreeNode * raiz = tree->root;
    while(raiz != NULL)
    {
        parent = raiz;
        if (is_equal(tree, key, raiz->pair->key)) return;
        if (tree->lower_than(key, raiz->pair->key) == 1) raiz = raiz->left;   
        else raiz = raiz->right;
    }
    nuevoMap->parent = parent;
    if (tree->lower_than(key, parent->pair->key) == 1) parent->left = nuevoMap;
    else parent->right = nuevoMap;
    tree->current = nuevoMap;
}

TreeNode * minimum(TreeNode * x)
{
    while(x->left != NULL) x = x->left;
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    TreeNode * raiz = tree->root;
    while(raiz != NULL)
    {
        if (is_equal(tree, key, raiz->pair->key) == 1)
        {
            tree->current = raiz;
            return raiz->pair;
        }
        if (tree->lower_than(key, raiz->pair->key) == 1) raiz = raiz->left;
        else raiz = raiz->right;
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
    TreeNode * raiz = tree->root;
    TreeNode * upperB = NULL;
    while(raiz != NULL)
    {
        if (is_equal(tree, key, raiz->pair->key) == 1)
        {
            tree->current = raiz;
            raiz = raiz->right;
        }
        else raiz = raiz->left;   
    }
    if (upperB != NULL)
    {
        tree->current = upperB;
        return upperB->pair;
    }
    else return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode * min = minimum(tree->root);
    tree->current = min;
    return min->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
