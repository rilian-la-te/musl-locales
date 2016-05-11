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
#include "categories.h"
#include <stdlib.h>
#include <string.h>

struct cat_item lc_time_cats [] =
{
    {ABDAY_1,"abday",CAT_TYPE_STRINGARRAY,ABDAY_1,ABDAY_7},
    {DAY_1,"day",CAT_TYPE_STRINGARRAY,DAY_1,DAY_7},
    {ABMON_1,"abmon",CAT_TYPE_STRINGARRAY,ABMON_1,ABMON_12},
    {MON_1,"mon",CAT_TYPE_STRINGARRAY,MON_1,MON_12},
    {AM_STR,"am_pm", CAT_TYPE_STRINGARRAY,AM_STR,PM_STR},
    {D_T_FMT,"d_t_fmt", CAT_TYPE_STRING,0,0},
    {D_FMT,"d_fmt", CAT_TYPE_STRING,0,0},
    {T_FMT,"t_fmt", CAT_TYPE_STRING,0,0},
    {ERA,"era", CAT_TYPE_STRING,0,0},
    {ERA_D_FMT,"era_d_fmt", CAT_TYPE_STRING,0,0},
    {ALT_DIGITS,"alt_digits", CAT_TYPE_STRING,0,0},
    {ERA_D_T_FMT,"era_d_t_fmt", CAT_TYPE_STRING,0,0},
    {ERA_T_FMT,"era_t_fmt", CAT_TYPE_STRING,0,0},
    {0,"", CAT_TYPE_END,0,0}
};

struct cat_item lc_ctype_cats [] =
{
    {CODESET, "charmap", CAT_TYPE_STRING,0,0},
    {0,"", CAT_TYPE_END,0,0}
};

struct cat_item lc_messages_cats [] =
{
    {YESEXPR, "yesexpr",CAT_TYPE_STRING,0,0},
    {NOEXPR, "noexpr",CAT_TYPE_STRING,0,0},
#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
    {YESSTR, "yesstr",CAT_TYPE_STRING,0,0},
    {NOSTR, "nostr",CAT_TYPE_STRING,0,0},
#endif
    {0,"", CAT_TYPE_END,0,0}
};

struct cat_item lc_numeric_cats [] =
{
    {RADIXCHAR, "decimal_point",CAT_TYPE_STRING,0,0},
    {THOUSEP, "thousands_sep",CAT_TYPE_STRING,0,0},
    {0,"", CAT_TYPE_END,0,0}
};

struct cat_item lc_monetary_cats [] =
{
    {CRNCYSTR, "crncystr",CAT_TYPE_STRING,0,0},
    {0,"", CAT_TYPE_END,0,0}
};

struct cat_item lc_collate_cats [] =
{
    {0,"", CAT_TYPE_END,0,0}
};

struct cat_item* cats[] =
{
    lc_ctype_cats,
    lc_numeric_cats,
    lc_time_cats,
    lc_collate_cats,
    lc_monetary_cats,
    lc_messages_cats
};

const struct cat_item get_cat_item_for_name(const char *name)
{
    struct cat_item invalid = {0,"", CAT_TYPE_END,0,0};
    for(int i = 0; i < LC_ALL; i++)
    {
        for(int j = 0; cats[i][j].type != CAT_TYPE_END; j++)
        {
            if(!strcmp(name,cats[i][j].name))
                return cats[i][j];
        }
    }
    return invalid;
}

const char* get_cat_name_for_item_name(const char *name)
{
    for(int i = 0; i < LC_ALL; i++)
    {
        for(int j = 0; cats[i][j].type != CAT_TYPE_END; j++)
        {
            if(!strcmp(name,cats[i][j].name))
                return get_name_for_cat(i);
        }
    }
    return "";
}

const struct cat_item* get_cat_for_locale_cat(int locale_cat)
{
    return cats[locale_cat];
}

int get_cat_num_for_name(const char* cat_name)
{
    if (!strcmp(cat_name,"LC_CTYPE"))
        return LC_CTYPE;
    if (!strcmp(cat_name,"LC_NUMERIC"))
        return LC_NUMERIC;
    if (!strcmp(cat_name,"LC_TIME"))
        return LC_TIME;
    if (!strcmp(cat_name,"LC_COLLATE"))
        return LC_COLLATE;
    if (!strcmp(cat_name,"LC_MONETARY"))
        return LC_MONETARY;
    if (!strcmp(cat_name,"LC_MESSAGES"))
        return LC_MESSAGES;
    return LC_INVAL;
}

const char *get_name_for_cat(int cat_no)
{
    if (cat_no == LC_CTYPE)
        return "LC_CTYPE";
    if (cat_no == LC_NUMERIC)
        return "LC_NUMERIC";
    if (cat_no == LC_TIME)
        return "LC_TIME";
    if (cat_no == LC_COLLATE)
        return "LC_COLLATE";
    if (cat_no == LC_MONETARY)
        return "LC_MONETARY";
    if (cat_no == LC_MESSAGES)
        return "LC_MESSAGES";
    return "";
}
