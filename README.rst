About
=====

This repository C high-level bindings for the Kodo Network Coding library.
The bindings provide access to basic functionality provided by Kodo,
such as encoding and decoding of data. The examples folder provides sample
applications showing usage of the C API.

Build
=====

To build the C bindings for Kodo you can follow the steps described in the
`Kodo manual`_, there you will find a thorough descriptions of the build steps
in the getting started section. Only difference is that you should clone the
``kodo-c-bindings`` git repository.

.. _Kodo manual: https://kodo.readthedocs.org/en/latest/

Below we outline the steps needed:

To configure the examples run:
::
  python waf configure --bundle=ALL

This will configure the project and download all the dependencies needed.

After configure run the following command to build the static library:
::
  python waf build

This will produce a static library in the ``build`` folder called ``libkodo.a``.
The following section will show you how to link with the library in your
application.

Linking with an application
===========================
Include ``ckodo.h`` in your application and link with ``libckodo``.
Here is a typical gcc link command:

::

  gcc myapp.c -o myapp -Ipath_to_ckodo_h -Wl,-Bstatic -Lpath_to_libkodo_a -lckodo -Wl,-Bdynamic -lstdc++

Substitute the ``path_to_ckodo_h`` with the path of ``ckodo.h`` similarly
Substitute the ``path_to_libkodo_a`` with the path of the ``libkodo.a``
library.






