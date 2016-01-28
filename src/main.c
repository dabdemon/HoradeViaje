#include "main.h"
#include <pebble.h>
#include "PDUtils.h"
#include "gbitmap_color_palette_manipulator.h"

//Pebble KEYS
enum TripTimeKeys {
	LOCAL_NAME_KEY = 0,       // TUPLE_CSTRING
	LOCAL_TZ_KEY = 1, 		// TUPLE_INT
	LOCAL_TZNAME_KEY = 2,     // TUPLE_CSTRING
	DUAL_NAME_KEY = 3,  		// TUPLE_CSTRING
	DUAL_TZ_KEY = 4, 			// TUPLE_INT
	DUAL_TZNAME_KEY = 5,  	// TUPLE_CSTRING
	LOCAL_TEMP_KEY = 6,     // TUPLE_CSTRING
	LOCAL_ICON_KEY = 7,     // TUPLE_INT
	DUAL_TEMP_KEY = 8,     // TUPLE_CSTRING
	DUAL_ICON_KEY = 9,     // TUPLE_INT
};

//Bitmaps
static const uint32_t WEATHER_ICONS[] = {
  RESOURCE_ID_ICON_CLEAR_DAY,
  RESOURCE_ID_ICON_CLEAR_NIGHT,
  RESOURCE_ID_ICON_WIND,
  RESOURCE_ID_ICON_COLD,
  RESOURCE_ID_ICON_HOT,
  RESOURCE_ID_ICON_PARTLY_CLOUDY_DAY,
  RESOURCE_ID_ICON_PARTLY_CLOUDY_NIGHT,
  RESOURCE_ID_ICON_FOG,
  RESOURCE_ID_ICON_RAIN,
  RESOURCE_ID_ICON_SNOW,
  RESOURCE_ID_ICON_SLEET,
  RESOURCE_ID_ICON_SNOW_SLEET,
  RESOURCE_ID_ICON_RAIN_SLEET,
  RESOURCE_ID_ICON_RAIN_SNOW,
  RESOURCE_ID_ICON_CLOUDY,
  RESOURCE_ID_ICON_THUNDER,
  RESOURCE_ID_ICON_NA,
  RESOURCE_ID_ICON_DRIZZLE,
  RESOURCE_ID_TakeOff,
  RESOURCE_ID_Landing,
}; 

/*
//number of available themes
#define theme_num = 2;
//Define the theme colors
uint8_t theme[4*theme_num]= {
    GColorMidnightGreen, GColorCadetBlue, GColorWhite, GColorBlack,   
    GColorPurple, GColorShockingPink, GColorWhite, GColorBlack
};
*/
	
//Variables
	static char localtime_text[] = "00:00";
	static char localweekday_text[] = "XXXXXXXXXXXX";
	static char localmonth_text[] = "XXXXXXXXXXXXX";

	static char dualtime_text[] = "00:00";
	static char dualweekday_text[] = "XXXXXXXXXXXX";
	static char dualmonth_text[] = "XXXXXXXXXXXXX";

	int localtz=0;
	int dualtz=0;
	int timediff=0; //dualtz-localtz

	char localname[] = "XXXXXXXXXXXXXXX";
	char dualname[] = "XXXXXXXXXXXXXXX";

	char LocalTZName[]  = "     ";
	char DualTZName[]  = "     ";

	char strLocalTemp[] = "     ";
    char strDualTemp[] = "     ";

	char strLocalAMPMInd[]  = "  ";
	char strDualAMPMInd[]  = "  ";

	static AppTimer *timer;
	uint32_t timeout_ms = 1800000; //30min (1min = 60000)

	// Setup messaging
	const int inbound_size = 512;
	const int outbound_size = 512;
	
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static GFont s_res_bitham_42_light;
static GFont s_res_bitham_30_black;
static GBitmap *s_res_takeoff;
static GBitmap *s_res_landing;
static TextLayer *LocalArea;
static TextLayer *DualArea;
static TextLayer *LocalTZ;
static TextLayer *LocalTemp;
static TextLayer *LocalTime;
static TextLayer *LocalAMPMInd;
static TextLayer *LocalDate;
static TextLayer *LocalDay;
static TextLayer *DualTime;
static TextLayer *DualAMPMInd;
static TextLayer *DualDate;
static TextLayer *DualDay;
static TextLayer *DualTemp;
static TextLayer *DualTZ;
static BitmapLayer *Local_img;
static BitmapLayer *Dual_img;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;

