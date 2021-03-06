#include "game_lib.h"


SDL_Surface *screen = NULL;                 
SDL_Surface *background_image = NULL;
SDL_Surface *statuswindow_image;
SDL_Surface *HPbar, *MPbar;
SDL_Surface *mine_image;
SDL_Surface *mark_image;
SDL_Surface *yakusou_image;
SDL_Surface *kusuri_image;
SDL_Surface *elixir_image;
SDL_Surface *deadcharacter_image;

type_character mycharacter;		/* 主人公キャラクタ */
type_character yourcharacter;           /* 相手キャラクタ　*/
double r_left_HP=50, r_center_HP=50, r_right_HP=50, r_king_HP=300;
double b_left_HP=50, b_center_HP=50, b_right_HP=50, b_king_HP=300;
int HPMAX = 10;

int map[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];

int keylock_flag;

int SDbomb_count=0;

SDL_TimerID ptimer_id;
SDL_TimerID htimer_id;
SDL_TimerID timer_id;
SDL_TimerID wtimer_id;
SDL_TimerID w_char_timer_id;
SDL_TimerID ltimer_id;
SDL_TimerID l_char_timer_id;


void init_my_status_and_rect(SDL_Rect *rect_tmp, SDL_Rect *scr_rect)
{
  int xpx, ypx;

  xpx = SQUARE_SIZE * 3;
  ypx = SQUARE_SIZE * 6;
  
  mycharacter.direction = dirSouth;
  mycharacter.dst_rect.x = xpx;
  mycharacter.dst_rect.y = ypx;
  mycharacter.square_x = 6;
  mycharacter.square_y = 3;
  mycharacter.attack = 1;
  mycharacter.HP = 10;
  mycharacter.MP = 50;

  rect_tmp->x = xpx;
  rect_tmp->y = ypx;
  scr_rect->x = xpx;
  scr_rect->y = ypx;
  
  return;
}


void init_your_status_and_rect(SDL_Rect *rect2_tmp, SDL_Rect *scr_rect2)
{
  int xpx, ypx;

  xpx = SQUARE_SIZE * 31;
  ypx = SQUARE_SIZE * 6;

  yourcharacter.direction = dirSouth;
  yourcharacter.dst_rect.x = xpx;
  yourcharacter.dst_rect.y = ypx;
  yourcharacter.square_x = 6;
  yourcharacter.square_y = 31;
  yourcharacter.attack = 1;
  yourcharacter.HP = 10;
  yourcharacter.MP = 50;

  rect2_tmp->x = xpx;
  rect2_tmp->y = ypx;
  scr_rect2->x = xpx;
  scr_rect2->y = ypx;
  
  map[yourcharacter.square_x][yourcharacter.square_y] = object;

  return;
}


void init_map(void)
{
  int i;
  
  /*障害物情報の入力*/
  for (i=0; i<MAP_SIZE_WIDTH; i++) {
    map[0][i] = object;
    map[MAP_SIZE_HEIGHT-1][i] = object;
  }
  for (i=0; i<MAP_SIZE_HEIGHT; i++) {
    map[i][0] = object;
    map[i][MAP_SIZE_WIDTH-1] = object;
  }

  map[2][17] = object;          /*　壁　*/
  map[4][17] = object;
  map[7][17] = object;
  map[9][17] = object;
  map[5][1] = object;           /* blue king */
  map[5][2] = object;
  map[6][1] = object;
  map[6][2] = object;
  map[3][6] = object;           /* blue left */
  map[8][6] = object;           /* blue right */
  map[6][10] = object;          /* blue center */
  map[5][32] = object;          /* red king */
  map[6][32] = object;  
  map[5][33] = object;
  map[6][33] = object;
  map[3][28] = object;          /* red left */
  map[8][28] = object;          /* red right */
  map[6][24] = object;          /* red center */
  map[6][23] = doku;          /* 毒マス  center*/
  map[5][23] = doku;
  map[7][23] = doku;
  map[5][24] = doku;
  map[7][24] = doku;
  map[5][25] = doku;
  map[6][25] = doku;
  map[7][25] = doku;
  map[2][27] = doku;          /* 毒マス　left */
  map[3][27] = doku;
  map[4][27] = doku;
  map[2][28] = doku;
  map[4][28] = doku;
  map[2][29] = doku;
  map[3][29] = doku;
  map[4][29] = doku;
  map[7][27] = doku;          /* 毒マス　right */
  map[8][27] = doku;
  map[9][27] = doku;
  map[7][28] = doku;
  map[9][28] = doku;
  map[7][29] = doku;
  map[8][29] = doku;
  map[9][29] = doku;
  map[4][31] = doku;         /* 毒マス　king */
  map[5][31] = doku;
  map[6][31] = doku;
  map[7][31] = doku;
  map[4][32] = doku;
  map[7][32] = doku;
  map[4][33] = doku;
  map[7][33] = doku;
  map[4][1] = heal;            /* 回復マス king */
  map[7][1] = heal;
  map[4][2] = heal;
  map[7][2] = heal;
  map[4][3] = heal;
  map[5][3] = heal;
  map[6][3] = heal;
  map[7][3] = heal;
  map[2][5] = heal;            /* 回復マス left */
  map[3][5] = heal;
  map[4][5] = heal; 
  map[2][6] = heal;
  map[4][6] = heal;
  map[2][7] = heal;
  map[3][7] = heal; 
  map[4][7] = heal; 
  map[5][9] = heal;            /* 回復マス center */
  map[6][9] = heal;
  map[7][9] = heal;
  map[5][10] = heal; 
  map[7][10] = heal;
  map[5][11] = heal;
  map[6][11] = heal; 
  map[7][11] = heal;
  map[7][5] = heal;           /* 回復マス right */
  map[8][5] = heal;
  map[9][5] = heal;
  map[7][6] = heal;
  map[9][6] = heal;
  map[7][7] = heal;
  map[8][7] = heal;
  map[9][7] = heal;

  return;
}


