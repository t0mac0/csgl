#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rbtree.h"
#include "rbtree_build.h"
#include "rbtree_equal.h"
#include "rbtree_inline.h"

extern void rbtree_insert_balance(rbtree_t *tree, rbtree_iter_t node);
extern void rbtree_delete_balance(rbtree_t *tree, rbtree_iter_t node);


int rbtree_check_attach_detach() {
    printf("check attach child ...\n");
    printf("check attach child pass!\n");
    return 1;
}

int rbtree_insert_case1() {
    return 1;
}

int rbtree_check_delete_balance() {
    
    puts("check delete balance ...");
    /*
    rbtree_delete_balance(tree, insert_node[3]);
    rbtree_detach_child(insert_node[3]);

    rbtree_delete_balance(tree, node[4]);
    rbtree_detach_child(node[4]);

    assert(rbtree_is_red(node[3]));
    rbtree_delete_balance(tree, insert_node[2]);
    assert(rbtree_is_red(node[3]));
    rbtree_detach_child(insert_node[2]);
    assert(rbtree_is_red(node[3]));
    assert(rbtree_parent(node[3]) == insert_node[1]);
    assert(rbtree_is_black(node[1]));


    assert(rbtree_parent(node[0]) == node[1]);
    rbtree_delete_balance(tree, node[0]);
    rbtree_detach_child(node[0]);
    assert(rbtree_parent(node[1]) == insert_node[0]);
    assert(rbtree_parent(node[3]) == insert_node[1]);
    assert(rbtree_parent(insert_node[1]) == insert_node[0]);
    assert(rbtree_is_red(node[3]));
    assert(rbtree_get_index(node[3]) == 1);

    rbtree_delete_balance(tree, node[1]);
    rbtree_detach_child(node[1]);
    assert(rbtree_is_black(node[3]));
    assert(rbtree_parent(node[3]) == insert_node[1]);

    rbtree_delete_balance(tree, node[3]);
    rbtree_detach_child(node[3]);
    assert(rbtree_is_red(insert_node[0]));

    rbtree_delete_balance(tree, insert_node[1]);
    rbtree_detach_child(insert_node[1]);
    assert(tree->root == insert_node[0]);

    assert(rbtree_tail.size == 0);
    rbtree_delete_balance(tree, insert_node[0]);
    rbtree_detach_child(insert_node[0]);
    assert(tree->root == &rbtree_tail);
    */
    puts("check delete balance pass!");
    return 1;
}


