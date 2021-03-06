//////////////////////////////////
//DEFINE AND INITALIZE VARIABLES//
//////////////////////////////////
var apikey = "AIzaSyBjakdvAf_X_MnC6UnurVlV-muBtD4b_I8";
var localtimezone;
var localtzname;
var dualtimezone;
var dualtzname;

var locallat;
var locallng;
var localpos;

var CLEAR_DAY = 0;
var CLEAR_NIGHT = 1;
var WINDY = 2;
var COLD = 3;
var HOT = 4;
var PARTLY_CLOUDY_DAY = 5;
var PARTLY_CLOUDY_NIGHT = 6;
var FOG = 7;
var RAIN = 8;
var SNOW = 9;
var SLEET = 10;
var SNOW_SLEET = 11;
var RAIN_SLEET = 12;
var RAIN_SNOW = 13;
var CLOUDY = 14;
var STORM = 15;
var NA = 16;
var DRIZZLE = 17;

var imageId = {
  0 : STORM, //tornado
  1 : STORM, //tropical storm
  2 : STORM, //hurricane
  3 : STORM, //severe thunderstorms
  4 : STORM, //thunderstorms
  5 : RAIN_SNOW, //mixed rain and snow
  6 : RAIN_SLEET, //mixed rain and sleet
  7 : SNOW_SLEET, //mixed snow and sleet
  8 : RAIN_SLEET, //freezing drizzle
  9 : DRIZZLE, //drizzle
  10 : RAIN_SLEET, //freezing rain
  11 : RAIN, //showers
  12 : RAIN, //showers
  13 : SNOW, //snow flurries
  14 : SNOW, //light snow showers
  15 : SNOW, //blowing snow
  16 : SNOW, //snow
  17 : SLEET, //hail
  18 : SLEET, //sleet
  19 : FOG, //dust
  20 : FOG, //foggy
  21 : FOG, //haze
  22 : FOG, //smoky
  23 : WINDY, //blustery
  24 : WINDY, //windy
  25 : COLD, //cold
  26 : CLOUDY, //cloudy
  27 : CLOUDY, //mostly cloudy (night)
  28 : CLOUDY, //mostly cloudy (day)
  29 : PARTLY_CLOUDY_NIGHT, //partly cloudy (night)
  30 : PARTLY_CLOUDY_DAY, //partly cloudy (day)
  31 : CLEAR_NIGHT, //clear (night)
  32 : CLEAR_DAY, //sunny
  33 : CLEAR_NIGHT, //fair (night)
  34 : CLEAR_DAY, //fair (day)
  35 : SNOW_SLEET, //mixed rain and hail
  36 : HOT, //hot
  37 : STORM, //isolated thunderstorms
  38 : STORM, //scattered thunderstorms
  39 : STORM, //scattered thunderstorms
  40 : STORM, //scattered showers
  41 : SNOW, //heavy snow
  42 : SNOW, //scattered snow showers
  43 : SNOW, //heavy snow
  44 : CLOUDY, //partly cloudy
  45 : STORM, //thundershowers
  46 : SNOW, //snow showers
  47 : STORM, //isolated thundershowers
  3200 : NA, //not available
};

//////////////////////////	
//Retrieve user settings//
//////////////////////////

var options = JSON.parse(localStorage.getItem('options'));
//console.log('read options: ' + JSON.stringify(options));
if (options === null) options = {	'use_gps' : "false",
									"localpos" : "madrid", //default to "Madrid"
									"dualpos" : "mountain view", //default to "Mountain View"
									"units" : "celsius",
									"key" : "",
									"weather" : "false"
};



//////////////////////
//Retrieve timezones//
//////////////////////



