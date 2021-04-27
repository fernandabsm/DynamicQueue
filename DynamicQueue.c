#include <stdio.h>
#include <stdlib.h>

#include "DynamicQueue.h"

void MEmpty_Queue(TQueue* Queue)
{
	Queue->front = (TCell*)malloc(sizeof(TCell));
	Queue->bottom = Queue->front;
	Queue->front->next = NULL;
	Queue->size = 0;
}

int Empty_Queue(TQueue Queue)
{
	return(Queue.size == 0);
}

void ToQueue(TItem Item, TQueue* Queue)
{
	Queue->bottom->next = (TCell*)malloc(sizeof(TCell));
	Queue->bottom = Queue->bottom->next;
	Queue->bottom->item = Item;
	Queue->bottom->next = NULL;
	Queue->size++;
}

void DeQueue(TQueue* Queue, TItem* Item)
{
	TCell* aux;
	if (!Empty_Queue(*Queue))
	{
		aux = Queue->front->next;
		Queue->front->next = aux->next;
		*Item = aux->item;
		free(aux);
		if (Queue->front->next == NULL)
		{
			Queue->bottom = Queue->front;
		}
		Queue->size--;
	}
}

void Print_Item(TItem Item)
{
	printf("Code: %d\n", Item.code);
}

void Print_Queue(TQueue* Queue)
{
	TItem Item;
	int N;
	N = Queue->size;
	while (N > 0)
	{
		DeQueue(Queue, &Item);
		Print_Item(Item);
		ToQueue(Item, Queue);
		N--;
	}
}

/* Questão 12 */
void Print_Queue_FIFO(TQueue* Queue)
{
	TQueue Aux_Queue;
	MEmpty_Queue(&Aux_Queue);
	TItem Item;
	while (!Empty_Queue(*Queue))
	{
		DeQueue(Queue, &Item);
		Print_Item(Item);
		ToQueue(Item, &Aux_Queue);
	}
	while (!Empty_Queue(Aux_Queue))
	{
		DeQueue(&Aux_Queue, &Item);
		ToQueue(Item, Queue);
	}
	Free_Queue(&Aux_Queue);
	
}

int Search_Item(TQueue* Queue, TItem Item)
{
	int result = 0;
	if (!Empty_Queue(*Queue))
	{
		TItem Aux_Item;
		TQueue Aux_Queue;
		MEmpty_Queue(&Aux_Queue);
		while (!Empty_Queue(*Queue))
		{
			DeQueue(Queue, &Aux_Item);
			if (Item.code == Aux_Item.code)
			{
				result = 1;
			}
			ToQueue(Aux_Item, &Aux_Queue);
		}
		while (!Empty_Queue(Aux_Queue))
		{
			DeQueue(&Aux_Queue, &Aux_Item);
			ToQueue(Aux_Item, Queue);
		}
		Free_Queue(&Aux_Queue);
		return result;
	}
	return 0;
}

void Free_Queue(TQueue* Queue)
{
	TItem Item;
	while (!Empty_Queue(*Queue))
	{
		DeQueue(Queue, &Item);
	}
	free(Queue->front);
}

