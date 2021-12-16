#include "pch.h"

#include "ndtechSampleApp.h"

void ndtech::sample::OnMLHandTrackingKeyPose_OpenHandBack(ndtech::components::hand_tracking::HandTracker* handTracker, ndtech::BaseApp* app) {
  app->m_applicationContext.m_state = 0;
}

void ndtech::sample::OnMLHandTrackingKeyPose_Finger(ndtech::components::hand_tracking::HandTracker* handTracker, ndtech::BaseApp* app) {

  ndtech::sample::ndtechSampleApp* concreteApp = static_cast<ndtech::sample::ndtechSampleApp*>(app);

  if constexpr (ndtech::features::SupportsFeature<ndtechSampleApp, ndtech::features::hand_tracking>()) {
#if NDTECH_ML
    MLTransform transform;
    transform.position.x = 0;
    transform.position.y = 0;
    transform.position.z = 0;
    transform.rotation.w = 0;
    transform.rotation.x = 0;
    transform.rotation.y = 0;
    transform.rotation.z = 0;

    glm::vec3 pos{
      handTracker->handTrackingData.left_hand_state.hand_center_normalized.x,
      handTracker->handTrackingData.left_hand_state.hand_center_normalized.y,
      handTracker->handTrackingData.left_hand_state.hand_center_normalized.x };

    //glm::vec3  pos4 = glm::vec3(pos, 1.0f);

    //glm::mat4 trans4 = glm::translate(glm::make_mat4(components::triangles::Triangle::matrixData), glm::vec3{ transform.position.x, transform.position.y, transform.position.z });

    //glm::vec3 transformedPos = trans4 * pos4;

    //concreteApp->triangles[concreteApp->leftHandTriangleIndex].position.x = transformedPos.x;
    //concreteApp->triangles[concreteApp->leftHandTriangleIndex].position.y = transformedPos.y;
    //concreteApp->triangles[concreteApp->leftHandTriangleIndex].position.z = transformedPos.z;
    app->m_timer.TogglePause();

#endif
  }


}

void ndtech::sample::ndtechSampleApp::AfterWindowSet() {

  ndtech::App<Settings, ndtechSampleApp>::AfterWindowSet();
  InitializeEntities();
}

