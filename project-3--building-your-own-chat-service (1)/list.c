#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
// Stretch feature: timestamps for messages 
// 
// Authors 
// <Izaac Ballard> <Noah Lee> <James Fisher> <Dion Simmons> <Akosua Wordie>
// <Myles Bostic> <Morenike Onifade> <Lea Clements> <Teanna Barrett> <Iyinoluwa Tugbobo> 
// <Kobe Petrus> <Allan Shane Oliver> 
// 
// ****When we do join of room, if room doesnt exist, 
// it still shows up when we type 'users' and 'rooms'
/////////////////////////////// USERLIST ////////////////////////////////
//display the list
void printListU(struct USER *head) 
{
  struct USER *ptr = head;
  struct USER *dm;
   printf("[Users:\n");
   //start from the beginning
   while(ptr != NULL) 
  {
      printf("USERNAME: %s \n ID: %d ",ptr->username , ptr->socket);
      ///*
      dm = ptr->dmhead;
      printf("\n [DM: ");
      while(dm != NULL)
      {
          printf("(%s,%d) ",dm->username, dm->socket);
          dm = dm->next;
      }
      printf("]");
      printListRoom(ptr->head); 
      //*/
      ptr = ptr->next;
      printf("\n");    
   }
   printf("]\n");
}

void display_users(struct USER *head, char *buf, int self) 
{
  struct USER *ptr = head;
  char tmpbuf[1024];
  if (ptr == NULL)
  {
    sprintf(buf,"no logins!\n");
  }
  else
  {
      sprintf(buf,"[USERS]: ");
      while(ptr != NULL) 
      {
        if(lengthRoom(ptr->head) == 0 && lengthU(ptr->dmhead) == 0 && ptr->socket != self) 
        {  // not belong to any groups or any DMs
            sprintf(tmpbuf,"%s", ptr->username);
            strcat(buf, tmpbuf);
            ptr = ptr->next;
            if(ptr == NULL)
            {
              strcat(buf, "]\n");
            }
            else
            {
              strcat(buf, ", ");
            }         
        }
      }
  }
}

//insert link at the first location
struct USER* insertFirstU(struct USER *head, int socket, char *username) 
{  
   if(findU(head,username) == NULL) 
   {       
       //create a link
       struct USER *link = (struct USER*) malloc(sizeof(struct USER));
       link->socket = socket;
       strcpy(link->username,username);
       //link->head = NULL;
       //link->dmhead = NULL;
       
       //point it to old first USER
       link->next = head;
       //point first to new first USER
       head = link;
   }
   else
   {
     printf("Duplicate: %s\n", username);
   } 
   return head;
}

//Extra Code
//delete first item
struct USER* deleteFirstU(struct USER *head)
{
   //save reference to first link
   struct USER *tempLink = head;
   //mark next to first link as first 
   head = head->next;
   //return the deleted link
   free(tempLink);
   return head;
}

//is list empty
bool isEmptyU(struct USER *head) 
{
   return head == NULL;
}

int lengthU(struct USER *head) 
{
   int length = 0;
   struct USER *current;
   for(current = head; current != NULL; current = current->next) 
   {
      length++;
   }
   return length;
}

//find a link with given socket
struct USER* findSocketU(struct USER *head, int socket) 
{
   //start from the first link
   struct USER* current = head;
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   //navigate through list
   while(current->socket != socket) 
   {
      //if it is last USER
      if(current->next == NULL) 
        {
           return NULL;
        } 
      else 
       {
           //go to next link
         current = current->next;
       }
   }      
   //if socket found, return the current Link
   return current;
}

//find a link with given user
struct USER* findU(struct USER *head, char* username) 
{
   //start from the first link
   struct USER* current = head;
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   //navigate through list
    while(strcmp(current->username, username) != 0) 
    {
      //if it is last USER
      if(current->next == NULL)
        {
           return NULL;
        } 
      else 
      {
         //go to next link
         current = current->next;
      }
   }      
   //if username found, return the current Link
   return current;
}

