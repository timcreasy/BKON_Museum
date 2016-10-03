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
import ParallaxScrollView from 'react-native-parallax-scroll-view';


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
      beacons: [],
      refreshing: false,
      tempBeaconList: []
    });
  },

  listenForBeacons() {
    NativeAppEventEmitter.addListener('BeaconsFound', (beacons) => {
      // if (this.state.scanNo === 1 || this.state.scanNo % 2 === 0) {
      //   console.log("BEACONS:", beacons);
      //   console.log("SCANNO:", this.state.scanNo);
      //   this.setState({ beacons: JSON.parse(beacons) });
      // }
      // this.setState({scanNo: this.state.scanNo + 1});

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
    }, 4000);
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
        console.log("STOPPING");
        this.setState({refreshing: false});
        PhyBridge.stopScanningForBeacons()
        this.setState({beacons: this.state.tempBeaconList});
      }, 7000);
    }
  },

  onRefresh() {
    // this.setState({refreshing: true});
    this.scanForBeacons();
    // fetchData().then(() => {
    //   this.setState({refreshing: false});
    // });
  },

       /*   <ParallaxScrollView
            backgroundColor="white"
            contentBackgroundColor="white"
            parallaxHeaderHeight={300}
            refreshControl={
              <RefreshControl
                refreshing={this.state.refreshing}
                onRefresh={this.onRefresh}
              />
            }
            renderForeground={() => (
             <View style={{ height: 300, flex: 1, alignItems: 'center', justifyContent: 'center' }}>
                <Text>Hello World!</Text>
              </View>
            )}>
            <View style={{ height: 500 }}>
              <Text>Scroll me</Text>
            </View>
          </ParallaxScrollView> */
  render() {
    return (
      <View style={styles.container}>

     <ParallaxView
          backgroundSource={require('./imgs/museum.jpg')}
          windowHeight={300}
          refreshControl={
              <RefreshControl
                refreshing={this.state.refreshing}
                onRefresh={this.onRefresh}
              />
          }
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
