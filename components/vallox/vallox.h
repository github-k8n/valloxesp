#pragma once

#include <Arduino.h>
#include "vallox_protocol.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/number/number.h"
#include "esphome/components/button/button.h"
#include "esphome/components/select/select.h"


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


#define VX_MSG_LENGTH 6
#define VX_MSG_DOMAIN 0x01
#define VX_MSG_POLL_BYTE 0x00
#define NOT_SET -999
#define QUERY_INTERVAL 300000 // in ms (5 min)
#define RETRY_INTERVAL 5000 // in ms (5 sec)
#define VX_MAX_RETRIES 10
#define VX_REPLY_WAIT_TIME 10

// senders and receivers
#define VX_MSG_MAINBOARD_1 0x11
#define VX_MSG_MAINBOARDS 0x10
#define VX_MSG_PANEL_1 0x21 // This panel address, should not be same with other panel(s)
#define VX_MSG_THIS_PANEL 0x22 // This panel address, should not be same with other panel(s)
#define VX_MSG_PANELS 0x20

#define CO2_LIFE_TIME_MS 2000 // Maximum time that LO and HI bytes are considered to be the same value


// default names of fan modes (1-8)
const std::set< std::string > preset_custom_fan_modes = {"1", "2", "3", "4", "5", "6", "7", "8"};


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


namespace esphome {
  namespace vallox {

      class ValloxVentilation;
      class ValloxVentilationHeatBypassNum;
      class ValloxVentilationServiceResetBtn;
      class ValloxVentilationSwitchSelectSel;
      class ValloxVentilationFanSpeedMaxNum;
      class ValloxVentilationFanSpeedMinNum;
      class ValloxVentilationSwitchBtn;

/////////////////////////////////////////////////////////////////////////////////////////

      class ValloxVentilationHeatBypassNum : public number::Number, public Component {
        public:
         void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

        protected:
         void control(float value) override;

         ValloxVentilation *parent_;
      };

/////////////////////////////////////////////////////////////////////////////////////////

      class ValloxVentilationServiceResetBtn : public button::Button, public Component {
        public:
         void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

        protected:
         void press_action() override;

         ValloxVentilation *parent_;
      };

/////////////////////////////////////////////////////////////////////////////////////////

      class ValloxVentilationSwitchTypeSelectSel : public select::Select, public Component {
        public:
         void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

        protected:
         void control(const std::string &value) override;

         ValloxVentilation *parent_;
      };

/////////////////////////////////////////////////////////////////////////////////////////

      class ValloxVentilationFanSpeedMaxNum : public number::Number, public Component {
        public:
         void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

        protected:
         void control(float value) override;

         ValloxVentilation *parent_;
      };

/////////////////////////////////////////////////////////////////////////////////////////

      class ValloxVentilationFanSpeedMinNum : public number::Number, public Component {
        public:
         void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

        protected:
         void control(float value) override;

         ValloxVentilation *parent_;
      };

/////////////////////////////////////////////////////////////////////////////////////////

      class ValloxVentilationSwitchBtn : public button::Button, public Component {
        public:
         void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

        protected:
         void press_action() override;

         ValloxVentilation *parent_;
      };

/////////////////////////////////////////////////////////////////////////////////////////


      class ValloxVentilation : public Component, public climate::Climate, public uart::UARTDevice {
        public:

         void setup() override;
         void dump_config() override;
         void loop() override;

         float get_setup_priority() const override { return esphome::setup_priority::LATE; }


