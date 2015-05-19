//
//  UBUMeshBeacon.h
//  UbuduMeshSDK
//
// Copyright (c) 2011-2015, UBUDU SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//         SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class UBUMeshBeacon;

typedef void (^UMeshBeaconSuccessBlock)(UBUMeshBeacon *meshBeacon, NSDictionary *userInfo);
typedef void (^UMeshBeaconProgressBlock)(UBUMeshBeacon *meshBeacon, NSDictionary *userInfo);
typedef void (^UMeshBeaconFailedBlock)(UBUMeshBeacon *meshBeacon, NSDictionary *userInfo, NSError *error);

@interface UBUMeshBeacon : NSObject

//General device state properties (not from GATT)
@property (nonatomic) BOOL isConnectable;
@property (nonatomic) BOOL isConnected;
@property (nonatomic, strong) NSNumber *RSSI;
@property (nonatomic, strong) NSDate *lastSeenAt;
@property (nonatomic, strong) NSString *identifier;             //iOS unique identifier (don't store this since it changes per device or after reboot)
@property (nonatomic, strong) CBPeripheral *peripheral;
@property (nonatomic, strong) NSString *deviceName;

- (void)updateStateFrom:(CBPeripheral *)peripheral
  withAdvertisementData:(NSDictionary *)advertisementData
                andRSSI:(NSNumber *)RSSI;

- (void)discoverRequiredCharacteristics:(UMeshBeaconSuccessBlock)successBlock
                          progressBlock:(UMeshBeaconProgressBlock)progressBlock
                            failedBlock:(UMeshBeaconFailedBlock)failedBlock;

- (void)connectedTo:(CBPeripheral *)peripheral;
- (void)disconnected;
- (void)abortMeshMessage;
- (void)clearMeshMessageQueue;

- (void)setMeshNotification:(BOOL)enable withCompletionBlock:(UMeshBeaconSuccessBlock)completionBlock;

- (void)sendMeshMessageWithData:(NSData *)meshMessageData
             toDeviceAdressData:(NSData *)addressData
           disconnectImmediatly:(BOOL)disconnect
                   successBlock:(UMeshBeaconSuccessBlock)successBlock
                  progressBlock:(UMeshBeaconProgressBlock)progressBlock
                    failedBlock:(UMeshBeaconFailedBlock)failedBlock;
@end
