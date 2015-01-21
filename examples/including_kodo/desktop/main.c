// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <dummy/dummy.h>
#include <stdio.h>

int main()
{
    if (start() == 1)
    {
        printf("Data decoded correctly\n");
    }
    else
    {
        printf("Unexpected failure to decode, please file a bug report :)\n");
    }

    return 0;
}
