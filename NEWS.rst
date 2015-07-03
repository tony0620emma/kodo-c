News for kodo-c
===============

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* Major: Renamed `trace` and `trace_callback` to the appropriate names from the
  new kodo version.
* Major: Upgrade to kodo 27
* Minor: Added buildbot.py for coverage reports.
* Minor: Added ``kodo_has_write_payload`` to check if a coder provides the
  ``kodo_write_payload`` function.

4.0.0
-----
* Major: Upgrade to kodo 26
* Major: Renamed ``kodo_symbol_pivot`` to ``kodo_is_symbol_pivot`` to match the
  function name in Kodo.

3.1.0
-----
* Minor: Added the ``kodo_sparse_seed_rlnc`` code type that implements a sparse
  seed-based RLNC codec. The code density should be set on the encoder side.
  The maximum size of the coding header is 9 bytes.
* Minor: Moved the factory functions from ``kodoc.cpp`` to separate translation
  units in order to decrease the compilation time. The optimizer might use
  gigabytes of RAM when instantiating a lot of coder stack variants in a
  single cpp file. This problem is mitigated with this separation.
* Minor: Added a seed-based RLNC codec (``kodo_seed_rlnc``).

3.0.0
-----
* Minor: Added sparse RLNC encoder.
* Major: Upgrade to kodo 25
* Major: Upgrade to fifi 19
* Minor: Added simple throughput benchmark in ``benchmark/kodoc_throughput``
* Minor: Extended the C API with functions for reading and writing symbols
  directly on the decoder and encoder.
* Minor: Added a shallow full RLNC codec.
* Major: Upgrade to sak 14
* Minor: Re-enabled the build task for the kodo-c static library.

2.0.0
-----
* Major: Restructured the API according to the Hourglass pattern that was
  presented at CppCon 2014: https://www.youtube.com/watch?v=PVYdHDm0q6Y
  This pattern encapsulates the complexity of the underlying C++ libraries
  by hiding all implementation details behind a simple C89 API. It makes
  providing bindings from other languages easier, facilitates integration with
  other C++ projects and build systems, and insulates from ABI issues.
* Minor: Update to waf 1.8.0-pre1
* Minor: Made python files comply with pep8
* Major: Upgrade to kodo 21
* Major: Upgrade to fifi 15
* Major: Upgrade to sak 13
* Major: Added recycle dependency
* Patch: The kodo_is_symbol_decoded() function call was forwarded to the
  wrong kodo function.
* Major: Removed debug functions (Replaced by trace layers)
* Minor: Add trace layer functions
* Minor: Added the sliding window algorithm
* Minor: Added new examples:
    sliding_window,
    switch_systematic_on_off
    use_trace_layers
* Minor: Updated examples:
    encode_decode_simple
    encode_decode_on_the_fly
    udp_sender_receiver
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
* Patch: Allow compilation without using a makespec

1.2.0
-----
* Minor: Added support for on-the-fly encoding and a corresponding example.
* Patch: Setting c++11 compiler flag to -std=c++0x in the makefile/Makefile

1.1.0
-----
* Minor: Added the standalone archiver Waf tool. The tool makes it possible to
  create self contained archives of the Kodo C bindings i.e. it contains all
  needed dependencies.

1.0.0
-----
* Major: Initial version of the Kodo C bindings based on Kodo version 11.x.y.
