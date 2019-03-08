#include "networks.h"
#include <math.h>   // 遊び

// 以下遊び用
#define MOJI ">>WAIT>-> >"
#define YOKOHABA 73
#define HAYASA 0.01
#define SA 2

void init_asobi(void);
void asobi(void);

double asobid[9];
double r, g, b;
int rflag, gflag, bflag;


UDPsocket server_socket_and_bind(int port)
{
  UDPsocket mySocket;
  IPaddress myAddr;

  /* ソケット生成 */
  if ( (mySocket = SDLNet_UDP_Open(port)) == NULL ) {
    fprintf(stderr, "Error: SDLNet_UDP_Open\n");
    exit(EXIT_FAILURE);
  }
  
  /* 自身のアドレス構造体設定 */
  if (SDLNet_ResolveHost(&myAddr, NULL, port) == -1) {
    fprintf(stderr, "Error: SDLNet_ResolveHost\n");
    exit(EXIT_FAILURE);
  }

  /* アドレス構造体の情報を生成ソケットに関連づけ */
  if (SDLNet_UDP_Bind(mySocket, CHANNEL, &myAddr) < 0) {
    fprintf(stderr, "Error:bind\n");
    exit(EXIT_FAILURE);
  }

  return mySocket;
}


UDPsocket client_socket_and_bind(int myPort, char *hostname, int hostPort, IPaddress *p_addr)
{
  UDPsocket mySocket;

  /* 名前解決 */
  if (SDLNet_ResolveHost(p_addr, hostname, hostPort) == -1) {
    fprintf(stderr, "Error: SDLNet_ResolveHost\n");
    exit(EXIT_FAILURE);
  }
  
  /* ソケット生成 */
  if ( (mySocket = SDLNet_UDP_Open(myPort)) == NULL ) {
    fprintf(stderr, "Error: SDLNet_UDP_Open\n");
    exit(EXIT_FAILURE);
  }
  
  /* アドレス構造体の情報を生成ソケットに関連づけ */
  if (SDLNet_UDP_Bind(mySocket, CHANNEL, p_addr) < 0) {
    fprintf(stderr, "Error:bind\n");
    exit(EXIT_FAILURE);
  }

  return mySocket;
}


int send_message(UDPsocket mySocket, char *buf, IPaddress *p_addr)
{
  int sent_len;
  UDPpacket *packet;

  packet = SDLNet_AllocPacket(MAX_MSG);
  if (packet == NULL) {
    fprintf(stderr, "ERROR: SDLNet_AllocPacket\n");
    exit(EXIT_FAILURE);
  }
  
  //packet->channel = CHANNEL;
  packet->len = strlen(buf) + 1;
  //packet->maxlen = MAX_MSG;
  packet->address.host = p_addr->host;
  packet->address.port = p_addr->port;
  memcpy(packet->data, buf, packet->len);

  sent_len = SDLNet_UDP_Send(mySocket, -1, packet);
  if (sent_len == 0) {
    fprintf(stderr, "ERROR: SDLNet_UDP_Send\n");
    exit(EXIT_FAILURE);
  }

  SDLNet_FreePacket(packet);

  return sent_len;
}


int send_open_session(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "open_session", p_addr);
}


int send_close_session(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "close_session", p_addr);
}


int send_game_end(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "game_end", p_addr);
}


int send_game_start(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "game_start", p_addr);
}


int send_coordinateion(UDPsocket mySocket, IPaddress *p_addr, int x, int y, int direction)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "coordination:%d:%d:%d", x, y, direction);
  return send_message(mySocket, buffer, p_addr);
}


int send_gameover(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "gameover", p_addr);  
}


int send_status(UDPsocket mySocket, IPaddress *p_addr, double hp, double mp)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "status:%f:%f", hp, mp);
  return send_message(mySocket, buffer, p_addr);
}


int send_attack(UDPsocket mySocket, IPaddress *p_addr, double mp, int target, double hp)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "attack:%f:%d:%f", mp, target, hp);
  return send_message(mySocket, buffer, p_addr);
}


int send_item_appear(UDPsocket mySocket, IPaddress *p_addr, int itemcode)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "item_appear:%d", itemcode);
  return send_message(mySocket, buffer, p_addr);
}


int send_get_item(UDPsocket mySocket, IPaddress *p_addr, int itemcode)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "get_item:%d", itemcode);
  return send_message(mySocket, buffer, p_addr);
}


int send_respawn(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "respawn", p_addr);  
}


int send_randbomb_appear(UDPsocket mySocket, IPaddress *p_addr, int x, int y)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "randbomb_appear:%d:%d", x, y);
  return send_message(mySocket, buffer, p_addr);
}


int send_randbomb_explode(UDPsocket mySocket, IPaddress *p_addr, int x, int y)
{
  char buffer[MAX_MSG];
  sprintf(buffer, "randbomb_explode:%d:%d", x, y);
  return send_message(mySocket, buffer, p_addr);
}
  

int send_session_established(UDPsocket mySocket, IPaddress *p_addr)
{
  return send_message(mySocket, "session_established", p_addr);  
}


