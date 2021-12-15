

#include "list.h"
//#include "server.h"
#define DEFAULT_ROOM "Lobby"
#include <time.h>


struct USER *head = NULL;
struct ROOM *roomhead = NULL;
struct USERSINROOMS *usersinroomhead = NULL;

int main(int argc, char **argv)
{
    /////// ROOM Functions ///////
    /*
    void printListRoom(struct ROOM *head);
    void display_rooms(struct USERSINROOMS *l, char *buf);
    struct ROOM* insertFirstRoom(struct ROOM *head, char *groupname);
    struct ROOM* deleteFirstRoom(struct ROOM *head);
    bool isEmptyRoom(struct ROOM *head);
    int lengthRoom(struct ROOM *head);
    struct ROOM* findRoom(struct ROOM *head, char* groupname);
    struct ROOM* deleteRoom(struct ROOM *head, char* groupname);
    void destroyRoom(struct ROOM *head);
    */
  

    roomhead = insertFirstRoom(roomhead,DEFAULT_ROOM);
    roomhead = insertFirstRoom(roomhead,"Room A");
    roomhead = insertFirstRoom(roomhead,"Room B");
    roomhead = insertFirstRoom(roomhead,"Room C");
  
  
    
    printListRoom(roomhead);
    printf("\n-------------------------------\n");
    
  
    /////// USER Functions ///////
    /*
    struct USER* insertFirstU(struct USER *head, int socket, char *username);
    struct USER* findU(struct USER *head, char* username);
    void printListU(struct USER *node); ///server side
    void display_users(struct USER *l, char *buf, int s);
    struct USER* deleteFirstU(struct USER *head);
    bool isEmptyU(struct USER *head);
    int lengthU(struct USER *head);
    struct USER* findSocketU(struct USER *head, int socket);
    struct USER* findU(struct USER *head, char* username);
    struct USER* deleteSocketU(struct USER *head, int socket);
    struct USER* deleteU(struct USER *head, char* username);
    void destroyU(struct USER *head);
    */

  
    head = insertFirstU(head, 28, "John");
    head = insertFirstU(head, 23328, "Joe");
    head = insertFirstU(head, 177, "Paul");
    //head = insertFirstU(head, 282, "John");
    printListU(head); 
    printf("\n-------------------------------\n");
   
    // head = deleteSocketU(head,282); //dc from a room
     //head = deleteU(head, "Paul"); // logining 
     //head = deleteSocketU(head,28); //dc from a room
    
    //printListU(head); 
    printf("\n-------------------------------\n");
  
    /////// USERSINROOMS Functions ///////
    /*
    void printListUsersInRooms(struct USERSINROOMS *head);
    struct USERSINROOMS* insertFirstUsersInRooms(struct USERSINROOMS *head, char *groupname);
    struct USERSINROOMS* deleteFirstUsersInRooms(struct USERSINROOMS *head);
    bool isEmptyUsersInRooms(struct USERSINROOMS *head);
    int lengthUsersInRooms(struct USERSINROOMS *head);
    struct USERSINROOMS* findUsersInRooms(struct USERSINROOMS *head, char* groupname);
    struct USERSINROOMS* deleteUsersInRooms(struct USERSINROOMS *head, char* groupname);
    void destroyUsersInRooms(struct USERSINROOMS *head);
    */
    
    
    usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room A");
    usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room B");
    usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room C");
    usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room A");
    usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room D");
    usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room B");
    printListUsersInRooms(usersinroomhead);
    //*/

        void timestamp()
  {
      time_t ltime; /* calendar time */
      ltime=time(NULL); /* get current cal time */
      printf("%s",asctime( localtime(&ltime) ) );
  }
    
    return 0;
}