void init_load_images(void)
{
  /* 画像読み込み */
  mycharacter.image = IMG_Load("./char/mycharacter.png");
  yourcharacter.image = IMG_Load("./char/yourcharacter.png");
  deadcharacter_image = IMG_Load("./char/deadcharacter.png");
  background_image = IMG_Load("./bg/field.png");
  statuswindow_image = IMG_Load("./bg/status.png");
  HPbar = IMG_Load("./bg/HPbar.png");
  MPbar = IMG_Load("./bg/MPbar.png");
  mine_image = IMG_Load("./item/randmine.png");
  mark_image = IMG_Load("./item/mark.png");
  yakusou_image = IMG_Load("./item/yakusou.png");
  kusuri_image = IMG_Load("./item/kusuri.png");
  elixir_image = IMG_Load("./item/elixir.png");
  
  return;
}


void init_rectsize(SDL_Rect *rect)
{
  /* 画像の矩形情報設定 */
  rect->x = 0;
  rect->y = 0;
  rect->w = CHAR_WIDTH;
  rect->h = CHAR_HEIGHT;
  
  return;
}


void init_statuswindow(SDL_Rect *status_rect)
{
  status_rect->x = 384;
  status_rect->y = 576;

  return;
}


void init_drawHP(void)
{
  drawHP(I);
  drawHP(you);
  drawHP(r_right);
  drawHP(r_left);
  drawHP(r_center);
  drawHP(r_king);
  drawHP(b_right);
  drawHP(b_left);
  drawHP(b_center);
  drawHP(b_king);

  return;
}


void init_drawMP(void)
{
  drawMP(I);
  drawMP(you);

  return;
}


void drawHP(int target)
{
  SDL_Rect tmp_rect;
  SDL_Rect HPbar_rect;
  SDL_Rect I_rect,Y_rect;
  SDL_Rect b_king_rect,b_center_rect,b_left_rect,b_right_rect;
  SDL_Rect r_king_rect,r_center_rect,r_left_rect,r_right_rect;
  double p;

  
  tmp_rect.x = 10;
  tmp_rect.y =10;
  tmp_rect.w = 64;
  tmp_rect.h = 8;

  HPbar_rect.x = 0;
  HPbar_rect.y = 0;
  HPbar_rect.w = 64;
  HPbar_rect.h = 8;
    
  I_rect.x = 746;
  I_rect.y = 669;
  Y_rect.x = 870;
  Y_rect.y = 669;
  b_king_rect.x = 419;
  b_center_rect.x = 635;
  b_left_rect.x = 531;
  b_right_rect.x = 531;
  b_king_rect.y = 768;
  b_center_rect.y = 737;
  b_left_rect.y = 651;
  b_right_rect.y = 822;
  r_king_rect.x = 1179;
  r_center_rect.x = 971;
  r_left_rect.x = 1060;
  r_right_rect.x = 1058;
  r_king_rect.y = 755;
  r_center_rect.y = 740;
  r_left_rect.y = 643;
  r_right_rect.y = 821;
 
  switch (target) {
  case I:  /* 自分のHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &I_rect);
    p = mycharacter.HP/10;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar,&HPbar_rect , screen, &I_rect );
    SDL_Flip(screen);
    break;
  case you:  /* 相手のHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect, screen, &Y_rect );
    p = yourcharacter.HP/10;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &Y_rect );
    SDL_Flip(screen);
    break;
  case b_king:  /* b_kingのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &b_king_rect);
    p = b_king_HP/300;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &b_king_rect);
    break;
  case b_left:  /* b_leftのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &b_left_rect);
    p = b_left_HP/50;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &b_left_rect );
    break;
  case b_center:  /* b_centerのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen,&b_center_rect  );
    p = b_center_HP/50;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &b_center_rect );
    break;
  case b_right:  /* b_rightのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen,&b_right_rect );
    p = b_right_HP/50;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &b_right_rect);
    break;
  case r_king:  /* r_kingのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &r_king_rect);
    p = r_king_HP/300;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &r_king_rect);
    break;
  case r_left:  /* r_leftのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &r_left_rect);
    p = r_left_HP/50;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen,&r_left_rect );
  case r_center:  /* r_centerのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &r_center_rect);
    p = r_center_HP/50;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen, &r_center_rect);
    break;
  case r_right: /* r_rightのHP */
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen,&r_right_rect );
    p = r_right_HP/50;
    HPbar_rect.w = p*64;
    SDL_BlitSurface(HPbar, &HPbar_rect, screen,&r_right_rect);
    break;
  default:
    break;

  }
    
  return;
}


