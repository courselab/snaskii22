#include "snake.h"
#include <stdlib.h>

body_t* create_body(int x, int y,int is_head) {
	body_t* body = malloc(sizeof(body_t));
	body->sp.x_pos = x;
	body->sp.y_pos = y;
	body->sp.value = is_head==1?SNAKE_HEAD_RIGHT:SNAKE_BODY;
	body->next = NULL;
	body->prev = NULL;
	return body;
}

void init_snake(snake_t* snake, int head_x, int head_y) {
	snake->direction = RIGHT;
	snake->length = 2;
	snake->alive = true;

	snake->head = create_body(head_x, head_y, 1);
	snake->head->next = create_body(head_x - 1, head_y, 0);

	snake->tail = snake->head->next;
	snake->tail->prev = snake->head;

	snake->prev_tail_x = snake->tail->sp.x_pos - 1;
	snake->prev_tail_y = snake->tail->sp.y_pos;
}

void grow_snake(snake_t* snake) {
	snake->tail->next = create_body(snake->prev_tail_x, snake->prev_tail_y, 0);
	snake->tail->next->prev = snake->tail;
	snake->tail = snake->tail->next;
	snake->length++;
}


char update_snake_head_icon(snake_t* snake) {
	snake->head->sp.value = SNAKE_BODY;
	switch(snake->direction) {
		case UP:
			return SNAKE_HEAD_UP;
			break;
		case DOWN:
			return SNAKE_HEAD_DOWN;
			break;
		case LEFT:
			return SNAKE_HEAD_LEFT;
			break;
		case RIGHT:
			return SNAKE_HEAD_RIGHT;
			break;
	}
	return '0';
}

void push_front(snake_t* snake, body_t* aux) {
	aux->prev = NULL;
	aux->next = snake->head;
	aux->sp.value = update_snake_head_icon(snake);

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


bool is_inside(body_t *aux) {
    return aux->sp.x_pos > 0 && aux->sp.x_pos < SCREEN_COLUMNS - 1 &&
           aux->sp.y_pos > 0 && aux->sp.y_pos < SCREEN_ROWS - 1;
}


// TODO: Make snake velocity not FPS dependent
void move_snake(snake_t* snake) {
	body_t* aux = pop_back(snake);

	snake->prev_tail_x = aux->sp.x_pos;
	snake->prev_tail_y = aux->sp.y_pos;

	aux->sp.x_pos = snake->head->sp.x_pos;
	aux->sp.y_pos = snake->head->sp.y_pos;

	push_front(snake, aux);

	if (!is_inside(aux)) {
		snake->alive = false;
	}


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
