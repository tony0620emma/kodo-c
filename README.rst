About
=====

This repository C bindings for the Kodo Network Coding library.

Build
=====

To build the C bindings for Kodo you can follow the steps described in the
Kodo manual, there you will find a thorough descriptions of the build steps.

Below we outline the steps needed:

To configure the examples run:
::
  python waf configure --bundle=ALL

This will configure the project and download all the dependencies needed.

After configure run the following command to build the static library:
::
  python waf build

This will produce a static library in the ``build`` folder create by waf.






