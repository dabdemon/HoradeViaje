//////////////////////////////////
//DEFINE AND INITALIZE VARIABLES//
//////////////////////////////////
var apikey = "AIzaSyBjakdvAf_X_MnC6UnurVlV-muBtD4b_I8";
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
	console.log("getDualTimeZone URL: " + url);
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
					var tz = (dstOffset + rawOffset)/3600; //check the daylight saving time

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

function Send2Pebble(Action,dualname, dualtz,dualtzname,localname,localtz,localtzname, localtemp, dualtemp){
	
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
		});
	}
	else if (Action == 2) { //Refresh Weather data
		Pebble.sendAppMessage({
							"localtemp" : localtemp,
							"dualtemp" : dualtemp,
		});
		
	}
	
}


function initialize(){
	var timestamp = getTimeStamp();
	//Get Local Position
	var localpos = getPosition("Navalcarnero");
	//Get Dual Position
	var dualpos = getPosition("Mountain View");
	//Get Local Timezone
	var localtz = getTimeZone(localpos[2],timestamp);
	//Get Dual Timezone
	var dualtz = getTimeZone(dualpos[2],timestamp);
	
	//Get Weather for Local Zone
	var localweather = getWeatherFromLatLong(localpos[0], localpos[1]);
	
	//Get Weather for Dual Zone
	var dualweather = getWeatherFromLatLong(dualpos[0], dualpos[1]);
	
	//Send messages to Pebble
	console.log("Local Name: " + "Navalcarnero");
	console.log("Local TZ: " + localtz[0]);
	console.log("Local TZ Name: " + localtz[1]);
	console.log("Dual Name: " + "Mountain View");
	console.log("Dual TZ: " + dualtz[0]);
	console.log("Dual TZ Name: " + dualtz[1]);
	console.log("Local Temp: " + localweather[0]);
	console.log("Local Icon: " + localweather[1]);
	console.log("Local Temp: " + dualweather[0]);
	console.log("Local Icon: " + dualweather[1]);
	
	Send2Pebble(1,"Mountain View", dualtz[0], dualtz[1], "Navalcarnero", localtz[0], localtz[1], localweather[0], dualweather[0]);
	


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
        if (response) {
			woeid = response.query.results.Result.woeid;
			
			
			temp = getWeatherFromWoeid(woeid);
			return temp;
        }
      } else {
        console.log("unable to get woeid from Yahoo! API");
		  return "999";
		
      }
    }

}

//Retrieves the Weather data from Yahoo! Weather//
function getWeatherFromWoeid(woeid) {
	
	/*if Hong Kong then override the woeid with a valid one*/
	if (woeid ==24865698){woeid=12467924;}
	var celsius = 'celsius';
	
	
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
	
	//Get Local Position
	var localpos = getPosition("Navalcarnero");
	//Get Dual Position
	var dualpos = getPosition("Mountain View");
	
	//Get Weather for Local Zone
	var localweather = getWeatherFromLatLong(localpos[0], localpos[1]);
	
	//Get Weather for Dual Zone
	var dualweather = getWeatherFromLatLong(dualpos[0], dualpos[1]);
	
	Send2Pebble(2,"Mountain View", null, null, "Navalcarnero", null, null, localweather[0], dualweather[0]);
	
}


///////////////////////////////////////
//Setup the connection with the watch//
///////////////////////////////////////

//Receive the Pebble's call to refresh the weather info
Pebble.addEventListener("appmessage",
                        function(e) {
                          updateWeather();
                        });

//Initiate the Appsync (This event is called just once)
Pebble.addEventListener("ready", function(e) {
	console.log("connect!" + e.ready);
	initialize();
	
	
});
