//
//  PHYPeripheral.h
//  PhySdk
//
//  Created by Beat Zenerino on 6/23/14.
//  Copyright (c) 2014-2016 BKON Connect Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "PHYCentralManager.h"

/**
 * List of attributes for a beacon. Returned by the delegate method
 * 'didUpdateAttribute', reporting which attribute was updated
 */
typedef NS_ENUM(NSInteger, PHYAttribute) {
	/// The update was not successful and returned an error.
	PHYError = -1,
	/// The advertising UUID value for the beacon was updated.
	PHYUUID,
	/// The advertising major value for the beacon was updated.
	PHYMajor,
	/// The advertising minor value for the beacon was updated.
	PHYMinor,
	/// The advertising rate for the beacon was updated.
	PHYAdvertisingRate,
	/// The transmission power for the beacon was updated.
	PHYTxPower,
	/// The identify value was updated and it is now possible to toggle the LED.
	PHYIdentify,
	/// The model number of the beacon was updated.
	PHYModelNumber,
	/// The hardware revision value for the beacon was updated.
	PHYHardwareRevision,
	/// The firmware revision value for the beacon was updated.
	PHYFirmwareRevision
};

/**
 * The PHYPeripheral class is used to interface with specific beacon after
 * a communication channel has been established through the PHYCentralManager.
 * It provides methods to modify a BKON beacons parameters.
 */
@class PHYCentralManager;
@protocol PHYPeripheralDelegate;

@interface PHYPeripheral : NSObject <CBPeripheralDelegate>

/**
 * The delegate for the peripheral.
 */
@property id<PHYPeripheralDelegate> delegate;
@property (nonatomic, weak) PHYCentralManager *centralManager;
@property (nonatomic, strong) CBPeripheral *peripheral;

/**
 * A unique device identifier for this beacon.
 */
@property (nonatomic, strong) NSUUID *deviceIdentifier;

/**
 * The assigned UUID this beacon uses in its advertising packet.
 */
@property (nonatomic, strong) NSUUID *uuid;

/**
 * The assigend major number this beacon uses in its advertising packet.
 */
@property (nonatomic, strong) NSNumber *major;

/**
 * The assigend minor number this beacon uses in its advertising packet.
 */
@property (nonatomic, strong) NSNumber *minor;

/**
 * The rate at which the beacon sends out an advertising packet.
 */
@property (nonatomic, strong) NSNumber *advertisingRate;

/**
 * The strength of this beacons transmissioin signal.
 */
@property (nonatomic, strong) NSNumber *txPower;

/**
 * The strength of the signal received by the device.
 */
@property (nonatomic, strong) NSNumber *rssi;

/**
 * Model number of BKON beacon.
 */
@property (nonatomic, strong) NSString *modelNumber;

/**
 * Revision of the BKON hardware beacon.
 */
@property (nonatomic, strong) NSString *hardwareRev;

/**
 * Revision of the firmware running on the BKON beacon.
 */
@property (nonatomic, strong) NSString *firmwareRev;

/**
 * Sent from the PHYCentralManager to the peripheral after a connection
 * has been established.
 */
- (void)didConnect;

/**
 * Write a new value for the UUID parameter in the advertsing packet
 *
 * @param uuid the new UUID to write to the beacon
 */
- (void)writeUUID:(NSString *)uuid;

/**
 * Write a new value for the major parameter in the advertsing packet
 *
 * @param major the new major to write to the beacon
 */
- (void)writeMajor:(NSNumber *)major;

/**
 * Write a new value for the minor parameter in the advertsing packet
 *
 * @param minor the new minor to write to the beacon.
 */
- (void)writeMinor:(NSNumber *)minor;

/**
 * Write a new value for the advertsing rate parameter
 *
 * @param rate the new advertising rate for the beacon
 */
- (void)writeAdvertisingRate:(NSNumber *)rate;

/**
 * Write a new value for the transmission power parameter
 *
 * @param power the new transmission strenght of the beacon
 */
- (void)writeTxPower:(NSNumber *)power;

/**
 * Reset the beacon to start transmitting with the new parameters
 */
- (void)writeReset;

/**
 * Pulse the LED on the beacon
 */
- (void)pulseLED;

- (id)initWithApiKey:(NSString *)apiKey andVersion:(NSUInteger)version;
- (BOOL)parseAdvertisingData:(NSData *)phyData;
@property (atomic, assign) long expireTime;

@end

/**
 *	The PHYPeripheralDelegate reports the discovery and updates to parameters
 */
@protocol PHYPeripheralDelegate
- (void)peripheral:(PHYPeripheral *)peripheral didUpdateAttribute:(PHYAttribute)attribute error:(NSError *)error;
@end
