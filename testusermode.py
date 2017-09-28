from fcntl import fcntl

# the module doesn't care what command you send it, but since an
# integer is expected, let's give it one
OPERATION = 12


oracle = open('/dev/oracle', 'rb')
fcntl(oracle, OPERATION)

print 'command sent'