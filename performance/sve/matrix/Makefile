all:
	gcc -g -march=armv8-a+sve -o main main.c

clean:
	rm -f main

check:
	qemu-system-aarch64 -m 1024 -cpu max,sve=on,sve=256 -M virt,gic-version=3,its=on,iommu=smmuv3 -nographic
