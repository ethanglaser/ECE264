// Modify this file at said locations
#include "decode.h"
#include "list.h"
#include "utility.h"


/*
------------------------------------------------------------------------------
You Can Modify below, Do Not modify above this
------------------------------------------------------------------------------
*/

#ifdef TEST_READHEADER

TreeNode * readHeader(FILE * infptr)
{
/* This function should have the following logic
	 * The first bit is a command bit and it is always 1.
	 * If a command is 1, then the next 8 bits(for this assignment) are the value stored
	 	 in a leaf node. Create a tree node to store this value. Add this tree node to the
		 beginning of the linked list (basically, LinkedList is acting like a stack here).
     This tree node is a single-node tree.  
	 * If a command is 0 and the list has two or more nodes, then take the first two nodes from
	 	 the list, create a tree node as the parent. Add this parent node to the linked list.
   * If a command is 0 and the list has only one node, then the complete tree has been built.
	 * After the tree is completely built, then read one more bit. If this is not the last
	 	 (rightmost) bit of the byte, discard the remaining bits in the byte.
	*/
	unsigned char command = 0;
	unsigned char bit = 0;
	int charval = 0;
	int loop = 0;
	int end = 0;
	unsigned char whichbit = 0;
	unsigned char curbyte = 0;
	char letter;
	ListNode * head = NULL;

	while(end == 0)
	{
	  readBit(infptr, &command, &whichbit, &curbyte);
	  charval = 0;

	  if(command)
	  {
	    for(loop = 0; loop < 8; loop++)
	    {
	      readBit(infptr, &bit, &whichbit, &curbyte);
	      charval = (2 * charval) + bit;
	    }
	    letter = (char) charval;
	    //need to malloc for next and treenode...
	    TreeNode * nextree = TreeNode_create(letter, 0);
	    ListNode * nextnode = ListNode_create(nextree);
	    head = List_insert(head, nextnode);
	  }
	  else
	  {
/*	    head -> tnptr -> right = head -> tnptr;
	    head -> tnptr -> left = head -> next -> tnptr;
	    head -> tnptr -> value = ' ';*/
	    if((head -> next == NULL))  //will not work if command is 0 for second byte
	    {
	      end = 1;
	    }
	    else
	    {
	      head = MergeListNode(head);
	    }
	  }
	}
	TreeNode * finaltree = head -> tnptr;
	free(head);
	return finaltree;
}

#endif


#ifdef TEST_DECODE

int decode(char * infile, char * outfile)
{
  // In this function, in addition to the last assignment, you will also decode the rest of the file.
  // After getting the Huffman tree and number of character from the header file as in last assignment,
  // we will decode the rest the file as explained in README and will print each character in the `outfile`.
  // Thus, this function have 3 prints into the outfile - printing Huffman tree using Tree_print function
  // (same as in last assignment), then printing number of characters using PrintNumberChar
  // function (same as in previous assignment using) and then printing each decoded character into
  // the outfile.
		// read the header from the input file  by calling readHeader function
	FILE * fptri = fopen(infile, "r");
	FILE * fptro = fopen(outfile, "w");
	TreeNode * finaltree = NULL;
	unsigned int finalnum = 0;
	fseek(fptri, 0, SEEK_SET);
	finaltree = readHeader(fptri);
	fread(&finalnum, sizeof(unsigned int), 1, fptri);
	// the generated tree from the header generated should be printed in outfile
	// to print the tree into the file use Tree_print function given to you.
  // After reading the header till codebook, read the next 4 bytes from the header,
  // these 4 bytes represent number of characters in the file.


  // Print the number of characters obtained by using the PrintNumberChar function
	Tree_print(finaltree, fptro);
	PrintNumberChar(finalnum, fptro);
	// Do not use your own print functions
	unsigned char enter = 0;
	fread(&enter, sizeof(unsigned char), 1, fptri);
	unsigned char whichbit = 0;
	unsigned char bit = 0;
	unsigned char curbyte = 0;
	TreeNode * location = finaltree;
	int end = 0;
	while(end < finalnum)
	{
	while(location -> value == 0)
	{
	  readBit(fptri, &bit, &whichbit, &curbyte);
	  if(bit)
	  {
//	    if(location -> right != NULL)
//	    {
	      location = location -> right;
//	    }
	  }
	  else
	  {
//	    if(location -> left != NULL)
//	    {
	      location = location -> left;
//	    }
	  }
	}
	fprintf(fptro, "%c", location -> value);
	location = finaltree;
	end ++;
	}
	// free up the memory

	Tree_destroy(finaltree);
	fclose(fptri);
	fclose(fptro);
	return 0;
}
#endif
