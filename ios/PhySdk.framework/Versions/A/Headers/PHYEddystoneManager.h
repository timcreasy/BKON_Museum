//
//  PHYEddystoneManager.h
//  PhySdk
//
//  Created by Beat Zenerino on 2/11/16.
//  Copyright © 2016 BKON Connect Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class PHYEddystoneBeacon;

@protocol PHYEddystoneManagerDelegate;

/**
 * The PHYEddystoneManager class is used to discover Eddystone beacons and query their
 * approximate distance to the iPhone.
 */
@interface PHYEddystoneManager : NSObject

@property (weak, nonatomic) id<PHYEddystoneManagerDelegate> delegate;


/**
 * Initializes the PHYLocationManager with an API key. You can obtain an
 * API key from https://phy.net
 *
 * @param apiKey The key associated with your application
 */
- (id)initWithApiKey:(NSString *)apiKey;

/**
 * Start looking for beacons. After calling this function the
 * PHYEddystoneManager will start returning the URL for any beacons found
 * through the delegate function 'didScanBeacons'.
 */
- (void)startScanningForBeacons;

/**
 * Start scanning for beacons. After calling this function the
 * PHYEddystoneManager will start returning metadata for any beacons found
 * through the delegate function 'didScanBeaconsWithMetadata'.
 */
- (void)startScanningForBeaconsWithMetadata;

/**
 * Start scanning for beacons. After calling this function the
 * PHYEddystoneManager will start returning metadata for any beacons found
 * through the delegate function 'didScanBeaconsWithMetadata'.
 *
 * @param vc The modal window will be added to this ViewController
 */
- (void)startScanningForBeaconsInModalView:(UIViewController *)vc;

/**
 * Stops scanning for beacons.
 */
- (void)stopScanningForBeacons;

/**
 * Add a user id to the scan URL
 *
 * @param userId a user id string
 */
- (void)addUserId:(NSString *)userId;

/**
 * Add a tag to the scan URL
 *
 * @param value the value for the tag
 * @param tag the tag
 */
- (void)setValue:(NSString *)value forTag:(NSString *)tag;

/**
 * Remove a tag from the scan URL
 *
 * @param tag a tag
 */
- (void)removeTag:(NSString *)tag;

/**
 * Returns a dictionary of current tags
 */
- (NSDictionary *)allTags;

/**
 * Set initial scan mode.
 *
 * @ param delayReport set initial delay and sort
 *
 * true = wait to gather beacons and sort according to distance before reporting:
 * false = report beacons immediately after they are found.
 */
- (void)setDelayedReport:(Boolean)delayReport;

- (void)didResolveUrl:(PHYEddystoneBeacon *)beacon;
- (void)didFetchFavicon;

@end


/**
 * The PHYEddystoneManagerDelegate is used to listen to beacon events from the
 * PHYEddystoneManager.
 */
@protocol PHYEddystoneManagerDelegate <NSObject>

@optional

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYEddystoneManager object
 * @param beacons an array of EddystoneBeacon's within proximity of the device
 */
- (void)phyManager:(PHYEddystoneManager *)manager didScanBeacons:(NSArray *)beacons;

/**
 * Invoked when the device enters the proximity of a beacon.
 *
 * @param manager the PHYEddystoneManager object
 * @param beacons an array of EddystoneBeacon's within proximity of the device
 */
- (void)phyManager:(PHYEddystoneManager *)manager didScanBeaconsWithMetadata:(NSArray *)beacons;

- (void)didFetchFavicon;

@end