void drawMP(int target)
{
  SDL_Rect tmp_rect;
  SDL_Rect I_rect,Y_rect;
  SDL_Rect MPbar_rect;
  double p;

  tmp_rect.x = 10;
  tmp_rect.y = 10;
  tmp_rect.w = 64;
  tmp_rect.h = 8;

  MPbar_rect.x = 0;
  MPbar_rect.y = 0;
  MPbar_rect.w = 64;
  MPbar_rect.h = 8;
    
  I_rect.x = 746;
  I_rect.y = 683;
  Y_rect.x = 870;
  Y_rect.y = 683;

  switch (target) {
  case I:
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &I_rect);
    p = mycharacter.MP/50;
    MPbar_rect.w = p*64;
    SDL_BlitSurface(MPbar,&MPbar_rect , screen, &I_rect );
    SDL_Flip(screen);
    break;
  case you:
    SDL_BlitSurface(statuswindow_image, &tmp_rect , screen, &Y_rect);
    p = yourcharacter.MP/50;
    MPbar_rect.w = p*64;
    SDL_BlitSurface(MPbar,&MPbar_rect , screen, &Y_rect );
    SDL_Flip(screen);
    break;
  default:
    break;
  }

  return;
}


int attack(int direction)
{
  int target=none;
  
  switch (direction) {
  case dirSouth:
    if (mycharacter.square_x+1 == yourcharacter.square_x && mycharacter.square_y == yourcharacter.square_y) {
      if (yourcharacter.HP > 0) {
	yourcharacter.HP -= mycharacter.attack;
	if (yourcharacter.HP < 0) yourcharacter.HP = 0;
	drawHP(you);
	target = you;
      }
    }
    else if (mycharacter.square_x+1 == 3 && mycharacter.square_y == 28) {
      if (r_left_HP > 0) {
	r_left_HP -= mycharacter.attack;
	if (r_left_HP < 0) {
	  r_left_HP = 0;
	  draw_brokenflag(r_left);
	}
	drawHP(r_left);
	target = r_left;
      }
    }
    else if (mycharacter.square_x+1 == 8 && mycharacter.square_y == 28) {
      if (r_right_HP > 0) {
	r_right_HP -= mycharacter.attack;
	if (r_right_HP < 0) {
	  r_right_HP = 0;
	  draw_brokenflag(r_right);
	}
	drawHP(r_right);
	target = r_right;
      }
    }
    else if (mycharacter.square_x+1 == 6 && mycharacter.square_y == 24) {
      if (r_center_HP > 0) {
	r_center_HP -= mycharacter.attack;
	if (r_center_HP < 0) {
	  r_center_HP = 0;
	  draw_brokenflag(r_center);
	}
	drawHP(r_center);
	target = r_center;
      }
    }
    else if ( mycharacter.square_x+1 == 5 && (mycharacter.square_y == 32 || mycharacter.square_y == 33) ) {
      if(r_right_HP <= 0 && r_center_HP <= 0 && r_left_HP <= 0 && r_king_HP > 0) {
	r_king_HP -= mycharacter.attack;
	if (r_king_HP < 0) {
	  r_king_HP = 0;
	  draw_brokenflag(r_king);
	}
	drawHP(r_king);
	target = r_king;
      }
    }
    break;
    
  case dirEast:
    if (mycharacter.square_x == yourcharacter.square_x && mycharacter.square_y+1 == yourcharacter.square_y) {
      if (yourcharacter.HP > 0) {
	yourcharacter.HP -= mycharacter.attack;
	if (yourcharacter.HP < 0) yourcharacter.HP = 0;
	drawHP(you);
	target = you;
      }
    }
    else if (mycharacter.square_x == 3 && mycharacter.square_y+1 == 28) {
      if (r_left_HP > 0) {
	r_left_HP -= mycharacter.attack;
	if (r_left_HP < 0) {
	  r_left_HP = 0;
	  draw_brokenflag(r_left);
	}
	drawHP(r_left);
	target = r_left;
      }
    }
    else if (mycharacter.square_x == 8 && mycharacter.square_y+1 == 28) {
      if (r_right_HP > 0) {
	r_right_HP -= mycharacter.attack;
	if (r_right_HP < 0) {
	  r_right_HP = 0;
	  draw_brokenflag(r_right);
	}
	drawHP(r_right);
	target = r_right;
      }
    }
    else if (mycharacter.square_x == 6 && mycharacter.square_y+1 == 24) {
      if (r_center_HP > 0) {
	r_center_HP -= mycharacter.attack;
	if (r_center_HP < 0) {
	  r_center_HP = 0;
	  draw_brokenflag(r_center);
	}
	drawHP(r_center);
	target = r_center;
      }
    }
    else if ( (mycharacter.square_x == 5 || mycharacter.square_x == 6) && mycharacter.square_y+1 == 32 ) {
      if (r_right_HP <= 0 && r_center_HP <= 0 && r_left_HP <= 0 && r_king_HP > 0) {
	r_king_HP -= mycharacter.attack;
	if (r_king_HP < 0) {
	  r_king_HP = 0;
	  draw_brokenflag(r_king);
	}
	drawHP(r_king);
	target = r_king;
      }
    }
    break;
    
  case dirNorth:
    if (mycharacter.square_x-1 == yourcharacter.square_x && mycharacter.square_y == yourcharacter.square_y) {
      if (yourcharacter.HP > 0) {
	yourcharacter.HP -= mycharacter.attack;
	if (yourcharacter.HP < 0) yourcharacter.HP = 0;
	drawHP(you);
	target = you;
      }
    }
    else if (mycharacter.square_x-1 == 3 &&  mycharacter.square_y == 28) {
      if (r_left_HP > 0) {
	r_left_HP -= mycharacter.attack;
	if (r_left_HP < 0) {
	  r_left_HP = 0;
	  draw_brokenflag(r_left);
	}
	drawHP(r_left);
	target = r_left;
      }
    }
    else if (mycharacter.square_x-1 == 8 && mycharacter.square_y == 28) {
      if (r_right_HP > 0) {
	r_right_HP -= mycharacter.attack;
	if (r_right_HP < 0) {
	  r_right_HP = 0;
	  draw_brokenflag(r_right);
	}
	drawHP(r_right);
	target = r_right;
      }
    }
    else if (mycharacter.square_x-1 == 6 && mycharacter.square_y == 24) {
      if (r_center_HP > 0) {
	r_center_HP -= mycharacter.attack;
	if (r_center_HP < 0) {
	  r_center_HP = 0;
	  draw_brokenflag(r_center);
	}
	drawHP(r_center);
	target = r_center;
      }
    }
    else if ( mycharacter.square_x-1 == 6 && (mycharacter.square_y == 32 || mycharacter.square_y == 33) ) {
      if (r_right_HP <= 0 && r_center_HP <= 0 && r_left_HP <= 0 && r_king_HP) {
	r_king_HP -= mycharacter.attack;
	if (r_king_HP < 0) {
	  r_king_HP = 0;
	  draw_brokenflag(r_king);
	}
	drawHP(r_king);
	target = r_king;
      }
    }
    break;
    
  case dirWest:
    if (mycharacter.square_x == yourcharacter.square_x && mycharacter.square_y-1 == yourcharacter.square_y) {
      if (yourcharacter.HP > 0) {
	yourcharacter.HP -= mycharacter.attack;
	if (yourcharacter.HP < 0) yourcharacter.HP = 0;
	drawHP(you);
	target = you;
      }
    }
    else if (mycharacter.square_x == 3 && mycharacter.square_y-1 ==28) {
      if (r_left_HP > 0) {
	r_left_HP -= mycharacter.attack;
	if (r_left_HP < 0) {
	  r_left_HP = 0;
	  draw_brokenflag(r_left);
	}
	drawHP(r_left);
	target = r_left;
      }
    }
    else if (mycharacter.square_x == 8 && mycharacter.square_y-1 == 28) {
      if (r_right_HP > 0) {
	r_right_HP -= mycharacter.attack;
	if (r_right_HP < 0) {
	  r_right_HP = 0;
	  draw_brokenflag(r_right);
	}
	drawHP(r_right);
	target = r_right;
      }
    }
    else if (mycharacter.square_x == 6 && mycharacter.square_y-1 == 24) {
      if (r_center_HP > 0) {
	r_center_HP -= mycharacter.attack;
	if (r_center_HP < 0) {
	  r_center_HP = 0;
	  draw_brokenflag(r_center);
	}
	drawHP(r_center);
	target = r_center;
      }
    }
    break;
  }
    
  return target;
}


