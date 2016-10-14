/*
 * Tests for Public API
 * This test, unlikely the others, is linked against the real, distributed,
 * shared library. Its sole purpose is to test for symbol availability.
 */

#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c-rbtree.h"

static void test_api(void) {
        CRBTree t = {};
        CRBNode n = C_RBNODE_INIT(n);

        assert(!c_rbnode_is_linked(&n));

        /* init, is_linked, add, remove, remove_init */

        c_rbtree_add(&t, NULL, &t.root, &n);
        assert(c_rbnode_is_linked(&n));

        c_rbtree_remove_init(&t, &n);
        assert(!c_rbnode_is_linked(&n));

        c_rbtree_add(&t, NULL, &t.root, &n);
        assert(c_rbnode_is_linked(&n));

        c_rbtree_remove(&t, &n);
        assert(c_rbnode_is_linked(&n)); /* @n wasn't touched */

        c_rbnode_init(&n);
        assert(!c_rbnode_is_linked(&n));

        /* first, last, leftmost, rightmost, next, prev */

        assert(!c_rbtree_first(&t));
        assert(!c_rbtree_last(&t));
        assert(&n == c_rbnode_leftmost(&n));
        assert(&n == c_rbnode_rightmost(&n));
        assert(!c_rbnode_next(&n));
        assert(!c_rbnode_prev(&n));

        /* postorder traversal */

        assert(!c_rbtree_first_postorder(&t));
        assert(!c_rbtree_last_postorder(&t));
        assert(&n == c_rbnode_leftdeepest(&n));
        assert(&n == c_rbnode_rightdeepest(&n));
        assert(!c_rbnode_next_postorder(&n));
        assert(!c_rbnode_prev_postorder(&n));
}

int main(int argc, char **argv) {
        test_api();
        return 0;
}
