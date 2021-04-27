#include <stdio.h>
#include <stdlib.h>

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

typedef struct Item
{
	int code;
}TItem;

typedef struct Cell
{
	TItem item;
	struct Cell* next;
}TCell;

typedef struct Queue
{
	TCell* front;
	TCell* bottom;
	int size;
}TQueue;

void MEmpty_Queue(TQueue* Queue);

int Empty_Queue(TQueue Queue);

void ToQueue(TItem Item, TQueue* Queue);

void DeQueue(TQueue* Queue, TItem* Item);

void Print_Item(TItem Item);

void Print_Queue(TQueue* Queue);

void Print_Queue_FIFO(TQueue* Queue);

int Search_Item(TQueue* Queue, TItem Item);

void Free_Queue(TQueue* Queue);

int Same_Elements(TQueue* Queue1, TQueue* Queue2);

void Remove_Item(TQueue* Queue, int N);

void Intersection_Queue(TQueue* Queue1, TQueue* Queue2, TQueue* Queue3);

void Diff_Queue(TQueue* Queue1, TQueue* Queue2, TQueue* Queue3);

#endif // !DYNAMIC_QUEUE_H