void damage(int target, double hp)
{
  switch (target) {   // target値は相手が見たときの値
  case you:
    mycharacter.HP = hp;
    drawHP(I);
    break;
    
  case r_left:
    b_right_HP = hp;
    drawHP(b_right);
    if (b_right_HP == 0) draw_brokenflag(b_right);
    break;

  case r_right:
    b_left_HP = hp;
    drawHP(b_left);
    if (b_left_HP == 0) draw_brokenflag(b_left);
    break;
    
  case r_center:
    b_center_HP = hp;
    drawHP(b_center);
    if (b_center_HP == 0) draw_brokenflag(b_center);
    break;
    
  case r_king:
    b_king_HP = hp;
    drawHP(b_king);
    if (b_king_HP == 0) draw_brokenflag(b_king);
    break;
    
  default:
    break;  
  }
  
  return;
}


/* キャラクタを書く(方向付き) */
void draw_character(type_character *character, SDL_Surface *screen, int a)
{
  if(a == 0){   // 通常時
    character->src_rect.x = character->direction * CHAR_WIDTH;
    character->src_rect.y = 0;
    character->src_rect.w = CHAR_WIDTH;
    character->src_rect.h = CHAR_HEIGHT;

    SDL_BlitSurface(
		    character->image,
		    &character->src_rect,
		    screen,
		    &character->dst_rect
		    );
    
    SDL_Flip(screen);
  }
  else{   // 攻撃時
    Update(&character->dst_rect);
    character->src_rect.x = (character->direction + 4) * CHAR_WIDTH;
    character->src_rect.y = 0;
    character->src_rect.w = CHAR_WIDTH;
    character->src_rect.h = CHAR_HEIGHT;
  
    SDL_BlitSurface(
		    character->image,
		    &character->src_rect,
		    screen,
		    &character->dst_rect
		    );

    SDL_Flip(screen);
    
    usleep(60000);

  }
  
  return;
}


