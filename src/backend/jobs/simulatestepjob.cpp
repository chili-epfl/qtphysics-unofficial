#include <backend/jobs/simulatestepjob.h>
#include <backend/physicsmanager.h>

namespace Physics {

SimulateStepJob::SimulateStepJob(PhysicsManager* manager):
    QAspectJob()
{
    m_manager=manager;
}
void SimulateStepJob::run(){
    m_manager->m_physics_world->stepSimulation();
}

}
