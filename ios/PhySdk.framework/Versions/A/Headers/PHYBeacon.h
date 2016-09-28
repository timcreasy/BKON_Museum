//
//  PHYBeacon.h
//  PhySdk
//
//  Created by Beat Zenerino on 5/16/14.
//  Copyright (c) 2014-2016 BKON Connect Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


/**
 * The PHYBeacon class defines the properties of a beacon. You don't create an
 * object from this class.PHYBeacon objects are returned from the
 * PHYLocationManager through the 'didRangeBeacons' delegate method.
 */
@interface PHYBeacon : NSObject

/**
 * The UUID this beacon is advertising.
 */
@property (strong, nonatomic) NSUUID *proximityUUID;

/**
 * The major this beacon is advertising.
 */
@property (strong, nonatomic) NSNumber *major;

/**
 * The minor this beacon is advertising.
 */
@property (strong, nonatomic) NSNumber *minor;

/**
 * The proximity of this beacon to the device. (far, near, immediate or unknown)
 */
@property (assign, nonatomic) CLProximity proximity;

/**
 * The accuracy of the proximity value in meters.
 */
@property (assign, nonatomic) CLLocationAccuracy accuracy;

/**
 * The strength of the received signal from the beacon.
 */
@property (assign, nonatomic) NSInteger rssi;

@end
