#include "forproto.h"
#include <tts.h>

//1차 Prototyp 상징
//신변처리, 물, 선생님, 좋아요, 싫어요, 주세

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
	Evas_Object *table;
	Evas_Object *btn;
	Evas_Object *img;
	int btnNum;

//	Evas_Object *box_game;//box object로 실제 게임을 그리는 공
//	Evas_Object *rect;//4개의 사각형을 그려 사용자가 터치로 게임을 할 수 있는 공

	tts_h tts;
} appdata_s;

//static void
//app_get_resource(const char *res_file_in, char *res_path_out, int res_path_max)
//{
//	char *res_path = app_get_resource_path();
//	if (res_path) {
//		snprintf(res_path_out, res_path_max, "%s%s", res_path, res_file_in);
//		free(res_path);
//	}
//}

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

/* Callback for whenever TTS changes state */
void state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data)
{
	if (TTS_STATE_READY == current && TTS_STATE_CREATED == previous) {
		appdata_s *ad = (appdata_s *) user_data;
		int ret;
		const char* text;
		if (ad->btnNum==1)
		{
			text="화장실 가고 싶어요.";
		}
		else if (ad->btnNum==2)
		{
			text="물 주세요.";
		}
		else if (ad->btnNum==3)
		{
			text="선생님";
		}
		else if (ad->btnNum==4)
		{
			text="좋아요.";
		}
		else if (ad->btnNum==5)
		{
			text="싫어요.";
		}
		else if (ad->btnNum==6)
		{
			text="주세요.";
		}


		const char* language = "ko_KR"; // Language
		int voice_type = TTS_VOICE_TYPE_FEMALE; // Voice type
		int speed = TTS_SPEED_AUTO; // Read speed
		int utt_id; // Utterance ID for the requested text

		ret = tts_add_text(ad->tts, text, language, voice_type, speed, &utt_id);

		ret = tts_play(ad->tts);
		dlog_print(DLOG_INFO, LOG_TAG, "Added text and started playing");
	}
}

/* Function which handles all the work of setting up and starting TTS */
void enter_tts(appdata_s *ad) {
	int ret;
	ret = tts_create(&(ad->tts));
	ret = tts_set_state_changed_cb(ad->tts, state_changed_cb, ad);
	ret = tts_prepare(ad->tts);
}

void exit_tts(appdata_s *ad) {
	int ret;
	ret = tts_stop(ad->tts);
	ret = tts_unprepare(ad->tts);
	ret = tts_unset_utterance_completed_cb(ad->tts);
	ret = tts_unset_state_changed_cb(ad->tts);
	ret = tts_destroy(ad->tts);
	dlog_print(DLOG_INFO, LOG_TAG, "exit_tts completed");
}

static void
clicked_btn1(void *user_data, Evas* e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad= user_data;
	ad->btnNum=1;
	dlog_print(DLOG_INFO,"MY_LOG","HHHHHHHHHHHHHHHHH");//log print

	enter_tts(ad);
}

static void
clicked_btn2(void *user_data, Evas* e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad= user_data;
	ad->btnNum=2;
	dlog_print(DLOG_INFO,"MY_LOG","HHHHHHHHHHHHHHHHH");//log print

	enter_tts(ad);
}

static void
clicked_btn3(void *user_data, Evas* e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad= user_data;
	ad->btnNum=3;
	dlog_print(DLOG_INFO,"MY_LOG","HHHHHHHHHHHHHHHHH");//log print

	enter_tts(ad);
}

static void
clicked_btn4(void *user_data, Evas* e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad= user_data;
	ad->btnNum=4;
	dlog_print(DLOG_INFO,"MY_LOG","HHHHHHHHHHHHHHHHH");//log print

	enter_tts(ad);
}

static void
clicked_btn5(void *user_data, Evas* e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad= user_data;
	ad->btnNum=5;
	dlog_print(DLOG_INFO,"MY_LOG","HHHHHHHHHHHHHHHHH");//log print

	enter_tts(ad);
}

static void
clicked_btn6(void *user_data, Evas* e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad= user_data;
	ad->btnNum=6;
	dlog_print(DLOG_INFO,"MY_LOG","HHHHHHHHHHHHHHHHH");//log print

	enter_tts(ad);
}

static void
create_base_gui(appdata_s *ad)
{
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	ad->conform = elm_conformant_add(ad->win);//conformant의 추가
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);//indicator의 visible/invisible setting
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);//indicator의 opacity(투명도) setting
	evas_object_size_hint_weight_set(ad->conform,0.2, 0.1);
	elm_win_resize_object_add(ad->win, ad->conform);//object의 resizing에 관한 setting. /add->conform을 ad->win에 추가하여,
	evas_object_show(ad->conform);//conformant component를 visible하게 함.

	ad->table=elm_table_add(ad->conform);
	elm_object_content_set(ad->conform,ad->table);
	evas_object_size_hint_weight_set(ad->table, 0.2, 0.3);
	evas_object_size_hint_align_set(ad->table, 0.4, 0.1);
	elm_table_padding_set(ad->table,10,10);
	evas_object_show(ad->table);

	//좌단 사이즈 맞추기용 버튼
	ad->btn = elm_button_add(ad->table);
