News for Kodo C bindings
========================

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* Minor: Added API to control systematic encoding. Systematic encoding means
  that all source symbols will be sent once un-coded before coding begins.

1.3.0
-----
* Minor: Bump dependency to Kodo version 12.x.y
* Minor: Improve on-the-fly encoding / decoding support

1.2.1
-----
* Bugfix: Allow compilation without using a makespec

1.2.0
-----
* Minor: Added support for on-the-fly encoding and a corresponding example.
* Bugfix: Setting c++11 compiler flag to -std=c++0x in the makefile/Makefile

1.1.0
-----
* Minor: Added the standalone archiver Waf tool. The tool makes it possible to
  create self contained archives of the Kodo C bindings i.e. it contains all
  needed dependencies.

1.0.0
-----
* Major: Initial version of the Kodo C bindings based on Kodo version 11.x.y.