#define LOCAL_AREA	PBL_IF_ROUND_ELSE(GRect(0, 0, 180, 89),GRect(3, 9, 137, 75))
#define DUAL_AREA	PBL_IF_ROUND_ELSE(GRect(0,91, 180, 89),GRect(4, 93, 137, 70))
#define LOCAL_TIME	PBL_IF_ROUND_ELSE(GRect(33, 44, 95, 42),GRect(3, 49, 95, 42))
#define LOCAL_AMPM	PBL_IF_ROUND_ELSE(GRect(130, 50, 20, 20),GRect(100, 54, 20, 20))
#define LOCAL_TZ 	PBL_IF_ROUND_ELSE(GRect(130, 60, 20, 20),GRect(28, 20, 41, 14))
#define LOCAL_DATE 	PBL_IF_ROUND_ELSE(GRect(90, 35, 88, 16),GRect(11, 40, 98, 16))
#define LOCAL_DAY 	PBL_IF_ROUND_ELSE(GRect(0, 35, 75, 16),GRect(11, 30, 98, 16))
#define LOCAL_CITY 	PBL_IF_ROUND_ELSE(GRect(0, 73, 180, 16),GRect(28, 8, 111, 17))
#define LOCAL_TEMP 	PBL_IF_ROUND_ELSE(GRect(0, -4, 115, 45),GRect(50, 13, 90, 45))
#define LOCAL_ICON	PBL_IF_ROUND_ELSE(GRect(100, 20, 20, 20),GRect(4, 9, 20, 20))
#define DUAL_TIME	PBL_IF_ROUND_ELSE(GRect(33, 99, 95, 42),GRect(3, 130, 95, 42))
#define DUAL_AMPM	PBL_IF_ROUND_ELSE(GRect(130, 104, 20, 20),GRect(100, 135, 20, 20))
#define DUAL_TZ 	PBL_IF_ROUND_ELSE(GRect(130, 114, 41, 14),GRect(28, 102, 41, 14))
#define DUAL_DATE 	PBL_IF_ROUND_ELSE(GRect(90, 125, 88, 16),GRect(11, 122, 98, 16))
#define DUAL_DAY 	PBL_IF_ROUND_ELSE(GRect(0, 125, 75, 16),GRect(11, 112, 98, 16))
#define DUAL_CITY 	PBL_IF_ROUND_ELSE(GRect(0, 90, 180, 17),GRect(28, 91, 100, 17))
#define DUAL_TEMP 	PBL_IF_ROUND_ELSE(GRect(0, 130, 115, 45),GRect(50, 95, 90, 45))
#define DUAL_ICON	PBL_IF_ROUND_ELSE(GRect(100, 152, 20, 20),GRect(4, 94, 20, 20))