//delete a link with given socket
struct USER* deleteSocketU(struct USER *head, int socket)  /// disconnect from a rooom 
{
   //start from the first link
   struct USER* current = head;
   struct USER* previous = NULL;
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   else
   if(findSocketU(head,socket)== false)
   {
       printf("Socket: %d Does Not Exist!\n",socket);
       return head;
   }
 
   //navigate through list
   while(current->socket != socket) 
   {
      //if it is last USER
      if(current->next == NULL) 
        {
           return NULL;
        } 
      else 
       {
           //store reference to current link
           previous = current;
           //move to next link
           current = current->next;
      }
   }
   //found a match, update the link
   if(current == head) 
     {
        //change first to point to next link
        head = head->next;
     } 
   else 
    {
        //bypass the current link
        previous->next = current->next;
    }    
   free(current);
   printf("Socket: %d Has Been Removed\n",socket);
   return head;
}

//delete a link with given username
struct USER* deleteU(struct USER *head, char* username) 
{
   //start from the first link
   struct USER* current = head;
   struct USER* previous = NULL;
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   else
   if(findU(head,username)== false)
   {
       printf("User: %s Does Not Exist!\n",username);
       return head;
   }
   //navigate through list
   while(strcmp(current->username, username) != 0) 
   {
      //if it is last USER
      if(current->next == NULL)
        {
           return NULL;
        } 
      else 
      {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }
   //found a match, update the link
   if(current == head) 
   {
      //change first to point to next link
      head = head->next;
   } 
  else 
  {
      //bypass the current link
      previous->next = current->next;
  }   
   free(current);
   //printf("User: %s Has Been Logged Out\n",username);
   return head;
}

void destroyU(struct USER *head)
{
    struct USER *cursor, *tmp;
    if(head != NULL)
    {
      cursor = head->next;
      head->next = NULL;
      while(cursor != NULL)
      {
          tmp = cursor->next;
          free(cursor);
          cursor = tmp;
      }
    }
}

/////////////////////////////// ROOMLIST ////////////////////////////////

//display the list
void printListRoom(struct ROOM *head) 
{
   struct ROOM *ptr = head;
   printf("\n Rooms:");
   //start from the beginning
   while(ptr != NULL) 
   {
      printf("(%s) ",ptr->roomname);
     // printListU(ptr->head);
      ptr = ptr->next;
   }
   printf(" ]\n");
}

void display_rooms(struct USERSINROOMS *head, char *buf) 
{
  struct USERSINROOMS *ptr = head;
  char tmpbuf[1024];
  if (ptr == NULL)
  {
    sprintf(buf,"no rooms!\n");
  }
  else
  {
      sprintf(buf,"[Rooms: ");
      while(ptr != NULL) 
      {
        sprintf(tmpbuf,"%s", ptr->roomname);
        ptr = ptr->next;
        strcat(buf, tmpbuf);
        if(ptr == NULL)
        {
          strcat(buf, "]\n");
        }
        else
        {
          strcat(buf, ", ");
        }    
       }
  }
}

//insert link at the first location
struct ROOM* insertFirstRoom(struct ROOM *head, char *roomname) 
{
    //head = NULL;
   if(findRoom(head,roomname) == NULL) 
   {        
       //create a link
       struct ROOM *link = (struct ROOM*) malloc(sizeof(struct ROOM));
       strcpy(link->roomname,roomname);
       //link->head = NULL;
       //point it to old first USER
       link->next = head;
       //point first to new first USER
       head = link;
   }
   else
   {
      printf("Duplicate Room: %s\n", roomname);
   }
   return head;
}

//Extra Code
//delete first item
struct ROOM* deleteFirstRoom(struct ROOM *head) 
{
   //save reference to first link
   struct ROOM *tempLink = head;
   //mark next to first link as first 
   head = head->next;
   //return the deleted link
   free(tempLink);
   return head;
}

//is list empty
bool isEmptyRoom(struct ROOM *head) 
{
   return head == NULL;
}

int lengthRoom(struct ROOM *head) 
{
   int length = 0;
   struct ROOM *current;
   for(current = head; current != NULL; current = current->next) 
   {
      length++;
   }
   return length;
}

//find a link with given group
struct ROOM* findRoom(struct ROOM *head, char* roomname) 
{
   //start from the first link
   struct ROOM* current = head;
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   //navigate through list
    while(strcmp(current->roomname, roomname) != 0)
    {
      //if it is last USER
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         //go to next link
         current = current->next;
      }
    }      
   //if username found, return the current Link
   return current;
}

