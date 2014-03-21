
void LED_Update() ;

void Set_LEDS(unsigned q) ;

void LED_On(unsigned nbr) ;

void LED_Off(unsigned nbr) ;

void Relay_On(unsigned nbr) ;

void Relay_Off(unsigned nbr) ;

void _os_init_output(void);

/** address all relays */
#define RLY1    23
#define RLY2    22
#define RLY3    21
#define RLY4    20
#define RLY5    19
#define RLY_NC3 18
#define RLY_NC2 17
#define RLY_NC1 16

/** address all LEDS */
#define LD5_A  15
#define LD5_B  14
#define LD6_A  13
#define LD6_B  12
#define LD7_A  11
#define LD7_B  10
#define LD8_A  9
#define LD8_B  8
#define LD1_A  7
#define LD1_B  6
#define LD2_A  5
#define LD2_B  4
#define LD3_A  3
#define LD3_B  2
#define LD4_A  1
#define LD4_B  0


#define LED_PWR  LD1_A

