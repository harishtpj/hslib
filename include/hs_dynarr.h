/*
 * Dynamic Array implementation
 * Written by M.V.Harish Kumar on 17-01-2026
 */
#ifndef HS_DYNARR_H
#define HS_DYNARR_H

#include <stdio.h>
#include <stdlib.h>

#define HS_DYNARR_TYPES(X) \
	X(int, Int, "%d") \
	X(float, Float, "%f") \
	X(double, Double, "%lf") \
	X(char, Char, "%c")

#define HS_PROTO_GEN(T, N, F) \
	typedef struct { \
		T *at; \
		size_t length; \
		size_t cap; \
	} HS##N##Array; \
	HS##N##Array* hs_new##N##Array(); \
	void hs_arrayPush##N(HS##N##Array *a, T val); \
	void hs_print##N##Array(HS##N##Array *a); \
	void hs_free##N##Array(HS##N##Array *a);

HS_DYNARR_TYPES(HS_PROTO_GEN)

#define hs_newArray(T) _Generic((T){0}, \
	HS_DYNARR_TYPES(HS_SELECT_NEW) \
	default: NULL \
)()

#define hs_arrayPush(a, val) _Generic((val), \
	HS_DYNARR_TYPES(HS_SELECT_PUSH) \
	default: NULL \
)(a, val)

#define hs_printArray(a) _Generic((a), \
	HS_DYNARR_TYPES(HS_SELECT_PRINT) \
	default: NULL \
)(a)

#define hs_freeArray(a) _Generic((a), \
	HS_DYNARR_TYPES(HS_SELECT_FREE) \
	default: NULL \
)(a)

#define HS_SELECT_NEW(T, N, F) T: hs_new##N##Array,
#define HS_SELECT_PUSH(T, N, F) T: hs_arrayPush##N,
#define HS_SELECT_PRINT(T, N, F) HS##N##Array*: hs_print##N##Array,
#define HS_SELECT_FREE(T, N, F) HS##N##Array*: hs_free##N##Array,

#endif

#ifdef HS_IMPL

#define HS_DYNARR_IMPL_GEN(T, N, F) \
	HS##N##Array* hs_new##N##Array() { \
		HS##N##Array *a = malloc(sizeof(HS##N##Array)); \
		if (!a) return NULL; \
		a->at = malloc(8 * sizeof(T)); \
		if (!a->at) { free(a); return NULL; } \
		a->length = 0; \
		a->cap = 8; \
		return a; \
	} \
	void hs_arrayPush##N(HS##N##Array *a, T val) { \
		if (!a || !a->at) return; \
		if (a->length >= a->cap) { \
			size_t newCap = a->cap * 2; \
			T *tmp = realloc(a->at, newCap * sizeof(T)); \
			if (tmp) { \
				a->at = tmp; \
				a->cap = newCap; \
			} else return; \
		} \
		a->at[a->length++] = val; \
	} \
	void hs_print##N##Array(HS##N##Array *a) { \
		if (!a) return; \
		putchar('[');\
		for (size_t i = 0; i < a->length; i++) { \
			printf(F, a->at[i]); \
			if (i < a->length - 1) putchar(' '); \
		} \
		puts("]"); \
	} \
	void hs_free##N##Array(HS##N##Array *a) { \
		if (!a) return; \
		free(a->at); \
		free(a); \
	}

HS_DYNARR_TYPES(HS_DYNARR_IMPL_GEN)

#endif
