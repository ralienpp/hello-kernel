import fcntl
import sys

# the module doesn't care what command you send it, but since an
# integer is expected, let's give it one

try:
    operation = int(sys.argv[-1])
except ValueError:
    # if no command line arg was given, just use 3 as an ioctl
    # operation; it doesn't really matter because the handler
    # does not use this number at all
    operation = 3


oracle = open('/dev/oracle', 'rb')
fcntl.ioctl(oracle, operation)

print 'ioctl %i sent ' % operation