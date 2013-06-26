About
=====

This repository C bindings for the Kodo Network Coding library.

Build
=====

To configure the examples run:
::
  ./waf configure --bundle=ALL --bundle-path=~/dev/bundled_dependencies/

This will configure the project and download all the dependencies needed.

The ``--bundle-path`` option specifies where to download the
dependencies (the kodo library + others). If you do not specify a ``--bundle-path``
the default will be within a folder within the project directory called
``bundle_dependencies``.

The ``--bundle`` says which dependencies should be downloaded automatically. If
you do not want to use e.g. the kodo library from the repository you may write
``--bundle=ALL,-kodo`` and then specify the path to the kodo library you wish to
use by writing ``--kodo-path=/home/xyz/kodo-lib``.

After configure run the following command to build:
::
  ./waf build




