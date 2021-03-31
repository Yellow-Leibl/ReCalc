#include "tort.h"

int keycmp(const char * arg, const char * key)
{
    int rc = 0;
    if (arg && key)
        if (*arg == '-' || *arg == '/')
            if (!strcasecmp(arg+1, key))
                rc = 1;
    return rc;
}

int isHelp(const char * s)
{
    return keycmp(s, "h") + keycmp(s, "help") + keycmp(s, "?");
}