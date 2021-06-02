PKG=atom.hardware.demo@1.0
LOC=1.0/default/impl
hidl-gen -Landroidbp -ratom.hardware:device/skyworth/hidlDemo/hardware/interfaces/  $PKG
hidl-gen -o $LOC -Lc++-impl  -ratom.hardware:device/skyworth/hidlDemo/hardware/interfaces/ -randroid.hidl:system/libhidl/transport $PKG
hidl-gen -o $LOC -Landroidbp-impl -ratom.hardware:device/skyworth/hidlDemo/hardware/interfaces/ -randroid.hidl:system/libhidl/transport $PKG
