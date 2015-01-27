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
This section will describe how to include the Kodo C bindings in an Android
application.
The guide has been made for Android Studio, running on Linux. However the
steps should be fairly universal.

First we need to configure and build kodo-c using the android NDK. Go to the
root of this repository and run the following command:

  python waf configure --options=cxx_mkspec=cxx_android_gxx48_armv7,android_sdk_dir={android-sdk},android_ndk_dir={android-ndk}

Where {android-sdk}, and {android-ndk} needs to be replaced by the path to the
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
machine, and the {class} with the name of the class, in the sample project
dummy_android, this would be ``com.steinwurf.dummy_android.MainActivity``.



We will assume that the platform you are using for building the
Android application is Linux, and the IDE .

Further more we use Android studio as the developement platform.


iOS
---
This section describes how to compile kodo-c for iOS, 
how to include kodo-c in another library for iOS, 
and how to include these in an app for iOS.
The part of the documentation assumes that the developer is using 
an updated version of Mac OS X with Xcode 6.0 or later.

First, configure and compile kodo-c for your desired architecture by executing the following commands from the root of this project::

  python waf configure --options=cxx_mkspec=cxx_ios70_apple_llvm60_{arch}
  python waf build
  python waf install --options=install_path={install_path},install_static_libs
  
Where ``{arch}`` is the desired architecture. Currently ``armv7``, ``armv7s``, ``arm64`` and ``i386`` is available, 
where ``i386`` is for the iOS simulator builds. 
``{install_path}`` denotes the path where libraries and includes will be installed. 
A prefix of ``/tmp/{arch}`` will install libraries and includes in ``/tmp/{arch}`` and ``/tmp/{arch}/include``, respectively.

NB: Include file installation not ready yet.

An automated bash script for configuring and building kodoc_static and dependencies is located in examples/including_kodo/ios/configure_and_build_all.sh. This script runs through the above step for the mentioned architectures.


Building multi arch static libraries
....................................

It may be desirable to build a multi architecture static library for iOS. 
In order to do this, the above configure, build, and install steps must be completed for each supported architecture.

After this, the static libraries can be combined to a "fat" multiarch static library using the ``lipo`` command::

  lipo -create /tmp/{arch1}/lib/libkodoc_static.a /tmp/{arch2}/lib/libkodoc_static.a -output libkodoc_static.a
  
The fat static lib is then located in the current directory.
Several input libraries can be included in the multi arch lib, e.g. all the above-mentioned architectures.
Multiarch libraries for the dependency libraries ``fifi`` and ``cpuid`` should also be created.
Architecture specific variants of these are installed alongside libkodoc_static.a in the specified prefix.

Building the dummy project static library
.........................................

A build script written in bash is located in examples/including_kodo/ios/build_ios.sh, and contains the commands necessary to build the dummy project into a static lib, and then use this to build a binary. It also contains the commands needed to build a multi arch static lib.
The build script assumes that all four supported architectures has been built and installed in path /tmp/{arch}/.


iOS demo project (Xcode)
........................

The folder examples/including_kodo/ios/kodoc-ios-demo contains an iOS demo example for including kodoc and libdummy in an iOS project/app.