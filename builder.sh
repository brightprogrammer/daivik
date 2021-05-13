# clear sysroot for fresh headers
rm sysroot/program/headers/* -rvf
rm sysroot/program/binaries/* -rvf
rm sysroot/program/libraries/* -rvf
rm sysroot/boot/* -rvf

# build os
mkdir -pv build
cd build
rm CMakeCache.txt
cmake ..
make -j2
make install
cd ..

# remove cache daivik.hdd
rm daivik.hdd

# Create an empty zeroed out 64MiB daivik file.
dd if=/dev/zero bs=1M count=0 seek=64 of=daivik.hdd
 
# Create a GPT partition table.
parted -s daivik.hdd mklabel gpt
 
# Create an ESP partition that spans the whole disk.
parted -s daivik.hdd mkpart ESP fat32 2048s 100%
parted -s daivik.hdd set 1 esp on

# Build limine-install.
make -C limine
 
# Install the Limine BIOS stages onto the daivik.
limine/bin/limine-install daivik.hdd
 
# Mount the loopback device.
USED_LOOPBACK=$(sudo losetup -Pf --show daivik.hdd)
 
# Format the ESP partition as FAT32.
sudo mkfs.fat -F 32 ${USED_LOOPBACK}p1
 
# Mount the partition itself.
mkdir -p bootdisk
sudo mount ${USED_LOOPBACK}p1 bootdisk

# copy in sysroot/boot
cp -v build/kernel/daivik sysroot/boot/daivik.elf
cp -v limine/bin/BOOTX64.EFI sysroot/boot/EFI/BOOT/
cp -v limine.cfg limine/bin/limine.sys sysroot/boot/

# Copy the relevant files over
sudo cp -v sysroot/* bootdisk/ -r
 
# Sync system cache and unmount partition and loopback device.
sync
sudo umount bootdisk
sudo losetup -d ${USED_LOOPBACK}