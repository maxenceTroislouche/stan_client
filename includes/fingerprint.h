#ifndef FINGERPRINT
#define FINGERPRINT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <wiringPi.h>
#include <pthread.h>

/* Ports GPIO */
#define WAKE_PIN 4
#define RST_PIN  5

/* Message de réponse */
#define ACK_SUCCESS 0x00
#define ACK_FAIL    0x01
#define ACK_FULL    0x04
#define ACK_NO_USER 0x05
#define ACK_TIMEOUT 0x08
#define ACK_GO_OUT  0x0F 

/* Informations utilisateurs */
#define ACK_ALL_USER     0x00
#define ACK_GUEST_USER   0x01
#define ACK_NORMAL_USER  0x02
#define ACK_MASTER_USER  0x03

// Datasheet du module
#define MAX_USERS 500

/* Commandes */
#define CMD_HEAD            0xF5
#define CMD_TAIL            0xF5
#define CMD_ADD_1           0x01
#define CMD_ADD_2           0x02
#define CMD_ADD_3           0x03
#define CMD_MATCH           0x0C
#define CMD_DEL             0x04
#define CMD_DEL_ALL         0x05
#define CMD_USER_CNT        0x09
#define CMD_COM_LEV         0x28
#define CMD_LP_MODE         0x2C
#define CMD_TIMEOUT         0x2E
#define CMD_FINGER_DETECTED 0x14

// Permet de connaitre l'état de fonctionnement du module (sleep mode)
extern bool fp_sleep_flag;

/**
 * @brief Initialise Wiring Pi et initialise les ports GPIO reliés au capteur d'empreinte
 * 
 */
void fp_init();

/**
 * @brief Allume le module en mettant à HIGH le pin RST
 *
 */
void fp_turn_on_module();

/**
 * @brief Ouvre le fichier du port serie
 * 
 * @return int file descriptor du fichier du port serie
 */
int fp_get_fd();

/**
 * @brief Ferme le fichier du port serie
 * 
 */
void fp_close_fd(int fd);

int fp_get_user_count(int fd);

int fp_get_compare_level(int fd);

bool fp_set_compare_level(int fd, char level);

bool fp_add_user(int fd);

int fp_compare_fingerprint(int fd);

bool fp_delete_all_fingerprints(int fd);

// NON IMPLEMENTE
void *fp_auto_verify_fingerprints(void *ptr_fd);
#endif
