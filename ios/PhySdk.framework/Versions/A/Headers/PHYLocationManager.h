//
//  PHYLocationManager.h
//  PhySdk
//
//  Created by Beat Zenerino on 3/18/14.
//  Copyright (c) 2014-2016 BKON Connect Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PHYRegion.h"

@protocol PHYLocationManagerDelegate;

/**
 * The PHYLocationManager class is used to discover beacons and query their
 * approximate distance to the iPhone. You define regions that look for specific
 * iBeacon parameters, such as UUID, major and minor and then pass those to the
 * PHYLocationManager.
 */
@interface PHYLocationManager : NSObject <CLLocationManagerDelegate>

@property (weak, nonatomic) id<PHYLocationManagerDelegate> delegate;


/**
 * Initializes the PHYLocationManager with an API key. You can obtain an
 * API key from https://bkonregistry.com
 *
 * @param apiKey The key associated with you application
 */
- (id)initWithApiKey:(NSString *)apiKey;

/**
 * Returns a boolean indicating if ranging for beacons is available.
 */
+ (BOOL)isRangingAvailable;

/**
 * Returns a boolean indicating if location services are enabled on this device.
 */
+ (BOOL)locationServicesEnabled;

/**
 * Starts monitoring for the specified region. PHYLocationManager will notify
 * your application, through the delegate method 'didEnterRegion', when the host
 * device enters the proximity of a beacon region. It will also notify your application
 * when the device leaves the proximity of a beacon region through the delegate method
 * 'didExitRegion'
 *
 * @param region a PHY region
 * @param always true if monitoring should work in background
 */
- (void)startMonitoringForRegion:(CLRegion *)region always:(BOOL)always;

/**
 * Stops monitoring for the specified region.
 *
 * @param region a PHY region
 */
- (void)stopMonitoringForRegion:(CLRegion *)region;

/**
 * Start looking for beacons in the specified region. After calling this function the
 * PHYLocationManager will start returning any beacon it found for the region
 * through the delegate function 'didRangeBeacons'.
 *
 * @param region a PHY region
 * @param always true if monitoring should work in background
 */
- (void)startRangingBeaconsInRegion:(PHYRegion *)region always:(BOOL)always;

/**
 * Stops ranging beacons in the specified region.
 *
 * @param region a PHY region
 */
- (void)stopRangingBeaconsInRegion:(PHYRegion *)region;

/**
 * Retrieves the state of a region. This will report if you are inside a region
 * through the delegate method 'didDetermineState'.
 *
 * @param region a PHY region
 */
- (void)requestStateForRegion:(PHYRegion *)region;

@end

/**
 * The PHYLocationManagerDelegate is used to listen to proximity events from the
 * PHYLocationManager.
 */
@protocol PHYLocationManagerDelegate <NSObject>

@optional

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param region a PHY region
 */
- (void)phyManager:(PHYLocationManager *)manager didEnterRegion:(PHYRegion *)region;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param region a PHY region
 */
- (void)phyManager:(PHYLocationManager *)manager didExitRegion:(PHYRegion *)region;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param state the state of the region
 * @param region a PHY region
 */
- (void)phyManager:(PHYLocationManager *)manager didDetermineState:(CLRegionState)state forRegion:(PHYRegion *)region;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param region a PHY region
 * @param error the error returned
 */
- (void)phyManager:(PHYLocationManager *)manager monitoringDidFailForRegion:(PHYRegion *)region withError:(NSError *)error;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param region a PHY region
 */
- (void)phyManager:(PHYLocationManager *)manager didStartMonitoringForRegion:(PHYRegion *)region;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param beacons an array of PHYBeacon's within proximity of the device
 * @param region a PHY region
 */
- (void)phyManager:(PHYLocationManager *)manager didRangeBeacons:(NSArray *)beacons inRegion:(PHYRegion *)region;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYLocationmanager object
 * @param region a PHY region
 * @param error the error returned
 */
- (void)phyManager:(PHYLocationManager *)manager rangingBeaconsDidFailForRegion:(PHYRegion *)region withError:(NSError *)error;

@end