static void initialise_ui(void) {
  s_window = window_create();


  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_bitham_42_light = fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
    
  // LocalArea
  LocalArea = text_layer_create(LOCAL_AREA);
  text_layer_set_font(LocalArea, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalArea);
  
  // DualArea
  DualArea = text_layer_create(DUAL_AREA);
  text_layer_set_font(DualArea, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualArea);
  
  // LocalTZ
  LocalTZ = text_layer_create(LOCAL_TZ);
  text_layer_set_background_color(LocalTZ, GColorClear);
  text_layer_set_text(LocalTZ, LocalTZName);
  text_layer_set_font(LocalTZ, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalTZ);
  
  //Here it was LocalTemp
  
  // LocalTime
  LocalTime = text_layer_create(LOCAL_TIME);
  text_layer_set_background_color(LocalTime, GColorClear);
  text_layer_set_text(LocalTime, localtime_text);
  text_layer_set_text_alignment(LocalTime, GTextAlignmentRight);
  text_layer_set_font(LocalTime, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalTime);
	
	
  // LocalTime AM/PM Indicator
  LocalAMPMInd = text_layer_create(LOCAL_AMPM);
  text_layer_set_background_color(LocalAMPMInd, GColorClear);
  text_layer_set_text(LocalAMPMInd, strLocalAMPMInd);
  text_layer_set_text_alignment(LocalAMPMInd, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalAMPMInd);
  
  // LocalDate
  LocalDate = text_layer_create(LOCAL_DATE);
  text_layer_set_background_color(LocalDate, GColorClear);
  text_layer_set_text(LocalDate, localmonth_text);
  text_layer_set_font(LocalDate, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalDate);
  
  // LocalDay
  LocalDay = text_layer_create(LOCAL_DAY);
  text_layer_set_background_color(LocalDay, GColorClear);
  text_layer_set_text_alignment(LocalDay, PBL_IF_ROUND_ELSE(GTextAlignmentRight,GTextAlignmentLeft));
  text_layer_set_text(LocalDay, localweekday_text);
  text_layer_set_font(LocalDay, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalDay);
  
  // DualTime
  DualTime = text_layer_create(DUAL_TIME);
  text_layer_set_background_color(DualTime, GColorClear);
  text_layer_set_text(DualTime, dualtime_text);
  text_layer_set_text_alignment(DualTime, GTextAlignmentRight);
  text_layer_set_font(DualTime, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualTime);
	
  // DualTime AM/PM Indicator
  DualAMPMInd = text_layer_create(DUAL_AMPM);
  text_layer_set_background_color(DualAMPMInd, GColorClear);
  text_layer_set_text(DualAMPMInd, strDualAMPMInd);
  text_layer_set_text_alignment(DualAMPMInd, GTextAlignmentLeft);
  //text_layer_set_font(DualAMPMInd, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualAMPMInd);
	
  
  // DualDate
  DualDate = text_layer_create(DUAL_DATE);
  text_layer_set_background_color(DualDate, GColorClear);
  text_layer_set_text(DualDate, dualmonth_text);
  text_layer_set_font(DualDate, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualDate);
  
  // DualDay
  DualDay = text_layer_create(DUAL_DAY);
  text_layer_set_background_color(DualDay, GColorClear);
  text_layer_set_text_alignment(DualDay, PBL_IF_ROUND_ELSE(GTextAlignmentRight,GTextAlignmentLeft));
  text_layer_set_text(DualDay, dualweekday_text);
  text_layer_set_font(DualDay, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualDay);
  
  //Here it was DualTemp
  
  // DualTZ
  DualTZ = text_layer_create(DUAL_TZ);
  text_layer_set_text(DualTZ, DualTZName);
  text_layer_set_background_color(DualTZ, GColorClear);
  text_layer_set_font(DualTZ, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualTZ);
  
  // Local_img
  Local_img = bitmap_layer_create(LOCAL_ICON);
  bitmap_layer_set_bitmap(Local_img, s_res_takeoff);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Local_img);
	
  // Dual_img
  Dual_img = bitmap_layer_create(DUAL_ICON);
  bitmap_layer_set_bitmap(Dual_img, s_res_landing);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Dual_img);
	
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(LOCAL_CITY);
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, localname);
  text_layer_set_text_alignment(s_textlayer_1, PBL_IF_ROUND_ELSE(GTextAlignmentCenter,GTextAlignmentLeft));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(DUAL_CITY);
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, dualname);
  text_layer_set_text_alignment(s_textlayer_2, PBL_IF_ROUND_ELSE(GTextAlignmentCenter,GTextAlignmentLeft));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
	
	// LocalTemp
  LocalTemp = text_layer_create(LOCAL_TEMP); //(GRect(73, 15, 65, 42));
  text_layer_set_background_color(LocalTemp, GColorClear);
  text_layer_set_text(LocalTemp, strLocalTemp);
  text_layer_set_text_alignment(LocalTemp, GTextAlignmentRight);
  text_layer_set_font(LocalTemp, s_res_bitham_42_light);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalTemp);
	
	// DualTemp 
  DualTemp = text_layer_create(DUAL_TEMP); //(93,97,45,42) //GRect(73, 97, 65, 42))
  text_layer_set_background_color(DualTemp, GColorClear);
  text_layer_set_text(DualTemp, strDualTemp);
  text_layer_set_text_alignment(DualTemp, GTextAlignmentRight);
  text_layer_set_font(DualTemp, s_res_bitham_42_light);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualTemp);
	
	#ifdef PBL_COLOR
		window_set_background_color(s_window, GColorBlack);
		
	//LOCAL AREA
		text_layer_set_background_color(LocalArea, GColorOrange);
	
		text_layer_set_text_color(LocalTZ, GColorWhite);
		text_layer_set_text_color(LocalTime, GColorWhite);
		text_layer_set_text_color(LocalAMPMInd, GColorWhite);
		text_layer_set_text_color(LocalDate, GColorWhite);
		text_layer_set_text_color(LocalDay, GColorWhite);
		text_layer_set_text_color(s_textlayer_1, GColorWhite);
		text_layer_set_text_color(LocalTemp, GColorWhite);
	
		//bitmap_layer_set_compositing_mode(Local_img, GCompOpSet);
		//bitmap_layer_set_compositing_mode(Dual_img, GCompOpSet);
	//DUAL AREA
		text_layer_set_background_color(DualArea, GColorRajah);
	
		text_layer_set_text_color(DualTZ, GColorBlack);
		text_layer_set_text_color(DualTime, GColorBlack);
		text_layer_set_text_color(DualAMPMInd, GColorBlack);
		text_layer_set_text_color(DualDate, GColorBlack);
		text_layer_set_text_color(DualDay, GColorBlack);
		text_layer_set_text_color(s_textlayer_2, GColorBlack);
		text_layer_set_text_color(DualTemp, GColorBlack);
	
		replace_gbitmap_color(GColorWhite, GColorBlack, s_res_landing, Dual_img);
	#else
		window_set_background_color(s_window, GColorBlack);
		text_layer_set_background_color(LocalArea, GColorWhite);
		text_layer_set_background_color(DualArea, GColorWhite);	
	
		//bitmap_layer_set_compositing_mode(Local_img, GCompOpAssign);
		//bitmap_layer_set_compositing_mode(Dual_img, GCompOpAssign);
	#endif
	
		//APLITE runs FW3.X now.
		bitmap_layer_set_compositing_mode(Local_img, GCompOpSet);
		bitmap_layer_set_compositing_mode(Dual_img, GCompOpSet);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(LocalArea);
  text_layer_destroy(DualArea);
  text_layer_destroy(LocalTZ);
  text_layer_destroy(LocalTemp);
  text_layer_destroy(LocalTime);
  text_layer_destroy(LocalDate);
  text_layer_destroy(LocalDay);
  text_layer_destroy(DualTime);
  text_layer_destroy(DualDate);
  text_layer_destroy(DualDay);
  text_layer_destroy(DualTemp);
  text_layer_destroy(DualTZ);
  bitmap_layer_destroy(Local_img);
  bitmap_layer_destroy(Dual_img);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  gbitmap_destroy(s_res_takeoff);
  gbitmap_destroy(s_res_landing);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main(void) {
  window_stack_remove(s_window, true);
}

