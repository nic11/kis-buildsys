Кросс-компиляция для проекта отсюда: https://github.com/akhtyamovpavel/TechProgSimpleLibrary

Запуск (Ubuntu 18.04):
```sh
apt install qemu-system-arm
apt install qemu-user-static

# Sanity check
~/apps/gcc-linaro-7.5.0-2019.12-i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ main.cpp
qemu-arm-static -L ~/apps/sysroot-glibc-linaro-2.25-2019.12-arm-linux-gnueabihf ./a.out

# Build using CMake
mkcd build
cmake .. -DSYSROOT=$HOME/apps/sysroot-glibc-linaro-2.25-2019.12-arm-linux-gnueabihf \
         -DTOOLCHAIN=$HOME/apps/gcc-linaro-7.5.0-2019.12-i686_arm-linux-gnueabihf
make

# Installs to sysroot
make install
```

Здесь предполагается, что скачаны тулчейн и sysroot и распакованы в `~/apps`:  
https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/