function ShortTimeZone(TZ)
{
	
	//Correct Google's names for get the right abbreviation
	if (TZ=="Central European Standard Time"){TZ="Central European Time";}
	else if (TZ=="Western European Standard Time"){TZ="Western European Time";}
	else if (TZ=="Eastern European Standard Time"){TZ="Eastern European Time";}	
	else if (TZ=="Moscow Standard Time"){TZ="Moscow Standard Kime";} //This is to trick the code and get MSK
	else if (TZ=="Moscow Summer Time"){TZ="Moscow Summer Dime";} //This is to trick the code and get MSD (Not longer user but... who knows?)
	
	
	//Format the Timezones before sending to Pebble
	var temp = TZ.substr(0,1);

	var i=0;
	while (i < TZ.length) {
		var pos = TZ.indexOf(" ",i);
		if (i==pos) {temp = temp + TZ.substr(pos+1,1);}
		i++;
	}
	return temp.toUpperCase();		
					
	
}



function getTimeStamp(){
	//The following returns the number of seconds since the epoch.
	new Date().getTime();
	var timestamp = Date.now()/1000;
	console.log("timestamp: " + timestamp);
	
	return timestamp;
	
}


//Try to optimizd the code//
function getCityName(pos){
	
	var url = "http://maps.googleapis.com/maps/api/geocode/json?latlng=" + pos + "";
	console.log("get location URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, false);
	req.send();

		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					//var position = new Array({'lat' : response.results[0].geometry.location.lat,
					//						'long' : response.results[0].geometry.location.lng});

					var location = response.results[1].formatted_address;
					console.log("city: " + location);
					return location;
					}
				}
			}
}

function getLocationName(pos){
	
	var url = "http://maps.googleapis.com/maps/api/geocode/json?latlng=" + pos + "";
	console.log("get location URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, false);
	req.send();

		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					//var position = new Array({'lat' : response.results[0].geometry.location.lat,
					//						'long' : response.results[0].geometry.location.lng});

					var location = new Array(2);
					location[0] = response.results[0].address_components[1].short_name; //Street
					location[1] = response.results[0].address_components[2].short_name;//City
					location[2] = response.results[0].address_components[3].long_name; //Province
					//console.log("ya he rellenado el array y voy a leerlo");
					console.log("Street: " + location[0]);
					console.log("City: " + location[1]);
					console.log("Province: " + location[2]);
					return location;
					}
				}
			}
}

function getPosition(cityname){
	

	var url = "http://maps.googleapis.com/maps/api/geocode/json?address=[" + cityname.replace(" ","%20") + "]";
	console.log("get positon URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, false);
	req.send();

		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					//var position = new Array({'lat' : response.results[0].geometry.location.lat,
					//						'long' : response.results[0].geometry.location.lng});

					var position = new Array(2);
					position[0] = response.results[0].geometry.location.lat;
					position[1] = response.results[0].geometry.location.lng;
					position[2] = response.results[0].geometry.location.lat + ',' + response.results[0].geometry.location.lng;
					//console.log("ya he rellenado el array y voy a leerlo");
					console.log("latitude: " + position[0]);
					console.log("longitude: " + position[1]);
					console.log("position: " + position[2]);
					return position;
					}
				}
			}

}

function getTimeZone(position, timestamp){

	var url = "https://maps.googleapis.com/maps/api/timezone/json?location="+position+"&timestamp="+timestamp+"&key=" + apikey;
	console.log("getTimeZone URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	
	req.open('GET', url, false);
	req.send();
	
		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					var dstOffset = response.dstOffset;
					var rawOffset = response.rawOffset;
					console.log("dual dstOffset = " + dstOffset);
					console.log("dual rawOffset = " + rawOffset);
					console.log("dual name = " + response.timeZoneName);
					//var tz = (dstOffset + rawOffset)/3600; //check the daylight saving time
					
					var tz = (dstOffset + rawOffset); //check the daylight saving time

					var tzname = response.timeZoneName;
					tzname = ShortTimeZone(tzname);
					
					var timezone = new Array(2);
					timezone[0] = tz;
					timezone[1] = tzname;
			
					return timezone;
				
					}
				}
			}
}

