import React from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  RefreshControl
} from 'react-native';
import {Card, CardItem, Thumbnail } from 'native-base';
import ParallaxView from 'react-native-parallax-view';
import { NativeModules } from 'react-native';
import { NativeAppEventEmitter } from 'react-native';

const PhyBridge = NativeModules.PhyBridge;
const API_KEY = "YOUR_API_KEY";

const Museum = React.createClass({

  getInitialState() {
    return({
      beacons: [],
      refreshing: false,
      tempBeaconList: []
    });
  },

  componentDidMount() {
    PhyBridge.initPhyManagerWithApiKey(API_KEY);
    NativeAppEventEmitter.addListener('BeaconsFound', (beacons) => {
      this.setState({tempBeaconList: JSON.parse(beacons)});
    });
    PhyBridge.startScanningForBeacons();
    this.setState({refreshing: true});
    setTimeout(() => {
      PhyBridge.stopScanningForBeacons()
      this.setState({refreshing: false});
      this.setState({beacons: this.state.tempBeaconList});
    }, 3000);
  },

  componentWillUnmount() {
    PhyBridge.stopScanningForBeacons();
  },

  scanForBeacons() {
    if (!this.state.refreshing) {
      this.setState({refreshing: true});
      PhyBridge.stopScanningForBeacons();
      PhyBridge.startScanningForBeacons();
      setTimeout(() => {
        this.setState({refreshing: false});
        PhyBridge.stopScanningForBeacons()
        this.setState({beacons: this.state.tempBeaconList});
      }, 3000);
    }
  },

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
});

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

AppRegistry.registerComponent('Museum', () => Museum);