void draw_damaged_character(type_character *character, SDL_Surface *screen)
{
  Update(&mycharacter.dst_rect);
  SDL_Delay(1);
  draw_character(character, screen, 0);
  return;
}


void draw_brokenflag(int target)
{
  SDL_Surface *b_flag, *b_kingflag;
  SDL_Surface *r_flag, *r_kingflag;
  SDL_Rect b_king_rect, b_center_rect, b_left_rect, b_right_rect;
  SDL_Rect r_king_rect, r_center_rect, r_left_rect, r_right_rect;
  SDL_Rect b_tmp_rect, b_tmp_rect2;
  SDL_Rect r_tmp_rect, r_tmp_rect2;
  
  b_flag = IMG_Load("./flag/b_broken.png");
  b_kingflag = IMG_Load("./flag/b_king_broken.png");
  r_flag = IMG_Load("./flag/r_broken.png");
  r_kingflag = IMG_Load("./flag/r_king_broken.png");

  b_king_rect.x = 48;
  b_center_rect.x = 480;
  b_left_rect.x = 288;
  b_right_rect.x = 288;
  b_king_rect.y = 240;
  b_center_rect.y = 288;
  b_left_rect.y = 144;
  b_right_rect.y = 384;
  r_king_rect.x = 1536;
  r_center_rect.x = 1152;
  r_left_rect.x = 1344;
  r_right_rect.x = 1344;
  r_king_rect.y = 240;
  r_center_rect.y = 288;
  r_left_rect.y = 144;
  r_right_rect.y = 384;

  r_tmp_rect.x = 864;
  r_tmp_rect.y = 48;
  r_tmp_rect.w = 48;
  r_tmp_rect.h = 48;
  r_tmp_rect2.x = 864;
  r_tmp_rect2.y = 48;
  r_tmp_rect2.w = 96;
  r_tmp_rect2.h = 96;
  b_tmp_rect.x = 48;
  b_tmp_rect.y = 48;
  b_tmp_rect.w = 48;
  b_tmp_rect.h = 48;
  b_tmp_rect2.x = 48;
  b_tmp_rect2.y = 48;
  b_tmp_rect2.w = 96;
  b_tmp_rect2.h = 96;
  
  switch (target) {
  case r_left:      /* r_left */
    SDL_BlitSurface(background_image, &r_tmp_rect,screen, &r_left_rect);
    SDL_BlitSurface(r_flag, NULL,screen,&r_left_rect);
    SDbomb_count++;
    break;
  case r_center:      /* r_center */
    SDL_BlitSurface(background_image, &r_tmp_rect,screen, &r_center_rect);
    SDL_BlitSurface(r_flag, NULL,screen,&r_center_rect);
    SDbomb_count++;
    break;
  case r_right:      /* r_right */
    SDL_BlitSurface(background_image, &r_tmp_rect,screen, &r_right_rect);
    SDL_BlitSurface(r_flag, NULL,screen,&r_right_rect);
    SDbomb_count++;
    break;
  case r_king:      /* r_king */
    SDL_BlitSurface(background_image, &r_tmp_rect2,screen, &r_king_rect);
    SDL_BlitSurface(r_kingflag, NULL, screen,&r_king_rect);
    break;
  case b_left:
    SDL_BlitSurface(background_image, &b_tmp_rect,screen, &b_left_rect);
    SDL_BlitSurface(b_flag, NULL,screen,&b_left_rect);
    SDbomb_count++;
    break;
  case b_center:
    SDL_BlitSurface(background_image, &b_tmp_rect,screen, &b_center_rect);
    SDL_BlitSurface(b_flag, NULL,screen,&b_center_rect);
    SDbomb_count++;
    break;
  case b_right:
    SDL_BlitSurface(background_image, &b_tmp_rect,screen, &b_right_rect);
    SDL_BlitSurface(b_flag, NULL,screen,&b_right_rect);
    SDbomb_count++;
    break;
  case b_king:
    SDL_BlitSurface(background_image, &b_tmp_rect2,screen, &b_king_rect);
    SDL_BlitSurface(b_kingflag, NULL,screen,&b_king_rect);
    SDbomb_count++;
    break;
  default:
    break;
  }

  return;
}


