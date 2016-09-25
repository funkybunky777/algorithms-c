#include <stdlib.h>
#include "headers.h"


int list_ins_next(List *list, ListElmt *element, const void *data) {

    ListElmt *new_element;

    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;

    // Insert the element into the list
    new_element->data = (void *)data;

/*       
                                           +---------+------+
      new_element:                         | *data   | NULL |
                                           +---------+------+
                                                       next
*/

    if (element == NULL) {

	// Handle insertion somewhere at the head
	if (list_size(list) == 0)
	    list->tail = new_element;


	new_element->next = list->head;
	list->head = new_element;

    } else {

	// Handle insertion somewhere other than at the head
	if (element->next == NULL) {

/*               +---------+------+
       element:  |         | NULL |
                 +---------+------+
                             next
*/  
            list->tail = new_element;
/*                                                                    +---------+------+
                                                                      |         | NULL |
                                                                      +---------+------+
                                                                       new_element next
    
                 +---------+------+                                   +---------+------+
       list:     |         |   *  |----------------------------------->         |   *  |
                 +---------+------+                                   +---------+------+
                                                                                  
*/
    }


new_element->next = element->next;
/*
                                           +---------+------+
 element:                                  |         |   *  +---------------+
                                           +---------+------+               |
                                            new_element next                |
                                                                            |
                                                                            |
                 +---------+---+--+                                   +-----v---+------+
 list:           |         |   *  |----------------------------------->         |   *  |
                 +---------+------+                                   +---------+------+
                   element   next
*/
element->next = new_element;
/*
                                           +---------+------+
 element:                      +----------->         |   *  +---------------+
                               |           +---------+------+               |
                               |            new_element next                |
                               |                                            |
                               |                                            |
                 +---------+---+--+                                   +-----v---+------+
 list:           |         |   *  |                                   |         |   *  |
                 +---------+------+                                   +---------+------+
                   element   next
*/

    }

    /* Adjust the size of the list to account for the inserted element */
    list->size++;
    return 0;
}

