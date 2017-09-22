Overview
========

This is a basic kernel module that does nothing at the moment. The planned behaviour:

- create a device file ``/dev/oracle`` where any process can write any string that ends with a ``?``
- when reading from the file, the answer will be ``42``
- when sending a specific ``ioctl`` to the module, it will increment the answer to 43, then 42, and so on...


Instructions
============

This was tested on Linux Mint 18.2, but should work on any Debian-based distro, as well as any other distro, if you adjust the dependencies accordingly.

Prerequisites
-------------

This only needs to be done once, to prepare the compilation environment.

- ``sudo apt-get install build-essentials``


Compilation
-----------




User-mode tool
==============

TODO