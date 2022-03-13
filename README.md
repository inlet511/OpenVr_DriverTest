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

```
"external_drivers" : 
	[
		"D:\\Dev\\SitwalkDriver\\OpenVrDriverExample\\Output\\Debug\\example"
	],
```

8. Run SteamVR, you'll find an extra controller there.

## Problem(Need help)
1. In the page "SteamVR->Devices->Controller Settings->Manage Controller Bindings", there's a Active Controller field, the value of this field seems to depend on which controller steamVR detects first, if so , how can I set up for my device if steamVR detects other device first?
![ActiveController](https://github.com/inlet511/OpenVr_DriverTest/blob/main/images/ActiveController.png)
2. Now I can see my controller in "TEST CONTROLLER" page of SteamVR, but I failed to get my controller working in any vr game. What can I do to make it work in games?
3. I tried to set my controller's ETrackedControllerRole to TrackedControllerRole_Treadmill and TrackedControllerRole_OptOut which seems to be fair, but in both of these cases, the "TEST CONTROLLER" page doesn't show the input correct(There's some screenshots in my git repository). Am I doing it wrong? Now I have to set it to TrackedControllerRole_LeftHand (or RightHand), but this seems to be conflicting the original controllers.....

Treadmill-Not working correctly in TEST CONTROLLER
![Treadmill](https://github.com/inlet511/OpenVr_DriverTest/blob/main/images/treadmill.png)
OptOut-Not working correctly in TEST CONTROLLER
![OptOut](https://github.com/inlet511/OpenVr_DriverTest/blob/main/images/optout.png)
LeftHandMode- Works in TEST CONTROLLER, but not in games. Besides, it seems to occupying the original controllers place.
![LeftHandMode](https://github.com/inlet511/OpenVr_DriverTest/blob/main/images/lefthand.png)

