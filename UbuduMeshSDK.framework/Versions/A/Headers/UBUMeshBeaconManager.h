//
//  UBUMeshBeaconManager.h
//  UbuduMeshSDK
//
// Copyright (c) 2015, UBUDU SAS
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

#import "UBUMeshBeaconManagerDelegate.h"

@class UBUMeshBeacon;
@class UBUMeshBeaconManager;

typedef void (^UBeaconMeshManagerSuccessBlock)(UBUMeshBeaconManager *manager, UBUMeshBeacon *meshBeacon, NSDictionary *userInfo);
typedef void (^UBeaconMeshManagerFailedBlock)(UBUMeshBeaconManager *manager, UBUMeshBeacon *meshBeacon, NSDictionary *userInfo, NSError *error);
typedef void (^UBeaconMeshManagerProgressBlock)(UBUMeshBeaconManager *manager, NSDictionary *userInfo);

@interface UBUMeshBeaconManager : NSObject

@property (nonatomic, weak) id <UBUMeshBeaconManagerDelegate> delegate;
@property (nonatomic, strong) UBUMeshBeacon *connectedBeacon;

/**
 *  Version of the SDK.
 */
@property (nonatomic, readonly) NSString *version;

+ (UBUMeshBeaconManager *)sharedInstance;

- (BOOL)startScanning;
- (BOOL)stopScanning;

- (CBCentralManagerState)getCentralManagerState;

- (void)sendMeshMessage:(NSString *)meshMessage
              networkId:(NSUUID *)networkId
               toDevice:(uint16_t)address
   disconnectImmediatly:(BOOL)disconnect
           successBlock:(UBeaconMeshManagerSuccessBlock)successBlock
          progressBlock:(UBeaconMeshManagerProgressBlock)progressBlock
            failedBlock:(UBeaconMeshManagerFailedBlock)failedBlock;

- (void)sendMeshMessage:(NSString *)meshMessage
              networkId:(NSUUID *)networkId
               toDevice:(uint16_t)address
       withConfirmation:(BOOL)confirmation
   disconnectImmediatly:(BOOL)disconnect
           successBlock:(UBeaconMeshManagerSuccessBlock)successBlock
          progressBlock:(UBeaconMeshManagerProgressBlock)progressBlock
            failedBlock:(UBeaconMeshManagerFailedBlock)failedBlock;

- (void)connectToClosestBeacon:(UBeaconMeshManagerSuccessBlock)successBlock
                 progressBlock:(UBeaconMeshManagerProgressBlock)progressBlock
                   failedBlock:(UBeaconMeshManagerFailedBlock)failedBlock;

- (void)disconnectFromConnectedBeacon;
@end
