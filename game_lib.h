#ifndef _GAME_LIB_H_
#define _GAME_LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>
#include "common.h"

/* ウインドウ設定 */
#define WINDOW_WIDTH 1680
#define WINDOW_HEIGHT 864
#define BPP 32
#define	UPDATE_MAX   (100)

/* キャラクタ設定 */
#define CHAR_WIDTH  48
#define CHAR_HEIGHT 48

/* 方向(値に意味あり) */
#define dirSouth 0
#define dirEast  1
#define dirNorth 2
#define dirWest  3

/*マップ設定*/
#define SQUARE_SIZE 48
#define MAP_SIZE_WIDTH  35
#define MAP_SIZE_HEIGHT 12

/*ステータスウインドウ*/
#define STATUS_WINDOW_X 0
#define STATUS_WINDOW_Y 576
#define STATUS_WINDOW_WIDTH  1680
#define STATUS_WINDOW_HEIGHT WINDOW_HEIGHT-576


enum enm_target {
  I,            /* 自分 */
  you,          /* 相手 */
  r_left,       /* 相手から見て左側の小旗 */
  r_center,     /* 相手から見て中央の小旗 */
  r_right,      /* 相手から見て右側の子旗 */
  r_king,       /* 相手の大将旗 */
  b_left,       /* 自分から見て左側の小旗 */
  b_center,     /* 自分から見て中央の小旗 */
  b_right,      /* 自分から見て右側の小旗 */
  b_king,       /* 自分の大将旗 */
  none          /* 対象なし */
};


/* キャラクタ構造体 */
typedef struct {
  SDL_Surface *image;	/* キャラクタイメージ 左から前、右、後ろ、左 */
  int direction;	/* 方向 */
  SDL_Rect src_rect;    /* コピー元矩形 */
  SDL_Rect dst_rect;	/* コピー先矩形 */
  int square_x;         /* マスの行 */
  int square_y;         /* マスの列 */
  double attack;        /* 攻撃力 */
  double HP;            /* HP */
  double MP;            /* MP */
} type_character;


void init_my_status_and_rect(SDL_Rect *rect_tmp, SDL_Rect *scr_rect);
void init_your_status_and_rect(SDL_Rect *rect2_tmp, SDL_Rect *scr_rect2);
void init_map(void);
void init_load_images(void);
void init_rectsize(SDL_Rect *rect);
void init_statuswindow(SDL_Rect *status_rect);
void init_drawHP(void);
void init_drawMP(void);
void drawHP(int target);
void drawMP(int target);
int attack(int direction);
void damage(int target, double hp);
void draw_character(type_character *character, SDL_Surface *screen, int a);
void draw_damaged_character(type_character *character, SDL_Surface *screen);
void draw_brokenflag(int target);
void Update(SDL_Rect *a);
void square_poison(int direction);
Uint32 poison(Uint32 interval, void *param);
void square_heal(int direction);
Uint32 recovery(Uint32 interval, void *param);
Uint32 item_appear(Uint32 interval, void* param);
void set_yakusou(void);
void set_attackup(void);
void set_mine_set(void);
void func_mine(type_character *character);
void func_yakusou(type_character *character);
void func_attackup(type_character *character);
Uint32 elx_appear(Uint32 interval, void *param);
void set_elixir(void);
void func_elixir(type_character *character);
void gamewin(void);
//Uint32 gamewin_window(Uint32 interval, void *param);
void gamewin_window(void);
//Uint32 game_win_character(Uint32 interval, void *param);
void game_win_character(void);
void gamelose(void);
//Uint32 gamelose_window(Uint32 interval, void *param);
void gamelose_window(void);
//Uint32 game_lose_character(Uint32 interval, void *param);
void game_lose_character(void);
void respawn(int target, SDL_Rect *rect_tmp, SDL_Rect *scr_rect);
Uint32 respawn_end(Uint32 interval, void *param);
void drop_surface(SDL_Surface *surface);


/* 以下game_lib.cに記述 */
extern SDL_Surface *screen;                 
extern SDL_Surface *background_image;
extern SDL_Surface *statuswindow_image;
extern SDL_Surface *HPbar, *MPbar;
extern SDL_Surface *mine_image;
extern SDL_Surface *mark_image;
extern SDL_Surface *yakusou_image;
extern SDL_Surface *kusuri_image;
extern SDL_Surface *elixir_image;
extern SDL_Surface *deadcharacter_image;

extern type_character mycharacter;
extern type_character yourcharacter;
extern double r_left_HP, r_center_HP, r_right_HP, r_king_HP;
extern double b_left_HP, b_center_HP, b_right_HP, b_king_HP;
extern int HPMAX;

extern int map[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];

extern int keylock_flag;

extern int SDbomb_count;

extern SDL_TimerID ptimer_id;
extern SDL_TimerID htimer_id;
extern SDL_TimerID timer_id;
extern SDL_TimerID wtimer_id;
extern SDL_TimerID w_char_timer_id;
extern SDL_TimerID ltimer_id;
extern SDL_TimerID l_char_timer_id;

#endif /* _GAME_LIB_H_ */
