#ifndef _COMMON_H_#define _COMMON_H_#include <SDL_net.h>enum SQUARE_data {  normal,       /* 普通のマス */  object,       /* 障害物あり */  doku,         /* ダメージマス */  heal,         /* 回復マス */  mine,         /* ランダム地雷 */  mine_set,     /* 地雷スイッチ */  yakusou,      /* 薬草(HP回復) */  attackup,     /* 攻撃力アップ */  star,         /* 無敵 */  elixir,       /* MP回復 */  SDbomb,       /* ボム? */  chasebomb,  randombomb};struct addressbox {  UDPsocket socket;  IPaddress *address;};// in networks.cint send_item_appear(UDPsocket mySocket, IPaddress *p_addr, int itemcode);#endif /* _COMMON_H_ */