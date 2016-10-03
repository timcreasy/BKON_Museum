import React from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  Image,
  RefreshControl
} from 'react-native';
import {Card, CardItem, Thumbnail } from 'native-base';
import ParallaxView from 'react-native-parallax-view';
import { NativeModules } from 'react-native';
import { NativeAppEventEmitter } from 'react-native';

const PhyBridge = NativeModules.PhyBridge;
const API_KEY = "51fd9f81-3d04-5c1b-8cd3-d86a3ea04453";

const Museum = React.createClass({

  getInitialState() {
    return({
      beacons: [],
      refreshing: false,
      tempBeaconList: []
    });
  },

  listenForBeacons() {
    NativeAppEventEmitter.addListener('BeaconsFound', (beacons) => {
      this.setState({tempBeaconList: JSON.parse(beacons)});
    });
  },

  componentDidMount() {
    PhyBridge.initPhyManagerWithApiKey(API_KEY);
    this.listenForBeacons();
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
    if (this.state.refreshing != true) {
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

  onRefresh() {
    this.scanForBeacons();
  },

  render() {
    return (
    <View style={styles.container}>
     <ParallaxView
          backgroundSource={require('./imgs/museum2.jpg')}
          windowHeight={300}
          refreshControl={
              <RefreshControl
                refreshing={this.state.refreshing}
                onRefresh={this.onRefresh}
              />
          } >
          <View style={styles.exhibitsContainer}>

           <Text style={styles.exhibitsHeader}>Exhibits Near You</Text>
              {
              this.state.beacons.map((beacon, index) => {

                const favicon = beacon.faviconUrl;

                return (

                  <Card key={index}>
                    <CardItem button onPress={() => console.log("Exhibit selected")}>
                      <Thumbnail source={{uri: favicon}} />
                      <Text>{beacon.title}</Text>
                    </CardItem>
                    <CardItem cardBody button onPress={() => console.log("Exhibit selected")}>
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
  header: {
    flex: 1,
    flexDirection: 'column',
    justifyContent: 'flex-end',
    paddingHorizontal: 100,
    paddingVertical: 24
  },
  headerText: {
    fontSize: 24,
    fontWeight: 'bold',
    color: '#253137'
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
  },
  beaconCard: {
    flex: 1
  },
  beaconTextContainer: {
    flex: 1
  },
  title: {
    fontSize: 15,
    backgroundColor: 'transparent'
  }
});

AppRegistry.registerComponent('Museum', () => Museum);