void Update(SDL_Rect *a)
{
  screen = SDL_GetVideoSurface();
  SDL_BlitSurface(background_image, a, screen, a);
  SDL_Flip(screen);
  return;
}


void square_poison(int direction)
{
  int interval=1000;
  int *param=NULL;

  switch (direction) {
  case dirSouth:
    if (map[mycharacter.square_x-1][mycharacter.square_y] != doku) {
      ptimer_id = SDL_AddTimer(interval, poison, param);
    }
    break;
  case dirEast:
    if (map[mycharacter.square_x][mycharacter.square_y-1] != doku) {
      ptimer_id = SDL_AddTimer(interval, poison, param);
    }
    break;
  case dirNorth:
    if (map[mycharacter.square_x+1][mycharacter.square_y] != doku ) {
      ptimer_id = SDL_AddTimer(interval, poison, param);
    }
    break;
  case dirWest:
    if (map[mycharacter.square_x][mycharacter.square_y+1] != doku ) {
      ptimer_id = SDL_AddTimer(interval, poison, param);
    }
    break;
  default:
    break;
  }

  return;
}


Uint32 poison(Uint32 interval, void *param)
{
  mycharacter.HP -= 1;
  drawHP(I);
  return (interval);
}


void square_heal(int direction)
{
  int interval=1000;
  int *param=NULL;

  switch (direction) {
  case dirSouth:
    if (map[mycharacter.square_x-1][mycharacter.square_y] != heal ) {
      htimer_id = SDL_AddTimer(interval, recovery, param);
    }
    break;
  case dirEast:
    if (map[mycharacter.square_x][mycharacter.square_y-1] != heal ) {
      htimer_id = SDL_AddTimer(interval, recovery, param);
    }
    break;
  case dirNorth:
    if (map[mycharacter.square_x+1][mycharacter.square_y] != heal ) {
      htimer_id = SDL_AddTimer(interval, recovery, param);
    }
    break;
  case dirWest:
    if (map[mycharacter.square_x][mycharacter.square_y+1] != heal ) {
      htimer_id = SDL_AddTimer(interval, recovery, param);
    }
    break;
  default:
    break;
  }

  return;
}


Uint32 recovery(Uint32 interval, void *param)
{
  if(mycharacter.HP < 10) mycharacter.HP += 1;
  if(mycharacter.MP < 50) mycharacter.MP += 5;
  drawHP(I);
  drawMP(I);
  return (interval);
}


