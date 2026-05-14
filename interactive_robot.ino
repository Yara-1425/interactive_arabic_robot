#include <cvzone.h>
#include <Servo.h>

// تعريف محركات السيرفو
Servo LServo; 
Servo RServo; 
Servo HServo; 

// تعريف الدبابيس
const int LS_pin = 8;
const int RS_pin = 9;
const int HS_pin = 10;
const int IR_pin = 2; // دبوس حساس الـ IR

// إعداد السيريال لاستقبال 3 قيم (زوايا السيرفو من بايثون)
SerialData serialData(3, 3); 
int valsRec[3]; 

// متغيرات للحساس والعد
int irCounter = 0;         // عداد المرات
bool lastIrState = HIGH;   // حالة الحساس السابقة (IR عادة يكون HIGH إذا لم يوجد عائق)
bool wavingActive = false; // هل الروبوت يلوح الآن؟

void setup() {
  serialData.begin(); 
  
  pinMode(IR_pin, INPUT);

  LServo.attach(LS_pin);
  RServo.attach(RS_pin);
  HServo.attach(HS_pin);
}

void loop() {
  // 1. استقبال البيانات من بايثون بشكل مستمر
  serialData.Get(valsRec);
  
  // إذا لم يكن الروبوت يلوح، يتبع أوامر البايثون
  if (!wavingActive) {
    LServo.write(valsRec[0]);
    RServo.write(valsRec[1]);
    HServo.write(valsRec[2]);
  }

  // 2. قراءة حالة حساس IR (منطق العد)
  bool currentIrState = digitalRead(IR_pin);

  // التحقق من مرور اليد (تغير الحالة من عدم وجود عائق إلى وجود عائق)
  if (currentIrState == LOW && lastIrState == HIGH) {
    irCounter++;
    delay(200); // لمنع القراءات المتكررة السريعة (Debouncing)
  }
  lastIrState = currentIrState;

  // 3. إذا تم المرور 3 مرات، ابدأ التلويح
  if (irCounter >= 4) {
    wavingActive = true;
    performWave();    // تنفيذ دالة التلويح
    irCounter = 0;    // تصغير العداد للبدء من جديد
    wavingActive = false; 
  }
}

// دالة التلويح (حركة للأعلى والأسفل 3 مرات)
void performWave() {
  for (int i = 0; i < 3; i++) {
    RServo.write(150); // زاوية للأعلى
    delay(300);
    RServo.write(30);  // زاوية للأسفل
    delay(300);
  }
}