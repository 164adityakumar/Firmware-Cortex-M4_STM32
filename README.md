
## About the project

This Project is all about building bare-metal firmware for a Cortex-M4 STM32 microcontroller, using open source tools and libraries such as GCC and libopencm3. This starts from blinking an LED, to building a bootloader for performing firmware updates over UART/USB, to building a signed firmware security mechanism that allow only authorised code to run on the device. Stretch goal content includes *breaking* the security we build, as well as exploring more peripherals, applications, and algorithms in depth.

## Prerequisites

For running it locally you need to have the following installed and properly setup. Ensure that they are available in your path.

- [GNU ARM Embedded tools](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [GNU Make](https://www.gnu.org/software/make/)

### When using vscode

install some extensions to make development smoother

- `C/C++`
- `Cortex-Debug`

## Repo setup

```bash
# Clone the repo
git clone git@github.com:164adityakumar/Firmware-Cortex-M4_STM32.git
cd Firmware-Cortex-M4_STM32

# Initialise the submodules (libopencm3)
git submodule init
git submodule update

# Build libopencm3
cd libopencm3
make
cd ..

# Build the main application firmware
cd app
make
```
