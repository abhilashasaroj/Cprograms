// 1. Modify the singly linked list to be a doubly linked list. 
// 2. Now write a routine that removes all duplicate data in the doubly linked list. 
// 3. The data will be integers generated at random from [0,49]. 
// 4.Initially have a list of 200 elements.

// Code by Abhilasha Saroj on 5 December 2020.

//HINT USED: Sort the list by its data field. Remove adjacent elements of the sorted list with the same value. 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Create typedef struct - linked list with one memeber as data and other (pointer to list) next.
typedef struct list{ int data; struct list* ptr_to_next; struct list* ptr_to_prev;} list;


// 2. Function to check if the list is empty
int is_empty(const list* l) {return (l == NULL);}

list* head = NULL;
list* tail = NULL;
list *current = NULL;

// 3. Create a function to create list
void insert_to_double_linked_list(int d)
{
	list* newNode = malloc(sizeof(list));
	newNode->data =d;
	newNode->ptr_to_next = NULL;
	newNode->ptr_to_prev = NULL;

	// if head for the linked list has not been initiated then initiate it
	if (head == NULL)
	{
		head = newNode;
		return ;
	}

	// If a link already exists then traverse from head to end and insert the link to the end

	current = head;

	while (current->ptr_to_next!=NULL)
	{
		current = current->ptr_to_next;
	}	

	current->ptr_to_next = newNode;
	tail = newNode;
	newNode->ptr_to_prev = current;

}


// 4. Function to print list data
int print_linked_list_elements(list *h, char *title)
{
	int i = 1;
	printf("%s\n", title);
	while (h!=NULL)
	{
		if ((i%10)!=0)
		{
			printf("%d\t",h->data);
			h = h->ptr_to_next;
		}

		else 
		{
			printf("%d\t\n",h->data);
			h = h->ptr_to_next;
		}

		i++;
	}
	return 0;
}


// 5. Function to swap list elements 
int swap_linked_list_elements(list *a, list *b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
	return 0;
}


// 6. Bubble sort function with argument as pointer to list
list* bubblesort_list_elements(list *h)
{
	list *ptr_to_first_list;
	list *ptr_to_last_list = NULL;
	int flag_swap;

	do
	{
		flag_swap = 0;
		ptr_to_first_list = head;
		while (ptr_to_first_list->ptr_to_next !=ptr_to_last_list)
		{
			if(ptr_to_first_list->data > ptr_to_first_list->ptr_to_next ->data)
			{
				swap_linked_list_elements(ptr_to_first_list, ptr_to_first_list->ptr_to_next);
				flag_swap = 1;
			}
			ptr_to_first_list=ptr_to_first_list->ptr_to_next ;
		}

		ptr_to_last_list = ptr_to_first_list;
	} while (flag_swap);

	return h;
}

// 7. Function to traverse through the list and delete duplicate node and return pointer to head of the list
list* delete_list_if_duplicate(list *h)
{

	while (h->ptr_to_next!=NULL)
	{
		if (h->data == h->ptr_to_next->data)
		{
			if (h->ptr_to_prev == NULL) // delete if first list node
			{
				//printf("%s\n", "HEAD DELETE");
				list* temp;
				temp = h;
				h = h->ptr_to_next;
				h->ptr_to_prev = NULL;
				free (temp);
			}

			else if (h->ptr_to_next==NULL) //delete if last list node
			{
				//printf("%s\n", "TAIL DELETE");
				list* temp;
				temp = h;
				h=h->ptr_to_prev;
				h->ptr_to_next = NULL;
				free (temp);
			}

			else 
			{
				//printf("%d\n", h->data );
				list* temp;
				temp = h;
				h->ptr_to_next->ptr_to_prev = h->ptr_to_prev;
				h->ptr_to_prev->ptr_to_next=h->ptr_to_next;
				h = h->ptr_to_next;
				free (temp);
			}

		}

		else 
		{
			h = h->ptr_to_next;
		}
			
	}
	while (h->ptr_to_prev!=NULL){h=h->ptr_to_prev;}
	return h;
}


// 8. Main function 

int main()
{
	srand(time(NULL)); //Random initialization
	int p;
	
	for (int i=0; i<200; i++)
	{
		p = rand()%(50);
		//printf("%d\n", p);
		insert_to_double_linked_list(p); //add new data to new list and add that to the to original list that has pointer to list component h1
	}
	print_linked_list_elements(head, "Data in 200 element linked list"); //Print to check if above functions worked

	//Apply bubblesort function for linked list
	list *sorted;
	sorted = bubblesort_list_elements(head);
	print_linked_list_elements(sorted, "Sorted data in 200 element linked list"); //Print to check if the bubblesort worked
	
	list *dupDeleted;
	dupDeleted = delete_list_if_duplicate(sorted);
	print_linked_list_elements(dupDeleted, "Duplicates deleted data from the 200 element sorted linked list"); //Print to check if the bubblesort worked

}

//----end of program