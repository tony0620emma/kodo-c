News for Kodo C Bindings
========================

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* Minor: Update to waf 1.8.0-pre1
* Minor: Made python files comply with pep8
* Major: Bump dependency to Fifi version 10.x.y
* Major: Bump dependency to Gauge version 7.x.y
* Bug: When calling the kodo_is_symbol_decoded(kodo_coder_t*,uint32_t) function
  the call was forward to the wrong C++ Kodo function.
* Major: Bump dependency to Kodo version 15.x.y
* Major: Bump dependency to Kodo version 16.x.y
* Major: Removed debug functions (Replaced by trace layers)
* Minor: Add trace layer functions
* Minor: Added algorithm Sliding window
* Minor: Added examples for: Sliding window, Switch systematic on and of
  and use trace layers
* Minor: Updated examples for: encode decode on the fly, encode decode simpel
  and udp sender and receiver
* Minor: Implemented method kodo_read_feedback
* Minor: Implemented method kodo_write_feedback



1.7.0
-----
* Minor: Bump dependency to Kodo version 14.x.y

1.6.0
-----
* Minor: Bump dependency to Kodo version 13.x.y

1.5.0
-----
* Minor: Added API for creating debug stacks and printing debug information.

1.4.0
-----
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
