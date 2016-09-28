#import "PhyBridge.h"
#import "RCTLog.h"
#import "RCTBridge.h"
#import "RCTEventDispatcher.h"

@interface PhyBridge()

@property PHYEddystoneManager *phyManager;

@end

@implementation PhyBridge

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(initPhyManagerWithApiKey:(NSString *)apiKey)
{
  // INSTANTIATE phyManager
  _phyManager = [[PHYEddystoneManager alloc] initWithApiKey:apiKey];
  _phyManager.delegate = self;
}

RCT_EXPORT_METHOD(startScanningForBeacons)
{
  RCTLogInfo(@"Starting scan for beacons");
  [_phyManager startScanningForBeaconsWithMetadata];
}

RCT_EXPORT_METHOD(stopScanningForBeacons)
{
  RCTLogInfo(@"Stoping scan for beacons");
  [_phyManager stopScanningForBeacons];
}


// CALLED WHEN BEACONS FOUND
- (void)phyManager:(PHYEddystoneManager *)manager didScanBeacons:(NSArray *)beacons {
  
    NSMutableArray* beaconsArray = [NSMutableArray array];
    for (int i = 0; i < beacons.count; i++)
    {
      PHYEddystoneBeacon *beacon = beacons[i];

      id null = [NSNull null];
      NSDictionary *dict =  [NSDictionary dictionaryWithObjectsAndKeys:
                              (beacon.scanUrl ?: null),@"scanUrl",
                              (beacon.txPowerLevel ?: null),@"txPowerLevel",
                              (beacon.rssi ?: null),@"rssi",
                              (beacon.title ?: null),@"title",
                              (beacon.hasMetadata ?: null),@"hasMetadata",
                              (beacon.destinationUrl ?: null),@"destinationUrl",
                              (beacon.faviconUrl ?: null),@"faviconUrl",
                              (beacon.desc ?: null),@"desc",
                              (beacon.jsonLd ?: null),@"jsonLd",
                              nil];
      
      [beaconsArray addObject:dict];
    }
    
    // JSONify beacon data
    NSError *error = nil;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:beaconsArray
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
  
    NSLog(@"%@", jsonString);

    [self.bridge.eventDispatcher sendAppEventWithName:@"BeaconsFound" body:jsonString];
  
}

@end
