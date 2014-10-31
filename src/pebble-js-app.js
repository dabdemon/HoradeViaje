//////////////////////////////////
//DEFINE AND INITALIZE VARIABLES//
//////////////////////////////////
var apikey = "AIzaSyBjakdvAf_X_MnC6UnurVsdadfasdlV-muBtD4b_I8";
var localtimezone;
var localtzname;
var dualtimezone;
var dualtzname;

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
if (options === null) options = {	"local" : "Madrid", //default to "Madrid"
									"dual" : "Mountain View" //default to "Mountain View"
};


//////////////////////
//Retrieve timezones//
//////////////////////

function getLocalTimeZone(position, timestamp, localname){

	var url = "https://maps.googleapis.com/maps/api/timezone/json?location="+position+"&timestamp="+timestamp+"&key=" + apikey;
	console.log("getLocalTimeZone URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.send();
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					var dstOffset = response.dstOffset;
					var rawOffset = response.rawOffset;
					console.log("local dstOffset = " + dstOffset);
					console.log("local rawOffset = " + rawOffset);
					localtimezone = (dstOffset + rawOffset)/3600; //check the daylight saving time
					console.log("localtimezone = " + localtimezone);
					localtzname = response.timeZoneName;
					console.log("localtzname = " + localtzname);
					
					getDualPosition("mountain view", timestamp, localname, localtimezone, localtzname); 
		
					//send the values to the Pebble!!
				//	Pebble.sendAppMessage({
				//		"localname" : localname,
				//		"localtz" : localtimezone,
				//		"localtzname" : localtzname,
				//	});
	
					}
				}
			}
		};
}

function ShortTimeZone(TZ)
{
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

function getDualTimeZone(position, timestamp, dualzone, localzone, localtz, localtzname){

	var url = "https://maps.googleapis.com/maps/api/timezone/json?location="+position+"&timestamp="+timestamp+"&key=" + apikey;
	console.log("getDualTimeZone URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.send();
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					var dstOffset = response.dstOffset;
					var rawOffset = response.rawOffset;
					console.log("dual dstOffset = " + dstOffset);
					console.log("dual rawOffset = " + rawOffset);
					dualtimezone = (dstOffset + rawOffset)/3600; //check the daylight saving time
					console.log("dualtimezone = " + dualtimezone);
					dualtzname = response.timeZoneName;
					console.log("dualtzname = " + dualtzname);
					console.log("localtz = " + localtz);
					
					dualtzname = ShortTimeZone(dualtzname);
					localtzname = ShortTimeZone(localtzname);
					
					console.log("local timezone: " + localtzname);
					console.log("dual timezone: " + dualtzname);
					
					
					//send the values to the Pebble!!
					Pebble.sendAppMessage({
						"dualname" : dualzone.toUpperCase(),
						"dualtz" : parseInt(dualtimezone),
						"dualtzname" : dualtzname,
						"localname" : localzone.toUpperCase(),
						"localtz" : parseInt(localtz),
						"localtzname" : localtzname,
					});
			
				
					}
				}
			}
		};
}


function getLocalPosition(localname, timestamp){

	var url = "http://maps.googleapis.com/maps/api/geocode/json?address=[" + localname.replace(" ","%20") + "]";
	console.log("LocalPosition URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.send();
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					var position = response.results[0].geometry.location.lat +","+ response.results[0].geometry.location.lng;
					console.log("localpos: " + position);
					
					getLocalTimeZone(position, timestamp, localname);
					}
				}
			}
		};
}

function getDualPosition(dualname, timestamp,  localzone, localtz, localtzname){

	var url = "http://maps.googleapis.com/maps/api/geocode/json?address=[" + dualname.replace(" ","%20") + "]";
	console.log("DualPosition URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.send();
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					var position = response.results[0].geometry.location.lat +","+ response.results[0].geometry.location.lng;
					console.log("dualpos: " + position);
					
					getDualTimeZone(position, timestamp, dualname, localzone, localtz, localtzname);
					}
				}
			}
		};
}

function getTimeZones(){
	//The following returns the number of seconds since the epoch.
	new Date().getTime();
	var timestamp = Date.now()/1000;
	console.log("timestamp: " + timestamp);
	
	getLocalPosition("navalcarnero", timestamp);
	//getDualPosition("mountain view", timestamp);

	
}


function initialize(){
	//get the timezones
	getTimeZones();
	//get the weather


}


///////////////////////////////////////
//Setup the connection with the watch//
///////////////////////////////////////

//Initiate the Appsync (This event is called just once)
Pebble.addEventListener("ready", function(e) {
	console.log("connect!" + e.ready);
	initialize();
	
});