Uint32 item_appear(Uint32 interval, void *param)
{
  int a = rand() % 3;
  struct addressbox *addrBox;

  addrBox = (struct addressbox *)param;
  
  if (a == 0) {
    set_yakusou();
    send_item_appear(addrBox->socket, addrBox->address, yakusou);
  }
  else if (a == 1) {
    set_attackup();
    send_item_appear(addrBox->socket, addrBox->address, attackup);
  }
  else if (a == 2) {
    set_mine_set();
    send_item_appear(addrBox->socket, addrBox->address, mine_set);
  }
  /* 無敵状態の実装ができるならばここ */

  return (interval);
}


void set_yakusou(void)
{
  SDL_Rect yakusou_rect;

  yakusou_rect.x = 48 * 17;
  yakusou_rect.y = 48;

  map[1][17] = yakusou;
  SDL_BlitSurface(yakusou_image, NULL, screen, &yakusou_rect);
  SDL_Flip(screen);
  
  return;
}


void set_attackup(void)
{
  SDL_Rect attackup_rect;

  attackup_rect.x = 48 * 17;
  attackup_rect.y = 48 * 3;

  map[3][17] = attackup;
  SDL_BlitSurface(kusuri_image, NULL, screen, &attackup_rect);
  SDL_Flip(screen);

  return;
}


void set_mine_set(void)
{
  SDL_Rect mine_set_rect;

  mine_set_rect.x = 48 * 17;
  mine_set_rect.y = 48 * 10;

  map[10][17] = mine_set;
  SDL_BlitSurface(mine_image, NULL, screen, &mine_set_rect);
  SDL_Flip(screen);
  
  return;
}


void func_mine(type_character *character)
{
  character->HP -= 5; //ダメージ量要検討
  if (character->HP <= 0) {
    character->HP = 0;
  }

  return;
}


void func_yakusou(type_character *character)
{
  character->HP += 5; //HP回復量要検討
  if (character->HP >= 10) {
    character->HP = 10;
  }
  
  return;
}


void func_attackup(type_character *character)
{
  character->attack += 5; //攻撃力上昇幅は要検討
  return;
}


Uint32 elx_appear(Uint32 interval, void *param)
{
  struct addressbox *addrBox;

  addrBox = (struct addressbox *)param;

  set_elixir();
  send_item_appear(addrBox->socket, addrBox->address, elixir);
  return (interval);
}


void set_elixir(void)
{
  SDL_Rect elixir_rect;

  elixir_rect.x=48*17;
  elixir_rect.y=48*5;

  map[5][17] = elixir;
  SDL_BlitSurface(elixir_image, NULL, screen, &elixir_rect);
  SDL_Flip(screen);

  return;
}


void func_elixir(type_character *character)
{
  character->MP += 15; //MP回復量要検討
  if (character->MP >= 50) {
    character->MP = 50;
  }
      
  return;
}


/* void gamewin(void) */
/* {               */
/*   int *param=NULL; */

/*   wtimer_id = SDL_AddTimer(5000, gamewin_window, param); */
/*   w_char_timer_id = SDL_AddTimer(1000, game_win_character, param); */

/*   return; */
/* } */


void gamewin(void)
{              
  SDL_Delay(1000);
  game_win_character();
  SDL_Delay(4000);
  gamewin_window();

  return;
}


/* Uint32 gamewin_window(Uint32 interval, void *param) */
void gamewin_window(void)
{
  SDL_Surface *game_win;
  SDL_Event event;
  int mouseX, mouseY;
  int loopflag=1;
  
  //SDL_WM_SetCaption("Flag Breaker!!! 勝利画面", NULL);
  SDL_WM_SetCaption("Flag Breaker!!! Win", NULL);
    
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_HWSURFACE);

  game_win = IMG_Load("./bg/game_win.png");

  SDL_BlitSurface(game_win, NULL, screen, NULL);

  SDL_Flip(screen);

  /* マウスカーソルを表示 */
  SDL_ShowCursor(1);

  while (loopflag) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
	if (event.type == SDL_QUIT) {
	  printf("quit\n");
	  exit(1);
	}
	
      case SDL_MOUSEBUTTONDOWN:
	SDL_GetMouseState(&mouseX, &mouseY);
	if(943 < mouseX && mouseX < 1642 && 714 < mouseY && mouseY < 829 ) {
	  loopflag = 0;
	}
	break;
	
      default:
	break;
      }
    }
  }

  drop_surface(game_win);

  return;
  /*   return 0; */
}


