Overview
========

This is a basic kernel module that does nothing at the moment. The planned behaviour:

- create a device file ``/dev/oracle`` where any process can write any string that ends with a ``?``
- when reading from the file, the answer will be ``42``
- when sending a specific ``ioctl`` to the module, it will increment the answer to 43, then 44, and so on...


Instructions
============

This was tested on Linux Mint 18.2, but should work on any Debian-based distro, as well as any other distro, if you adjust the dependencies accordingly.

Prerequisites
-------------

This only needs to be done once, to prepare the compilation environment.

- ``sudo apt-get install build-essentials``
- ``sudo apt-get install raspberrypi-kernel-headers`` (raspi-specific) or ``sudo apt-get install linux-headers-$(uname -r)`` (untested)

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


User-mode tool
==============

TODO



References
==========

- https://www.apriorit.com/dev-blog/195-simple-driver-for-linux-os
- https://www.youtube.com/watch?v=Zn8mEZXr6nE