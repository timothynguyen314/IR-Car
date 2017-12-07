#define WHEEL_L 11
#define WHEEL_R 10

#define IR_RIGHT 16
#define IR_LEFT 17
#define IR_FRONT 18

#define LED_G 12
#define LED_R 3
#define LED_B 8

#define R_THRESHOLD 100
#define L_THRESHOLD 100
#define F_THRESHOLD 100

#define R_SPEED 120
#define L_SPEED 120

void setup() {
    pinMode(WHEEL_R, OUTPUT);
    pinMode(WHEEL_L, OUTPUT);
    
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_B, OUTPUT);
    
    pinMode(IR_RIGHT, INPUT);
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_FRONT, INPUT);
    
    Serial.begin(9600);
}

int rMax = 0;
int lMax = 0;
int fMax = 0;
int count = 0;
bool first = true;

void loop() {
    if(first){
        for(int i = 0; i < 100; i++)
        {
            int r = analogRead(IR_RIGHT);
            if(r > 1023)
                r = rMax;
            if(r > rMax)
                rMax = r;
            
            int l = analogRead(IR_LEFT);
            if(l > 1023)
                l = lMax;
            if(l > lMax)
                lMax = l;
            
            int f = analogRead(IR_FRONT);
            if(f > 1023)
                f = fMax;
            if(f > fMax)
                fMax = f;
        }
        first = false;
    }
    
    int r = analogRead(IR_RIGHT);
    int l = analogRead(IR_LEFT);
    int f = analogRead(IR_FRONT);
    if (r > rMax)
        rMax = r;
    if (l > lMax)
        lMax = l;
    if (f > fMax)
        fMax = f;
    
    int rmap = map(r, 0, rMax, 0, 255);
    int lmap = map(l, 0, lMax, 0, 255);
    int fmap = map(f, 0, fMax, 0, 255);
    
    bool rw;
    bool lw;
    
    if (rmap > R_THRESHOLD || (lmap > L_THRESHOLD && rmap <= R_THRESHOLD && fmap <= F_THRESHOLD))
    {
        analogWrite(WHEEL_R, R_SPEED);
        rw = true;
    }
    else
    {
        analogWrite(WHEEL_R, 0);
        rw = false;
    }
    
    if (lmap > L_THRESHOLD || (lmap <= L_THRESHOLD && rmap > R_THRESHOLD && fmap <= F_THRESHOLD))
    {
        analogWrite(WHEEL_L, L_SPEED);
        lw = true;
    }
    else
    {
        analogWrite(WHEEL_L, 0);
        lw = false;
    }
    
    if(rw && lw)
        digitalWrite(LED_G, HIGH);
    else
        digitalWrite(LED_G, LOW);
    
    if((!rw && lw) || (!rw && !lw))
        digitalWrite(LED_R, HIGH);
    else
        digitalWrite(LED_R, LOW);
    
    if((rw && !lw) || (!rw && !lw))
        digitalWrite(LED_B, HIGH);
    else
        digitalWrite(LED_B, LOW);
    
    if(!rw && !lw)
        while(true)
            ;
    
    
//    if(count % 1000 == 0)
//    {
//        Serial.print("front: ");
//        Serial.print(f);
//        Serial.print('\t');
//        Serial.print("left: ");
//        Serial.print(l);
//        Serial.print('\t');
//        Serial.print("right: ");
//        Serial.print(r);
//        Serial.print('\t');
//        Serial.print("fscale: ");
//        Serial.print(fmap);
//        Serial.print('\t');
//        Serial.print("lscale: ");
//        Serial.print(lmap);
//        Serial.print('\t');
//        Serial.print("rscale: ");
//        Serial.print(rmap);
//        Serial.print('\n');
//    }
//    count = count + 1;
}