function Send2Pebble(Action,dualname, dualtz,dualtzname,localname,localtz,localtzname, localtemp, dualtemp, localicon, dualicon){
	
	if (Action == 1) { //Initialize
	//send the values to the Pebble!!
		Pebble.sendAppMessage({
							"dualname" : dualname.toUpperCase(),
							"dualtz" : parseInt(dualtz),
							"dualtzname" : dualtzname,
							"localname" : localname.toUpperCase(),
							"localtz" : parseInt(localtz),
							"localtzname" : localtzname,
							"localtemp" : localtemp,
							"dualtemp" : dualtemp,
							"localicon" : localicon,
							"dualicon" : dualicon,
		});
	}
	else if (Action == 2) { //Refresh Weather data
		Pebble.sendAppMessage({
							"localtemp" : localtemp,
							"dualtemp" : dualtemp,
							"localicon" : localicon,
							"dualicon" : dualicon,
		});
		
	}
	
}


//Retrieve the weather based on the selected settings (GPS on/off)
var locationOptions = { "timeout": 15000, "maximumAge": 0, "enableHighAccuracy": true};

function useGPS() {

    window.navigator.geolocation.getCurrentPosition(locationSuccess,
                                                    locationError,
                                                    locationOptions);
}



function locationSuccess(pos) {
  var coordinates = pos.coords;
  var timestamp = getTimeStamp();
	
  console.log("location success");
	
	//Get Local Name
	var localname = getLocationName(coordinates.latitude + ',' + coordinates.longitude);
	//Get Dual Position
	var dualpos = getPosition(options['dualpos']);
	//Get Local Timezone
	var localtz = getTimeZone(coordinates.latitude + ',' + coordinates.longitude,timestamp);
	//Get Dual Timezone
	var dualtz = getTimeZone(dualpos[2],timestamp);
	
	if (options['weather'] == "true"){
		//Get Weather for Local Zone
		var localweather = getWeatherFromLatLong(coordinates.latitude, coordinates.longitude);

		//Get Weather for Dual Zone
		var dualweather = getWeatherFromLatLong(dualpos[0], dualpos[1]);

		//Send messages to Pebble
			console.log("Local Name: " + localname[1]);
			console.log("Local TZ: " + localtz[0]);
			console.log("Local TZ Name: " + localtz[1]);
			console.log("Dual Name: " + options['dualpos']);
			console.log("Dual TZ: " + dualtz[0]);
			console.log("Dual TZ Name: " + dualtz[1]);
			console.log("Local Temp: " + localweather[0]);
			console.log("Local Icon: " + localweather[1]);
			console.log("Local Temp: " + dualweather[0]);
			console.log("Local Icon: " + dualweather[1]);

		Send2Pebble(1,options['dualpos'], dualtz[0], dualtz[1], localname[1], localtz[0], localtz[1], localweather[0], dualweather[0], localweather[1], dualweather[1]);
	}
	else{
		Send2Pebble(1,options['dualpos'], dualtz[0], dualtz[1], localname[1], localtz[0], localtz[1], "    ", "    ", 18, 19);
	}
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);
}

function weatherGPS(){
	 window.navigator.geolocation.getCurrentPosition(weatherSuccess,
                                                    locationError,
                                                    locationOptions);	
}

function weatherSuccess(pos){
	var coordinates = pos.coords;
	//Get Local Name
	var localname = getLocationName(coordinates.latitude + ',' + coordinates.longitude);
	//Get Dual Position
	var dualpos = getPosition(options['dualpos']);
	
	//Get Weather for Local Zone
	var localweather = getWeatherFromLatLong(coordinates.latitude, coordinates.longitude);
	
	//Get Weather for Dual Zone
	var dualweather = getWeatherFromLatLong(dualpos[0], dualpos[1]);
	
	Send2Pebble(2,options['dualpos'], null, null, localname, null, null, localweather[0], dualweather[0], localweather[1], dualweather[1]);
	
}

