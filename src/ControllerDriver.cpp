#include "ControllerDriver.h"
#include <cstdlib>

EVRInitError ControllerDriver::Activate(uint32_t unObjectId)
{
	driverId = unObjectId; //unique ID for your driver

	PropertyContainerHandle_t props = VRProperties()->TrackedDeviceToPropertyContainer(driverId); //this gets a container object where you store all the information about your driver

	VRProperties()->SetStringProperty(props, Prop_InputProfilePath_String, "{example}/input/controller_profile.json"); //tell OpenVR where to get your driver's Input Profile
	VRProperties()->SetInt32Property(props, Prop_ControllerRoleHint_Int32, ETrackedControllerRole::TrackedControllerRole_Treadmill); //tells OpenVR what kind of device this is
	VRProperties()->SetBoolProperty(props, Prop_NeverTracked_Bool, true);
	VRProperties()->SetStringProperty(props, Prop_SerialNumber_String, "example_controler");
	VRProperties()->SetStringProperty(props, Prop_RegisteredDeviceType_String, "openvr_treadmill_controller");
	VRProperties()->SetInt32Property(props, Prop_Axis0Type_Int32, k_eControllerAxis_TrackPad);
	VRProperties()->SetInt32Property(props, Prop_Axis1Type_Int32, k_eControllerAxis_Joystick);

	//VRDriverInput()->CreateBooleanComponent(props, "/input/anything/x", &boolHandle);

	VRDriverInput()->CreateScalarComponent(props, "/input/joystick/x", &joystickXHandle, EVRScalarType::VRScalarType_Absolute, EVRScalarUnits::VRScalarUnits_NormalizedTwoSided);
	VRDriverInput()->CreateScalarComponent(props, "/input/joystick/y", &joystickYHandle, EVRScalarType::VRScalarType_Absolute,EVRScalarUnits::VRScalarUnits_NormalizedTwoSided); 
	//VRDriverInput()->CreateBooleanComponent(props, "/input/joystick/touch", &joyStickTouchHandle);
	//VRDriverInput()->CreateBooleanComponent(props, "/input/joystick/click", &joyStickClickHandle);

	VRDriverInput()->CreateScalarComponent(props, "/input/trackpad/y", &trackpadYHandle, EVRScalarType::VRScalarType_Absolute,EVRScalarUnits::VRScalarUnits_NormalizedTwoSided);
	VRDriverInput()->CreateScalarComponent(props, "/input/trackpad/x", &trackpadXHandle, EVRScalarType::VRScalarType_Absolute,EVRScalarUnits::VRScalarUnits_NormalizedTwoSided); 
	//VRDriverInput()->CreateBooleanComponent(props, "/input/trackpad/touch", &trackpadTouchHandle);
	//VRDriverInput()->CreateBooleanComponent(props, "/input/trackpad/click", &trackpadClickHandle);

	VRDriverInput()->CreateBooleanComponent(props, "/input/trigger/touch", &triggerTouchHandle);
	VRDriverInput()->CreateBooleanComponent(props, "/input/trigger/click", &triggerClickHandle);

	VRDriverInput()->CreateScalarComponent(props, "/input/grip/value", &gripHandle, EVRScalarType::VRScalarType_Absolute, EVRScalarUnits::VRScalarUnits_NormalizedOneSided);


	return VRInitError_None;
}

DriverPose_t ControllerDriver::GetPose()
{
	DriverPose_t pose = { 0 }; //This example doesn't use Pose, so this method is just returning a default Pose.
	pose.poseIsValid = false;
	pose.result = TrackingResult_Calibrating_OutOfRange;
	pose.deviceIsConnected = true;

	HmdQuaternion_t quat;
	quat.w = 1;
	quat.x = 0;
	quat.y = 0;
	quat.z = 0;

	pose.qWorldFromDriverRotation = quat;
	pose.qDriverFromHeadRotation = quat;

	return pose;
}

void ControllerDriver::RunFrame()
{
	int r = rand() % 100;

	VRDriverInput()->UpdateScalarComponent(trackpadYHandle, 0.95f, 0);
	VRDriverInput()->UpdateScalarComponent(trackpadXHandle, (r > 50) ? -0.5f : 0.5f, 0); 
	//VRDriverInput()->UpdateBooleanComponent(trackpadClickHandle, true, 0);
	//VRDriverInput()->UpdateBooleanComponent(trackpadTouchHandle, true, 0);

	VRDriverInput()->UpdateScalarComponent(joystickXHandle, (r > 50) ? -0.5f : 0.5f, 0); 
	VRDriverInput()->UpdateScalarComponent(joystickYHandle, 0.95f, 0);
	//VRDriverInput()->UpdateBooleanComponent(joyStickClickHandle, true, 0);
	//VRDriverInput()->UpdateBooleanComponent(joyStickTouchHandle, true, 0);
	if (GetAsyncKeyState(69) & 0x8000)
	{
		VRDriverInput()->UpdateBooleanComponent(triggerTouchHandle, true, 0);
		VRDriverInput()->UpdateBooleanComponent(triggerClickHandle, true, 0);
	} else
	{
		VRDriverInput()->UpdateBooleanComponent(triggerTouchHandle, false, 0);
		VRDriverInput()->UpdateBooleanComponent(triggerClickHandle, false, 0);
	}
	

	/*VRDriverInput()->UpdateBooleanComponent(boolHandle, r>50, 0);*/
}

void ControllerDriver::Deactivate()
{
	driverId = k_unTrackedDeviceIndexInvalid;
}

void* ControllerDriver::GetComponent(const char* pchComponentNameAndVersion)
{
	//I found that if this method just returns null always, it works fine. But I'm leaving the if statement in since it doesn't hurt.
	//Check out the IVRDriverInput_Version declaration in openvr_driver.h. You can search that file for other _Version declarations 
	//to see other components that are available. You could also put a log in this class and output the value passed into this 
	//method to see what OpenVR is looking for.
	if (strcmp(IVRDriverInput_Version, pchComponentNameAndVersion) == 0)
	{
		return this;
	}
	return NULL;
}

void ControllerDriver::EnterStandby() {}

void ControllerDriver::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) 
{
	if (unResponseBufferSize >= 1)
	{
		pchResponseBuffer[0] = 0;
	}
}