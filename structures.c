#ifndef STRUCTURES_C
#define STRUCTURES_C
#define FALSE 0
#define TRUE 1
/*
 * Structure representing a cell on the field. For each cell, information
 * required are the cell id, the row number and the col number (for graphic),
 * the state (FALSE: covered, TRUE: uncovered) and the possible flag set
 * (flagged -> FALSE: not flagged, TRUE: flagged) 
 */
struct cell{
	int id;
	int position-x;
	int position-y;
	int state;
	int flagged;
}

/*
 * Actually, we don't need to define a struct for the field. The state of the
 * field is contained in each of its cells, so we just define a field as a
 * matrix of cells.
 */
typedef cell[][] field;

/*
 * There are several ways to implement the turn management. The implementation
 * for this system is quite simple. For each turn made, a stack is filled up with
 * modifications on the field. The turn is so defined as a set of cells that changed
 * their state. For example, if an empty cell is hit then that turn will be represented
 * as a set of pushes on the array where each push is a cell id that changed its state.
 */
struct turn{
	int turn_number;
	int cell_id;
}

/*
 * The node of the linked list which will be the data structure for the stack contains,
 * of course, information of type turn.
 */
struct node{
    turn info;
    struct node *ptr;
}

/*
 * A list is nothing but a pointer to the first element.
 */
typedef *node list;
#endif