function initialize(){
	var timestamp = getTimeStamp();
	
	if (options['use_gps'] == "true") {
		useGPS();
	}
	else{
		//Get Local Position
		var localpos = getPosition(options['localpos']);
		//Get Dual Position
		var dualpos = getPosition(options['dualpos']);
		//Get Local Timezone
		var localtz = getTimeZone(localpos[2],timestamp);
		//Get Dual Timezone
		var dualtz = getTimeZone(dualpos[2],timestamp);

		//Get Weather for Local Zone
		var localweather = getWeatherFromLatLong(localpos[0], localpos[1]);

		//Get Weather for Dual Zone
		var dualweather = getWeatherFromLatLong(dualpos[0], dualpos[1]);
	
	
		//Send messages to Pebble
		console.log("Local Name: " + options['localpos']);
		console.log("Local TZ: " + localtz[0]);
		console.log("Local TZ Name: " + localtz[1]);
		console.log("Dual Name: " + options['dualpos']);
		console.log("Dual TZ: " + dualtz[0]);
		console.log("Dual TZ Name: " + dualtz[1]);
		console.log("Local Temp: " + localweather[0]);
		console.log("Local Icon: " + localweather[1]);
		console.log("Local Temp: " + dualweather[0]);
		console.log("Local Icon: " + dualweather[1]);
	if (options['weather'] == "true"){
		Send2Pebble(1,options['dualpos'], dualtz[0], dualtz[1], options['localpos'], localtz[0], localtz[1], localweather[0], dualweather[0], localweather[1], dualweather[1]);
	}
	else{
		Send2Pebble(1,options['dualpos'], dualtz[0], dualtz[1], options['localpos'], localtz[0], localtz[1], "    ", "    ", 18, 19);
	}
	}


}

/////////////////////////
//Retreive Weather data//
/////////////////////////

//Get the WOEID & City name from Flickr when the GPS is ON
// accuracy =  World level is 1, Country is ~3, Region ~6, City ~11, Street ~16 
function getWeatherFromLatLong(latitude, longitude) {
  var response;
  var woeid = -1;
  var query = encodeURI("select woeid, county, city, street from geo.placefinder where text=\"" + latitude + "," + longitude +"\" and gflags=\"R\"");
	console.log("geo query: " + query);
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";
  var req = new XMLHttpRequest();
	var temp;
	
  req.open('GET', url, false);
  req.send();
    if (req.readyState == 4) {
      if (req.status == 200) {
        console.log(req.responseText);
        response = JSON.parse(req.responseText);
        if (response.query.results !== null) {
			woeid = response.query.results.Result.woeid;
			
			
			temp = getWeatherFromWoeid(woeid);
			return temp;
        }
		  else{
			  	console.log('Yahoo! geo.placefinder is not retriving a shit...');
			 	//if geo.placefinder is not working, try to get location from google and get the WOEID by city name.
				  var location = getCityName(latitude + ','+ longitude);
				  console.log("location name: " + location);
			  	  temp = getWeatherFromLocation(location);
			      console.log("bypassed temp: " + temp);
			  	  return temp;
		  }
      } else {
        console.log("unable to get woeid from Yahoo! API");
		  return "999";
		
      }
    }

}

function getWeatherFromLocation(location_name) {
	
//check the weather provider to define how to proceed

	//Yahoo! Weather	

		  console.log("Getting weather from Yahoo Weather");
		  var response;
		  var woeid = -1;
		  var query = encodeURI("select woeid, name from geo.places(1) where text=\"" + location_name + "\"");
		  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";
		  var req = new XMLHttpRequest();
		  var temperature;
	
		  req.open('GET', url, false);
		  req.send();
			if (req.readyState == 4) {
			  if (req.status == 200) {
				console.log(req.responseText);
				response = JSON.parse(req.responseText);
				if (response) {
					woeid = response.query.results.place.woeid;

					console.log("Call GetWeatherFromWoeid: woeid=" + woeid);
					temperature = getWeatherFromWoeid(woeid);
					console.log("temperature from Location: " + temperature);
					return temperature;
				}
			  } else {
				console.log("unable to get woeid from Yahoo! API");
			  }
			}	

}
//Retrieves the Weather data from Yahoo! Weather//
function getWeatherFromWoeid(woeid) {
	
	/*if Hong Kong then override the woeid with a valid one*/
	if (woeid ==24865698){woeid=12467924;}
	var celsius = options['units'] == 'celsius';
	
	
	//get today's conditions	
	var query = encodeURI("select  item.condition, item.forecast, astronomy, wind, atmosphere from weather.forecast where woeid = " + woeid +
                        " and u = " + (celsius ? "\"c\"" : "\"f\"") + " |truncate(count=4)");
	
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";

  var response;
	var temperature;
	var icon;
  var req = new XMLHttpRequest();
  console.log(url);
  req.open('GET', url, false);
  req.send();
	
    if (req.readyState == 4) {
      if (req.status == 200) {
        response = JSON.parse(req.responseText);
        if (response) {
			var channel = response.query.results.channel;

			temperature = channel[0].item.condition.temp + "\u00B0";
			//if current conditions are not retrieved, get the forecasted for the day icon
			if (channel[0].item.condition.code == 3200){icon = imageId[channel[0].item.forecast.code];}
			else {icon = imageId[channel[0].item.condition.code];}

	
			var weather = new Array(2);
			weather[0] = temperature;
			weather[1] = icon;
			
			return weather;
        }
      } else {
        console.log("Error WFW");
		  return "999";
      }
    }

}