int receive_message(int flag, UDPsocket mySocket, char *buf, IPaddress *p_addr)
{
  int judge;
  UDPpacket *packet;


  packet = SDLNet_AllocPacket(MAX_MSG);
  if (packet == NULL) {
    fprintf(stderr, "ERROR: SDLNet_AllocPacket\n");
    exit(EXIT_FAILURE);
  }
  
  init_asobi();   // 遊び

  do {   // main内の通信のみloop

    if (flag) {   // 遊び
      asobi();
    }

    judge = SDLNet_UDP_Recv(mySocket, packet);
    switch (judge) {
    case 0:
      break;
    case 1:
      memcpy(buf, packet->data, packet->len);
      p_addr->host = packet->address.host;
      p_addr->port = packet->address.port;
      flag = 0;   // 確認完了
      break;
    case -1:
      break;
    }

  } while (flag);   // ブロッキング用繰り返し

  SDLNet_FreePacket(packet);

  return judge;
}


int sockaddr_in_cmp(IPaddress *first, IPaddress *second)
{
  if (first->port == second->port && first->host == second->host) {
    return 0;
  } else{
    return 1;
  }
}


Control_parameter message_interpreter(char *buffer)
{
  Control_parameter control_parameter;
  static char parameter[MAX_MSG];

  control_parameter.parameter = parameter;
  if (!STRNCMP(buffer, "open_session")) {
    control_parameter.control = OPEN_SESSION;
  } else if (!STRNCMP(buffer, "close_session")) {
    control_parameter.control = CLOSE_SESSION;
  } else if (!STRNCMP(buffer, "game_end")) {
    control_parameter.control = GAME_END;
  } else if (!STRNCMP(buffer, "game_start")) {
    control_parameter.control = GAME_START;
  } else if (!STRNCMP(buffer, "session_established")) {
    control_parameter.control = SESSION_ESTABLISHED;
  } else if (!STRNCMP(buffer, "coordination")) {
    sscanf(buffer, "coordination:%[^\n]", parameter);
    control_parameter.control = COORDINATION;
  } else if (!STRNCMP(buffer, "status")) {
    sscanf(buffer, "status:%[^\n]", parameter);
    control_parameter.control = STATUS;
  } else if (!STRNCMP(buffer, "attack")) {
    sscanf(buffer, "attack:%[^\n]", parameter);
    control_parameter.control = ATTACK;
  } else if (!STRNCMP(buffer, "item_appear")) {
    sscanf(buffer, "item_appear:%[^\n]", parameter);
    control_parameter.control = ITEM_APPEAR;
  } else if (!STRNCMP(buffer, "get_item")) {
    sscanf(buffer, "get_item:%[^\n]", parameter);
    control_parameter.control = GET_ITEM;
  } else if (!STRNCMP(buffer, "randbomb_appear")) {
    sscanf(buffer, "randbomb_appear:%[^\n]", parameter);
    control_parameter.control = BOMB_APPEAR;
  } else if (!STRNCMP(buffer, "randbomb_explode")) {
    sscanf(buffer, "randbomb_explode:%[^\n]", parameter);
    control_parameter.control = BOMB_EXPLODE;
  } else if (!STRNCMP(buffer, "respawn")) {
    control_parameter.control = RESPAWN;
  } else if (!STRNCMP(buffer, "gameover")) {
    control_parameter.control = GAMEOVER;
  } else { 
    control_parameter.control = EXCEPTION;
  }

  return control_parameter;
}
　

void init_asobi(void)
{
  int i;

  for (i=0; i<9; i++) {
    asobid[i] = i * SA;
  }

  r=0, g=0, b=0;
  rflag=0, gflag=0, bflag=0;

  return;
}

void asobi(void)
{
  int i;
  int cnt=0, rollflag=0;
  
  clear();
  attron(COLOR_PAIR(1));
  mvaddstr( 0, 0, "|> Waiting for oppornent.");
  mvaddstr( 1, 0, "|> please stand by");
  
  switch (rollflag) {
  case 0:
    mvaddstr(1,18, "");
    break;
  case 1:
    mvaddstr(1,18, ".");
    break;
  case 2:
    mvaddstr(1,18, "..");      
    break;
  case 3:
    mvaddstr(1,18, "...");
    break;
  }
  
  if (cnt < 1000) {  
    mvaddstr(1,30, "|");
  } else if (1000 <= cnt && cnt < 2000) {
    mvaddstr(1,30, "\\");
  } else if (2000 <= cnt && cnt < 3000) {
    mvaddstr(1,30, "-");
  } else if (3000 <= cnt) {
    mvaddstr(1,30, "/");
  }
  cnt++;
  cnt %= 4000;
  if (cnt == 0) {
    rollflag++;
    rollflag %= 4;
  }
  
  init_color(COLOR_RED, (int)r, (int)g, (int)b);
  attron(COLOR_PAIR(2));
  
  for (i=0; i<9; i++) {
    mvaddstr( 3+i, (int)asobid[i], MOJI);
    mvaddstr(19-i, (int)asobid[i], MOJI);
    asobid[i] += HAYASA;
    asobid[i] = fmod(asobid[i], YOKOHABA);
  }

  if (r == 1000) rflag = 1; else if (r == 0) rflag = 0;
  if (g == 1000) gflag = 1; else if (g == 0) gflag = 0;
  if (b == 1000) bflag = 1; else if (b == 0)  bflag = 0;
  
  if (rflag == 0) r += 0.5; else r -= 2.0;
  if (gflag == 0) g += 1.0; else g -= 0.5;
  if (bflag == 0) b += 2.0; else b -= 1.0;
  
  refresh();
  
  return;
}
