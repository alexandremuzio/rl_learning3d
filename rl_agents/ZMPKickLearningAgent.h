//
// Created by luis on 7/15/18.
//

#ifndef ITANDROIDS_SOCCER3D_CPP_ZMPKICKLEARNINGAGENT_H
#define ITANDROIDS_SOCCER3D_CPP_ZMPKICKLEARNINGAGENT_H

#include "BaseLearningAgent.h"

#include "soccer3d.grpc.pb.h"

#include "external/json.h"

#include "control/ControlStub.h"


using api::Action;
using api::SetupEnvResponse;
using api::SimulationResponse;
using api::State;

struct referenceState {
    double timeStep;
    representations::NaoJoints refJoints;
};


class ZMPKickLearningAgent : public BaseLearningAgent {
public:
    ZMPKickLearningAgent(std::string host = "127.0.0.1", int serverPort = 3100, int monitorPort = 3200, int agentNumber = 2,
                         int robotType = 0, std::string teamName = std::string("ITAndroids"));

    State newEpisode() override;
    SimulationResponse runStep(Action action) override;
    SetupEnvResponse setup() override;

private:
    // Checks whether the episode has finished
    bool episodeOver();

    // Reward signal
    double reward();

    // Environment state
    State state();

    // Runs simulation step in the environment
    void step();

    //helper methods
    void drawEnvironment();
    void drawStats();
    double getJointsDiffNorm(const representations::NaoJoints &frame1, const representations::NaoJoints &frame2);
    void printJoints(representations::NaoJoints &frame);

    Json::Value config;
    int iEpi = 0;
    int nbEpisodeSteps;
    int nbTotalSteps = 0;
    double currReward;
    double currState;
    double episodeAvgReward;

    std::ifstream learningFile;
    control::ControlStub controlStub;
    control::JointsController controller;
    representations::NaoJoints commandedJointsPos;
    representations::NaoJoints initialJointsPos;
    representations::NaoJoints jointsWeight;

    int referenceDataIt = 0;
};


#endif //ITANDROIDS_SOCCER3D_CPP_ZMPKICKLEARNINGAGENT_H