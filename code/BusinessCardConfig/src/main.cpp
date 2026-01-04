// #include <Wire.h>
// #include "SparkFun_BMA400_Arduino_Library.h"

// // Create a new sensor object
// BMA400 accelerometer;

// // I2C address selection
// // uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT; // 0x14
// uint8_t i2cAddress = BMA400_I2C_ADDRESS_SECONDARY; // 0x15

// // Pin used for interrupt detection
// int interruptPin = 2;

// // Flag to know when interrupts occur
// volatile bool interruptOccurred = false;

// void setup()
// {
//     // Start serial
//     Serial.begin(115200);
//     delay(5000);
//     Serial.println("BMA400 Example 6 - Motion Detection");

//     // Initialize the I2C library
//     Wire.begin();
//     delay(5000);

//     // Check if sensor is connected and initialize
//     // Address is optional (defaults to 0x14)
//     while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
//     {
//         // Not connected, inform user
//         Serial.println("Error: BMA400 not connected, check wiring and I2C address!");

//         // Wait a bit to see if connection is established
//         delay(1000);
//     }

//     Serial.println("BMA400 connected!");

//     accelerometer.setMode(BMA400_MODE_LOW_POWER);

//     // Here we configure the generic interrupt feature of the BMA400. It
//     // triggers an interrupt when the measured acceleration exceeds some
//     // reference acceleration that we can specify. There are several other
//     // parameters that can be configured, such as acceleration threshold,
//     // hysteresis, automatic reference updates, etc. The BMA400 has 2 generic
//     // interrupts that can be configured independently
//     bma400_gen_int_conf config =
//     {
//         .gen_int_thres = 50, // 8mg resolution (eg. gen_int_thres=5 results in 40mg)
//         .gen_int_dur = 50, // 10ms resolution (eg. gen_int_dur=5 results in 50ms)
//         .axes_sel = BMA400_AXIS_XYZ_EN, // Which axes to evaluate for interrupts (X/Y/Z in any combination)
//         .data_src = BMA400_DATA_SRC_ACCEL_FILT_2, // Which filter to use (must be 100Hz, datasheet recommends filter 2)
//         .criterion_sel = BMA400_ACTIVITY_INT, // Trigger interrupts when active or inactive
//         .evaluate_axes = BMA400_ANY_AXES_INT, // Logical combining of axes for interrupt condition (OR/AND)
//         .ref_update = BMA400_UPDATE_EVERY_TIME, // Whether to automatically update reference values
//         .hysteresis = BMA400_HYST_96_MG, // Hysteresis acceleration for noise rejection
//         .int_thres_ref_x = 0, // Raw 12-bit acceleration value
//         .int_thres_ref_y = 0, // Raw 12-bit acceleration value
//         .int_thres_ref_z = 128, // Raw 12-bit acceleration value (at 4g range (default), 512 = 1g)
//         .int_chan = BMA400_INT_CHANNEL_1 // Which pin to use for interrupts
//     };
//     accelerometer.setGeneric1Interrupt(&config);

//     bma400_wakeup_conf wakeconf = {
//       .wakeup_ref_update = BMA400_UPDATE_EVERY_TIME, // Whether to automatically update reference values
//       .sample_count = BMA400_SAMPLE_COUNT_3,
//       .wakeup_axes_en = BMA400_AXIS_XY_EN,
//       .int_wkup_threshold = 64,
//       .int_wkup_ref_x = 64, // Raw 12-bit acceleration value
//       .int_wkup_ref_y = 64, // Raw 12-bit acceleration value
//       .int_chan = BMA400_INT_CHANNEL_1 // Which pin to use for interrupts
//     };
//     if(0 == accelerometer.setWakeupInterrupt(&wakeconf))
//     {
//         Serial.println("Wakeup interrupt configured.");
//     }
//     else
//     {
//         Serial.println("Error configuring wakeup interrupt.");
//     }

//     bma400_auto_lp_conf lpconf = {
//       .auto_low_power_trigger = BMA400_AUTO_LP_TIMEOUT_EN, // drdy, gen1, timeout, timeout reset
//       .auto_lp_timeout_threshold = 400 // 2.5ms resolution (eg. 400 results in 1s)
//     };
//     accelerometer.setAutoLowPower(&lpconf);

//     // Here we configure the INT1 pin to push/pull mode, active high
//     accelerometer.setInterruptPinMode(BMA400_INT_CHANNEL_1, BMA400_INT_PUSH_PULL_ACTIVE_1);
    
//     // Enable auto wakeup interrupt condition
//     accelerometer.enableInterrupt(BMA400_AUTO_WAKEUP_EN, true);
//     // Enable generic 1 interrupt condition
//     // accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, true);
    