         // number sensors
         void set_fan_speed_sensor(sensor::Sensor *sensor)            { this->fan_speed_sensor_            = sensor; }
         void set_fan_speed_default_sensor(sensor::Sensor *sensor)    { this->fan_speed_default_sensor_    = sensor; }
         void set_temperature_target_sensor(sensor::Sensor *sensor)   { this->temperature_target_sensor_   = sensor; }
         void set_temperature_outside_sensor(sensor::Sensor *sensor)  { this->temperature_outside_sensor_  = sensor; }
         void set_temperature_inside_sensor(sensor::Sensor *sensor)   { this->temperature_inside_sensor_   = sensor; }
         void set_temperature_outgoing_sensor(sensor::Sensor *sensor) { this->temperature_outgoing_sensor_ = sensor; }
         void set_temperature_incoming_sensor(sensor::Sensor *sensor) { this->temperature_incoming_sensor_ = sensor; }
         void set_humidity_1_sensor(sensor::Sensor *sensor)           { this->humidity_1_sensor_           = sensor; }
         void set_humidity_2_sensor(sensor::Sensor *sensor)           { this->humidity_2_sensor_           = sensor; }
         void set_co2_sensor(sensor::Sensor *sensor)                  { this->co2_sensor_                  = sensor; }
         void set_service_period_sensor(sensor::Sensor *sensor)       { this->service_period_sensor_       = sensor; }
         void set_service_remaining_sensor(sensor::Sensor *sensor)    { this->service_remaining_sensor_    = sensor; }
         // text sensors
         void set_switch_type_text_sensor(text_sensor::TextSensor *sensor) { this->switch_type_text_sensor_ = sensor; }
         void set_fault_condition_text_sensor(text_sensor::TextSensor *sensor) { this->fault_condition_text_sensor_ = sensor; }
         // binary sensors
         void set_status_on_binary_sensor(binary_sensor::BinarySensor *sensor)        { this->status_on_binary_sensor_        = sensor; }
         void set_status_motor_in_binary_sensor(binary_sensor::BinarySensor *sensor)  { this->status_motor_in_binary_sensor_  = sensor; }
         void set_status_motor_out_binary_sensor(binary_sensor::BinarySensor *sensor) { this->status_motor_out_binary_sensor_ = sensor; }
         void set_service_needed_binary_sensor(binary_sensor::BinarySensor *sensor)   { this->service_needed_binary_sensor_   = sensor; }
         void set_switch_active_binary_sensor(binary_sensor::BinarySensor *sensor)    { this->switch_active_binary_sensor_    = sensor; }
         void set_heating_binary_sensor(binary_sensor::BinarySensor *sensor)          { this->heating_binary_sensor_          = sensor; }
         void set_heating_mode_binary_sensor(binary_sensor::BinarySensor *sensor)     { this->heating_mode_binary_sensor_     = sensor; }
         void set_front_heating_binary_sensor(binary_sensor::BinarySensor *sensor)    { this->front_heating_binary_sensor_    = sensor; }
         void set_summer_mode_binary_sensor(binary_sensor::BinarySensor *sensor)      { this->summer_mode_binary_sensor_      = sensor; }
         void set_problem_binary_sensor(binary_sensor::BinarySensor *sensor)          { this->problem_binary_sensor_          = sensor; }
         void set_error_relay_binary_sensor(binary_sensor::BinarySensor *sensor)      { this->error_relay_binary_sensor_      = sensor; }
         void set_extra_func_binary_sensor(binary_sensor::BinarySensor *sensor)       { this->extra_func_binary_sensor_       = sensor; }
         // number controls
         void set_heat_bypass_number(number::Number *number)   { this->heat_bypass_number_ = number; }
         void set_fan_speed_max_number(number::Number *number) { this->fan_speed_max_number_ = number; }
         void set_fan_speed_min_number(number::Number *number) { this->fan_speed_min_number_ = number; }
         // button controls
         void set_service_reset_button(button::Button *button) { this->service_reset_button_ = button; }
         void set_switch_button(button::Button *button)        { this->switch_button_        = button; }
         // select controls
         void set_switch_type_select_select(select::Select *select) { this->switch_type_select_select_ = select; }


         // valloxesp functions called by other classes
         static byte cel2Ntc(int cel);
         void setVariable(byte variable, byte value);
         void setProgramVariable(byte bitpos, bool value);
         void setFlags06Variable(byte bitpos, bool value);
         void requestVariable(byte variable);
         int service_period = 1; // set to 1 month to make any issue more obvious

       private:
         // lock status (prevent sending and overriding different values until we have received the last)
         boolean statusMutex = false;
         boolean programMutex = false;
         boolean flags06Mutex = false;
         unsigned long lastRetryLoop = 0;
         unsigned long lastRequested = 0;

         boolean readMessage(byte message[]);
         void retryLoop();
         void setStatusVariable(byte variable, byte value);
         void setVariable(byte variable, byte value, byte target);
         void decodeMessage(const byte message[]);
         void decodeStatus(byte status);
         void decodeVariable08(byte variable08);
         void decodeFlags06(byte flags06);
         void decodeProgram(byte program);
         static int ntc2Cel(byte ntc);
         static int hex2Rh(byte hex);
         static byte fanSpeed2Hex(int fan);
         static int hex2FanSpeed(byte hex);

         static byte calculateCheckSum(const byte message[]);
         bool validateCheckSum(const byte message[]);


        protected:
         void control(const climate::ClimateCall &call) override;
         climate::ClimateTraits traits() override;
         sensor::Sensor *fan_speed_sensor_{nullptr};
         sensor::Sensor *fan_speed_default_sensor_{nullptr};
         sensor::Sensor *temperature_target_sensor_{nullptr};
         sensor::Sensor *temperature_outside_sensor_{nullptr};
         sensor::Sensor *temperature_inside_sensor_{nullptr};
         sensor::Sensor *temperature_outgoing_sensor_{nullptr};
         sensor::Sensor *temperature_incoming_sensor_{nullptr};
         sensor::Sensor *humidity_1_sensor_{nullptr};
         sensor::Sensor *humidity_2_sensor_{nullptr};
         sensor::Sensor *co2_sensor_{nullptr};
         sensor::Sensor *service_period_sensor_{nullptr};
         sensor::Sensor *service_remaining_sensor_{nullptr};
         text_sensor::TextSensor *switch_type_text_sensor_{nullptr};
         text_sensor::TextSensor *fault_condition_text_sensor_{nullptr};
         binary_sensor::BinarySensor *status_on_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *status_motor_in_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *status_motor_out_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *service_needed_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *switch_active_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *heating_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *heating_mode_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *front_heating_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *summer_mode_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *problem_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *error_relay_binary_sensor_{nullptr};
         binary_sensor::BinarySensor *extra_func_binary_sensor_{nullptr};
         number::Number *heat_bypass_number_{nullptr};
         number::Number *fan_speed_max_number_{nullptr};
         number::Number *fan_speed_min_number_{nullptr};
         button::Button *service_reset_button_{nullptr};
         button::Button *switch_button_{nullptr};
         select::Select *switch_type_select_select_{nullptr};

         byte buffer_status = 0x00;
         byte target_status = 0x00;
         byte buffer_flags06 = 0x00;
         byte buffer_program = 0x00;

         byte buffer_co2_hi = 0x00;
         byte buffer_co2_lo = 0x00;
         unsigned long buffer_co2_hi_ts = 0;
         unsigned long buffer_co2_lo_ts = 0;

      };

  }  // namespace vallox
}  // namespace esphome