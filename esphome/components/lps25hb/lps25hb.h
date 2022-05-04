#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace lpsxx {

class LPSXXComponent : public PollingComponent, public i2c::I2CDevice {
 private:
  int sensor_address;
  int who_am_i_id;

 public:
  void set_temperature(sensor::Sensor *temperature) { temperature_ = temperature; }
  void set_pressure(sensor::Sensor *pressure) { pressure_ = pressure; }

  /// Setup the sensor and test for a connection.
  void setup() override;

  /// Schedule temperature+pressure readings.
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override;

 protected:
  struct CalibrationData {
    int16_t ac1, ac2, ac3;
    uint16_t ac4, ac5, ac6;
    int16_t b1, b2;
    int16_t mb, mc, md;
    float temp;
  };

  /// Internal method to read the temperature from the component after it has been scheduled.
  void read_temperature_();
  /// Internal method to read the pressure from the component after it has been scheduled.
  void read_pressure_();

  bool set_mode_(uint8_t mode);

  sensor::Sensor *temperature_{nullptr};
  sensor::Sensor *pressure_{nullptr};
  CalibrationData calibration_;
};

}  // namespace lpsxx
}  // namespace esphome
