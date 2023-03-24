#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

const char *NORMAL_DIR_NAME = "Locker";
const char *LOCKED_DIR_NAME =
    "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B3LOCKER}";
const char *PASSWORD = "UserPassword";

int main() {
  if (isDirExists(LOCKED_DIR_NAME) == 1) {
    return unlock();
  } else {
    if (isDirExists(NORMAL_DIR_NAME) != 1) {
      if (mkdir(NORMAL_DIR_NAME) == 0) {
        printf("Folder created successfully\n\n");
      } else {
        printf("Unable to create folder\n");
      }
    }
    return lock();
  }
}

int lock() {
  printf("Are you sure to lock the folder?(Y/N)\n");
  char ch;
  scanf("%c", &ch);
  if (ch == 'Y' || ch == 'y') {
    if (rename(NORMAL_DIR_NAME, LOCKED_DIR_NAME) == 0) {
      SetFileAttributesA(LOCKED_DIR_NAME,
                         FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
      printf("Locked successfully\n");
      return 0;
    }
    printf("Unable to lock\n");
  } else if (ch == 'N' || ch == 'n') {
    return 0;
  } else {
    printf("Invalid input\n");
  }
  return main();
}

int unlock() {
  printf("Enter password to unlock:\n");
  char pass[16];
  scanf("%s", &pass);
  if (strcmp(pass, PASSWORD) == 0) {
    SetFileAttributesA(LOCKED_DIR_NAME, FILE_ATTRIBUTE_NORMAL);
    if (rename(LOCKED_DIR_NAME, NORMAL_DIR_NAME) == 0) {
      printf("Unlocked successfully\n");
      return 0;
    } else
      printf("Unable to unlock\n");
  } else
    printf("Incorrect password\n");
  return main();
}

int isDirExists(const char *d) {
  DIR *dirptr;

  if (access(d, F_OK) != -1) {
    if ((dirptr = opendir(d)) != NULL) {
      closedir(dirptr); /* d exists and is a directory */
    } else {
      return -2; /* d exists but is not a directory */
    }
  } else {
    return -1; /* d does not exist */
  }
  return 1;
}