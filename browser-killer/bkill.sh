#!/bin/bash

for pid in `show_browser_pid`
do
    echo adb shell kill $pid
    adb shell kill $pid
done