void getDualTime(){
	
	time_t actualPtr = time(NULL);

	
			//Read persistent storage to calculate the time difference
	
			if (persist_exists(LOCAL_TZ_KEY)){localtz = persist_read_int(LOCAL_TZ_KEY);} 
			if (persist_exists(DUAL_TZ_KEY)){dualtz = persist_read_int(DUAL_TZ_KEY);}
			
		
			timediff= dualtz - localtz;
	
			
			//Define and Calculate Time Zones
			//TIME ZONE 1
			struct tm *tzPtr = localtime(&actualPtr);
		
			tzPtr->tm_sec += timediff;
			//Since mktime() is not realible in Pebble's firmware, use PUtils to built the dual time.
			time_t dualtime = p_mktime(tzPtr);
			struct tm *tz1Ptr = gmtime(&dualtime);
	
	
			if (clock_is_24h_style()){strftime(dualtime_text, sizeof(dualtime_text), "%H:%M", tz1Ptr);}
			else {strftime(dualtime_text, sizeof(dualtime_text), "%I:%M", tz1Ptr);}
	

				//Remove the leading 0s
				if (dualtime_text[0]=='0') {memcpy(&dualtime_text," ",1);}
	
			//Calculate the Dual Zone Date
			char *sys_locale = setlocale(LC_ALL, "");

			if (strcmp("en_US", sys_locale) == 0) {
			  strftime(dualmonth_text,sizeof(dualmonth_text),"%B %e",tz1Ptr);
			
			} else {
			  strftime(dualmonth_text,sizeof(dualmonth_text),"%e %B",tz1Ptr);
			}
			
			strftime(dualweekday_text,sizeof(dualweekday_text),"%A",tz1Ptr);
	
	
			
	
			//DISPLAY THE TIME ZONES	
			text_layer_set_text(DualTime, dualtime_text);
			text_layer_set_text(DualDay,dualweekday_text);
			text_layer_set_text(DualDate,dualmonth_text); 
			if(!clock_is_24h_style()){strftime(strDualAMPMInd, sizeof(strDualAMPMInd), "%p", tz1Ptr);} 
}