//delete a link with given rooomname
struct ROOM* deleteRoom(struct ROOM *head, char* roomname) 
{
   //start from the first link
   struct ROOM* current = head;
   struct ROOM* previous = NULL;
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   //navigate through list
   while(strcmp(current->roomname, roomname) != 0)
   {
      //if it is last USER
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }
   //found a match, update the link
   if(current == head) 
   {
      //change first to point to next link
      head = head->next;
   } 
   else 
   {
      //bypass the current link
      previous->next = current->next;
   }   
   free(current);
   return head;
}

void destroyRoom(struct ROOM *head)
{
    struct ROOM *cursor, *tmp;
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}


/////////////////// USERSINROOMS FUNCTIONS //////////////////////////

//display the list SERVER SIDE
void printListUsersInRooms(struct USERSINROOMS *head)
{
  struct USERSINROOMS *ptr = head; //save allinfo to a local variable
  struct USER *userptr = ptr->head;
  while(ptr !=NULL)
  {
    printf("(Room: %s)\n" , ptr->roomname);
    //ptr = ptr->head; // refers to users
    while(userptr != NULL)
    {
      printf("(User: %s)\n" , userptr->username);
      userptr = userptr->next;
    }
    //printListUsersInRooms(ptr->head);
    ptr = ptr->next; // next item which is 2nd room and we repeat bc loop
    printf("\n");
  }
}

void display_usersinrooms(struct USERSINROOMS *head, char *buf) 
{
  struct USERSINROOMS *ptr = head;
  char tmpbuf[1024]; 
  if (ptr == NULL){
    sprintf(buf,"There Are No ROOMS!\n");
  }
  else{
      sprintf(buf,"[Available Rooms]\n[ ");
      while(ptr != NULL) 
      {
        sprintf(tmpbuf," (%s) ", ptr->roomname);
        ptr = ptr->next;
        strcat(buf, tmpbuf);
        if(ptr == NULL)
        {
            strcat(buf, " ]\n");
        }
        else
            strcat(buf, ", ");
      }
  }
}

  
struct USERSINROOMS* insertFirstUsersInRooms(struct USERSINROOMS *allusersinrooms, char *selectedRoom)
{
  if(findUsersInRooms(allusersinrooms,selectedRoom)== NULL)
  {
    //create a link
    struct USERSINROOMS *link = (struct USERSINROOMS*) malloc(sizeof(struct USERSINROOMS));
    strcpy(link->roomname,selectedRoom);
    link->head = NULL;
    
    // point first to old first Item
    link->next = allusersinrooms;
    
    // point first to new first Item
    allusersinrooms = link;
  }
  else
  {
    printf("Duplicate Room: %s\n",selectedRoom);
  }
  return allusersinrooms;
}
  
  
struct USERSINROOMS* deleteFirstUsersInRooms(struct USERSINROOMS *head)
{
  
   //save reference to first link
   struct USERSINROOMS *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   free(tempLink);
   return head;

}
//*/

//is list empty?
bool isEmptyUsersInRooms(struct USERSINROOMS *head)
{
  return head == NULL;
}

int lengthUsersInRooms(struct USERSINROOMS *head)
{
  int length = 0;
  struct USERSINROOMS *current;
  for(current = head; current != NULL; current = current->next) 
  {
    length++;
  }
   return length;
}