int rbtree_check_internal() {
    const int len = 5;

    assert(rbtree_is_black(&rbtree_tail));
    rbtree_t *tree;
    rbtree_create(&tree, 0);
    rbtree_iter_t iter;
    rbtree_node_t *node[len];
    for (int i=0; i<len; ++i) {
        rbtree_node_create(&node[i]);
        node[i]->id = i;
        node[i]->key.i = i + 23;
    }

    printf("check set_child ...\n");
    rbtree_attach_child(node[1], 0, node[0]);
    rbtree_attach_child(node[1], 1, node[2]);
    rbtree_attach_child(node[3], 0, node[1]);
    rbtree_attach_child(node[3], 1, node[4]);
    printf("check set_child pass!\n");

    printf("check iter_head, iter_next ...\n");
    tree->root = node[3];
    rbtree_iter_head(tree, &iter);
    assert(iter == node[0]);
    rbtree_iter_next(tree, &iter);
    assert(iter == node[1]);
    rbtree_iter_next(tree, &iter);
    assert(iter == node[2]);
    rbtree_iter_next(tree, &iter);
    assert(iter == node[3]);
    rbtree_iter_next(tree, &iter);
    assert(iter == node[4]);
    printf("check iter_head, iter_next pass!\n");

    printf("check iter_tail, iter_prev ...\n");
    rbtree_iter_tail(tree, &iter);
    assert(iter == node[4]);
    rbtree_iter_prev(tree, &iter);
    assert(iter == node[3]);
    rbtree_iter_prev(tree, &iter);
    assert(iter == node[2]);
    rbtree_iter_prev(tree, &iter);
    assert(iter == node[1]);
    rbtree_iter_prev(tree, &iter);
    assert(iter == node[0]);
    printf("check iter_tail, iter_prev pass!\n");

    puts("check iter value ...");
    rbtree_iter_value(tree, (cdata_t)23, &iter);
    assert(iter == node[0]);
    rbtree_iter_value(tree, (cdata_t)24, &iter);
    assert(iter == node[1]);
    rbtree_iter_value(tree, (cdata_t)25, &iter);
    assert(iter == node[2]);
    rbtree_iter_value(tree, (cdata_t)26, &iter);
    assert(iter == node[3]);
    rbtree_iter_value(tree, (cdata_t)27, &iter);
    assert(iter == node[4]);
    puts("check iter value pass!");







    printf("check gparent parent uncle sibling ...\n");
    assert(rbtree_parent(node[0]) == node[1]);
    assert(rbtree_parent(node[2]) == node[1]);
    assert(rbtree_parent(node[1]) == node[3]);
    assert(rbtree_parent(node[4]) == node[3]);

    assert(rbtree_gparent(node[0]) == node[3]);
    assert(rbtree_gparent(node[2]) == node[3]);

    assert(rbtree_sibling(node[0]) == node[2]);
    assert(rbtree_sibling(node[2]) == node[0]);
    assert(rbtree_sibling(node[1]) == node[4]);
    assert(rbtree_sibling(node[4]) == node[1]);

    assert(rbtree_uncle(node[0]) == node[4]);
    assert(rbtree_uncle(node[2]) == node[4]);
    printf("check gparent parent uncle sibling pass!\n");

    rbtree_set_black(node[0]);
    rbtree_set_black(node[2]);
    rbtree_set_black(node[3]);

    puts("check rotate right ...");
    rbtree_attach_child(&rbtree_head, 0, node[3]);
    assert(rbtree_parent(node[3]) == &rbtree_head);
    rbtree_rotate_right(0, node[3]);
    assert(rbtree_parent(node[0]) == node[1]);
    assert(rbtree_parent(node[3]) == node[1]);
    assert(rbtree_parent(node[2]) == node[3]);
    assert(rbtree_parent(node[4]) == node[3]);

    assert(rbtree_gparent(node[2]) == node[1]);
    assert(rbtree_gparent(node[4]) == node[1]);

    assert(rbtree_sibling(node[2]) == node[4]);
    assert(rbtree_sibling(node[4]) == node[2]);
    assert(rbtree_sibling(node[0]) == node[3]);
    assert(rbtree_sibling(node[3]) == node[0]);

    assert(rbtree_uncle(node[2]) == node[0]);
    assert(rbtree_uncle(node[4]) == node[0]);
    puts("check rotate right pass!");

    puts("check rotate left ...");
    assert(rbtree_parent(node[1]) == &rbtree_head);
    rbtree_rotate_left(0, node[1]);

    assert(rbtree_parent(node[0]) == node[1]);
    assert(rbtree_parent(node[2]) == node[1]);
    assert(rbtree_parent(node[1]) == node[3]);
    assert(rbtree_parent(node[4]) == node[3]);

    assert(rbtree_gparent(node[0]) == node[3]);
    assert(rbtree_gparent(node[2]) == node[3]);

    assert(rbtree_sibling(node[0]) == node[2]);
    assert(rbtree_sibling(node[2]) == node[0]);
    assert(rbtree_sibling(node[1]) == node[4]);
    assert(rbtree_sibling(node[4]) == node[1]);

    assert(rbtree_uncle(node[0]) == node[4]);
    assert(rbtree_uncle(node[2]) == node[4]);
    puts("check rotate left pass!");

    printf("check borrow ...\n");
    rbtree_rotate_borrow(&rbtree_head, node[3], node[4], node[1]);
    assert(rbtree_parent(node[1]) == &rbtree_head);
    assert(rbtree_parent(node[0]) == node[1]);
    assert(rbtree_parent(node[3]) == node[1]);
    assert(rbtree_parent(node[2]) == node[3]);
    assert(rbtree_parent(node[4]) == node[3]);

    assert(rbtree_gparent(node[2]) == node[1]);
    assert(rbtree_gparent(node[4]) == node[1]);

    assert(rbtree_sibling(node[2]) == node[4]);
    assert(rbtree_sibling(node[4]) == node[2]);
    assert(rbtree_sibling(node[0]) == node[3]);
    assert(rbtree_sibling(node[3]) == node[0]);

    assert(rbtree_uncle(node[2]) == node[0]);
    assert(rbtree_uncle(node[4]) == node[0]);

    rbtree_rotate_borrow(&rbtree_head, node[1], node[0], node[3]);
    assert(rbtree_parent(node[3]) == &rbtree_head);
    assert(rbtree_parent(node[0]) == node[1]);
    assert(rbtree_parent(node[2]) == node[1]);
    assert(rbtree_parent(node[1]) == node[3]);
    assert(rbtree_parent(node[4]) == node[3]);

    assert(rbtree_gparent(node[0]) == node[3]);
    assert(rbtree_gparent(node[2]) == node[3]);

    assert(rbtree_sibling(node[0]) == node[2]);
    assert(rbtree_sibling(node[2]) == node[0]);
    assert(rbtree_sibling(node[1]) == node[4]);
    assert(rbtree_sibling(node[4]) == node[1]);

    assert(rbtree_uncle(node[0]) == node[4]);
    assert(rbtree_uncle(node[2]) == node[4]);
    printf("check borrow pass!\n");

    printf("check return ...\n");
    rbtree_rotate_return(&rbtree_head, node[3], node[1], node[4]); 
    assert(rbtree_parent(node[1]) == &rbtree_head);
    assert(rbtree_parent(node[0]) == node[1]);
    assert(rbtree_parent(node[3]) == node[1]);
    assert(rbtree_parent(node[2]) == node[3]);
    assert(rbtree_parent(node[4]) == node[3]);

    assert(rbtree_gparent(node[2]) == node[1]);
    assert(rbtree_gparent(node[4]) == node[1]);

    assert(rbtree_sibling(node[2]) == node[4]);
    assert(rbtree_sibling(node[4]) == node[2]);
    assert(rbtree_sibling(node[0]) == node[3]);
    assert(rbtree_sibling(node[3]) == node[0]);

    assert(rbtree_uncle(node[2]) == node[0]);
    assert(rbtree_uncle(node[4]) == node[0]);

    printf("check return pass!\n");

    printf("check insert balance ...\n");
    rbtree_set_black(node[0]);
    rbtree_set_black(node[1]);
    rbtree_set_black(node[3]);
    rbtree_set_red(node[2]);
    rbtree_set_red(node[4]);

    tree->root = node[1];
    const int insert_len = 5;
    rbtree_node_t *insert_node[insert_len];
    for (int i=0; i<insert_len; ++i) {
        rbtree_node_create(&insert_node[i]);
        rbtree_set_black(insert_node[i]);
        insert_node[i]->id = len + i;
    }

    rbtree_attach_child(node[2], 0, insert_node[0]);
    rbtree_insert_balance(tree, insert_node[0]);

    assert(rbtree_parent(insert_node[0]) == node[2]);
    assert(rbtree_is_red(insert_node[0]));
    assert(rbtree_is_black(node[2]));
    assert(rbtree_is_black(node[4]));
    assert(rbtree_is_red(node[3]));

    rbtree_attach_child(insert_node[0], 1, insert_node[1]);
    rbtree_insert_balance(tree, insert_node[1]);
    assert(rbtree_parent(insert_node[1]) == node[3]);
    assert(rbtree_parent(insert_node[0]) == insert_node[1]);
    assert(rbtree_parent(node[2]) == insert_node[1]);
    assert(rbtree_is_red(node[2]));
    assert(rbtree_is_red(insert_node[0]));
    assert(rbtree_is_black(insert_node[1]));

    rbtree_attach_child(node[4], 1, insert_node[2]);
    rbtree_insert_balance(tree, insert_node[2]);
    rbtree_attach_child(insert_node[2], 1, insert_node[3]);
    rbtree_insert_balance(tree, insert_node[3]);
    assert(rbtree_parent(insert_node[3]) == insert_node[2]);
    assert(rbtree_parent(node[4]) == insert_node[2]);
    assert(rbtree_is_red(node[4]));
    assert(rbtree_is_red(insert_node[3]));
    assert(rbtree_is_black(insert_node[2]));
    puts("check insert balance pass!");


    assert(rbtree_is_red(node[3]));
    
    rbtree_create(&tree, 0);
    rbtree_elem_insert(tree, 0, 123);
    rbtree_elem_insert(tree, 5, 128);
    assert(tree->root->val.i == 123);
    assert(tree->root->child[1]->val.i == 128);
    rbtree_elem_insert(tree, 2, 125);
    assert(tree->root->val.i == 125);

    rbtree_elem_insert(tree, 1, 124);
    assert(tree->root->child[0]->child[1]->val.i == 124);
    rbtree_elem_insert(tree, 3, 126);
    assert(tree->root->child[1]->child[0]->val.i == 126);
    rbtree_elem_insert(tree, 4, 127);
    assert(tree->root->child[1]->val.i == 127);

    puts("check elem delete ....!");
    cdata_t val;
    rbtree_elem_remove(tree, 0, &val); 
    assert(val.i == 123);
    assert(tree->root->child[0]->val.i == 124);
    rbtree_elem_remove(tree, 4, &val);
    printf("val :%d\n", val.i);
    assert(val.i == 127);
    assert(tree->root->child[1]->val.i == 128); 
    assert(tree->root->child[1]->child[1] == &rbtree_tail);
    rbtree_elem_remove(tree, 2, &val);
    assert(val.i == 125);
    assert(tree->root->val.i == 126);
    rbtree_elem_remove(tree, 3, &val);
    assert(val.i == 126);
    rbtree_elem_remove(tree, 1, &val);
    assert(val.i == 124);
    rbtree_elem_remove(tree, 5, &val);
    assert(val.i == 128);
    puts("check elem delete pass!");



    rbtree_delete(&tree);

    assert(rbtree_is_black(&rbtree_tail));
    return 1;
}

