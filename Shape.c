#include <stdlib.h>

/* Shape */

struct ShapeVtbl;

typedef struct {
  struct ShapeVtbl *vptr;
} /* abstract */ Shape;

typedef struct ShapeVtbl {
  /* abstract */ int (*area)(Shape *);
} ShapeVtbl;

void Shape_init(Shape *self) {
}

int Shape_area(Shape *self) {
  return (*self->vptr->area)(self);
}

/* Rect */

typedef struct {
  Shape base;
  int width;
  int height;
} Rect;

int Rect_area(Shape *base) {
  Rect *self = (Rect *) base;

  return self->width * self->height;
}

ShapeVtbl Rect_vtbl = {
  .area = Rect_area,
};

void Rect_init(Rect *self) {
  Shape *base = (Shape *) self;
  Shape_init(base);
  base->vptr = &Rect_vtbl;
}

/* Square */

typedef struct {
  Shape base;
  int length;
} Square;

int Square_area(Shape *base) {
  Square *self = (Square *) base;
  return self->length * self->length;
}

ShapeVtbl Square_vtbl = {
  .area = Square_area,
};

void Square_init(Square *self) {
  Shape *base = (Shape *) self;
  Shape_init(base);
  base->vptr = &Square_vtbl;
}

/* Main */

#include <stdio.h>

int main() {
  Rect rect = {.width = 15, .height = 20};
  Rect_init(&rect);

  Square square = {.length = 5};
  Square_init(&square);

  Shape *a = (Shape *) &rect;
  Shape *b = (Shape *) &square;

  printf("%d\n", Shape_area(a));
  printf("%d\n", Shape_area(b));
}
