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
on various desktop platforms.

Common for all platforms is that you need to build the kodo-c bindings.
By using the Steinwurf build system, dependencies and compiler configuration is
handled automatically.

Simply go to the root of this repository and execute the following command::

  python waf configure

This will attempt to download the kodo-c dependencies and find the needed
build tools on your machine.

If successful you can now try to build kodo-c::

  python waf build

And finally, if the build succeeded, you should be able to install the following
command::

  python waf install --options=install_path="./static_libs",install_static_libs

This will build and install kodoc and all it's dependencies. As shown in the
previous code example, we've used the ``./static_libs`` directory.


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
root of this repository and run the following command::

  python waf configure --options=cxx_mkspec=cxx_android_gxx48_armv7,android_sdk_dir={android-sdk},android_ndk_dir={android-ndk}

Where {android-sdk}, and {android-ndk} needs to be replaced by the path to the
Android SDK and a standalone version of the Android NDK, respectively.

First, create a new project using the Android Studio wizard.

Now add the path to the android NDK to local.properties

Right click in the Project panel and go into the menu New -> Folder -> JNI Folder

This will create a folder called C in the project panel
(note: the actual name of this folder in the file system is jni).

Change directory to the newly generated directory and use javah to generate the
jni headers, using the following command::

    javah -cp {android-sdk}/platforms/android-16/android.jar:../java {class}

Please exchange {android-sdk} with the path to the android sdk on your
machine, and the {class} with the name of the class, in the sample project
dummy_android, this would be ``com.steinwurf.dummy_android.MainActivity``.

