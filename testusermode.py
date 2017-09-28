import fcntl
import sys

# the module doesn't care what command you send it, but since an
# integer is expected, let's give it one
operation = int(sys.argv[-1])


oracle = open('/dev/oracle', 'rb')
fcntl.ioctl(oracle, operation)

print 'ioctl %i sent ' % operation