function updateWeather(){
	
	if (options['use_gps'] == "true") {
		weatherGPS();
	}
	else{
		//Get Local Position
		var localpos = getPosition(options['localpos']);
		//Get Dual Position
		var dualpos = getPosition(options['dualpos']);
		

			//Get Weather for Local Zone
			var localweather = getWeatherFromLatLong(localpos[0], localpos[1]);

			//Get Weather for Dual Zone
			var dualweather = getWeatherFromLatLong(dualpos[0], dualpos[1]);
			
			Send2Pebble(2,options['dualpos'], null, null, options['localpos'], null, null, localweather[0], dualweather[0], localweather[1], dualweather[1]);
		
	}
}

function CheckUserKey()
{
	var lt = 0;
	var key = options['key'];
	var token = Pebble.getAccountToken();
	var decrypt;
	
	//if there is not user key, then license is 0
	if ((key==undefined)||(key==null)||(key=="")||(key=="undefined")){key="00000000000"}
	//check the user key

	//extract the key from the Account token
	decrypt = token.substring(10,11) + token.substring(2,3) + token.substring(7,8) + token.substring(14,15) + token.substring(0,1);
	decrypt = decrypt + key.substring(5,6);
	decrypt = decrypt + token.substring(1,2) + token.substring(8,9) + token.substring(5,6) + token.substring(3,4) + token.substring(6,7)

	if (decrypt == key) {lt = key.substring(5,6);}
	else {lt = 0;
		 }
	
	//confirm that the javascript code works fine
	//options['key']=decrypt;

	
	console.log("Key: " + key + " Decrypt: " + decrypt + " LT: " + lt);
	
	return lt;
}

///////////////////////////////////////
//Setup the connection with the watch//
///////////////////////////////////////
//Displays the configuration page in the phone
Pebble.addEventListener('showConfiguration', function(e) {
  var uri = 'http://dabdemon.github.io/HoradeViaje/development.html?' + //Here you need to enter your configuration webservice
	'&use_gps=' + encodeURIComponent(options['use_gps']) +
    '&localpos=' + encodeURIComponent(options['localpos']) +
	'&dualpos=' + encodeURIComponent(options['dualpos']) +
    '&units=' + encodeURIComponent(options['units']) +
	'&UUID=' + encodeURIComponent(Pebble.getAccountToken()) +
	'&lt=' + encodeURIComponent(CheckUserKey()) +
	'&key=' + encodeURIComponent(options['key']) +
	'&weather=' + encodeURIComponent(options['weather']);

	//console.log('showing configuration at uri: ' + uri);

  Pebble.openURL(uri);
});

//Retrieve user settings after submitting
Pebble.addEventListener('webviewclosed', function(e) {
  if (e.response) {
    options = JSON.parse(decodeURIComponent(e.response));
    localStorage.setItem('options', JSON.stringify(options));
    console.log('storing options: ' + JSON.stringify(options));
    initialize();
  } else {
    console.log('no options received');
  }
});

//Receive the Pebble's call to refresh the weather info
Pebble.addEventListener("appmessage",
                        function(e) {
							if (options['weather'] == "true"){updateWeather();}
                        });

//Initiate the Appsync (This event is called just once)
Pebble.addEventListener("ready", function(e) {
	console.log("connect!" + e.ready);
	initialize();
});
