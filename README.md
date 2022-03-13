# OpenVr_DriverTest
A test driver for OpenVr
## Reference
https://github.com/terminal29/Simple-OpenVR-Driver-Tutorial
https://github.com/finallyfunctional/openvr-driver-example

## Build(windows)
1. Clone this repository
2. Create a directory in the folder, name it "build" or something else
3. Open command line prompt, cd into build directory, type "cmake .."
4. Open sln file in build folder with visual studio, press F7 to build the project.
5. You'll find a folder in this path "Output\Debug\example"
6. Copy the example folder into the steamvr driver folder, typically "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\drivers"
7. (Alternative for step 6) Edit C:\Users\<YourUserName>\AppData\Local\openvr\openvrpaths.vrpath, add the example folder path to "external_drivers" field, like this:

"external_drivers" : 
	[
		"D:\\Dev\\SitwalkDriver\\OpenVrDriverExample\\Output\\Debug\\example"
	],

8. Run SteamVR, you'll find an extra controller there.

## Problem(Need help)
I can see the controller in "Test Controllers", however I can't make it work in any of the games, Any ideas please?
