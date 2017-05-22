#ifndef STRUCTURES_H
#define STRUCTURES_H
#define FALSE 0
#define TRUE 1
#define MAX_FIELD_LENGTH 100
/*
 * Structure representing a cell on the field. For each cell, information
 * required are the cell id, the row number and the col number (for graphic),
 * the state (FALSE: covered, TRUE: uncovered) and the possible flag set
 * (flagged -> FALSE: not flagged, TRUE: flagged).
 * Value must be evaluated like:
 * < 0 : empy cell;
 * 0: bomb;
 * > 0: number in the cell;
 */
typedef struct Cell{
	int id;
	int state;
	int flagged;
	int value;
} cell;

/*
 * Actually, we don't need to define a struct for the field. The state of the
 * field is contained in each of its cells, so we just define a field as a
 * matrix of cells.
 */
typedef cell field[MAX_FIELD_LENGTH][MAX_FIELD_LENGTH];

/*
 * There are several ways to implement the turn management. The implementation
 * for this system is quite simple. For each turn made, a stack is filled up with
 * modifications on the field. The turn is so defined as a set of cells that changed
 * their state. For example, if an empty cell is hit then that turn will be represented
 * as a set of pushes on the array where each push is a cell id that changed its state.
 */
typedef struct Turn{
	int turn_number;
	int cell_id;
} turn;

/*
 * The node of the linked list which will be the data structure for the stack contains,
 * of course, information of type turn.
 */
typedef struct Node{
    turn info;
    struct node *ptr;
} node;

/*
 * A list is nothing but a pointer to the first element.
 */
typedef node* stack;


/*
 * Introdotta questa struttura con il seguente scopo: quando scopro una cella, voglio restituire
 * al chiamante (che sraà l'interfaccia grafica) un array di tutte le celle scoperte con i relativi
 * valori in modo da evitare una scansione completa del campo ad ogni turno.
 */
typedef struct Flip{
	int cell_id;
	int value;
} flip;
#endif