//*********************************//
//** Get the current date & time **//
//*********************************//
void getDate()
{
	//Get the date
	time_t actualPtr = time(NULL);
	struct tm *tz1Ptr = localtime(&actualPtr);
	
	//get the local date
	char *sys_locale = setlocale(LC_ALL, "");
		
	if (strcmp("en_US", sys_locale) == 0) {
		strftime(localmonth_text,sizeof(localmonth_text),"%B %e",tz1Ptr);
			
	} else {
		strftime(localmonth_text,sizeof(localmonth_text),"%e %B",tz1Ptr);
	}
	
	strftime(localweekday_text,sizeof(localweekday_text),"%A",tz1Ptr);
	
	//set the layers
	text_layer_set_text(LocalDay,localweekday_text);
	text_layer_set_text(LocalDate,localmonth_text); 
}

void getTime()
	{
		clock_copy_time_string(localtime_text, sizeof(localtime_text));
			
		//Set the Local Time
        text_layer_set_text(LocalTime, localtime_text);
		
		//Set the Dual Time
		getDualTime();
	
}

//************************//
// Capture the Tick event //
//************************//
void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{

			//Set the AM/PM indicator
			//if(clock_is_24h_style()){memcpy(&ampm_text,  "24H", strlen("24H"));}
			//else {strftime(ampm_text, sizeof(ampm_text), "%p", tick_time);}
			//text_layer_set_text(ampm_layer, ampm_text); //Update the weekday layer  


       if (units_changed & MINUTE_UNIT)
       {

		   //update the time
		   //if(!clock_is_24h_style()){strftime(strLocalAMPMInd, sizeof(strLocalAMPMInd), "%p", tick_time);} 
		   
		   if (clock_is_24h_style()){strftime(localtime_text, sizeof(localtime_text), "%H:%M", tick_time);}
				else {strftime(localtime_text, sizeof(localtime_text), "%I:%M", tick_time);
					 strftime(strLocalAMPMInd, sizeof(strLocalAMPMInd), "%p", tick_time);}
	

				//Remove the leading 0s
				if (localtime_text[0]=='0') {memcpy(&localtime_text," ",1);}
		   
			//getTime();
		//Set the Dual Time
		getDualTime();


       } //MINUTE CHANGES
	   if (units_changed & DAY_UNIT){
			//Update the date
			getDate();}
	
} //HANDLE_TICK

//*****************//
// AppSync options //
//*****************//