//find a link with given socket
struct USERSINROOMS* findUsersInRooms(struct USERSINROOMS *head, char* roomname)
{
    struct USERSINROOMS* currentitem = head;
    //if list is empty
    if(head == NULL)
    {
      return NULL;
    }
    //navigate through rooms
    //navigate through list
    while(strcmp(currentitem->roomname, roomname) != 0)
    {
      //if it is last node
      if(currentitem->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         //go to next link
         currentitem = currentitem->next;
      }
    }      
	
   //if username found, return the current Link
   return currentitem;
}

//delete a link with given groupname
struct USERSINROOMS* deleteUsersInRooms(struct USERSINROOMS *head, char* roomname)
{
  //start from the first link
   struct USERSINROOMS* current = head;
   struct USERSINROOMS* previous = NULL;
	
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }
   //navigate through list
   while(strcmp(current->roomname, roomname) != 0) 
   {
      //if it is last node
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }
   //found a match, update the link
   if(current == head) 
   {
      //change first to point to next link
      head = head->next;
   } 
   else 
   {
    //bypass the current link
    previous->next = current->next;
   }  
   free(current);
   return head;

}

void destroyUsersInRooms(struct USERSINROOMS *head)
{
    struct USERSINROOMS *cursor, *tmp;
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
} 



  
  
  
  
  
//// OLD CODE PLUS BURGE AT BOTTOM BOTTOM  
//{
//}
  /*
  //struct USER* userlinkedlist; // has info of uname next member and dms socket
  //roomname
  struct USERSINROOMS* currentRoomWithUsers = head;
  
  if(head == NULL)
  {
    return NULL;
  }
  //userlinkedlist = findU(userlinkedlist,username);
  while(strcmp(currentRoomWithUsers->roomname,roomname) != 0)
  {
    //if it's the last ROOM W USERS
    if(currentRoomWithUsers->next == NULL)
    {
      return NULL;
    }
    else
    {
      //go to next room w users
      //headofallusers = userlinkedlist;
      currentRoomWithUsers = currentRoomWithUsers->next;
    }
  }
   return currentRoomWithUsers;
}

  
  
 
   int i; 
   for(i = 0; i < 5; i++)// LOOPS TO PRINT ALL ROOMS
   {
      struct USERSINROOMS *printTemp = roomArray[i];
      struct USER *userlinkedlist; // needs to get info but how?
      printf("Room[%p]\n",roomArray[i]);//allinfo->roomname);//headofallusers);//->username);
      printf("\t Users:\n");
      while(printTemp);//allinfo != NULL)
      {  
        //headofallusers 
        //int j = 0;
        printf("Testing: asdiojhhas");
        printf("\t %p \n",printTemp->headofallusers); //j);//allinfo->headofallusers->username);//printTemp->headofallusers);
        //printf("hi");
        //allinfo->next = next->roomname;
        //allinfo=allinfo->next->roomname;//roomname;
        printTemp = printTemp->next;
        //j++;
      }
      
      printf("Null?\n");
   }	
  // printf("\n");  
  */


/*
 * struct USER
{
   char username[30];
   int socket;
   struct ROOM *headofroom; // list of all rooms that user belongs to
   struct USER *dmhead; // list of all users you are connected to
   struct USER *next; //list of all users
};

struct ROOM
{
  char roomname[30];
  struct ROOM *next;
};

struct USERSINROOMS
{
  char roomname[30]; // key
  struct USER *headofallusers; // value // the linked list of users per room
  struct USERSINROOMS *next;
};
//*/
//struct USER *getUInfo(struct USER *listofusers)//retrives username for FirstUsersInRooms // getUInfo backup idea struct USER *getU
//{
  
 // return 
//}
//
//

//insert link at the first location



