/* Implement getpwnam() using setpwent(), getpwent() and endpwent(). */

#include "tlpi_hdr.h"
#include <pwd.h>

struct passwd *my_getpwnam(const char *name){
  
  struct passwd *pwd;
  
  while((pwd = getpwent()) != NULL){
    if(strcmp(pwd->pw_name, name) == 0){
      
      endpwent(); /* Needed to reset the calls to getpwent */
      return pwd;
    }
  }
  
  endpwent();
  return NULL;
}

int main(int argc, char *argv[]){

  char * user_name1 = "david";
  char * user_name2 = "guest";
  char * user_name3 = "amanda"; /* Doesn't exist */

  struct passwd * pwd;
  pwd = my_getpwnam(user_name1);

  if(pwd != NULL){

  printf("Login name:\t%s\n", pwd->pw_name);
  printf("Encrypted pass:\t%s\n", pwd->pw_passwd);
  printf("User ID:\t%d\n", pwd->pw_uid);
  printf("Group ID:\t%d\n", pwd->pw_gid);
  printf("Inital working directory:\t%s\n", pwd->pw_dir);
  printf("Login shell: %s\n", pwd->pw_shell);
  printf("\n");
  printf("----");
  printf("\n");}

  pwd = my_getpwnam(user_name3);
  if(pwd != NULL){

  printf("Login name:\t%s\n", pwd->pw_name);
  printf("Encrypted pass:\t%s\n", pwd->pw_passwd);
  printf("User ID:\t%d\n", pwd->pw_uid);
  printf("Group ID:\t%d\n", pwd->pw_gid);
  printf("Inital working directory:\t%s\n", pwd->pw_dir);
  printf("Login shell: %s\n", pwd->pw_shell);
  printf("\n");
  printf("----");
  printf("\n");}

  pwd = my_getpwnam(user_name2);

  if(pwd != NULL){
  printf("Login name:\t%s\n", pwd->pw_name);
  printf("Encrypted pass:\t%s\n", pwd->pw_passwd);
  printf("User ID:\t%d\n", pwd->pw_uid);
  printf("Group ID:\t%d\n", pwd->pw_gid);
  printf("Inital working directory:\t%s\n", pwd->pw_dir);
  printf("Login shell: %s\n", pwd->pw_shell);
  printf("\n");
  printf("----");
  printf("\n");}

  pwd = my_getpwnam(user_name1);

  if(pwd != NULL){
  printf("Login name:\t%s\n", pwd->pw_name);
  printf("Encrypted pass:\t%s\n", pwd->pw_passwd);
  printf("User ID:\t%d\n", pwd->pw_uid);
  printf("Group ID:\t%d\n", pwd->pw_gid);
  printf("Inital working directory:\t%s\n", pwd->pw_dir);
  printf("Login shell: %s\n", pwd->pw_shell);
  printf("\n");
  printf("----");
  printf("\n");}

  pwd = getpwnam(user_name3); /* Actual call to the glibc function for reference */

  if(pwd != NULL){
  printf("Login name:\t%s\n", pwd->pw_name);
  printf("Encrypted pass:\t%s\n", pwd->pw_passwd);
  printf("User ID:\t%d\n", pwd->pw_uid);
  printf("Group ID:\t%d\n", pwd->pw_gid);
  printf("Inital working directory:\t%s\n", pwd->pw_dir);
  printf("Login shell: %s\n", pwd->pw_shell);
  printf("\n");
  printf("----");
  printf("\n");}
  
  
  return(EXIT_SUCCESS);
}
