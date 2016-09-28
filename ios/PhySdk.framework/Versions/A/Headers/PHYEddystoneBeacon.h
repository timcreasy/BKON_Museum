//
//  PHYEddystoneBeacon.h
//  PhySdk
//
//  Created by Beat Zenerino on 2/20/16.
//  Copyright © 2016 BKON Connect Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class PHYEddystoneManager;

/**
 * The PHYEddystoneBeacon class defines the properties of an Eddystone beacon. You
 * don't create an object from this class. PHYEddystoneBeacon objects are returned
 * from the PHYEddystoneManager through the 'didScanBeacons' or 'didScanBeaconsWithMetadata'
 * delegate method.
 */
@interface PHYEddystoneBeacon : NSObject

@property (nonatomic, strong) CBPeripheral *peripheral;

@property (nonatomic, weak) PHYEddystoneManager *delegate;

/**
 * The URL for an Eddystone URL beacon.
 */
@property (nonatomic, strong) NSString *scanUrl;

/**
 * The tx power.
 */
@property (nonatomic, strong) NSNumber *txPowerLevel;

/**
 * The RSSI value of the scan.
 */
@property (nonatomic, strong) NSNumber *rssi;

/**
 * Set if the scanUrl was resolved for metadata.
 */
@property (nonatomic, strong) NSString *hasMetadata;

/**
 * The resolved URL.
 */
@property (nonatomic, strong) NSString *destinationUrl;

/**
 * The title associated with the destinationUrl.
 */
@property (nonatomic, strong) NSString *title;

/**
 * The url for retrieving the favicon associated with the destinationUrl.
 */
@property (nonatomic, strong) NSString *faviconUrl;

/**
 * The description associated with the destinationUrl.
 */
@property (nonatomic, strong) NSString *desc;

/**
 * The favicon image associated with the destinationUrl.
 */
@property (nonatomic, strong) UIImage *faviconImage;

/**
 * The JSON-LD data associated with the destinationUrl. Can be either
 * an NSDictionary or NSArray
 */
@property (nonatomic, strong) id jsonLd;

/**
 * The distance between the beacon and the device.
 */
@property (nonatomic, assign) double distance;

@end