//insert link at the first location
// CHANGE THIS TO INCLUDE USER AS PARAMETER
//struct USERSINROOMS* insertFirstUsersInRooms(struct USERSINROOMS *allusersinrooms, char *allofroomnames)

  /*
  // lets try calling prev functions 
  //item->headofallusers = allusersinrooms->headofallusers; 
  //if()
    //
    struct ROOM* currentRoom =(struct ROOM*) malloc(sizeof(struct ROOM));
      allofroomnames = currentRoom->roomname; 
     //currentRoom->roomname = allofroomnames;
    //if(findRoom(roomHead,roomHead->roomname))
    while(strcmp(currentRoom->roomname,allofroomnames)!=0)
    {
      if(currentRoom->next == NULL)
      {
        return NULL;
      }
      else
      {
        //goes to next room
        //tempRoom = currentRoom->roomname;
        //currentRoom->roomname = allofroomnames;//->allofroomnames; //tempRoom;
        //allusersinrooms->roomname =  currentRoom->roomname;
        strcpy(allusersinrooms->roomname,allofroomnames);
        currentRoom = currentRoom->next;
        if(findUsersInRooms(allusersinrooms,allofroomnames)==NULL)
          {
           // create item = Room & users to specfied room
          struct USERSINROOMS *item = (struct USERSINROOMS*) malloc(sizeof(struct USERSINROOMS));
          struct USER *linkedlist = (struct USER*) malloc(sizeof(struct USER));
        
          int tempsocket =0;
          char *tempusername;
          //userlinkedlist = findU(userlinkedlist,userlinkedlist->username);
          linkedlist = findU(userlinkedlist,userlinkedlist->username);
          tempusername = linkedlist;
          //strcpy(linkedlist->username,username);

          //Get ALL INfo?
          if(linkedlist == NULL)
          {
              linkedlist = findSocketU(userlinkedlist,userlinkedlist->socket);//cket;
              tempsocket = linkedlist->socket;        
              struct USER *Info = (struct USER*) malloc(sizeof(struct USER));
              Info->socket = tempsocket;
              strcpy(Info->username,tempusername);
              Info->next = linkedlist ;
              linkedlist = Info;
          }
          userlinkedlist = linkedlist;



          //while()
           // while(linkedlist->socket !=tempsocket)
            /{
               //if it is last USER in the room
              if(linkedlist->next == NULL) 
                {
                   return NULL;
                } 
              else 
               {
                   //go to next link
                 linkedlist = linkedlist->next;
               }
            }
            return linkedlist;
          item->headofallusers = userlinkedlist; 
            //char temp[7] = {"ted","bob"};
            userlinkedlist->username = temp;
            userlinkedlist->next = NULL;
          strcpy(item->roomname,allofroomnames);

         //point to old FIRST ROOM W USERS
         item->next = allusersinrooms;

         //point First to new FIRST ROOM W USERS
         allusersinrooms = item;
        }
        else
          {
           printf("Duplicate: %s\n", "Name");
        }
      }  
    
      //allusersinrooms->roomname = currentRoom;
      allusersinrooms->headofallusers = userlinkedlist;
      allusersinrooms = allusersinrooms->next;
    }
    
  return allusersinrooms;
}
//*/
  
  /// This should work in theory as a hash table
  /*
   * 
  int i;
  for(i = 0; i < strlen(allofroomnames);i++)
  {
    roomArray[i] = NULL;
  }

  int i;
  for(i = 0; i < strlen(allofroomnames);i++)
  {
    roomArray[i] = NULL;
  }
  struct USERSINROOMS *item = (struct USERSINROOMS*) malloc(sizeof(struct USERSINROOMS));
  item->headofallusers = allusersinrooms->headofallusers;
  item->next = NULL;
  //HASH position
  int key = i % strlen(allofroomnames);
  if(roomArray[key]==NULL)
  {
    roomArray[key] = item;
  }
  else
  {
    tempitem = roomArray[key];
    while(tempitem->next)
    {
      tempitem = tempitem->next;
    }
    tempitem->next = item;
  }
  return item;
}
*/

/*

//Extra Code
//delete first item 
struct USERSINROOMS* deleteFirstUsersInRooms(struct USERSINROOMS *head){
  ;
}
//*/


//*/

