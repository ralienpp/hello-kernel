Overview
========

This is a basic kernel module that implements the following basics:

- entry point for loading and unloading the kernel module
- debug statements that can be observed with ``dmesg``
- optionally transmitting a parameter, ``magic``, when the module is loaded (otherwise a default value is used)
- creation of a character device, ``/dev/oracle`` (mknod must be invoked manually for now)
- implements the ``read`` API, which takes the current value of ``magic`` and copies it from the kernel to the user-space buffer
- reacts to any ``ioctl`` sent to the module by incrementing ``magic``


Instructions
============

This was tested on Debian 7 x64.

Prerequisites
-------------

This only needs to be done once, to prepare the compilation environment.

- ``sudo apt-get install build-essentials``
- ``sudo apt-get install linux-headers-$(uname -r)`` or ``sudo apt-get install raspberrypi-kernel-headers`` if you have a RaspberryPi (untested)

Compilation
-----------

Get into the directory where you cloned the git repo and run ``make``. The output will be stored in ``hellok.ko``.

#. ``git clone https://github.com/ralienpp/hello-kernel.git``
#. ``cd hello-kernel``
#. ``make``


Basic test
----------

You can make sure this loads and unloads correctly as follows:

#. ``sudo insmod ./hellok.ko``
#. run ``lsmod`` and it should be in the list of loaded modules, e.g. ::

	Module                  Size  Used by
	hellok                 12452  0

#. unload it with ``sudo rmmod hellok``
#. run ``dmesg`` to see what has just happened, the debug lines should be there::

	[73964.820487] hellok: module license 'unspecified' taints kernel.
	[73964.820492] Disabling lock debugging due to kernel taint
	[74342.727012] Loaded hellok
	[74469.278069] Unloaded hellok

Notes on parameters
~~~~~~~~~~~~~~~~~~~

- You can pass a parameter at load time, e.g. ``sudo insmod ./hellok.ko magic=12``. If not specified, a default value will be used.
- The value can be examined after the module is loaded: ``cat /sys/module/hellok/parameters/magic``
- You can write to it (if permissions allow so), e.g. (as root) ``echo 45 > /sys/module/hellok/parameters/magic``


Character-device operations
~~~~~~~~~~~~~~~~~~~~~~~~~~~

To check if the devices was created successfully, run ``cat /proc/devices`` and expect something like this::

	Character devices:
	100 Oracle

The number is the ``MAJOR`` defined in the code, and the name is the string we used to name the device.

Before you can interact with this device, run ``sudo mknod -m 666 /dev/oracle c 100 0`` (create a character device, allowing everyone to do everything with it, 100 is ``MAJOR`` as defined in the code, and 0 is the minor [taken "as is" from a guide]).

User-mode tool
==============

To demonstrate communication between kernel-space and user-space, you can run ``cat /dev/oracle`` and the value of ``magic`` will be shown on the screen as a string.

This happens by copying this value from a buffer in the kernel's address space, into a buffer in user-space, using ``copy_to_user``.


Alternatively, run ``python testusermode.py``, which will send an ``ioctl`` to ``/dev/oracle`` (the driver doesn't care what command is sent, they're all handled equally). You can observe the effect by reading from ``/dev/oracle``, the read value should be incremeted after each ioctl call.



References
==========

- http://www.tldp.org/LDP/lkmpg/2.4/html/x281.htm
- https://www.apriorit.com/dev-blog/195-simple-driver-for-linux-os
- https://www.youtube.com/watch?v=Zn8mEZXr6nE
- http://www.virtsync.com/c-error-codes-include-errno
- https://lwn.net/Articles/115651/



Questions
=========

#. why ``static``? Other tutorials don't have that.
#. what is the point of having major and minor versions?
#. can ``mknod`` be invoked automatically?
#. ``cat`` never stops, should I add an ``EOF`` at the end? (does stop when run as root, strange)
#. what format specifier to use for ``size_t``? ``%z`` does not work.
#. ``#define ENOTTY      25  /* Not a typewriter */`` why can't my character device handle this?