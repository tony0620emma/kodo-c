Including Kodo Example
======================

This example shows how to include and use the Kodo C bindings in a library.
Further it is shown how to use this library in applications on the
following platforms:

* Desktop (Linux, Mac OSX and Windows)
* Android
* iOS.

The Dummy Library
-----------------

The dummy library is a simple library in which use the Kodo C API. The
library implements a single function which runs a simple encoding/decoding
example and returns whether the test was successful or not.

Desktop
-------

This section we will explain how to use kodo-c for your desktop application.
The desktop example application is a simple console application which uses
the dummy library to determine which string to print, either
``Data decoded correctly`` or ``Data decoding failed``.

In the following subsections, it will be explained how to build the application
on various platforms.

Common for all platforms is that you need to build the kodo-c bindings.
By using the Steinwurf build system, dependencies and compiler configuration is
handled automatically.

Simply go to the root of this repository and execute the following command::

    python waf configure

This will attempt to download the kodo-c dependencies and find the necessary
build tools on your machine.

If successful, you can now try to build kodo-c::

    python waf build

If the build succeeded, you can install the kodo-c static libraries with the
following command::

    python waf install --options=install_path="./static_libs",install_static_libs

This command also installs the static libraries from the kodo-c dependencies.
You can link with these static libraries using your own build system. The
following script demonstrates the necessary steps and settings for the gcc/g++
compiler (other compilers require similar settings)::

    cd examples/including_kodo
    sh compile_dummy_example.sh

In many cases, it can be easier to include the kodo-c *shared* library in
your application. With the following command, you can copy the compiled
*.so, *.dylib or *.dll file (the extension depends on your platform)
to the folder specified with the ``install_path`` option::

    python waf install --options=install_path="./shared_libs",install_shared_libs

If you dynamically link your application with this shared library, then you
have to copy the shared library to a folder where your system can find it.

Android
-------

This section describes how to include the Kodo C bindings in an Android
application.
The guide has been made for Android Studio, running on Linux. However the
steps should be fairly universal.

First we need to configure and build kodo-c using the android NDK. Go to the
root of the kodo-c repository and run the following command:

  python waf configure --options=cxx_mkspec=cxx_android_gxx48_armv7,android_sdk_dir={android-sdk},android_ndk_dir={android-ndk}

Where {android-sdk}, and {android-ndk} should be replaced with the path to the
Android SDK and a standalone version of the Android NDK, respectively.

First, create a new project using the Android Studio wizard.

Now add the path to the android NDK to local.properties

Right click in the Project panel and go into the menu New -> Folder -> JNI Folder

This will create a folder called C in the project panel
(note: the actual name of this folder in the file system is jni).

Change directory to the newly generated directory and use javah to generate the
jni headers, using the following command:

    javah -cp {android-sdk}/platforms/android-16/android.jar:../java {class}

Please exchange {android-sdk} with the path to the android sdk on your
machine, and the {class} with the name of the class. In the ``dummy_android``
sample project, this would be ``com.steinwurf.dummy_android.MainActivity``.


iOS
---

This section describes how to compile kodo-c for iOS,
how to include kodo-c in another library for iOS,
and how to include these in an app for iOS.
We assume that the developer is using a recent version of Mac OS X with Xcode 6.0 or later.

First, configure and compile kodo-c for your desired architecture by
executing the following commands from the root of the kodo-c repository::

  python waf configure --options=cxx_mkspec=cxx_ios70_apple_llvm60_{arch}
  python waf build
  python waf install --options=install_path=/tmp/{arch},install_static_libs

Where ``{arch}`` is the desired architecture. Currently ``armv7``, ``armv7s``,
``arm64``, ``i386``, and ```x86_64`` are available, where the latter two are
for the iOS simulator builds.
The ``install_path`` option determines where the static libraries will be
installed. Here, we install the static libraries to ``/tmp/{arch}``. This
means 5 different folder for the 5 supported architectures.

To run the above steps for the mentioned architectures, execute the following
bash script::

    cd examples/including_kodo/ios
    sh configure_and_build_all.sh

Building multi-arch static libraries
....................................

It may be desirable to build a multi-architecture static library for iOS.
In order to do this, the above configure, build, and install steps must be
completed for each supported architecture.

After this, the static libraries can be combined to a "fat" multiarch static
library using the ``lipo`` command::

  lipo -create /tmp/{arch1}/lib/libkodoc_static.a /tmp/{arch2}/lib/libkodoc_static.a -output libkodoc_static.a

The fat static lib is then located in the current directory. Several input
libraries can be included in the multi arch lib, e.g. all the above-mentioned
architectures. Multi-arch libraries for the ``fifi`` and ``cpuid`` dependencies
should also be created. Architecture-specific variants of these are installed
alongside libkodoc_static.a in the specified ``install_path``.

To create the fat static libs for the mentioned architectures, execute the
following script (after you have executed ``configure_and_build_all.sh``)::

    cd examples/including_kodo/ios
    sh build_ios_fat_libs.sh

iOS demo project (Xcode)
........................

The ``examples/including_kodo/ios/kodoc-ios-demo`` contains an iOS demo
project for including kodo-c in an iOS application. This project will work
fine after you execute the ``configure_and_build_all.sh`` and
``build_ios_fat_libs.sh`` scripts mentioned above.

If you want to include kodo-c in your own Xcode project, then please set
the library and include path options as follows:

- Specify the library path and dependencies in "Link Binary with Libraries"
  under "Build Phases" in the project navigator
- Specify the include path in "Header Search Paths" under "Search Paths",
  in the "Build Settings"