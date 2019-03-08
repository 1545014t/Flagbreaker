#ifndef _NETWORKS_H_
#define _NETWORKS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "common.h"


/* 通信設定 */
#define DEFAULT_PORT 6000
#define MAX_MSG 1024
#define CHANNEL 0

/* マップ設定 */
#define SQUARE_SIZE 48
#define MAP_SIZE_WIDTH 35
#define MAP_SIZE_HEIGHT 12

#define SEND_ATTACK(target, target_HP) send_attack(mySocket, &yourAddr, mycharacter.MP, target, target_HP)
#define STRNCMP(STRING_A,STRING_B) strncmp(STRING_A, STRING_B, strlen(STRING_B))
#define RECEIVE_FIRST(SOCKET, P_BUF, P_ADDR) receive_message(1, SOCKET, P_BUF, P_ADDR)
#define RECEIVE_NORMAL(SOCKET, P_BUF, P_ADDR) receive_message(0, SOCKET, P_BUF, P_ADDR)


typedef enum _Status {
  CONNECTED,     /* 接続中 */
  DISCONNECTED   /* 切断中 */
} Status;

typedef enum _Judge {
  SELECT,    /* 選択可能 */
  PAUSING,   /* 自分が相手の返答待機中 */
  WAITED,    /* 相手が自分の返答待機中 */
  RUN        /* 実行中 */
} JUDGE;

typedef enum _Control {
  OPEN_SESSION,          /* clientからserverへの接続要求 */
  CLOSE_SESSION,         /* 切断要求 */
  GAME_END,              /* SDL_QUIT実行(途中終了) */
  SESSION_ESTABLISHED,   /* serverからclientへの接続許可 */
  GAME_START,            /* game実行要求 */
  COORDINATION,          /* キャラクタの座標データ */
  STATUS,                /* キャラクタのステータスデータ */
  ATTACK,                /* 攻撃データ */
  ITEM_APPEAR,           /* アイテム出現データ */
  GET_ITEM,              /* アイテム取得時データ */
  BOMB_APPEAR,           /* ランダムボム出現データ */
  BOMB_EXPLODE,          /* ランダムボム爆発データ */
  RESPAWN,               /* リスポーン通知 */
  GAMEOVER,              /* ゲーム終了通知 */
  EXCEPTION              /* その他 */
} Control;


typedef struct _Control_Parameter {
  Control control;   /* メッセージの種類 */
  char *parameter;   /* メッセージデータ */
} Control_parameter;


UDPsocket server_socket_and_bind(int myPort);
UDPsocket client_socket_and_bind(int myPort, char *hostname, int hostPort, IPaddress *p_addr);
int send_message(UDPsocket mySocket, char *buf, IPaddress *p_addr);
int send_open_session(UDPsocket mySocket, IPaddress *p_addr);
int send_close_session(UDPsocket mySocket, IPaddress *p_addr);
int send_game_end(UDPsocket mySocket, IPaddress *p_addr);
int send_game_start(UDPsocket mySocket, IPaddress *p_addr);
int send_coordinateion(UDPsocket mySocket, IPaddress *p_addr, int x, int y, int direction);
int send_status(UDPsocket mySocket, IPaddress *p_addr, double hp, double mp);
int send_attack(UDPsocket mySocket, IPaddress *p_addr, double mp, int target, double hp);
int send_get_item(UDPsocket mySocket, IPaddress *p_addr, int itemcode);
int send_randbomb_appear(UDPsocket mySocket, IPaddress *p_addr, int x, int y);
int send_randbomb_explode(UDPsocket mySocket, IPaddress *p_addr, int x, int y);
int send_respawn(UDPsocket mySocket, IPaddress *p_addr);
int send_gameover(UDPsocket mySocket, IPaddress *p_addr);
int send_session_established(UDPsocket mySocket, IPaddress *p_addr);
int receive_message(int flag, UDPsocket mySocket, char *buf, IPaddress *p_addr);
int sockaddr_in_cmp(IPaddress *first, IPaddress *second);
Control_parameter message_interpreter(char *buffer);

#endif /* _NETWORKS_H_ */
