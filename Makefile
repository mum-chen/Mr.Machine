MR_ROOT:=$(shell pwd)/$(lastword $(MAKEFILE_LIST))
MR_ROOT:=$(shell dirname $(MR_ROOT))

PRO_NAME:= mr_machine
TOOL_CHAIN:= toolchain
RT_THREAD:= rt-thread
BUILD_DIR:= $(MR_ROOT)/$(RT_THREAD)/bsp/$(PRO_NAME)


build:
	rm -rf $(BUILD_DIR)
	cp -rf $(MR_ROOT)/src $(BUILD_DIR)
	cd $(BUILD_DIR); scons

.PHONY: env_prepare clean_env
env_prepare:$(TOOL_CHAIN) $(RT_THREAD)

$(TOOL_CHAIN):
	tar -xjvf package/arm-2014.05-28-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
	mv arm-2014.05 $(TOOL_CHAIN)

$(RT_THREAD):
	tar -xzvf package/rt-thread-2.1.0.tar.gz
	mv rt-thread-2.1.0 $(RT_THREAD)

clean_env:
	rm -rf $(TOOL_CHAIN) $(RT_THREAD)

