#define CYFRAL_SIGNAL !(ACSR & (1<<ACO))

void cyfral_send(uint16_t key);
long int read_cyfral(void);
long int read_cyfral_with_check(void);
