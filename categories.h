/*
 *
 * Copyright (c) 2016  Konstantin Pugin
 * Konstantin Pugin (ria.freelander@gmail.com)
 *
 * Licensed under the LGPL v3.
 *
 * A 'locale' command implementation for musl.
 *
 */
#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <locale.h>
#include <langinfo.h>

#define CAT_TYPE_STRING 0
#define CAT_TYPE_STRINGARRAY 1
#define CAT_TYPE_STRINGLIST 2
#define CAT_TYPE_BYTE 3
#define CAT_TYPE_BYTEARRAY 4
#define CAT_TYPE_WORD 4
#define CAT_TYPE_WORDARRAY 5
#define CAT_TYPE_END 6

#define LC_INVAL -1

typedef int cat_type;

struct cat_item
{
    nl_item id;
    const char* name;
    cat_type type;
    int min;
    int max;
};
const struct cat_item get_cat_item_for_name(const char* name);
const struct cat_item* get_cat_for_locale_cat(int locale_cat);
int get_cat_num_for_name(const char *cat_name);
const char* get_name_for_cat(int cat_no);
const char* get_cat_name_for_item_name(const char *name);
#endif // CATEGORIES_H
