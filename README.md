### Quickly Build a Physical Web Application With BKON and React Native

#### Introduction
As software continues to find it's way into our everyday lives, afordable tools such as the BKON A1 make integration with the Physical Web an easy experience.

This guide aims to show how quickly powerful applications can be built utilizing the Physical Web, as the shift towards a mobile world ever increases.

[BKON](https://bkon.com/) is a company based in Nashville, TN., producing hardware and software for the physical web.  [React Native](https://facebook.github.io/react-native/) is a framework to quickly build native mobile applications using React.

#### Requirements
To build a React Native application, the React Native command line interface must be installed.  A getting started guide can be found [here](https://facebook.github.io/react-native/docs/getting-started.html#content).

To use the BKON Mobile SDK, sign up for an account at [PHY.net](https://www.phy.net/).

The completed code for this project can be found [here](https://github.com/timcreasy/BKON_Museum).

#### Set Up
For the purposes of this guide, we will narrow our focus to an iOS application with React Native. This guide assumes a basic working knowledge of React Native, a detailed getting started guide can be found [here](https://facebook.github.io/react-native/docs/getting-started.html). Although there are many use cases for beacon technology, a Museum application will demonstrate the interactivity with the BKON SDK.  Our users will have a Museum application, which displays all exhibits nearby, as broadcast by a BKON A1.

Begin by initializing a React Native application using the React Native command line utility (we will be calling this project Museum for here out, but please note this can be a name of your choice):
```bash
react-native init Museum
```

Once the initializes completes, open your project in your favorite editor.  React Native comes with a very useful hot reloading feature, which speeds up application development, allowing reloading of minor changes.  This hot reloading depends on the start script which can be ran by the following commands (leave this running during development):
```bash
cd path/to/Museum
npm start
```

#### Building The View
React Native, like React, is a component based framework.  React Native comes with many basic components built in to the react-native module included in every project.  Also, many open-source components are availble, which allow for quick application development.

Our finished product will look like this:

![](http://i.imgur.com/POa1Ytd.gif)

Two open-source modules we will be using are [NativeBase](http://nativebase.io/) and [react-native-parallax-view](https://github.com/lelandrichardson/react-native-parallax-view).  Install both of these with npm:
```bash
npm install native-base react-native-parallax-view --save
```

Open the file:
```
index.io.js
```
Import these modules, along with React and React Native, at the top of the application.  Using [ES6 destructuring](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Destructuring_assignment), we will pull out only the components we need.
```jsx
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  RefreshControl
} from 'react-native';
import {Card, CardItem, Thumbnail } from 'native-base';
import ParallaxView from 'react-native-parallax-view';
```
In our main project directory, find an image to use as the header image, and place it in a folder titled:
```
imgs
```

In our applications main component render function, add the following code, which renders a fullscreen view with a header image with a parallax effect, and a view below which will contain a list of all beacons within proximity when complete:
```jsx
render() {
  return (
  <View style={styles.container}>
    <ParallaxView
      backgroundSource={require('./imgs/YOURIMAGE.jpg')}
      windowHeight={300} >
        <View style={styles.exhibitsContainer}>
          <Text style={styles.exhibitsHeader}>Exhibits Near You</Text>
        </View>
      </ParallaxView>
    </View>
  );
}
```

Create a StyleSheet object named 'styles', to hold all of our custom styles used within the application.

```jsx
const styles = StyleSheet.create({
  container: {
    flex: 1
  },
  exhibitsContainer: {
    paddingHorizontal: 10,
    paddingVertical: 20
  },
  exhibitsHeader: {
    fontSize: 20,
    fontWeight: 'bold',
    color: '#253137',
    paddingBottom: 15
  }
});
```
At this point, we are ready to write the code to bridge the native BKON Mobile SDK to be used in our application.

#### Bridging The BKON Mobile SDK

For as powerful a framework as React Native is, it does not include every feature one may need in mobile application development. Thankfully, the ability to [include native modules](https://facebook.github.io/react-native/docs/native-modules-ios.html) and existing native Objective-C or Swift code was included.  This section details how to write a bridging header file to use existing Objective-C methods from the BKON Mobile SDK in our React Native code.

Before beginning, make sure to download the most recent copy of the BKON Mobile SDK found [here](https://www.phy.net/sdk/physical-web-sdk-ios/), as well as review the documentation.

Open your projects .xcodeproj in Xcode, which can be found at:
```
ios/PROJECT_NAME.xcodeproj
```

In Xcode, navigate to File -> Add Files to "PROJECT_NAME"... to add the BKON Mobile SDK to our project:

![](http://i.imgur.com/3nBpk4d.png)

Navigate to your downloaded copy of the iOS SDK, and select the PhySdk.framework to add to your project.
![](http://i.imgur.com/uQf3e2H.png)

Next, we will create our bridging header file.  Navigate to File -> New -> File to create an Objective-C class.
![](http://i.imgur.com/DDoELM7.png)

Under iOS, create a new Cocoa Touch Class, and name it PhyBridge, making sure it inherits from NSObject:
![](http://i.imgur.com/cxYpA0M.png)

You will now have two newly created files in your project, PhyBridge.h and PhyBridge.m.  This Objective-C class will be what bridges the native BKON SDK to our React Native application.

Import the RCTBridgeModule header into our bridging header so that our PhyBridge.h looks like the following:
```objective-c
#import "RCTBridgeModule.h"
#import <PhySdk/PhySdk.h>

@interface PhyBridge : NSObject <RCTBridgeModule>
@end
```

Now we can begin work on writing the implementation of our bridge, and specifiying what methods we need to export to React Native.

To begin, our implementation file should look like the following:
```objective-c
#import "PhyBridge.h"
#import "RCTBridge.h"
#import "RCTEventDispatcher.h"

@interface PhyBridge()

@end

@implementation PhyBridge

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE();

@end
```

In the above, we are simply including the necessary React bridging headers, and specifying this as as a module for to be availble in our React Native code.

To begin working with the BKON SDK, let us first define a property for a PHYEddystoneManager to work with by changing the following:
```objective-c
@interface PhyBridge()
@property PHYEddystoneManager *phyManager;
@end
```

Then, we will export our first method to React Native! Every method we want to expose to React Native will be wrapped in RCT_EXPORT_METHOD():
```objective-c
RCT_EXPORT_METHOD(initPhyManagerWithApiKey:(NSString *)apiKey)
{
  _phyManager = [[PHYEddystoneManager alloc] initWithApiKey:apiKey];
  _phyManager.delegate = self;
}
```
This method, initPhyManagerWithApiKey, will accept an API key, and instantiate a PHYEddystoneManager object.

Our _phyManager object has two methods, startScanningForBeaconsWithMetadata and stopScanningForBeacons, which both start and stop a scanning for beacons within proximity.  We will need to expose these two methods to control when to begin and end a scan:
```objective-c
RCT_EXPORT_METHOD(startScanningForBeacons)
{
  [_phyManager startScanningForBeaconsWithMetadata];
}

RCT_EXPORT_METHOD(stopScanningForBeacons)
{
  [_phyManager stopScanningForBeacons];
}
```

Lastly, a method gets called anytime a beacon is withing proximity during a scan, and it is: didScanBeacons, which returns an NSArray of all beacons within proximity. Due to the asynchronous nature of this, we will need to instead emit an event any time this method fires (note how we included RCTEventDispatcher.h above).  Add the following code, and read ahead for an explanation:
```objective-c
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

    NSError *error = nil;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:beaconsArray
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];

    [self.bridge.eventDispatcher sendAppEventWithName:@"BeaconsFound" body:jsonString];
}
```
The code above does a few key things: First it iterates through each beacon passed in the 'beacons' array, and instantiates a PHYEddystoneBeacon object.  Next, a dictionary is created with key/value pairs of either the beacon data or null, and this dictionary is added to an NSMutableArray named beaconsArray.  Next, the beaconsArray is serialized to JSON, and converted to a string.  Lastly, this JSON data, containing all beacons within proximity, is emitted with the event name "BeaconsFound", to be able to be used in our JavaScript.

That's it! We can now use these methods and listen for the BeaconsFound event in our React Native code!

#### Using BKON Methods In React Native

Back in our React Native project, add the following modules to be imported along side our existing code:
```jsx
import { NativeModules } from 'react-native';
import { NativeAppEventEmitter } from 'react-native';
```

Through the NativeModules and NativeAppEventEmitter objects, we can interface with our native Objective-C code.

Create a variable which will have all of our exposed methods on it:
```jsx
const PhyBridge = NativeModules.PhyBridge;
```

Next, let's set up the initial state of our component, and add a few properties which we will later modify:
```jsx
getInitialState() {
  return({
    beacons: [],
    tempBeaconList: []
    refreshing: false,
  });
}
```

After that, let's define what needs to occur when our component initially mounts.  We will need to first, initiliaze our PHYEddystoneManager, through our exposed method.  Then, we will need to set up a listener for when beacons our within proximity, which will be called anytime our defined event is emitted.  Next, we start our scan for beacons, again through an exposed method, and after a delay of 4 seconds (4000 milliseconds), we will stop our scan.  The componentDidMount lifecycle method looks like this:
```jsx
componentDidMount() {
  // Initialize PHYEddystoneManager
  PhyBridge.initPhyManagerWithApiKey(API_KEY);
  // Set up event listener and define callback
  NativeAppEventEmitter.addListener('BeaconsFound', (beacons) => {
    // Add any beacons found to tempBeaconList array on state object
    this.setState({tempBeaconList: JSON.parse(beacons)});
  });
  // Start scanning for beacons
  PhyBridge.startScanningForBeacons();
  // Set refreshing state to true, to prevent a pull-to-refresh action during first load
  this.setState({refreshing: true});
  // Set a timeout of 4 seconds, then stop scan, set refreshing state to false to allow future refreshing, and set beacons array on state to be equal to tempBeaconList
  setTimeout(() => {
    PhyBridge.stopScanningForBeacons()
    this.setState({refreshing: false});
    this.setState({beacons: this.state.tempBeaconList});
  }, 4000);
}
```
NOTE: the 'refreshing' property on state defines when a pull-to-refresh has occured or is in progress

While we are at it, we want to ensure any scanning is stopped before our main component unmounts.  This can be added to the componentWillUnmount lifecycle method:
```jsx
componentWillUnmount() {
  PhyBridge.stopScanningForBeacons();
}
```

Next, let's define a method to be called when a pull-to-refresh has occured:
```jsx
scanForBeacons() {
  // If no current refresh is in progress
  if (!this.state.refreshing) {
    // Set refreshing to be true, stop any current scanning, and start new scan
    this.setState({refreshing: true});
    PhyBridge.stopScanningForBeacons();
    PhyBridge.startScanningForBeacons();
    // After 4 seconds, reset refreshing to false, stop scan, and set beacons array to be equal to the tempBeaconList array
    setTimeout(() => {
      this.setState({refreshing: false});
      PhyBridge.stopScanningForBeacons()
      this.setState({beacons: this.state.tempBeaconList});
    }, 4000);
  }
}
```

Lastly, let's update our components render method to incorporate the pull-to-refresh functionality, as well as a method to loop through the array stored at this.state.beacons and crete a formatted card component for each beacon within proximity.  The code is as follows:
```jsx
render() {
  return (
  <View style={styles.container}>
    <ParallaxView
      backgroundSource={require('./imgs/museum.jpg')}
      windowHeight={300}
      refreshControl={
        <RefreshControl
          refreshing={this.state.refreshing}
          onRefresh={this.scanForBeacons}
        />
      } >
      <View style={styles.exhibitsContainer}>
        <Text style={styles.exhibitsHeader}>Exhibits Near You</Text>
          {
            this.state.beacons.map((beacon, index) => {
              const favicon = beacon.faviconUrl;
              return (
                <Card key={index}>
                  <CardItem>
                    <Thumbnail source={{uri: favicon}} />
                    <Text>{beacon.title}</Text>
                  </CardItem>
                  <CardItem cardBody>
                    <Text>{beacon.desc}</Text>
                  </CardItem>
                </Card>
              );
            })
          }
        </View>
      </ParallaxView>
    </View>
  );
}
```

That's it! In just a short amount of time, we have created a mobile appliation which can communicate with the powerful mobile SDK provided by BKON and interface with the Physical Web.

The completed code for this project can be found [here](https://github.com/timcreasy/BKON_Museum).

#### Related Links
- [BKON]()
- [React Native](https://facebook.github.io/react-native/)
- [NativeBase](http://nativebase.io/)
- [react-native-parallax-view](https://github.com/lelandrichardson/react-native-parallax-view)

#### About The Author
Tim Creasy is a current student at [Nashville Software School](http://nashvillesoftwareschool.com/).  Specializing in MEAN stack development, he has an increasing interest in mobile application development.  His contact info can be found [here](http://timcreasy.com/), or he can be reached on [LinkedIn](https://www.linkedin.com/in/tim-creasy).
