/**
 * @file electromech_angle_calc.h
 * @brief Header file to calculate angle or rotor and required phase
 * @TODO: Should this
 */

#ifndef ELECTROMECH_ANGLE_CALC_H
#define ELECTROMECH_ANGLE_CALC_H

#include "generic_block.h"

class ElectromechAngleCalc : public Block {
  BLOCK_INPUT(int64_t, positionRaw);
  int64_t rotorOfst;
  int32_t polePeriod;
  BLOCK_OUTPUT(int64_t, rotorAngle);

 public:
  /**
   * @brief ElectromechAngleCalc constructor.
   * @param positionRaw Raw position of the motor in deg.
   * @param rotorOfst Offset of sensor due to manual alignment in deg.
   * @param polePeriod The fractional period of the poles x 100
   */
  ElectromechAngleCalc(const int64_t& positionRaw,
                       const int64_t& rotorOfst,
                       const int32_t& polePeriod)
      : positionRaw_(positionRaw),
        rotorOfst(rotorOfst),
        polePeriod(polePeriod) {}

  /**
   * @brief Updates angle calcs
   */
  void tick() override;

 private:
};

void ElectromechAngleCalc::tick() {
  rotorAngle_ = ((positionRaw_ - rotorOfst) * polePeriod) / 100;
}

#define INIT_ELECROMECH_ANGLE_CALC(instance_name, positionRaw, rotorOfst, \
                                   polePeriod)                            \
  ElectromechAngleCalc instance_name((positionRaw), (rotorOfst), (polePeriod))

#endif  // ELECTROMECH_ANGLE_CALC_H