int verify_rbtree_build() {
    puts("verify rbtree_build ...");
    puts("verify rbtree_build case1:");
    rbtree_t *tree;
    rbtree_build("nil", &tree);
    assert(tree->root == &rbtree_tail);
    rbtree_delete(&tree);
    puts("verify rbtree_build case1 pass!");

    puts("verify rbtree_build case2:");
    rbtree_build("{(1, 23), [nil, nil]}", &tree);
    assert(tree->root != &rbtree_tail);
    assert(rbtree_is_black(tree->root));
    assert(tree->root->id == 23);
    assert(tree->root->child[0] == &rbtree_tail);
    assert(tree->root->child[1] == &rbtree_tail);
    rbtree_delete(&tree);
    puts("verify rbtree_build case2 pass!");

    puts("verify rbtree_build case3:");
    rbtree_build("{(1, 1), [{(1, 0), [nil, nil]}, {(1, 3),[{(0,2), [nil, nil]}, {(0, 4), [nil, nil]}]}]}", &tree);
    assert(tree->root != &rbtree_tail);
    assert(rbtree_is_black(tree->root));
    assert(rbtree_is_black(tree->root->child[0]));
    assert(rbtree_is_black(tree->root->child[1]));
    assert(rbtree_is_red(tree->root->child[1]->child[0]));
    assert(rbtree_is_red(tree->root->child[1]->child[1]));

    assert(tree->root->id == 1);
    assert(tree->root->child[0]->id == 0);
    assert(tree->root->child[1]->id == 3);
    assert(tree->root->child[1]->child[0]->id == 2);
    assert(tree->root->child[1]->child[1]->id == 4);

    assert(rbtree_parent(tree->root->child[0]) == tree->root);
    assert(rbtree_parent(tree->root->child[1]) == tree->root);
    assert(rbtree_parent(tree->root->child[1]->child[0]) == tree->root->child[1]);
    assert(rbtree_parent(tree->root->child[1]->child[1]) == tree->root->child[1]);

    assert(rbtree_sibling(tree->root->child[0]) == tree->root->child[1]);
    assert(rbtree_sibling(tree->root->child[1]) == tree->root->child[0]);
    assert(rbtree_sibling(tree->root->child[1]->child[0]) == tree->root->child[1]->child[1]);
    assert(rbtree_sibling(tree->root->child[1]->child[1]) == tree->root->child[1]->child[0]);

    assert(rbtree_uncle(tree->root->child[1]->child[0]) == tree->root->child[0]);
    assert(rbtree_uncle(tree->root->child[1]->child[1]) == tree->root->child[0]);

    rbtree_delete(&tree);
    puts("verify rbtree_build case3 pass!");


    puts("verify rbtree_build pass!");
    return 1;
}