/* simple base 10 only itoa */
char *
itoa10 (int value, char *result)
{
    char const digit[] = "0123456789";
    char *p = result;
    if (value < 0) {
        *p++ = '-';
        value *= -1;
    }

    /* move number of required chars and null terminate */
    int shift = value;
    do {
        ++p;
        shift /= 10;
    } while (shift);
    *p = '\0';

    /* populate result in reverse order */
    do {
        *--p = digit [value % 10];
        value /= 10;
    } while (value);

    return result;
}

  static AppSync sync;
  static uint8_t sync_buffer[512];

  static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context) {

        
  // App Sync keeps new_tuple in sync_buffer, so we may use it directly
  switch (key) {
	  case LOCAL_NAME_KEY:
	  		persist_write_string(LOCAL_NAME_KEY, new_tuple->value->cstring);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring);
      		break;
	  case LOCAL_TZ_KEY:
	      	//persist_write_int(LOCAL_TZ_KEY, new_tuple->value->uint16);
	 		persist_write_int(LOCAL_TZ_KEY, new_tuple->value->uint32);
	  
	  		//debug
	  		//static char strdebug[15];
	  		//itoa10(new_tuple->value->uint32, strdebug);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, strdebug);
	  		//debug - END
	  
      		break;
	  case LOCAL_TZNAME_KEY:
	  		persist_write_string(LOCAL_TZNAME_KEY, new_tuple->value->cstring);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring);
      		break;
	  case DUAL_NAME_KEY:
	  		persist_write_string(DUAL_NAME_KEY, new_tuple->value->cstring);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring);
      		break;
	  case DUAL_TZ_KEY:
	      	persist_write_int(DUAL_TZ_KEY, new_tuple->value->uint32);
		  	//debug
	  		//static char strdebug2[15];
	  		//itoa10(new_tuple->value->uint32, strdebug2);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, strdebug2);
	  		//debug - END
      		break;
	  case DUAL_TZNAME_KEY:
	  		persist_write_string(DUAL_TZNAME_KEY, new_tuple->value->cstring);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring);
      		break;
	  
	  case LOCAL_TEMP_KEY:
	  		persist_write_string(LOCAL_TEMP_KEY, new_tuple->value->cstring);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring);
      		break;
	  case LOCAL_ICON_KEY:
	  		persist_write_int(LOCAL_ICON_KEY, new_tuple->value->uint8);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring); 
      		break;
	  
	  
	  case DUAL_TEMP_KEY:
	  		persist_write_string(DUAL_TEMP_KEY, new_tuple->value->cstring);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring);
      		break;
	  
	  case DUAL_ICON_KEY:
	  		persist_write_int(DUAL_ICON_KEY, new_tuple->value->uint8);
	  		//APP_LOG(APP_LOG_LEVEL_DEBUG, new_tuple->value->cstring); 
      		break;

  }
	  
	  //refresh the screen
	  
		if (persist_exists(LOCAL_NAME_KEY)){persist_read_string(LOCAL_NAME_KEY, localname, sizeof(localname));}
	  	if (persist_exists(DUAL_NAME_KEY)){persist_read_string(DUAL_NAME_KEY, dualname, sizeof(dualname));}
	  	if (persist_exists(LOCAL_TZNAME_KEY)){persist_read_string(LOCAL_TZNAME_KEY, LocalTZName, sizeof(LocalTZName));}
	  	if (persist_exists(DUAL_TZNAME_KEY)){persist_read_string(DUAL_TZNAME_KEY, DualTZName, sizeof(DualTZName));}
	  	if (persist_exists(LOCAL_TEMP_KEY)){persist_read_string(LOCAL_TEMP_KEY, strLocalTemp, sizeof(strLocalTemp));}
	  	if (persist_exists(DUAL_TEMP_KEY)){persist_read_string(DUAL_TEMP_KEY, strDualTemp, sizeof(strDualTemp));}
	  	if (persist_exists(LOCAL_ICON_KEY)){
			if (s_res_takeoff != NULL){gbitmap_destroy(s_res_takeoff);}
			s_res_takeoff = gbitmap_create_with_resource(WEATHER_ICONS[persist_read_int(LOCAL_ICON_KEY)]);
			bitmap_layer_set_bitmap(Local_img, s_res_takeoff);
			#ifdef PBL_BW
				//use Jonathan's library to change the icon's color (from white to black, for consistency)
				replace_gbitmap_color(GColorWhite, GColorBlack, s_res_takeoff, Local_img);
			#endif
		}
	  	if (persist_exists(DUAL_ICON_KEY)){
			if (s_res_landing != NULL){gbitmap_destroy(s_res_landing);}
			s_res_landing = gbitmap_create_with_resource(WEATHER_ICONS[persist_read_int(DUAL_ICON_KEY)]);
			bitmap_layer_set_bitmap(Dual_img, s_res_landing);
			//#ifdef PBL_COLOR
				//use Jonathan's library to change the icon's color (from white to black, for consistency)
				replace_gbitmap_color(GColorWhite, GColorBlack, s_res_landing, Dual_img);
			//#endif
		}
	 

	  	
	  
}

