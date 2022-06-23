# Embedded Linux Device Drivers

- Creating a Device file Manually
```bash
mknod -m <permissions> <name> <device type> <major> <minor>

<name> – your device file name that should have a full path (/dev/name)

<device type> – Put c or b

c – Character Device

b – Block Device

<major> – major number of your driver

<minor> – minor number of your driver

-m <permissions> – optional argument that sets the permission bits of the new device file to permissions
```