/* SURPRISE. GET THIS WORKING AND ADD SOME NEW COMMANDS
 * 
 
 
 /////////////////////////////// USER GROUPLIST ////////////////////////////////

//display the list
void printListUG(struct ugnode *head) {
   struct ugnode *ptr = head;
   printf("\t[USERGROUPS ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%s) ",ptr->groupname);
      ptr = ptr->next;
   }

   printf("]");
}

//insert link at the first location
struct ugnode* insertFirstUG(struct ugnode *head, char *groupname) {
    
   if(findUG(head,groupname) == NULL) {
           
       //create a link
       struct ugnode *link = (struct ugnode*) malloc(sizeof(struct ugnode));

       strcpy(link->groupname,groupname);
       
       //point it to old first node
       link->next = head;

       //point first to new first node
       head = link;
 
   }
   else
       printf("Duplicate Group: %s\n", groupname);
   return head;
}

//delete first item
struct ugnode* deleteFirstUG(struct ugnode *head) {

   //save reference to first link
   struct ugnode *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   free(tempLink);
   return head;
}

//is list empty
bool isEmptyUG(struct ugnode *head) {
   return head == NULL;
}

int lengthUG(struct ugnode *head) {
   int length = 0;
   struct ugnode *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given group
struct ugnode* findUG(struct ugnode *head, char* groupname) {

   //start from the first link
   struct ugnode* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
    while(strcmp(current->groupname, groupname) != 0) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if username found, return the current Link
   return current;
}

//delete a link with given groupname
struct ugnode* deleteUG(struct ugnode *head, char* groupname) {

   //start from the first link
   struct ugnode* current = head;
   struct ugnode* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(strcmp(current->groupname, groupname) != 0) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }  
    
   free(current);
   return head;
}

void destroyUG(struct ugnode *head)
{
    struct ugnode *cursor, *tmp;
 
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}


//////////////////////////

//display the list
void printListG(struct gnode *head) {
   struct gnode *ptr = head;
    
   printf("\n[Groups ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%s)\t",ptr->groupname);
       
      printListU(ptr->head);
   
      ptr = ptr->next;
   }
	
   printf("]");
}

void display_groups(struct gnode *head, char *buf) {
  struct gnode *ptr = head;
  char tmpbuf[1024];

    
  if (ptr == NULL){
    sprintf(buf,"no groups!\n");
  }
  else{
      sprintf(buf,"[Groups: ");
      while(ptr != NULL) {
        sprintf(tmpbuf,"%s", ptr->groupname);
        ptr = ptr->next;
        strcat(buf, tmpbuf);
        if(ptr == NULL){
            strcat(buf, "]\n");
        }
        else
            strcat(buf, ", ");
      }
  }
}

//insert link at the first location
struct gnode* insertFirstG(struct gnode *head, char *groupname) 
{
    
   if(findG(head,groupname) == NULL) {
           
       //create a link
       struct gnode *link = (struct gnode*) malloc(sizeof(struct gnode));

       strcpy(link->groupname,groupname);

       link->head = NULL;
       
       //point it to old first node
       link->next = head;

       //point first to new first node
       head = link;
 
   }
   else
       printf("Duplicate Group: %s\n", groupname);
   return head;
}

//delete first item
struct gnode* deleteFirstG(struct gnode *head) {

   //save reference to first link
   struct gnode *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   free(tempLink);
   return head;
}

//is list empty
bool isEmptyG(struct gnode *head) {
   return head == NULL;
}

int lengthG(struct gnode *head) {
   int length = 0;
   struct gnode *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given group
struct gnode* findG(struct gnode *head, char* groupname) {

   //start from the first link
   struct gnode* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
    while(strcmp(current->groupname, groupname) != 0) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if username found, return the current Link
   return current;
}

//delete a link with given groupname
struct gnode* deleteG(struct gnode *head, char* groupname) {

   //start from the first link
   struct gnode* current = head;
   struct gnode* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(strcmp(current->groupname, groupname) != 0) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }  
    
   free(current);
   return head;
}

void destroyG(struct gnode *head)
{
    struct gnode *cursor, *tmp;
 
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}

*/