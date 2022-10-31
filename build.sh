#!/bin/bash
if [ ! -d "build" ]; then
	mkdir build
	cd build
	cmake ..
	cd ..
fi
cd build
make -j16&&[[ -d "$PICO_DRIVE_PATH" ]]&&cp touch_button.uf2 "$PICO_DRIVE_PATH/touch_button.uf2"
cd ..
