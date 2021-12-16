#pragma once

#include <ndtech/App.h>
#include <ndtech/ApplicationSettings.h>
#include <ndtechComponents/hand_tracking.h>
#include <ndtech/TypeUtilities.h>
#include <ndtechComponents/ModelSystem.h>
#include <ndtech/VertexTypes.h>
#include <ndtechComponents/IndexedInstancedIndirectModelSystem.h>
#include <ndtechComponents/VoidVertexBufferSystem.h>


namespace ndtech {
  namespace sample {

    void OnMLHandTrackingKeyPose_OpenHandBack(ndtech::components::hand_tracking::HandTracker* handTracker, ndtech::BaseApp* app);
    void OnMLHandTrackingKeyPose_Finger(ndtech::components::hand_tracking::HandTracker* handTracker, ndtech::BaseApp* app);

    using VPCModelSystem = ndtech::components::ModelSystem<ndtech::vertexTypes::VertexPositionColor>;
    using VPCModelSystem2 = ndtech::components::IndexedInstancedIndirectModelSystem<ndtech::vertexTypes::VertexPositionColor>;

    using VoidVBModelSystem = ndtech::components::VoidVertexBufferSystem;
    using ComponentSystems = TypeUtilities::Typelist<ndtech::components::hand_tracking::HandTrackerSystem, VPCModelSystem, VPCModelSystem2, VoidVBModelSystem>;
    using Components = TypeUtilities::Typelist<ndtech::components::hand_tracking::HandTracker, typename VPCModelSystem::Component, VPCModelSystem2::Component, VoidVBModelSystem::Component>;
    using Settings = ApplicationSettings<Components, ComponentSystems>;

    //using VoidVBModelSystem = ndtech::components::VoidVertexBufferSystem;
    //using ComponentSystems = TypeUtilities::Typelist<VoidVBModelSystem>;
    //using Components = TypeUtilities::Typelist<VoidVBModelSystem::Component>;
    //using Settings = ApplicationSettings<Components, ComponentSystems>;

    //using ComponentSystems = TypeUtilities::Typelist<ndtech::components::hand_tracking::HandTrackerSystem, VPCModelSystem, VPCModelSystem2>;
    //using Components = TypeUtilities::Typelist<ndtech::components::hand_tracking::HandTracker, typename VPCModelSystem::Component, VPCModelSystem2::Component>;
    //using Settings = ApplicationSettings<Components, ComponentSystems>;


    struct ndtechSampleApp : public ndtech::App<Settings, ndtechSampleApp> {

#if NDTECH_SUPPORTS_FINGER_TRACKING
      //VPCModelSystem::Component leftHandTriangle;
      int leftHandTriangleIndex = -1;
      ndtech::components::hand_tracking::HandTracker handTracker{};
#endif
      VPCModelSystem::Component*      component1;
      VPCModelSystem::Component*      component2;
      VPCModelSystem2::Component*     component3;

      size_t                      m_instance1Id;
      size_t                      m_instance2Id;

      glm::vec3 component2OriginalPosition;

      unsigned int RED_MATERIAL_ID;
      unsigned int BLUE_MATERIAL_ID;
      unsigned int GREEN_MATERIAL_ID;

      VoidVBModelSystem::Component*   component4;
      size_t                          m_voidVBInstance1Id;
      size_t                          m_voidVBInstance2Id;

      void AfterWindowSet() override;
      void PreUpdateComponentSystem(VPCModelSystem componentSystem, std::vector<VPCModelSystem::Component>* components, PlatformApp* app);
      void PostUpdateComponentSystem(VPCModelSystem componentSystem, std::vector<VPCModelSystem::Component>* components, PlatformApp* app);

      template<typename LambdaType>
      void ApplyLambdaToInstance(VPCModelSystem2::Component* component, size_t instanceId, LambdaType lambdaFunction) {
        auto instance = std::find_if(
          component->m_instances.begin(),
          component->m_instances.end(),
          // if it is the right instance ide
          [instanceId](VPCModelSystem2::Component::InstanceType instance) {
            return instance.m_id == instanceId;
          });

        if (instance != component->m_instances.end()) {
          lambdaFunction(instance);
        }
      }

      template<typename LambdaType>
      void ApplyLambdaToInstance(VoidVBModelSystem& voidVBModelSystem, size_t instanceId, LambdaType lambdaFunction) {

        if (instanceId < voidVBModelSystem.m_cpuOnlyInstanceData.size()) {
          ndtech::components::CPUOnlyInstanceData& cpuOnlyInstanceData = voidVBModelSystem.m_cpuOnlyInstanceData[instanceId];
          ndtech::components::PerInstanceData& perInstanceData = voidVBModelSystem.m_perInstanceData[instanceId];

          lambdaFunction(cpuOnlyInstanceData, perInstanceData);
        }

      }

    protected:
      bool InitializeEntities();
      void ConcreteUpdate(StepTimer timer) override;
    public:
    };

  }



}