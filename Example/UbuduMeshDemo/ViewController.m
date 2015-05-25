//
//  ViewController.m
//  UbuduMeshDemo
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

#import "ViewController.h"

@interface ViewController () <UBUMeshBeaconManagerDelegate>

@property (weak, nonatomic) IBOutlet UIButton *btContact;
@property (weak, nonatomic) IBOutlet UILabel *lblTextHolder;

@property (nonatomic) BOOL isSendingMessage;
@property (nonatomic) NSInteger nbOfConnectableNodes;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupMesh];
    [self.meshManager startScanning];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
    [self.meshManager stopScanning];
}

#pragma mark - Mesh SDK Setup

- (void)setupMesh
{
    self.meshManager = [UBUMeshBeaconManager sharedInstance];
    self.meshManager.delegate = self;
    
    self.isSendingMessage = NO;
    self.nbOfConnectableNodes = 0;
}

- (IBAction)buttonClick:(id)sender {
    // Disable button until a connectable node is discovered
    [self sendMessage];
}

- (void)sendMessage {

    __block BOOL labelStateFlag = NO;
    
    NSString * messageToSend = @"Hello World";
    NSString * networkId = @"F80ECE82-9749-A840-17B1-1500EDABF6FF";
    uint16_t endpoint = 16449;

    [self.meshManager stopScanning];

    self.isSendingMessage = YES;
    [self updateUIState];
    
    [self.meshManager sendMeshMessage:messageToSend
                            networkId:[[NSUUID alloc] initWithUUIDString:networkId]
                             toDevice:(uint16_t)endpoint
                 disconnectImmediatly:YES
                         successBlock:^(UBUMeshBeaconManager *manager, UBUMeshBeacon *meshBeacon, NSDictionary *userInfo) {
                             
                             NSLog(@"Send message success: meshBeacon = %@ userInfo = %@", meshBeacon, userInfo);
                             [self.meshManager startScanning];
                             [self.lblTextHolder setText:@"Message succesfully sent"];
                             labelStateFlag = YES;
                             self.isSendingMessage = NO;
                             [self updateUIState];
                         }
                        progressBlock:^(UBUMeshBeaconManager *manager, NSDictionary *userInfo) {
                            
                            if( labelStateFlag == NO ){
                                NSLog(@"Send message progress block: userInfo = %@", userInfo);
                                // Display something while in progress
                                [self.lblTextHolder setText:@"Retry in progress..."];
                            }
                        }
                          failedBlock:^(UBUMeshBeaconManager *manager, UBUMeshBeacon *meshBeacon, NSDictionary *userInfo, NSError *error) {
                              
                              NSLog(@"Send message failed: meshBeacon = %@ userInfo = %@ error = %@", meshBeacon, userInfo, error);
                              [self.lblTextHolder setText:@"Message not sent, target not reachable"];
                              [self.meshManager startScanning];
                              labelStateFlag = YES;
                              self.isSendingMessage = NO;
                              [self updateUIState];
                          }];
}

- (void)updateUIState
{
    if (self.isSendingMessage) {
        [self.btContact setEnabled:NO];
        [self.btContact setTitle:@"Sending message..." forState:UIControlStateNormal];
    } else {
        if (self.nbOfConnectableNodes > 0) {
            // Enable button when near a connectable node
            [self.btContact setEnabled:YES];
            [self.btContact setTitle:@"Send Message" forState:UIControlStateNormal];
            [self.lblTextHolder setText:@"A connectable mesh beacons is visible"];
        } else {
            // Disable button when no connectable node around
            [self.btContact setEnabled:NO];
            [self.btContact setTitle:@"No Connectable Beacon Arround" forState:UIControlStateNormal];
            [self.lblTextHolder setText:@"Looking for a connectable mesh beacon"];
            
        }
    }
}

#pragma mark - UBUMeshBeaconManagerDelegate

- (void)meshManager:(UBUMeshBeaconManager *)meshManager didUpdateVisibleAndConnectableNodes:(NSArray *)meshNodes
{
    self.nbOfConnectableNodes = 0;
    for (UBUMeshBeacon *node in meshNodes) {
        if( node.identifier != nil && node.isConnectable ){
            self.nbOfConnectableNodes++;
        }
    }
    [self updateUIState];
}

@end
