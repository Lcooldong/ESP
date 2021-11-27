#include <SoftwareSerial.h>
#define	RX_S 7
#define	TX_S 6
SoftwareSerial Esp12s =	 SoftwareSerial(RX_S, TX_S);

uint8_t	PRINTPORT =	0; FILE	fOUT = {0,};
#define	printr(x, y, args...) PRINTPORT=x,fprintf(&fOUT, y,	##args)
#define	printg(x, y, args...) PRINTPORT=x,fprintf(&fOUT, y"\r\n", ##args)
#define	AtCIPSENDEX(x) printg(3, "AT+CIPSENDEX=0,%d", x)
static int putchr(char c, FILE*	stream)
{
	!PRINTPORT ? Serial.write(c):Esp12s.write(c);
	return(0);
}

const int EN_L = 9;
const int MC_L1	= 2;
const int MC_L2	= 3;
const int EN_R = 10;
const int MC_R1	= 4;
const int MC_R2	= 5;

#define	motor(en, m1, v1, m2, v2, rate)\
	digitalWrite(en, LOW);\
	digitalWrite(m1, v1);\
	digitalWrite(m2, v2);\
	analogWrite(en,	rate)

void brake (int	side=0)
{
	switch(side){
	case 1:	motor(EN_L,	MC_L1, LOW,	MC_L2, LOW,	0);	break;
	case 2:	motor(EN_R,	MC_R1, LOW,	MC_R2, LOW,	0);	break;
	default:
		motor(EN_L, MC_L1, LOW, MC_L2, LOW, 0);
		motor(EN_R, MC_R1, LOW, MC_R2, LOW, 0);
	}
}

void forward (int side=0, int rate=255)
{
	brake();
	switch(side){
	case 1:	motor(EN_L,	MC_L1, HIGH, MC_L2,	LOW, rate);	break;
	case 2:	motor(EN_R,	MC_R1, HIGH, MC_R2,	LOW, rate);	break;
	default:
		motor(EN_L, MC_L1, HIGH, MC_L2, LOW, rate);
		motor(EN_R, MC_R1, HIGH, MC_R2, LOW, rate);
	}
}

void reverse (int rate=255)
{
	brake();
	motor(EN_L, MC_L1, LOW, MC_L2, HIGH, rate);
	motor(EN_R, MC_R1, LOW, MC_R2, HIGH, rate);
}

int	TRIG1 =	13;
int	ECHO1 =	12;
void Sonar_init()
{
	pinMode(TRIG1, OUTPUT);
	pinMode(ECHO1, INPUT);
}

int sonarAlt = 0;
void Sonar_update()
{
	float duration,	distance;
	digitalWrite(TRIG1,	HIGH);
	delay(10);
	digitalWrite(TRIG1,	LOW);

	duration = pulseIn(ECHO1, HIGH);
	distance = ((float)(340.0 *	duration) /	10000.0) / 2.0;
	sonarAlt = (int)distance;//	+ offset;
}

int	testLED;//LED_BUILTIN(13)
void setup() {
	fdev_setup_stream(&fOUT, putchr, NULL, _FDEV_SETUP_WRITE);

	// put your setup	code here, to run once:
	Serial.begin(115200);
	//Esp12s.begin(9600);
	//printg(3, "AT+UART_DEF=115200,8,1,0,0");delay(5);
	Esp12s.begin(115200);

	printg(3, "ATE0");delay(5);
	printg(3, "AT+CWMODE=3");delay(5);
	//printg(3, "AT+CWSAP=\"poly\",\"1234\",1,2"); delay(5);
	printg(3, "AT+CIPMUX=1"); delay(5);
	printg(3, "AT+CIPSERVER=1,1009"); delay(5);
	printg(3, "AT+CIPSTO=0"); delay(5);
	printg(3, "AT+CIPMODE=0"); delay(5);
	printg(0, "setup...");

	pinMode(EN_L, OUTPUT);
	pinMode(MC_L1, OUTPUT);
	pinMode(MC_L2, OUTPUT);
	pinMode(EN_R, OUTPUT);
	pinMode(MC_R1, OUTPUT);
	pinMode(MC_R2, OUTPUT);
	brake();

	//pinMode(RX_S, INPUT);
	//pinMode(TX_S, OUTPUT);

	Sonar_init();

	pinMode(LED_BUILTIN, OUTPUT);
	testLED = HIGH;
	digitalWrite(LED_BUILTIN, testLED);
}

void loop()	{
  // put your main code	here, to run repeatedly:

	//printr(0, ".");
	Sonar_update();
	//sonarAlt = random(0, 5);

	static uint16_t	eTime =	0;
	uint16_t cTime = millis();
	if(cTime - eTime > 500){
		eTime =	cTime;

		printg(0, "sonarAlt: %5d", sonarAlt);

		AtCIPSENDEX(10 + 5 + 2); delay(5);
		printg(3, "sonarAlt: %5d", sonarAlt); delay(10);

		//printr(0,	".");
		testLED	= !testLED;	
		digitalWrite(LED_BUILTIN, testLED);
	}
#if 1
	while(Esp12s.available() > 0){
		String cmd = Esp12s.readStringUntil(13);
		cmd.trim();//+IPD,1,3:9
#if 0
		printg(0, "recevie: %s", cmd.c_str());
#endif
		if(cmd.length()	> 0	&& cmd.startsWith("+IPD"))
		{
#if 1
			printg(0, "revCmd: %s", cmd.substring(cmd.indexOf(':')+1).c_str());
#endif
			switch(cmd.substring(cmd.indexOf(':')+1).toInt()){
			case 1: forward(); break;
			case 2: forward(1); break;
			case 3: forward(2); break;
			case 4: brake(); break;
			case 5: reverse(); break;
			}
		}
	}
#else
	if (Serial.available() > 0) {
		int cmd = Serial.read();
		//Serial.println(cmd);
		switch(cmd){
		case '1': forward(); break;
		case '2': forward(1); break;
		case '3': forward(2); break;
		case '4': brake(); break;
		case '5': reverse(); break;
		}
	}
#endif
}
