/*
  MIT License
  
  Copyright (c) 2026 dahni
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef DARRAY_H
#define DARRAY_H

typedef struct {
	void **data;
	size_t capacity;
	size_t length;
} darray;

darray darray_init();
void *darray_at(darray *self, size_t i);
void darray_push(darray *self, void *item);
void darray_pop(darray *self);
void darray_delete(darray *self, size_t i);
void darray_destroy(darray *self);

#endif
#ifdef DARRAY_IMPLEMENTATION

darray darray_init() {
	darray self;
	self.capacity = 10;
	self.length = 0;
	self.data = calloc(self.capacity, sizeof(void *));

	return self;
}

void *darray_at(darray *self, size_t i) {
	if (i < self->length) {
		return self->data[i];
	}
	return NULL;
}


void darray_push(darray *self, void *item) {
	if (self->length >= self->capacity) {
		self->capacity += 2;
		void *tmp = realloc(self->data, self->capacity * sizeof(void *));
		if (!tmp) return;
		self->data = tmp;
	}
	self->data[self->length] = item;
	self->length++;
}

void darray_pop(darray *self) {
	if (self->length > 0) {
		self->length--;
	}
}

void darray_delete(darray *self, size_t i) {
	if (i >= self->length) return;
	memmove(
		self->data + i,
		self->data + i + 1,
		(self->length - i - 1) * sizeof(void *)
	);
	self->length--;
}

void darray_destroy(darray *self) {
	free(self->data);
	self->data = NULL;
	self->length = 0;
	self->capacity = 0;
}

#endif