bool ndtech::sample::ndtechSampleApp::InitializeEntities() {
  LOG(INFO) << "Initializing Entities";

  if constexpr (ndtech::features::SupportsFeature<ndtechSampleApp, ndtech::features::hand_tracking>()) {
    LOG(INFO) << "supports hand tracking";
#if NDTECH_ML
    handTracker.handTrackingConfiguration.handtracking_pipeline_enabled = true;
    handTracker.handTrackingConfiguration.keypose_config[MLHandTrackingKeyPose::MLHandTrackingKeyPose_Ok] = true;
    handTracker.handTrackingConfiguration.keypose_config[MLHandTrackingKeyPose::MLHandTrackingKeyPose_Finger] = true;
    handTracker.handTrackingConfiguration.keypose_config[MLHandTrackingKeyPose::MLHandTrackingKeyPose_OpenHandBack] = true;
    handTracker.handTrackingConfiguration.pose_filter_level = MLPoseFilterLevel_2;

    handTracker.onMLHandTrackingKeyPose_Finger = ndtech::sample::OnMLHandTrackingKeyPose_Finger;
    handTracker.onMLHandTrackingKeyPose_OpenHandBack = ndtech::sample::OnMLHandTrackingKeyPose_OpenHandBack;
    handTracker.handTrackingConfiguration.keypoints_filter_level = MLKeypointFilterLevel::MLKeypointFilterLevel_0;

    IncreaseComponentStorageTo<ndtech::components::hand_tracking::HandTracker>(1);
    EntityType handTrackerEntity = AddEntity();
    AddComponent<ndtech::components::hand_tracking::HandTracker>(handTrackerEntity, handTracker);
#endif
  }
  Settings::EntityType& entity1 = AddEntity();

  float matrixData[16] = {
.25, 0, 0, 0,
0, .25, 0, 0,
0, 0, .25, 0,
0, 0, 0, 1 };

  typename VPCModelSystem::Component vpcModel1;
  vpcModel1.m_vertices.assign({
        {glm::vec3(-.25f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
      { glm::vec3(0.0f, .25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
      { glm::vec3(.25f,  0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}
    });
  vpcModel1.m_indices.assign({
    0,1,2
    });
  vpcModel1.m_position = { 0.3f, 0.0f, -2.0f };
  vpcModel1.m_scale = { 0.25f, 0.25f, 0.25f };
  vpcModel1.m_angularVelocityAxis = glm::vec3(0.0f, 0.0f, -1.0f);
  vpcModel1.m_angularVelocityRadiansPerSecond = glm::pi<float>();

  component1 = &AddComponent<typename VPCModelSystem::Component>(entity1, vpcModel1);


  Settings::EntityType& entity2 = AddEntity();


  typename VPCModelSystem::Component vpcModel2;
  vpcModel2.m_vertices.assign({
      { glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f)}, // left, bottom, back
      { glm::vec3(-0.1f, -0.1f,  0.1f), glm::vec3(0.0f, 0.0f, 1.0f)}, // left, bottom, front
      { glm::vec3(-0.1f,  0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f)}, // left, top, back
      { glm::vec3(-0.1f,  0.1f,  0.1f), glm::vec3(0.0f, 1.0f, 1.0f)}, // left, top, front
      { glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(1.0f, 0.0f, 0.0f)},  // right, bottom, back
      { glm::vec3(0.1f, -0.1f,  0.1f), glm::vec3(1.0f, 0.0f, 1.0f)},  // right, bottom, front
      { glm::vec3(0.1f,  0.1f, -0.1f), glm::vec3(1.0f, 1.0f, 0.0f)},  // right, top, back
      { glm::vec3(0.1f,  0.1f,  0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},  // right, top, front
    });
  vpcModel2.m_indices.assign({
        2,1,0, // -x
        2,3,1,

        6,4,5, // +x
        6,5,7,

        0,1,5, // -y
        0,5,4,

        2,6,7, // +y
        2,7,3,

        0,4,6, // -z
        0,6,2,

        1,3,7, // +z
        1,7,5,
    });
  vpcModel2.m_position = { -0.3f, 0.0f, -2.0f };
  vpcModel2.m_scale = { 1.25f, 1.25f, 1.25f };
  vpcModel2.m_angularVelocityAxis = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
  vpcModel2.m_angularVelocity = glm::angleAxis(180.0f, vpcModel2.m_angularVelocityAxis);
  vpcModel2.m_angularVelocityRadiansPerSecond = glm::pi<float>();

  component2 = &AddComponent<typename VPCModelSystem::Component>(entity2, vpcModel2);

  component2OriginalPosition = component2->m_position;


#if NDTECH_HOLO
  Settings::EntityType& entity3 = AddEntity();

  typename VPCModelSystem2::Component vpcModel3;

  vpcModel3.m_vertices.assign({
        {glm::vec3(-.25f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
      { glm::vec3(0.0f, .25f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
      { glm::vec3(.25f,  0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}
    });
  vpcModel3.m_indices.assign({
    0,1,2
    });

  component3 = &AddComponent<typename VPCModelSystem2::Component>(entity3, vpcModel3);


  typename VPCModelSystem2::Component::InstanceType vpcInstance1;
  vpcInstance1.m_position = { -0.3f, 0.0f, -2.0f };
  vpcInstance1.m_scale = { 0.25f, 0.25f, 0.25f };
  vpcInstance1.m_angularVelocity = glm::angleAxis(glm::pi<float>(), glm::vec3(0.0f, 0.0f, -1.0f));
  m_instance1Id = vpcInstance1.m_id;

  component3->AddInstance(vpcInstance1);



  Settings::EntityType& entity4 = AddEntity();

  typename VPCModelSystem2::Component::InstanceType vpcInstance2;
  vpcInstance2.m_position = { -0.1f, 0.2f, -2.0f };
  vpcInstance2.m_scale = { 0.25f, 0.25f, 0.25f };
  m_instance2Id = vpcInstance2.m_id;
  vpcInstance2.m_angularVelocity = glm::angleAxis(-2 * glm::pi<float>(), glm::vec3(0.0f, 0.0f, -1.0f));

  component3->AddInstance(vpcInstance2);
#endif






  typename VPCModelSystem2::Component vpcModel;

  Settings::EntityType& entity = AddEntity();


  vpcModel.m_vertices.assign({
      { glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f)}, // left, bottom, back
      { glm::vec3(-0.1f, -0.1f,  0.1f), glm::vec3(0.0f, 0.0f, 1.0f)}, // left, bottom, front
      { glm::vec3(-0.1f,  0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f)}, // left, top, back
      { glm::vec3(-0.1f,  0.1f,  0.1f), glm::vec3(0.0f, 1.0f, 1.0f)}, // left, top, front
      { glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(1.0f, 0.0f, 0.0f)},  // right, bottom, back
      { glm::vec3(0.1f, -0.1f,  0.1f), glm::vec3(1.0f, 0.0f, 1.0f)},  // right, bottom, front
      { glm::vec3(0.1f,  0.1f, -0.1f), glm::vec3(1.0f, 1.0f, 0.0f)},  // right, top, back
      { glm::vec3(0.1f,  0.1f,  0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},  // right, top, front
    });

  vpcModel.m_indices.assign({
        2,1,0, // -x
        2,3,1,

        6,4,5, // +x
        6,5,7,

        0,1,5, // -y
        0,5,4,

        2,6,7, // +y
        2,7,3,

        0,4,6, // -z
        0,6,2,

        1,3,7, // +z
        1,7,5,
    });

  //VPCModelSystem2::Component* component = &AddComponent<typename VPCModelSystem2::Component>(entity, vpcModel);

  //for (int col = 0; col < 4; col++) {
  //  for (int row = 0; row < 4; row++) {

  //    typename VPCModelSystem2::Component::InstanceType vpcInstance;
  //    vpcInstance.m_position = { -0.2f + 0.1f * col, 0.2f - 0.1f * row, -2.0f };
  //    vpcInstance.m_scale = { 0.25f, 0.25f, 0.25f };
  //    vpcInstance.m_angularVelocity = glm::angleAxis(-2 * glm::pi<float>(), glm::vec3(0.0f, 0.0f, -1.0f));
  //    vpcInstance.m_orientation = glm::angleAxis((-2 * .3f) * glm::pi<float>(), glm::vec3(1.0f, 1.0f, 1.0f));

  //    component->AddInstance(vpcInstance);

  //  }

  //}


  /////////////////////// VOID VB MODEL : START

  ndtech::components::VoidVertexBufferSystem& voidVBModelSystem = std::get<ndtech::components::VoidVertexBufferSystem>(m_componentSystems);

  RED_MATERIAL_ID = voidVBModelSystem.CreateMaterial(this, glm::vec4(1, 0, 0, 1));
  //GREEN_MATERIAL_ID = voidVBModelSystem.CreateMaterial(this, glm::vec4(0, 1, 0, 1));
  //BLUE_MATERIAL_ID = voidVBModelSystem.CreateMaterial(this, glm::vec4(0, 0, 1, 1));

  //std::vector<glm::vec3> vertices1({
  //  glm::vec3(-0.1f, -0.1f, -0.1f), // left, bottom, back
  //  glm::vec3(-0.1f, -0.1f,  0.1f), // left, bottom, front
  //  glm::vec3(-0.1f,  0.1f, -0.1f), // left, top, back
  //  glm::vec3(-0.1f,  0.1f,  0.1f), // left, top, front
  //  glm::vec3(0.1f, -0.1f, -0.1f),  // right, bottom, back
  //  glm::vec3(0.1f, -0.1f,  0.1f),  // right, bottom, front
  //  glm::vec3(0.1f,  0.1f, -0.1f),  // right, top, back
  //  glm::vec3(0.1f,  0.1f,  0.1f),  // right, top, front
  //  });

  //std::vector<unsigned short> indices1({
  //      2,1,0, // -x
  //      2,3,1,

  //      6,4,5, // +x
  //      6,5,7,

  //      0,1,5, // -y
  //      0,5,4,

  //      2,6,7, // +y
  //      2,7,3,

  //      0,4,6, // -z
  //      0,6,2,

  //      1,3,7, // +z
  //      1,7,5,
  //  });

  //std::vector<glm::vec3> vertices1({
  //glm::vec3(-.25f, 0.0f, 0.0f), 
  //glm::vec3(0.0f, 0.25f, 0.0f),
  //glm::vec3(0.25f,  0.0f, 0.0f)
  //  });

  //std::vector<unsigned short> indices1({
  //     0,1,2
  //  });

  //std::vector<glm::vec4> vertices1({
  //glm::vec4(-.25f, 0.0f, 0.0f, 1.0f), 
  //glm::vec4(0.0f, 0.25f, 0.0f, 1.0f),
  //glm::vec4(0.25f,  0.0f, 0.0f, 1.0f)
  //  });

  //std::vector<unsigned short> indices1({
  //     0,1,2
  //  });

  //std::vector<glm::vec4> vertices1({
  //  glm::vec4(-0.1f, -0.1f, -0.1f, 1.0f), // left, bottom, back
  //  glm::vec4(-0.1f, -0.1f,  0.1f, 1.0f), // left, bottom, front
  //  glm::vec4(-0.1f,  0.1f, -0.1f, 1.0f), // left, top, back
  //  glm::vec4(-0.1f,  0.1f,  0.1f, 1.0f), // left, top, front
  //  glm::vec4(0.1f, -0.1f, -0.1f, 1.0f),  // right, bottom, back
  //  glm::vec4(0.1f, -0.1f,  0.1f, 1.0f),  // right, bottom, front
  //  glm::vec4(0.1f,  0.1f, -0.1f, 1.0f),  // right, top, back
  //  glm::vec4(0.1f,  0.1f,  0.1f, 1.0f),  // right, top, front
  //  });

  //std::vector<unsigned short> indices1({
  //      2,1,0, // -x
  //      2,3,1,

  //      6,4,5, // +x
  //      6,5,7,

  //      0,1,5, // -y
  //      0,5,4,

  //      2,6,7, // +y
  //      2,7,3,

  //      0,4,6, // -z
  //      0,6,2,

  //      1,3,7, // +z
  //      1,7,5,
  //  });

  //std::vector<ndtech::components::ModelData> vertices1({
  //ndtech::components::ModelData{glm::vec3(-.1f, -.1f, 0.0f), 0.0f}, // 0 bottom front left
  //ndtech::components::ModelData{glm::vec3(-.1f, 0.1f, 0.0f), 0.0f}, // 1 top front left
  //ndtech::components::ModelData{glm::vec3(0.1f,  -.1f, 0.0f), 0.0f}, // 2 bottom front right
  //ndtech::components::ModelData{glm::vec3(0.1f,  0.1f, 0.0f), 0.0f}, // 3 top front right
  //  });

  //std::vector<unsigned short> indices1({
  //     0,1,2,
  //     1,3,2
  //  });  


  std::vector<ndtech::components::ModelVertex> vertices1({
ndtech::components::ModelVertex{glm::vec3(-.1f, -.1f, .1f), 0.0f}, // 0 bottom front left
ndtech::components::ModelVertex{glm::vec3(-.1f, 0.1f, .1f), 0.0f}, // 1 top front left
ndtech::components::ModelVertex{glm::vec3(0.1f,  -.1f, .1f), 0.0f}, // 2 bottom front right
ndtech::components::ModelVertex{glm::vec3(0.1f,  0.1f, .1f), 0.0f}, // 3 top front right
ndtech::components::ModelVertex{glm::vec3(-.1f, -.1f, -.1f), 0.0f}, // 4 bottom back left
ndtech::components::ModelVertex{glm::vec3(-.1f, 0.1f, -.1f), 0.0f}, // 5 top back left
ndtech::components::ModelVertex{glm::vec3(0.1f,  -.1f, -.1f), 0.0f}, // 6 bottom back right
ndtech::components::ModelVertex{glm::vec3(0.1f,  0.1f, -.1f), 0.0f}, // 7 top back right
    });

  std::vector<unsigned short> indices1({
       0,1,2, // Front
       1,3,2, // Front
       5,1,4, // Left
       1,0,4, // Left
       1,5,7, // Top
       1,7,3, // Top
       0,2,6, // Bottom
       0,6,4, // Bottom
       2,3,7, // Right
       2,7,6, // Right
       6,7,5, // Back
       6,5,4, // Back
    });



  //std::vector<ndtech::components::ModelData> vertices1({
  //  ndtech::components::ModelData{glm::vec3(-0.1f, -0.1f, -0.1f), 0.0f}, // left, bottom, back
  //  ndtech::components::ModelData{glm::vec3(-0.1f, -0.1f,  0.1f), 0.0f}, // left, bottom, front
  //  ndtech::components::ModelData{glm::vec3(-0.1f,  0.1f, -0.1f), 0.0f}, // left, top, back
  //  ndtech::components::ModelData{glm::vec3(-0.1f,  0.1f,  0.1f), 0.0f}, // left, top, front
  //  ndtech::components::ModelData{glm::vec3(0.1f, -0.1f, -0.1f), 0.0f},  // right, bottom, back
  //  ndtech::components::ModelData{glm::vec3(0.1f, -0.1f,  0.1f), 0.0f},  // right, bottom, front
  //  ndtech::components::ModelData{glm::vec3(0.1f,  0.1f, -0.1f), 0.0f},  // right, top, back
  //  ndtech::components::ModelData{glm::vec3(0.1f,  0.1f,  0.1f), 0.0f},  // right, top, front
  //  });

  //std::vector<unsigned short> indices1({
  //      2,1,0, // -x
  //      2,3,1,

  //      6,4,5, // +x
  //      6,5,7,

  //      0,1,5, // -y
  //      0,5,4,

  //      2,6,7, // +y
  //      2,7,3,

  //      0,4,6, // -z
  //      0,6,2,

  //      1,3,7, // +z
  //      1,7,5,
  //  });



  size_t modelId1 = voidVBModelSystem.CreateModel(vertices1, indices1, this);

  //unsigned int materialId1 = voidVBModelSystem.CreateMaterial(this, glm::vec4(0,1,0,1));

  //typename VoidVBModelSystem::Component tmpVoidVBComponent1 = voidVBModelSystem.CreateComponent(modelId1, materialId1, glm::vec3{ -0.1f, 0.1f, -2.0f }, glm::vec3{ 1.25f, 1.25f, 1.25f }, glm::quat(), this);

  typename VoidVBModelSystem::Component tmpVoidVBComponent1 = voidVBModelSystem.CreateComponent(modelId1, RED_MATERIAL_ID, glm::vec3{ -0.1f, 0.1f, -2.0f }, glm::vec3{ 1.25f, 1.25f, 1.25f }, glm::quat(), this);

  m_voidVBInstance1Id = tmpVoidVBComponent1.m_instanceId;

  //voidVBModelSystem.SetMaterialByVertexId(this, 0, BLUE_MATERIAL_ID);
  //voidVBModelSystem.SetMaterialByVertexId(this, 1, BLUE_MATERIAL_ID);
  //voidVBModelSystem.SetMaterialByVertexId(this, 2, BLUE_MATERIAL_ID);
  //voidVBModelSystem.SetMaterialByVertexId(this, 3, GREEN_MATERIAL_ID);
  //voidVBModelSystem.SetMaterialByVertexId(this, 4, GREEN_MATERIAL_ID);
  //voidVBModelSystem.SetMaterialByVertexId(this, 5, GREEN_MATERIAL_ID);


  //tmpVoidVBComponent1.m_position = { -0.4f, 0.1f, -2.0f };
  //tmpVoidVBComponent1.m_scale = { 1.25f, 1.25f, 1.25f };
  //tmpVoidVBComponent1.m_angularVelocityAxis = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
  //tmpVoidVBComponent1.m_angularVelocity = glm::angleAxis(180.0f, vpcModel2.m_angularVelocityAxis);
  //tmpVoidVBComponent1.m_angularVelocityRadiansPerSecond = glm::pi<float>();

  Settings::EntityType& voidVBModelEntity1 = AddEntity();

  VoidVBModelSystem::Component* voidVBComponent1 = &AddComponent<typename VoidVBModelSystem::Component>(voidVBModelEntity1, tmpVoidVBComponent1);


  ndtech::components::DirectionalLight directionalLight;
  directionalLight.color = { 1.0f ,0.0f ,0.0f };
  directionalLight.direction = { 1.0f, 1.0f, -1.0f };
  directionalLight.intensity = 1.0f;

  voidVBModelSystem.CreateDirectionalLight(directionalLight, this);


  /////////////////////// VOID VB MODEL : END

  //std::vector<glm::vec3> vertices2({
  //    glm::vec3(-.25f, 0.0f, 0.0f),
  //    glm::vec3(0.0f, .25f, 0.0f),
  //    glm::vec3(.25f,  0.0f, 0.0f)
  //  });

  //std::vector<unsigned short> indices2({
  //    0,1,2
  //  });

  //size_t modelId2 = voidVBModelSystem.CreateModel(vertices2, indices2, this);


  //typename VoidVBModelSystem::Component tmpVoidVBComponent2 = voidVBModelSystem.CreateComponent(modelId2, materialId1, glm::vec3{ -0.3f, -0.3f, -2.0f }, glm::vec3{ 1.25f, 1.25f, 1.25f }, glm::quat(), this);

  //Settings::EntityType& voidVBModelEntity2 = AddEntity();

  //VoidVBModelSystem::Component* voidVBComponent2 = &AddComponent<typename VoidVBModelSystem::Component>(voidVBModelEntity2, tmpVoidVBComponent2);



  //std::vector<glm::vec3> vertices2({
  //    glm::vec3(-.25f, 0.0f, 0.0f),
  //    glm::vec3(0.0f, .25f, 0.0f),
  //    glm::vec3(.25f,  0.0f, 0.0f)
  //  });

  //std::vector<unsigned short> indices2({
  //    0,1,2
  //  });

  //size_t modelId2 = voidVBModelSystem.CreateModel(vertices2, indices2);


  //typename VoidVBModelSystem::Component tmpVoidVBComponent2 = voidVBModelSystem.CreateComponent(modelId2);

  //Settings::EntityType& voidVBModelEntity2 = AddEntity();

  //VoidVBModelSystem::Component* voidVBComponent2 = &AddComponent<typename VoidVBModelSystem::Component>(voidVBModelEntity2, tmpVoidVBComponent2);



  //std::vector<glm::vec3> vertices3({
  //    glm::vec3(-.25f, 0.0f, 0.0f),
  //    glm::vec3(0.0f, .25f, 0.0f),
  //    glm::vec3(.25f,  0.0f, 0.0f)
  //  });

  //std::vector<unsigned short> indices3({
  //    0,1,2
  //  });

  //size_t modelId3 = voidVBModelSystem.CreateModel(vertices3, indices3);


  //typename VoidVBModelSystem::Component tmpVoidVBComponent3 = voidVBModelSystem.CreateComponent(modelId3);

  //Settings::EntityType& voidVBModelEntity3 = AddEntity();

  //VoidVBModelSystem::Component* voidVBComponent3 = &AddComponent<typename VoidVBModelSystem::Component>(voidVBModelEntity3, tmpVoidVBComponent3);



  return true;
}

void ndtech::sample::ndtechSampleApp::ConcreteUpdate(StepTimer timer) {

  double elapsedSeconds = timer.GetElapsedSeconds();
  ndtech::components::VoidVertexBufferSystem& voidVBModelSystem = std::get<ndtech::components::VoidVertexBufferSystem>(m_componentSystems);

  //// Update the position of the triangle
  //component1->m_position.x -= elapsedSeconds * .05;

  //// Update the position of the cube
  //float delta = (timer.GetTotalSeconds() - ((int)(timer.GetTotalSeconds() / 10) * 10));
  //component2->m_position.x = component2OriginalPosition.x + delta;


  //ApplyLambdaToInstance(component3, m_instance1Id, [elapsedSeconds](auto instance) {

  //  instance->m_position.x += elapsedSeconds * .05;
  //  instance->m_orientation = glm::angleAxis(static_cast<float>(glm::angle(instance->m_angularVelocity) * elapsedSeconds), glm::axis(instance->m_angularVelocity)) * instance->m_orientation;

  //  });

  //ApplyLambdaToInstance(component3, m_instance2Id, [elapsedSeconds](auto instance) {

  //  instance->m_position.y -= elapsedSeconds * .05;
  //  instance->m_orientation = glm::angleAxis(static_cast<float>(glm::angle(instance->m_angularVelocity) * elapsedSeconds), glm::axis(instance->m_angularVelocity)) * instance->m_orientation;

  //  });

  ApplyLambdaToInstance(voidVBModelSystem, m_voidVBInstance1Id, [elapsedSeconds, &voidVBModelSystem](auto& cpuOnlyInstance, auto& perInstanceData) {

    //cpuOnlyInstance.position.y -= elapsedSeconds * .05;
    //glm::quat angularVelocity = glm::angleAxis(glm::pi<float>(), glm::vec3(.250f, .250f, -.250f));

    // Update the orientation
    glm::quat orientationChange =
      glm::angleAxis(
        static_cast<float>(glm::pi<float>() * elapsedSeconds),
        glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));

    //cpuOnlyInstance.orientation = glm::angleAxis(static_cast<float>(glm::angle(angularVelocity) * elapsedSeconds), glm::axis(angularVelocity)) * cpuOnlyInstance.orientation;

    cpuOnlyInstance.orientation = orientationChange * cpuOnlyInstance.orientation;

    //perInstanceData.world = glm::translate(glm::mat4(), cpuOnlyInstance.position) * glm::mat4_cast(cpuOnlyInstance.orientation) * glm::scale(cpuOnlyInstance.scale);
    //voidVBModelSystem.m_transformationMatrix = perInstanceData.world;

    //voidVBModelSystem.m_transformationMatrix = glm::translate(glm::mat4(), cpuOnlyInstance.position) * glm::mat4_cast(cpuOnlyInstance.orientation) * glm::scale(cpuOnlyInstance.scale);
    perInstanceData.world = glm::translate(glm::mat4(), cpuOnlyInstance.position) * glm::mat4_cast(cpuOnlyInstance.orientation) * glm::scale(cpuOnlyInstance.scale);
    });



}

void ndtech::sample::ndtechSampleApp::PreUpdateComponentSystem(VPCModelSystem componentSystem, std::vector<VPCModelSystem::Component>* components, PlatformApp* app) {
  LOG(INFO) << "PreUpdateComponentSystem";
}

void ndtech::sample::ndtechSampleApp::PostUpdateComponentSystem(VPCModelSystem componentSystem, std::vector<VPCModelSystem::Component>* components, PlatformApp* app) {
  LOG(INFO) << "PostUpdateComponentSystem";
}