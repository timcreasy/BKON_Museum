import React from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  Image
} from 'react-native';
import {Card, CardItem, Thumbnail } from 'native-base';
import ParallaxView from 'react-native-parallax-view';
import { NativeModules } from 'react-native';
import { NativeAppEventEmitter } from 'react-native';

const PhyBridge = NativeModules.PhyBridge;
const API_KEY = "51fd9f81-3d04-5c1b-8cd3-d86a3ea04453";

const Museum = React.createClass({

  searchForBeacons() {
    // Stop any previous scanning
    PhyBridge.stopScanningForBeacons();
    // Start scanning for beacons
    PhyBridge.startScanningForBeacons();
    // setTimeout(this.searchForBeacons, 5000);
  },

  getInitialState() {
    return({
      beacons: []
    });
  },

  listenForBeacons() {
    NativeAppEventEmitter.addListener('BeaconsFound', (beacons) => {
      this.setState({ beacons: JSON.parse(beacons) });
    });
  },

  componentDidMount() {
    PhyBridge.initPhyManagerWithApiKey(API_KEY);
    this.listenForBeacons();
    this.searchForBeacons();
  },

  componentWillUnmount() {
    PhyBridge.stopScanningForBeacons();
  },

  render() {
    return (
      <View style={styles.container}>
        <ParallaxView
          backgroundSource={require('./imgs/museum.jpg')}
          windowHeight={300}
          header={(
            <View style={styles.header}>
              <Text style={styles.headerText}>
                  Museum Tour
              </Text>
            </View>
          )} >
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
    paddingHorizontal: 20,
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
    fontSize: 18,
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
