# This is a red-black-tree implementation with clear interface and careful optimization.  
1.  use parent pointer to store pointer, index and color.
2.  use head and tail node to simplify the implementation.
3.  add size field to get a log(N) algorithm to find n-th element.

# Data Structure  
```c
typedef struct rbtree rbtree_t;  
typedef struct rbtree_node* rbtree_iter_t;  
typedef int (*rbtree_cmp_func)(const cdata_t, const cdata_t);  
```
# Interface  
```c
extern int rbtree_create(rbtree_t **tree, rbtree_cmp_func cmp);  
extern int rbtree_delete(rbtree_t **tree);  

extern int rbtree_elem_insert(rbtree_t *tree, const cdata_t key, const cdata_t val);  
extern int rbtree_elem_update(rbtree_t *tree, const cdata_t key, const cdata_t val);  

extern int rbtree_elem_delete(rbtree_t *tree, const cdata_t idx, cdata_t *val);  
extern int rbtree_elem_remove(rbtree_t *tree, const cdata_t key, cdata_t *val);  

extern int rbtree_iter_index(const rbtree_t *tree, const cdata_t key, rbtree_iter_t *iter);  
extern int rbtree_iter_value(const rbtree_t *tree, const cdata_t val, rbtree_iter_t *iter);  

extern int rbtree_iter_head(const rbtree_t *tree, rbtree_iter_t *iter);  
extern int rbtree_iter_tail(const rbtree_t *tree, rbtree_iter_t *iter);  
extern int rbtree_iter_prev(const rbtree_t *tree, rbtree_iter_t *iter);  
extern int rbtree_iter_next(const rbtree_t *tree, rbtree_iter_t *iter);  
extern int rbtree_iter_discard(rbtree_t *tree, rbtree_iter_t iter);  
```
# Benchmark  
```c
this is the benchmark of insert 1,000,000 elements, and delete 1,000,000 elements.
CPU: Intel(R) Xeon(R) CPU E5-2430 0 @ 2.20GHz
CPU cores : 1 (on virtual machine)
time.h clocks per sec: 1000000

optimize flag : default
2000000 ops, time used: 2750000 clocks = 2.75 s
727272.73 ops per second
2000000 ops time used: 2840000 clocks = 2.84 s
704225.35 ops per second
2000000 ops time used: 2980000 clocks = 2.98 s
671140.94 ops per second
2000000 ops time used: 2870000 clocks = 2.87 s
696864.11 ops per second
2000000 ops time used: 2830000 clocks = 2.83 s
706713.78 ops per second


optimize flag : -O3
2000000 ops time used: 2170000 clocks = 2.17 s
921658.99 ops per second
2000000 ops time used: 2220000 clocks = 2.22 s
900900.90 ops per second
2000000 ops time used: 2190000 clocks = 2.19 s
913242.01 ops per second
2000000 ops time used: 2240000 clocks = 2.24 s
892857.14 ops per second
2000000 ops time used: 2240000 clocks = 2.24 s
892857.14 ops per second
```


