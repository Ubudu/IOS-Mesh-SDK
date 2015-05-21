# IOS-Mesh-SDK

Ubudu mesh SDK for iOS allows devices to establish a connection to a mesh network and to send messages through it.

### System and hardware requirements

For iBeacon related features:

iOS 7.0 or higher (IOS 7.1.2 or iOS 8.0+ recommended)
iPhone 4S / iPad 3rd generation / iPad mini / iPod touch 5th generation, or any more recent device.

For geofencing :

iOS 6.0 or higher
iPhone 4 or more recent

## I. Adding the Ubudu SDK to a project.

Starting to use the ubudu mesh SDK on iOS native app should be a few minutes to process.

### Using CocoaPods

This is the prefered and simplest way to get started. Just add the following line to your Podfile

`pod 'UbuduMeshSDK'` then execute `pod install`.

If you are not already using CocoaPods for your project you can get started by reading the [CocoaPods documentation](https://guides.cocoapods.org/).


### Manually

If you don't want to use CocoaPods you can install the SDK manually by following the instructions bellow.

1. Drag & drop the **UbuduMeshSDK.framework** folder into the Frameworks folder of your project in XCode. Check the **"Copy items into destination group's folder (if needed)"** option.

2. Add the following list of frameworks and libraries to your project if they are not already present.

	- "Foundation"
	- "CoreBluetooth"

3. In the project settings go to : `"General"->"Your Target"->"Build Settings"->"(All)"->"Other Linker Flags"` Then add the following flags: `-ObjC`.


## II. Project configuration

First of all, you have to prepare your beacons and setup the mesh properties from the [manager plateform](https://manager.ubudu.com/).

Basicly you need to configure in **Mesh network settings**.

- Setup Mesh Network Id.
- Setup Mesh General Settings.
- Setup the beacon id in the mesh network.
- Setup the Mesh relay node


## III. Get started with the SDK - Objective-C.


Import SDK : `#import <UbuduMeshSDK/UbuduMeshSDK.h>`

In order to use the method :
`sendMeshMEssage`.

_Few properties are required and set previously from the manager plateform_

```
- (void)sendMeshMessage:(NSString *)meshMessage
              networkId:(NSUUID *)networkId
               toDevice:(uint16_t)address
   disconnectImmediatly:(BOOL)disconnect
           successBlock:(UBeaconMeshManagerSuccessBlock)successBlock
          progressBlock:(UBeaconMeshManagerProgressBlock)progressBlock
            failedBlock:(UBeaconMeshManagerFailedBlock)failedBlock;
```


## IV. Ubudu Mesh Delegate.

The `UBUMeshBeaconManagerDelegate` provides callback method which you can implement to recieve events from the mesh beacon manager.

Implement the method below to receive events that interest your application :  
`- (void)meshManager:(UBUMeshBeaconManager *)meshManager didUpdateVisibleAndConnectableNodes:(NSArray *)meshNodes;`

Two methods to enable and disable that callback can be call from the `UBUMeshBeaconManager` :

- `startScanning` to scan around and it trigger the method describe previously.
- `stopScanning` to stop the scan.


## V. Create your own app.

Once the framework included in the project, you are now able to initialize the manager and to set the delegate.

```
	/// Manager setup
    self.meshManager = [UBUMeshBeaconManager sharedInstance];
    self.meshManager.delegate = self;
```

Here we define the elements we did set in the manager plateform *(cf: II. Project configuration )* :

- A **message** or references to send through the mesh network (max:16bytes).
- An **endpoint** is an mesh beacon id (the target), on the manager the target can have a status : node connected to internet.
- A **networkId** is the id of a mesh network that you want to join. (the same network id, can contains some mesh beacon connectable, mesh beacon none connectable, and also mesh beacon connected to the internet).

```
    /// definition
    NSString * messageToSend = @"Hello World"; /// short message or reference to long speach
    NSString * networkId = @"F80ECE82-9749-A840-17B1-1500EDABF6FF"; /// mesh network id
    unsigned  endpoint = 16449; /// Mesh device id
    
    [self.meshManager sendMeshMessage:messageToSend
                            networkId:[[NSUUID alloc] initWithUUIDString:networkId]
                             toDevice:(uint16_t)endpoint
                 disconnectImmediatly:YES
                         successBlock:^(UBUMeshBeaconManager *manager, UBUMeshBeacon *meshBeacon, NSDictionary *userInfo)
                         {
                             /// on success
                             NSString *log = @"success : message sent ";
                             NSLog(log);
                         }
                         progressBlock:^(UBUMeshBeaconManager *manager, NSDictionary *userInfo)
                         {
                             /// to check in progress / retry
                             NSString *log = @"Retry in progress...";
                             NSLog(log);
                         }
                         failedBlock:^(UBUMeshBeaconManager *manager, UBUMeshBeacon *meshBeacon, NSDictionary *userInfo, NSError *error)
                         {
                             /// Log on failure
                             NSString *log = @"message not sent, but not reached";
                             NSLog(log);
                         }]; 
```

The code below is an illustration of where you can start and stop the scanning.

``` 
/// we can start the scanning here StartScanning
- (void)viewDidLoad {
    [super viewDidLoad];
    // mesh setup
    [self meshSetup];
    [self.meshManager startScanning];
}

/// we can stop the scanning here.
- (void)viewDidDisappear:(BOOL)animated
{
    [self.meshManager stopScanning];
}
```

Finaly the implementation of the methode delegate.

```
	/// An example of meshdelegate implementation
	- (void)meshManager:(UBUMeshBeaconManager *)meshManager didUpdateVisibleAndConnectableNodes:(NSArray *)meshNodes
{
	/// implemente here the action to sendMeshMessage for example.
}
```