//	elm_object_text_set(ad->btn, "");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 0, 0, 1, 1);
//	evas_object_show(ad->btn);

	ad->btn = elm_button_add(ad->table);
	elm_object_text_set(ad->btn, "<font_size=22>1</font_size>");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 1, 1, 1, 1);
	evas_object_show(ad->btn);

	evas_object_event_callback_add(ad->btn, EVAS_CALLBACK_MOUSE_DOWN, clicked_btn1, ad);

	ad->btn = elm_button_add(ad->table);
	elm_object_text_set(ad->btn, "2");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 2, 1, 1, 1);
	evas_object_show(ad->btn);

	evas_object_event_callback_add(ad->btn, EVAS_CALLBACK_MOUSE_DOWN, clicked_btn2, ad);

	ad->btn = elm_button_add(ad->table);
	elm_object_text_set(ad->btn, "<font_size=22>3</font_size>");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 3, 1, 1, 1);
	evas_object_show(ad->btn);

	evas_object_event_callback_add(ad->btn, EVAS_CALLBACK_MOUSE_DOWN, clicked_btn3, ad);

	ad->btn = elm_button_add(ad->table);
	elm_object_text_set(ad->btn, "<font_size=22>4</font_size>");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 1, 2, 1, 1);
	evas_object_show(ad->btn);

	evas_object_event_callback_add(ad->btn, EVAS_CALLBACK_MOUSE_DOWN, clicked_btn4, ad);

	ad->btn = elm_button_add(ad->table);
	elm_object_text_set(ad->btn, "<font_size=22>5</font_size>");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 2, 2, 1, 1);
	evas_object_show(ad->btn);

	evas_object_event_callback_add(ad->btn, EVAS_CALLBACK_MOUSE_DOWN, clicked_btn5, ad);


	//버튼만
//	ad->btn = elm_button_add(ad->table);
//	elm_object_text_set(ad->btn, "<font_size=22>주세요</font_size>");
//	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
//	elm_table_pack(ad->table, ad->btn, 3, 2, 1, 1);
//	evas_object_show(ad->btn);

	//이미지만
	ad->img =elm_image_add(ad->table);
	elm_image_file_set(ad->img, "give_me.png", NULL);
	evas_object_size_hint_weight_set(ad->img, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->img, 3, 2, 1, 1);
	evas_object_show(ad->img);

//	ad->btn =elm_button_add(ad->table);
//	ad->img=elm_button_add(ad->btn);
//	elm_image_file_set(ad->img, "/opt/usr/apps/org.example.forproto/res/give_me.png", NULL);
//	elm_image_file_set(ad->img, "give_me.png", NULL);
//	elm_object_part_content_set(ad->btn, "give_me", ad->img);
//	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//	evas_object_size_hint_align_set(ad->btn,EVAS_HINT_FILL,EVAS_HINT_FILL);
//	elm_table_pack(ad->table, ad->btn, 3, 2, 1, 1);
//	evas_object_show(ad->btn);
//	evas_object_show(ad->img);

	evas_object_event_callback_add(ad->img, EVAS_CALLBACK_MOUSE_DOWN, clicked_btn6, ad);

	//우하단 사이즈 맞추기용 버튼
	ad->btn = elm_button_add(ad->table);
//	elm_object_text_set(ad->btn, "Button6");
	evas_object_size_hint_weight_set(ad->btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(ad->table, ad->btn, 4, 3, 1, 1);
//	evas_object_show(ad->btn);


//기존 버튼 하나
//	//grid_main생성
//	ad->grid_main=elm_grid_add(ad->conform);
//	elm_object_content_set(ad->conform,ad->grid_main);
//
//	//Box_bottom 생성
//	ad->box_game =elm_box_add(ad->grid_main);
//	elm_box_horizontal_set(ad->box_game, EINA_TRUE);
//	elm_box_padding_set(ad->box_game,15,0);
//	elm_grid_pack(ad->grid_main,ad->box_game,0,20,100,70);
//	evas_object_show(ad->box_game);
//
//	//Box_bottom 안에 rectangle
//	ad->rect=evas_object_rectangle_add(ad->box_game);//rectangle 객체 생성
//	evas_object_color_set(ad->rect,40,50,10,255);//상 지정
//	evas_object_size_hint_min_set(ad->rect,100,230);//크기 지정
//	evas_object_show(ad->rect);
//	elm_box_pack_end(ad->box_game, ad->rect);//box_game에 rect[i]삽입
//
//	//rect callback 함수 지정
//	evas_object_event_callback_add(ad->rect, EVAS_CALLBACK_MOUSE_DOWN, clicked_rect, ad);

	/* Show window after base gui is set up */

	evas_object_show(ad->win);
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;
	ad->btnNum=0;
	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */

}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