/*Questão 13*/
int Same_Elements(TQueue* Queue1, TQueue* Queue2)
{
	if (!Empty_Queue(*Queue1) && !Empty_Queue(*Queue2))
	{
		if (Queue1->size == Queue2->size)
		{
			int count = 0, N = Queue2->size, size = Queue1->size;
			TQueue Aux_Queue1, Aux_Queue2, Aux_Queue3;
			MEmpty_Queue(&Aux_Queue1);
			MEmpty_Queue(&Aux_Queue2);
			MEmpty_Queue(&Aux_Queue3);
			TItem aux1, aux2;
			while (!Empty_Queue(*Queue1))
			{
				DeQueue(Queue1, &aux1);
				ToQueue(aux1, &Aux_Queue1);
				while (!Empty_Queue(*Queue2))
				{
					if (N == 0)
					{
						while (!Empty_Queue(Aux_Queue1))
						{
							DeQueue(&Aux_Queue1, &aux1);
							ToQueue(aux1, &Aux_Queue3);
						}
						while (!Empty_Queue(*Queue1))
						{
							DeQueue(Queue1, &aux1);
							ToQueue(aux1, &Aux_Queue3);
						}
						while (!Empty_Queue(Aux_Queue3))
						{
							DeQueue(&Aux_Queue3, &aux1);
							ToQueue(aux1, Queue1);
						}
						while (Aux_Queue2.size < size)
						{
							DeQueue(Queue2, &aux2);
							ToQueue(aux2, &Aux_Queue2);
						}
						if (!Empty_Queue(*Queue2))
						{
							/* Qualquer coisa ver isso */
							Free_Queue(Queue2);
							MEmpty_Queue(Queue2);
							while (!Empty_Queue(Aux_Queue2))
							{
								DeQueue(&Aux_Queue2, &aux2);
								ToQueue(aux2, Queue2);
							}
						}
						return 0;
					}
					DeQueue(Queue2, &aux2);
					if (aux1.code == aux2.code)
					{
						count++;
						if (Aux_Queue2.size < size)
							ToQueue(aux2, &Aux_Queue2);
						break;
					}
					else
					{
						ToQueue(aux2, Queue2);
						//ToQueue(aux2, &Aux_Queue2);
						N--;
					}
					if (Aux_Queue2.size < size)
						ToQueue(aux2, &Aux_Queue2);
				}
				N = Queue1->size;
			}
			
			while (!Empty_Queue(Aux_Queue1))
			{
				DeQueue(&Aux_Queue1, &aux1);
				ToQueue(aux1, Queue1);
			}
			Free_Queue(&Aux_Queue1);
			while (!Empty_Queue(Aux_Queue2))
			{
				DeQueue(&Aux_Queue2, &aux2);
				ToQueue(aux2, Queue2);
			}
			Free_Queue(&Aux_Queue2);
			if (count == Queue1->size)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

/* QUESTÃO 14 */
void Remove_Item(TQueue* Queue, int N)
{
	if (Queue->size < N)
	{
		printf("\n\t\t >>>>> MSG: Error! This queue don't have an nth item! <<<<< \n");
	}
	else
	{
		int count = 1;
		TQueue Aux_Queue;
		TItem Item;
		MEmpty_Queue(&Aux_Queue);
		while (!Empty_Queue(*Queue))
		{
			DeQueue(Queue, &Item);
			if (count != N)
			{
				ToQueue(Item, &Aux_Queue);
			}
			count++;
		}
		while (!Empty_Queue(Aux_Queue))
		{
			DeQueue(&Aux_Queue, &Item);
			ToQueue(Item, Queue);
		}
		Free_Queue(&Aux_Queue);
	}
}

/* Questão 15 */
void Intersection_Queue(TQueue* Queue1, TQueue* Queue2, TQueue* Queue3)
{
	int result;
	TItem Item;
	TQueue Aux_Queue;
	MEmpty_Queue(&Aux_Queue);
	while (!Empty_Queue(*Queue1))
	{
		DeQueue(Queue1, &Item);
		result = Search_Item(Queue2, Item);
		ToQueue(Item, &Aux_Queue);
		if (result == 1)
		{
			ToQueue(Item, Queue3);
		}
	}
	while (!Empty_Queue(Aux_Queue))
	{
		DeQueue(&Aux_Queue, &Item);
		ToQueue(Item, Queue1);
	}
	Free_Queue(&Aux_Queue);
}

/* Questão 16 */
void Diff_Queue(TQueue* Queue1, TQueue* Queue2, TQueue* Queue3)
{
	int result;
	TItem Item;
	TQueue Aux_Queue;
	MEmpty_Queue(&Aux_Queue);
	while (!Empty_Queue(*Queue1))
	{
		DeQueue(Queue1, &Item);
		result = Search_Item(Queue2, Item);
		ToQueue(Item, &Aux_Queue);
		if (result == 0)
		{
			ToQueue(Item, Queue3);
		}
	}
	while (!Empty_Queue(Aux_Queue))
	{
		DeQueue(&Aux_Queue, &Item);
		ToQueue(Item, Queue1);
	}
	Free_Queue(&Aux_Queue);
}