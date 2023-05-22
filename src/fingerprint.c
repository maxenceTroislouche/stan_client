#include <fingerprint.h>

bool fp_sleep_flag = false;

void fp_init()
{
    // Initialise WiringPi
    wiringPiSetup();

    // Définit le port GPIO Wake en entrée
    pinMode(WAKE_PIN, INPUT);

    // Définit le port GPIO RST en sortie
    pinMode(RST_PIN, OUTPUT);
}

void fp_turn_on_module()
{
    // On met à HIGH le pin RST
    digitalWrite(RST_PIN, HIGH);

    // Délai le temps que le module s'allume correctement
    delay(500);
}

int fp_get_fd()
{
    // O_RDWR : Lecture / écriture
    // O_NOCTTY : Précise que le fichier ne correspond pas à une console terminal	
    int fd = open("/dev/serial0", O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        perror("Erreur lors de l'ouverture du fichier /dev/serial0");
        exit(-1);
    }

    // Défintion des options de la communication série
    struct termios options;
    	// B19200 : baudrate de 19200 bauds
	// CS8 : Communication sur 8 octets
	// CLOCAL : Ignore modem control lines
	// CREAD : Enable receiver
	options.c_cflag = B19200 | CS8 | CLOCAL | CREAD;
	// IGNPAR : Ignore framing errors and parity errors
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	// Application des options
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);

    return fd;
}

void fp_close_fd(int fd)
{
    close(fd);
}

int fp_get_user_count(int fd)
{
    // Commande
    char cmd[8] = {CMD_HEAD, CMD_USER_CNT, 0, 0, 0, 0, CMD_USER_CNT, CMD_TAIL};
	int len = write(fd, cmd, 8);

	char res[8] = {0};
	len = read(fd, res, 8);

    // Vérification que la réponse est bien un succès
    if (res[4] != ACK_SUCCESS)
    {
        return -1;
    }

	int nb_high = (int)res[2] << 8;
	int nb_low = (int)res[3];

    return nb_high + nb_low;
}

int fp_get_compare_level(int fd)
{
    char checksum = CMD_COM_LEV ^ 1;
    char cmd[8] = {CMD_HEAD, CMD_COM_LEV, 0, 0, 1, 0, checksum, CMD_TAIL};

    int len = write(fd, cmd, 8);
    char res[8] = {0};
    len = read(fd, res, 8);

    // Vérification que la réponse est bien un succès
    if (res[4] != ACK_SUCCESS)
    {
        return -1;
    }

    int level = res[3];
    return level;
}

bool fp_set_compare_level(int fd, char level)
{
    if (level < 0 || level > 9)
    {
        return false;
    }

    char checksum = CMD_COM_LEV ^ level;
    char cmd[8] = {CMD_HEAD, CMD_COM_LEV, 0, level, 0, 0, checksum, CMD_TAIL};

    int len = write(fd, cmd, 8);
    char res[8] = {0};
    len = read(fd, res, 8);

    // Vérification que la réponse est bien un succès
    if (res[4] != ACK_SUCCESS)
    {
        return false;
    }
    return true;
}

bool fp_add_user(int fd)
{
    int nb_users = fp_get_user_count(fd);

    if (nb_users >= MAX_USERS)
    {
        return false;
    }

    char checksum = CMD_ADD_1 ^ (nb_users + 1) ^ 3;

    char id_user_high = (char)((nb_users + 1) >> 8);
    char id_user_low = (char)(nb_users + 1);
    char cmd[8] = {CMD_HEAD, CMD_ADD_1, id_user_high, id_user_low, 3, 0, checksum, CMD_TAIL};
    int len = write(fd, cmd, 8);
    char res [8] = {0};
    len = read(fd, res, 8);

    if (res[4] != ACK_SUCCESS)
    {
        return false;
    }

    checksum = CMD_ADD_3 ^ (nb_users + 1) ^ 3;
    cmd[1] = CMD_ADD_3;
    cmd[6] = checksum;

    len = write(fd, cmd, 8);
    len = read(fd, res, 8);

    if (res[4] != ACK_SUCCESS)
    {
        return false;
    }

    return true;
}

int fp_compare_fingerprint(int fd)
{
    char cmd[8] = {CMD_HEAD, CMD_MATCH, 0, 0, 0, 0, CMD_MATCH, CMD_TAIL};
    int len = write(fd, cmd, 8);
    char res[8] = {0};
    len = read(fd, res, 8);

    if (res[4] == ACK_TIMEOUT || res[4] == ACK_NO_USER)
    {
        return -1;
    }

    int user_id_high = (int)res[2] << 8;
    int user_id_low = (int)res[3]; 

    return user_id_high + user_id_low;
}

bool fp_delete_all_fingerprints(int fd)
{
    char cmd[8] = {CMD_HEAD, CMD_DEL_ALL, 0, 0, 0, 0, CMD_DEL_ALL, CMD_TAIL};
    int len = write(fd, cmd, 8);
    char res[8] = {0};
    len = read(fd, res, 8);

    if (res[4] != ACK_SUCCESS)
    {
        return false;
    }
    return true;
}

// NON IMPLEMENTE !
void *fp_auto_verify_fingerprints(void *ptr_fd)
{
		int fd = *(int *)ptr_fd;
		while(1)
		{
			if (fp_sleep_flag && digitalRead(WAKE_PIN))
			{
				delay(100);
				if (digitalRead(WAKE_PIN))
				{
					digitalWrite(RST_PIN, HIGH);
					delay(250);
					int id_user = fp_compare_fingerprint(fd);
					if (id_user == -1)
					{
						printf("Empreinte inconnue !\n");
					}
					else
					{
						printf("Empreinte de l'utilisateur n°%d\n", id_user);
					}
					digitalWrite(RST_PIN, LOW);
				}
			}	
			delay(200);
		}
}