/* Uint32 game_win_character(Uint32 interval, void *param) */
void game_win_character(void)
{
  SDL_Surface *b_win;
  SDL_Surface *r_lose;

  b_win = IMG_Load("./char/win_blue.png");
  r_lose = IMG_Load("./char/lose_red.png");

  Update(&mycharacter.dst_rect);
  Update(&yourcharacter.dst_rect);

  SDL_BlitSurface(
		  b_win,
		  NULL,
		  screen,
		  &mycharacter.dst_rect
		  );
  SDL_BlitSurface(
		  r_lose,
		  NULL,
		  screen,
		  &yourcharacter.dst_rect
		  );
  
  SDL_Flip(screen);
  
  return;
  /*   return (interval); */
}


/* void gamelose(void) */
/* { */
/*   int *param=NULL; */

/*   ltimer_id = SDL_AddTimer(5000, gamelose_window, param); */
/*   l_char_timer_id = SDL_AddTimer(1000, game_lose_character, &target); */

/*   return; */
/* } */


void gamelose(void)
{
  SDL_Delay(1000);
  game_lose_character();
  SDL_Delay(4000);
  gamelose_window();

  return;
}


/* Uint32 gamelose_window(Uint32 interval, void *param) */
void gamelose_window(void)
{
  SDL_Surface *game_lose;
  SDL_Event event;
  int mouseX, mouseY;
  int loopflag=1;
  
  SDL_RemoveTimer(ltimer_id);
  SDL_RemoveTimer(l_char_timer_id);

  //SDL_WM_SetCaption("Flag Breaker!!! 敗北画面", NULL);
  SDL_WM_SetCaption("Flag Breaker!!! Lose", NULL);
    
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_HWSURFACE);

  game_lose = IMG_Load("./bg/game_lose.png");

  SDL_BlitSurface(game_lose, NULL, screen, NULL);

  SDL_Flip(screen);

  /* マウスカーソルを表示 */
  SDL_ShowCursor(1);

  while (loopflag) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
	if (event.type == SDL_QUIT) {
	  printf("quit\n");
	  exit(1);
	}
	
      case SDL_MOUSEBUTTONDOWN:
	SDL_GetMouseState(&mouseX, &mouseY);
	if(943 < mouseX && mouseX < 1642 && 714 < mouseY && mouseY < 829 ) {
	  loopflag = 0;
	}
	break;
	
      default:
	break;
      }
    }
  }

  drop_surface(game_lose);

  return;
  /* return 0; */
}


/* Uint32 game_lose_character(Uint32 interval, void *param) */
void game_lose_character(void)
{
  SDL_Surface *b_lose;
  SDL_Surface *r_win;

  b_lose = IMG_Load("./char/lose_blue.png");
  r_win = IMG_Load("./char/win_red.png");

  Update(&yourcharacter.dst_rect);
  Update(&mycharacter.dst_rect);

  SDL_BlitSurface(
		  r_win,
		  NULL,
		  screen,
		  &yourcharacter.dst_rect
		  );
  SDL_BlitSurface(
		  b_lose,
		  NULL,
		  screen,
		  &mycharacter.dst_rect
		  );

  SDL_Flip(screen);

  return;
  /* return (interval); */
}


void respawn(int target, SDL_Rect *rect_tmp, SDL_Rect *scr_rect)
{
  int interval = 5000;
  int *param=NULL;
  double pre_attack;
  
  switch (target) {
  case I:
    keylock_flag = 1;   // keylockフラグ立て

    pre_attack = mycharacter.attack;
    Update(&mycharacter.dst_rect);
    map[mycharacter.square_x][mycharacter.square_y] = normal;
    init_my_status_and_rect(rect_tmp, scr_rect);
    // map[mycharacter.square_x][mycharacter.square_y] = object;
    mycharacter.attack = pre_attack;
    
    SDL_BlitSurface(deadcharacter_image, NULL, screen, &mycharacter.dst_rect);
    drawHP(I);
    drawMP(I);
    
    SDL_RemoveTimer(ptimer_id);
    timer_id = SDL_AddTimer(interval, respawn_end, param);
    break;

  case you:
    pre_attack = yourcharacter.attack;
    Update(&yourcharacter.dst_rect);
    init_your_status_and_rect(rect_tmp, scr_rect);
    mycharacter.attack = pre_attack;
    
    SDL_BlitSurface(deadcharacter_image, NULL, screen, &yourcharacter.dst_rect);
    drawHP(you);
    drawMP(you);
    break;
  }
    
  return;
}


Uint32 respawn_end(Uint32 interval, void *param)
{
  SDL_RemoveTimer(timer_id);
  keylock_flag = 0;   // keylockフラグ下ろし
  draw_character(&mycharacter, screen, 0);
  return 0;
}


/* サーフェス破棄 */
void drop_surface(SDL_Surface *surface)
{
  SDL_FreeSurface(surface);
  return;
}
