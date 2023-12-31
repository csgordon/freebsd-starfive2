/*	$OpenBSD: rb-test.c,v 1.4 2008/04/13 00:22:17 djm Exp $	*/
/*
 * Copyright 2002 Niels Provos <provos@citi.umich.edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <sys/types.h>

#define _RB_DIAGNOSTIC 1
#include <sys/tree.h>
#include <stdlib.h>

#include <atf-c.h>

struct node {
	RB_ENTRY(node) node;
	int key;
};

static RB_HEAD(tree, node) root;

static int
compare(struct node *a, struct node *b)
{
	if (a->key < b->key) return (-1);
	else if (a->key > b->key) return (1);
	return (0);
}

RB_PROTOTYPE(tree, node, node, compare);

RB_GENERATE(tree, node, node, compare);

#define ITER 150

ATF_TC_WITHOUT_HEAD(rb_test);
ATF_TC_BODY(rb_test, tc)
{
	struct node *tmp, *ins, store[ITER];
	int i, j, k, max, min;

	min = ITER;
	max = -1;

	RB_INIT(&root);

	/* Initialize keys */
	for (i = 0; i < ITER; i++)
		store[i].key = i;

	/* Randomly shuffle keys */
	for (i = 0; i < ITER; i++) {
		j = i + arc4random_uniform(ITER - i);
		k = store[j].key;
		store[j].key = store[i].key;
		store[i].key = k;
	}

	for (i = 0; i < ITER; i++) {
		for (j = 0; j < i; ++j) {
			tmp = &store[j];
			ATF_REQUIRE_EQ(tmp, RB_FIND(tree, &root, tmp));
		}
		tmp = &store[i];
		if (tmp->key > max)
			max = tmp->key;
		if (tmp->key < min)
			min = tmp->key;
		ATF_REQUIRE_EQ(NULL, RB_INSERT(tree, &root, tmp));
		ins = RB_MIN(tree, &root);
		ATF_REQUIRE_MSG(ins != NULL, "RB_MIN error");
		ATF_CHECK_EQ(min, ins->key);
		ins = RB_MAX(tree, &root);
		ATF_REQUIRE_MSG(ins != NULL, "RB_MAX error");
		ATF_CHECK_EQ(max, ins->key);
	}
	tmp = RB_ROOT(&root);
	ATF_REQUIRE_MSG(tree_RB_RANK(tmp) >= 0, "RB rank balance error");
	for (i = 0; i < ITER; i++) {
		tmp = RB_ROOT(&root);
		ATF_REQUIRE_MSG(tmp != NULL, "RB_ROOT error");
		ATF_CHECK_EQ(tmp, RB_REMOVE(tree, &root, tmp));
	}
}

ATF_TP_ADD_TCS(tp)
{

	ATF_TP_ADD_TC(tp, rb_test);

	return (atf_no_error());
}
