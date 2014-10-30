#include "main.h"
#include <pebble.h>

//Variables
	static char localtime_text[] = "00:00";
	static char localweekday_text[] = "XXXXXXXXXXXX";
	static char localmonth_text[] = "XXXXXXXXXXXXX";

	static char dualtime_text[] = "00:00";
	static char dualweekday_text[] = "XXXXXXXXXXXX";
	static char dualmonth_text[] = "XXXXXXXXXXXXX";
	
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
static TextLayer *LocalDate;
static TextLayer *LocalDay;
static TextLayer *DualTime;
static TextLayer *DualDate;
static TextLayer *DualDay;
static TextLayer *DualTemp;
static TextLayer *DualTZ;
static BitmapLayer *Local_img;
static BitmapLayer *Dual_img;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_bitham_42_light = fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_takeoff = gbitmap_create_with_resource(RESOURCE_ID_TakeOff);
  s_res_landing = gbitmap_create_with_resource(RESOURCE_ID_Landing);
  // LocalArea
  LocalArea = text_layer_create(GRect(3, 9, 137, 75));
  text_layer_set_font(LocalArea, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalArea);
  
  // DualArea
  DualArea = text_layer_create(GRect(4, 93, 137, 70));
  text_layer_set_font(DualArea, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualArea);
  
  // LocalTZ
  LocalTZ = text_layer_create(GRect(28, 20, 41, 14));
  text_layer_set_background_color(LocalTZ, GColorClear);
  text_layer_set_text(LocalTZ, "GMT+1");
  text_layer_set_font(LocalTZ, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalTZ);
  
  // LocalTemp
  LocalTemp = text_layer_create(GRect(75, 15, 69, 42));
  text_layer_set_background_color(LocalTemp, GColorClear);
  text_layer_set_text(LocalTemp, "27");
  text_layer_set_text_alignment(LocalTemp, GTextAlignmentCenter);
  text_layer_set_font(LocalTemp, s_res_bitham_42_light);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalTemp);
  
  // LocalTime
  LocalTime = text_layer_create(GRect(3, 49, 83, 30));
  text_layer_set_background_color(LocalTime, GColorClear);
  text_layer_set_text(LocalTime, localtime_text);
  text_layer_set_text_alignment(LocalTime, GTextAlignmentRight);
  text_layer_set_font(LocalTime, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalTime);
  
  // LocalDate
  LocalDate = text_layer_create(GRect(11, 43, 98, 14));
  text_layer_set_background_color(LocalDate, GColorClear);
  text_layer_set_text(LocalDate, localmonth_text);
  text_layer_set_font(LocalDate, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalDate);
  
  // LocalDay
  LocalDay = text_layer_create(GRect(11, 32, 98, 14));
  text_layer_set_background_color(LocalDay, GColorClear);
  text_layer_set_text(LocalDay, localweekday_text);
  text_layer_set_font(LocalDay, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)LocalDay);
  
  // DualTime
  DualTime = text_layer_create(GRect(3, 130, 83, 42));
  text_layer_set_background_color(DualTime, GColorClear);
  text_layer_set_text(DualTime, dualtime_text);
  text_layer_set_text_alignment(DualTime, GTextAlignmentRight);
  text_layer_set_font(DualTime, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualTime);
  
  // DualDate
  DualDate = text_layer_create(GRect(11, 124, 98, 14));
  text_layer_set_background_color(DualDate, GColorClear);
  text_layer_set_text(DualDate, dualmonth_text);
  text_layer_set_font(DualDate, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualDate);
  
  // DualDay
  DualDay = text_layer_create(GRect(11, 114, 98, 14));
  text_layer_set_background_color(DualDay, GColorClear);
  text_layer_set_text(DualDay, dualweekday_text);
  text_layer_set_font(DualDay, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualDay);
  
  // DualTemp
  DualTemp = text_layer_create(GRect(75, 101, 69, 42));
  text_layer_set_background_color(DualTemp, GColorClear);
  text_layer_set_text(DualTemp, "16");
  text_layer_set_text_alignment(DualTemp, GTextAlignmentCenter);
  text_layer_set_font(DualTemp, s_res_bitham_42_light);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualTemp);
  
  // DualTZ
  DualTZ = text_layer_create(GRect(28, 102, 41, 14));
  text_layer_set_text(DualTZ, "GMT-7");
  text_layer_set_font(DualTZ, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)DualTZ);
  
  // Local_img
  Local_img = bitmap_layer_create(GRect(4, 9, 20, 20));
  bitmap_layer_set_bitmap(Local_img, s_res_takeoff);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Local_img);
  
  // Dual_img
  Dual_img = bitmap_layer_create(GRect(4, 94, 20, 20));
  bitmap_layer_set_bitmap(Dual_img, s_res_landing);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Dual_img);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(28, 8, 111, 17));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "MADRID");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(28, 91, 100, 17));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, "SAN FRANCISCO");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
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

			//Define and Calculate Time Zones
			//TIME ZONE 1
				struct tm *tz1Ptr = gmtime(&actualPtr);
				tz1Ptr->tm_hour += -8; //change this hard code
				tz1Ptr->tm_min += 0; //change this hard code
		
				//try to fix the timezone when half and hour diff
				if (tz1Ptr->tm_min >=60){
					tz1Ptr->tm_hour = 1 + tz1Ptr->tm_hour;
					tz1Ptr->tm_min = tz1Ptr->tm_min - 60;
				}
		
				//try to fix the timezone when half and hour diff
				if (tz1Ptr->tm_min <0){
					tz1Ptr->tm_hour = tz1Ptr->tm_hour - 1;
					tz1Ptr->tm_min = 60 + tz1Ptr->tm_min;
				}

				//try to fix the timezone when negative
		
				if (tz1Ptr->tm_hour <0){
					tz1Ptr->tm_hour = 24 + tz1Ptr->tm_hour;
					tz1Ptr->tm_mday = tz1Ptr->tm_mday - 1;
					tz1Ptr->tm_wday = tz1Ptr->tm_wday - 1;
				}
		
				//try to fix the timezone when more than 24
				if (tz1Ptr->tm_hour >=24){
					tz1Ptr->tm_hour = tz1Ptr->tm_hour - 24;
					tz1Ptr->tm_mday = tz1Ptr->tm_mday + 1;
					tz1Ptr->tm_wday = tz1Ptr->tm_wday + 1;
				}

				if (clock_is_24h_style()){strftime(dualtime_text, sizeof(dualtime_text), "%H:%M", tz1Ptr);}
				else {strftime(dualtime_text, sizeof(dualtime_text), "%I:%M", tz1Ptr);}
	

				//Remove the leading 0s
				if (dualtime_text[0]=='0') {memcpy(&dualtime_text," ",1);}
	
			//Calculate the Dual Zone Date
			strftime(dualmonth_text,sizeof(dualmonth_text),"%B %e",tz1Ptr);
			strftime(dualweekday_text,sizeof(dualweekday_text),"%A",tz1Ptr);
			
	
			//DISPLAY THE TIME ZONES	
			text_layer_set_text(DualTime, dualtime_text);
			text_layer_set_text(DualDay,dualweekday_text);
			text_layer_set_text(DualDate,dualmonth_text); 

}

//*********************************//
//** Get the current date & time **//
//*********************************//
void getDate()
{
	//Get the date
	time_t actualPtr = time(NULL);
	struct tm *tz1Ptr = gmtime(&actualPtr);
	
	//get the local date
	strftime(localmonth_text,sizeof(localmonth_text),"%B %e",tz1Ptr);
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
			getTime();


       } //MINUTE CHANGES
	   if (units_changed & DAY_UNIT){
			//Update the date
			getDate();}
	
} //HANDLE_TICK


//*************//
// ENTRY POINT //
//*************//
void handle_init(void)
{
	//Display the UI
	show_main();
	
	//Setup the date & time
	getDate();
	getTime();
	
	//subscribe to the tick event
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);

	handle_tick(current_time, MINUTE_UNIT);
	tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);
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

