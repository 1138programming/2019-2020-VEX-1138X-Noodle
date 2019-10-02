#ifndef _COMMANDS_GETDATA_H_
#define _COMMANDS_GETDATA_H_

#include "libIterativeRobot/commands/Command.h"

class GetData: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    GetData();
  private:
    const int maxRamp = 100;
    int ramp = 0;
    const int maxTrials = 20;
    int trial = 0;
    int voltage = 0;

    std::uint32_t lastTime = 0;
    std::uint32_t time = 0;

    int lastPos = 0;
    int pos = 0;

    double vel = 0;
    double avgVel = 0;
};

#endif // _COMMANDS_GETDATA_H_
