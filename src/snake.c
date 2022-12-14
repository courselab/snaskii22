#include "snake.h"
#include <stdlib.h>

body_t* create_body(int x, int y) {
	body_t* body = malloc(sizeof(body_t));
	body->sp.x_pos = x;
	body->sp.y_pos = y;
	body->sp.value = SNAKE_BODY;
	body->next = NULL;
	body->prev = NULL;
	return body;
}

void init_snake(snake_t* snake, int head_x, int head_y) {
	snake->direction = RIGHT;
	snake->length = 2;

	snake->head = create_body(head_x, head_y);
	snake->head->next = create_body(head_x - 1, head_y);

	snake->tail = snake->head->next;
	snake->tail->prev = snake->head;

	snake->prev_tail_x = snake->tail->sp.x_pos - 1;
	snake->prev_tail_y = snake->tail->sp.y_pos;
}

void grow_snake(snake_t* snake) {
	snake->tail->next = create_body(snake->prev_tail_x, snake->prev_tail_y);
	snake->tail->next->prev = snake->tail;
	snake->tail = snake->tail->next;
	snake->length++;
}

void push_front(snake_t* snake, body_t* aux) {
	aux->prev = NULL;
	aux->next = snake->head;

	snake->head->prev = aux;

	snake->head = aux;

	snake->length++;
}

body_t* pop_back(snake_t* snake) {
	body_t* ret = snake->tail;

	snake->tail = ret->prev;
	snake->length--;

	ret->prev->next = NULL;
	ret->next = NULL;
	ret->prev = NULL;
	return ret;
}

// TODO: Make snake velocity not FPS dependent
void move_snake(snake_t* snake) {
	body_t* aux = pop_back(snake);

	snake->prev_tail_x = aux->sp.x_pos;
	snake->prev_tail_y = aux->sp.y_pos;

	aux->sp.x_pos = snake->head->sp.x_pos;
	aux->sp.y_pos = snake->head->sp.y_pos;

	push_front(snake, aux);


#if 1
	switch(snake->direction) {
		case UP:
			snake->head->sp.y_pos -= 1;
			break;
		case DOWN:
			snake->head->sp.y_pos += 1;
			break;
		case LEFT:
			snake->head->sp.x_pos -= 1;
			break;
		case RIGHT:
			snake->head->sp.x_pos += 1;
			break;
	}
#endif
}

void draw_snake(snake_t* snake) {
	for(body_t* aux = snake->head; aux != NULL; aux = aux->next) {
		draw_sprite(&aux->sp);
	}
}
