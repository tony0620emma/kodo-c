Including Kodo Example
======================

This example shows how to include and use the kodo c bindings in a library.
Further it is shown how to use this library in applications running on the
following platforms:

* Desktop (Linux, MacOS and Windows)
* Android, and
* iOS.

The Dummy Library
-----------------

The dummy library is a simple library in which we are going to use kodo-c. The
library implements a single function which will run a encoding/decoding example,
and return whether the run was scuccesful or not.

Desktop
-------
In this section we will explain how to use kodo-c for your desktop application.
The desktop example application is a simple console application which uses
the dummy library to determine which string to print, either
``Data decoded correctly`` or ``Data decoding failed``.

In the following subsections, it will be explained how to build the application
on various platforms.

Common for all platforms is that you need to build the kodo-c bindings.
By using the Steinwurf build system, dependencies and compiler configuration is
handled automatically.

Simply go to the root of this repository and execute the following command:

  python waf configure

This will attempt to download the kodo-c and find the needed build tools on your
machine.

If successful you can now try to build kodo-c:

  python waf build

And finally, if the build succeeded, you should be able to install the following
command:

  python waf install --options=install_path="./static_libs",install_static_libs

This

Linux
.....


MacOS
.....

Windows
.......


Android
-------
In this step we will assume that the platform you are using for building the
Android application is Linux.