int verify_rbtree_equal() {
    puts("verify rbtree_equal ....!");
    rbtree_t *tree_a;
    rbtree_build("{(1, 1), [{(1, 0), [nil, nil]}, {(1, 3),[{(0,2), [nil, nil]}, {(0, 4), [nil, nil]}]}]}", &tree_a);

    rbtree_t *tree_b;
    rbtree_build("{(1, 1), [{(1, 0), [nil, nil]}, {(1, 3),[{(0,2), [nil, nil]}, {(0, 4), [nil, nil]}]}]}", &tree_b);
    assert(rbtree_equal(tree_a, tree_b));

    rbtree_t *tree_c;
    rbtree_build("{(1, 1), [{(1, 0), [nil, nil]}, {(1, 3),[{(0,2), [nil, nil]}, nil ]}]}", &tree_b);
    assert(!rbtree_equal(tree_a, tree_c));
    assert(!rbtree_equal(tree_b, tree_c));

    puts("verify rbtree_equal pass!");
    return 1;
}




int main(int argc, char * argv[] ) {

    assert(verify_rbtree_build());
    assert(verify_rbtree_equal());

    rbtree_iter_t iter;
    iter = calloc(1, sizeof(struct rbtree_node));


    assert(rbtree_check_internal());
    return 0;
}