//************************************************//
// TIMER to refresh the weather data every 30 min //
//************************************************//
static void send_cmd(void) {

         Tuplet value = MyTupletCString(2, LocalTZName);
        
         DictionaryIterator *iter;
         app_message_outbox_begin(&iter);
        
         if (iter == NULL) {
                return;
         }
        
         dict_write_tuplet(iter, &value);
         dict_write_end(iter);
        
         app_message_outbox_send();
	
}

static void timer_callback(void *context) {

		//Developer vibe: confirm that timer is not killed
		//vibes_double_pulse();
	
        timer = app_timer_register(timeout_ms, timer_callback, NULL);

        //Refresh the weather
        send_cmd();
	       

}



//*************//
// ENTRY POINT //
//*************//
void SetupMessages(){

	
                app_message_open(inbound_size, outbound_size);
        
                Tuplet initial_values[] = {
					MyTupletCString(LOCAL_NAME_KEY, localname),
					TupletInteger(LOCAL_TZ_KEY, persist_read_int(LOCAL_TZ_KEY)), 
					MyTupletCString(LOCAL_TZNAME_KEY, LocalTZName),
					MyTupletCString(DUAL_NAME_KEY, dualname),
					TupletInteger(DUAL_TZ_KEY, persist_read_int(DUAL_TZ_KEY)),
					MyTupletCString(DUAL_TZNAME_KEY, DualTZName),
					MyTupletCString(LOCAL_TEMP_KEY, strLocalTemp),
					MyTupletCString(DUAL_TEMP_KEY, strDualTemp),
					TupletInteger(LOCAL_ICON_KEY, persist_read_int(LOCAL_ICON_KEY)), 
					TupletInteger(DUAL_ICON_KEY, persist_read_int(DUAL_ICON_KEY)), 
					
                }; //TUPLET INITIAL VALUES
        
                app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
                ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
                NULL, NULL);
}


void handle_init(void)
{
	
	//Use the internationalization API to detect the user's language
	setlocale(LC_ALL, i18n_get_system_locale());
	
	//Read the persistent storage
	if (persist_exists(LOCAL_NAME_KEY)){persist_read_string(LOCAL_NAME_KEY, localname, sizeof(localname));}
	if (persist_exists(DUAL_NAME_KEY)){persist_read_string(DUAL_NAME_KEY, dualname, sizeof(dualname));}
	if (persist_exists(LOCAL_TZNAME_KEY)){persist_read_string(LOCAL_TZNAME_KEY, LocalTZName, sizeof(LocalTZName));}
	if (persist_exists(DUAL_TZNAME_KEY)){persist_read_string(DUAL_TZNAME_KEY, DualTZName, sizeof(DualTZName));}
	if (persist_exists(LOCAL_TEMP_KEY)){persist_read_string(LOCAL_TEMP_KEY, strLocalTemp, sizeof(strLocalTemp));}
	if (persist_exists(DUAL_TEMP_KEY)){persist_read_string(DUAL_TEMP_KEY, strDualTemp, sizeof(strDualTemp));}
	
	if (persist_exists(LOCAL_ICON_KEY)){s_res_takeoff = gbitmap_create_with_resource(WEATHER_ICONS[persist_read_int(LOCAL_ICON_KEY)]);}
	else{s_res_takeoff = gbitmap_create_with_resource(RESOURCE_ID_TakeOff);}
	
	if (persist_exists(DUAL_ICON_KEY)){s_res_landing = gbitmap_create_with_resource(WEATHER_ICONS[persist_read_int(DUAL_ICON_KEY)]);}
	else{s_res_landing = gbitmap_create_with_resource(RESOURCE_ID_Landing);}
	
	//Display the UI
	show_main();
	
	//Init the AppSync with the js code
	SetupMessages();
	
	//Setup the date & time
	getDate();
	//getTime();
	
	//subscribe to the tick event
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);

	handle_tick(current_time, MINUTE_UNIT);
	tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);
	
	//setup the timer to refresh the weather info every 30min
	timer = app_timer_register(timeout_ms, timer_callback, NULL);
}

void handle_deinit(void)
{
	hide_main();
}


int main(void)
{        
        handle_init();
        app_event_loop();
        handle_deinit();
}

