# IOS-Mesh-SDK

ubudu Mesh SDK for iOS allows devices to connect to a Mesh network, in order to create two-way communication.

The following details the steps to add Mesh capability to your iOS app. 

To help you further, we're giving you an [Example](https://github.com/Ubudu/IOS-Mesh-SDK/tree/master/Example) of sample implementation code.   

## System and hardware requirements

For iBeacon related features:

- iOS 7.0 or higher (IOS 7.1.2 or iOS 8.0+ recommended).

- iPhone 4S / iPad 3rd generation / iPad mini / iPod touch 5th generation, or any more recent device.

## Configure your Mesh network 

First of all, you have to prepare your uBeacon Mesh devices, and to setup the Mesh network properties from the [ubudu Manager](https://manager.ubudu.com/). If you're following the step-by-step instructions in ubudu's Knowledge Base, then you should already have done it. Go straight to the next chapter.

Otherwise: 

Once logged in, go to the tab 'Devices', 'Edit' the beacon you want to configure, then you'll reach the **Mesh network settings** at the bottom of the page. Now, you'll be able to setup :

- The UUID of the Mesh network
- The Mesh network settings 
- The beacon ID in the Mesh network
- Indicate if the node is connected to the Internet

## Add the SDK to a project

Setting up the ubudu Mesh SDK on an iOS native app only takes a few minutes, either using CocoaPods (recommended) or manually.

### Using CocoaPods

This is the easiest way to get started. Add to your Podfile the line `pod 'UbuduMeshSDK'`, then execute `pod install`.

If you are not already using CocoaPods for your project, you can get started by reading the [CocoaPods documentation](https://guides.cocoapods.org/).


### Manually

If you don't want to use CocoaPods, you can manually install the SDK:

1. **Drag & drop the *UbuduMeshSDK.framework* folder** into the "Frameworks" folder of your project in XCode. If needed, check the "Copy items into destination group's folder" option.

2. **Add the following list of frameworks and libraries** to your project, if not already displayed.
	 - "Foundation"
	 - "CoreBluetooth"
	 

3. In your project settings, follow the steps `"General"` > `"Your Target"` > `"Build Settings"` > `"(All)"` > `"Other Linker Flags"`. Then, add the flag `-ObjC`.


## Import the SDK

Import the SDK in the header file.

`#import <UbuduMeshSDK/UbuduMeshSDK.h>` 

## Start/stop the service

To use Mesh in your app you need to start the service :`UBeaconMeshManager * meshManager` 

It may done by calling  `[self.meshManager startScanning]`.

`startScanning` method starts the search for enabled Mesh beacons.

To stop searching for Mesh beacons, call the `stopScanning` method. 


## Discover nearby Mesh beacons 

`UBUMeshBeaconManagerDelegate` provides callback method which you can implement to receive events from the ubudu Manager:

Implement the method below to receive events relevant to your application :  
`- (void)meshManager:(UBUMeshBeaconManager *)meshManager didUpdateVisibleAndConnectableNodes:(NSArray *)meshNodes;`

`meshManager` method callbacks :

- `meshNodes` : array of objects of `UBUMeshBeacon` class


## Send a message 

To send message through a Mesh network, use the following method :

```
- (void)sendMeshMessage:(NSString *)meshMessage
              networkId:(NSUUID *)networkId
               toDevice:(uint16_t)address
   disconnectImmediatly:(BOOL)disconnect
           successBlock:(UBeaconMeshManagerSuccessBlock)successBlock
          progressBlock:(UBeaconMeshManagerProgressBlock)progressBlock
            failedBlock:(UBeaconMeshManagerFailedBlock)failedBlock;
```

`sendMeshMessage` method parameters:

- **meshMessage** is a string containing the Mesh message to be send. It should be no longer than 16 bytes.

- **networkId** is a string containing the Mesh network UUID. ```meshId``` should be part of the network.

- **address** may be the target Mesh beacon address in decimal format. The value Should be between 1-32767.

`sendMeshMessage` method callbacks :

- `successBlock` indicates whether the message was sent or not
- `progressBlock` indicates the retries _(10times)_ after a failure
- `failedBlock` indicates failure to send the message. Failure can be cause by a time out / nearby node not connectable / mesh service missed.