//     // Setup interrupt handler debug only
//     //attachInterrupt(digitalPinToInterrupt(interruptPin), bma400InterruptHandler, RISING);
// }

// void loop()
// {
//     // Wait for interrupt to occur
//     if(interruptOccurred)
//     {
//         // Reset flag for next interrupt
//         interruptOccurred = false;

//         Serial.print("Interrupt occurred!");
//         Serial.print("\t");

//         // Get the interrupt status to know which condition triggered
//         uint16_t interruptStatus = 0;
//         accelerometer.getInterruptStatus(&interruptStatus);
        
//         // Check if this is the generic 1 interrupt condition
//         if(interruptStatus & BMA400_ASSERTED_GEN1_INT)
//         {
//             Serial.println("Motion detected!");
//         }
//         else
//         {
//             Serial.println("Wrong interrupt condition!");
//         }
//     }
// }

// void bma400InterruptHandler()
// {
//     interruptOccurred = true;
// }







#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"

// Create a new sensor object
BMA400 accelerometer;

// I2C address selection
// uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT; // 0x14
uint8_t i2cAddress = BMA400_I2C_ADDRESS_SECONDARY; // 0x15

// Pin used for interrupt detection
int interruptPin = 2;

// Flag to know when interrupts occur
volatile bool interruptOccurred = false;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("BMA400 Example 6 - Motion Detection");

    // Initialize the I2C library
    Wire.begin();

    delay(5000);
    // Check if sensor is connected and initialize
    // Address is optional (defaults to 0x14)
    while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
    {
        // Not connected, inform user
        Serial.println("Error: BMA400 not connected, check wiring and I2C address!");

        // Wait a bit to see if connection is established
        delay(1000);
    }

    Serial.println("BMA400 connected!");

    // Here we configure the generic interrupt feature of the BMA400. It
    // triggers an interrupt when the measured acceleration exceeds some
    // reference acceleration that we can specify. There are several other
    // parameters that can be configured, such as acceleration threshold,
    // hysteresis, automatic reference updates, etc. The BMA400 has 2 generic
    // interrupts that can be configured independently
    bma400_gen_int_conf config =
    {
        .gen_int_thres = 10, // 8mg resolution (eg. gen_int_thres=5 results in 40mg)
        .gen_int_dur = 50, // 10ms resolution (eg. gen_int_dur=5 results in 50ms)
        .axes_sel = BMA400_AXIS_XYZ_EN, // Which axes to evaluate for interrupts (X/Y/Z in any combination)
        .data_src = BMA400_DATA_SRC_ACCEL_FILT_2, // Which filter to use (must be 100Hz, datasheet recommends filter 2)
        .criterion_sel = BMA400_ACTIVITY_INT, // Trigger interrupts when active or inactive
        .evaluate_axes = BMA400_ANY_AXES_INT, // Logical combining of axes for interrupt condition (OR/AND)
        .ref_update = BMA400_UPDATE_EVERY_TIME, // Whether to automatically update reference values
        .hysteresis = BMA400_HYST_96_MG, // Hysteresis acceleration for noise rejection
        .int_thres_ref_x = 512, // Raw 12-bit acceleration value
        .int_thres_ref_y = 512, // Raw 12-bit acceleration value
        .int_thres_ref_z = 512, // Raw 12-bit acceleration value (at 4g range (default), 512 = 1g)
        .int_chan = BMA400_INT_CHANNEL_1 // Which pin to use for interrupts
    };
    if( 0 == accelerometer.setGeneric1Interrupt(&config))
    {
        Serial.println("Generic 1 interrupt configured.");
    }
    else
    {
        Serial.println("Error configuring generic 1 interrupt.");
    }
    
    // Here we configure the INT1 pin to push/pull mode, active high
    if(0 == accelerometer.setInterruptPinMode(BMA400_INT_CHANNEL_1, BMA400_INT_PUSH_PULL_ACTIVE_1))
    {
        Serial.println("Interrupt pin configured.");
    }
    else
    {
        Serial.println("Error configuring interrupt pin.");
    }
    
    // Enable generic 1 interrupt condition
    if(0 == accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, true))
    {
        Serial.println("Generic 1 interrupt enabled.");
    }
    else
    {
        Serial.println("Error enabling generic 1 interrupt.");
    }
    
    // Setup interrupt handler
    // attachInterrupt(digitalPinToInterrupt(interruptPin), bma400InterruptHandler, RISING);
}

void loop()
{
    delay(1000);
    Serial.println("Checking for interrupt...");
}

void bma400InterruptHandler()
{
    interruptOccurred = true;
}