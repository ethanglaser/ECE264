/*
Modify the file at the said location
*/
#include "list.h"
#include <stdlib.h>

#ifdef DO_NOT_MODIFY
ListNode * ListNode_create(TreeNode * tn)
{
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> next = NULL;
  ln -> tnptr = tn;
  return ln;
}
// head may be NULL
// ln must not be NULL
// ln -> next must be NULL
ListNode * List_insert(ListNode * head, ListNode * ln)
{
  if (ln == NULL)
    {
      printf("ERROR! ln is NULL\n");
      return NULL;
    }
  if ((ln -> next) != NULL)
    {
      printf("ERROR! ln -> next is not NULL\n");
    }
  if (head == NULL)
    {
      return ln;
    }
    ln -> next = head;
    return ln;
}


#endif


/*
------------------------------------------------------------------------------
You Can Modify below, Do Not modify above this
------------------------------------------------------------------------------
*/


#ifdef TEST_MERGELIST

ListNode * MergeListNode(ListNode * head)
{
  /*
  This function is same as you did in HW20
  */
	ListNode * merge1 = head;
	ListNode * merge2 = head -> next;
	TreeNode * tree1 = merge1 -> tnptr;
	TreeNode * tree2 = merge2 -> tnptr;
	TreeNode * newtree = Tree_merge(tree2, tree1);
	ListNode * newnode = ListNode_create(newtree);
	head = List_insert(head -> next -> next, newnode);
	free(merge1);
	free(merge2);


	return head;
}
#endif
