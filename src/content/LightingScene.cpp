#include "LightingScene.h"

void LightingScene::init()
{
    // position + normals
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint VBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // can reuse same VBO since the light src is also a cube, already bound. only position, no need for normals
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    lightingShader.load("shaders/simple_lighting.vs.glsl", "shaders/simple_lighting.fs.glsl");
    lightSourceShader.load("shaders/light_source.vs.glsl", "shaders/light_source.fs.glsl");
}

void LightingScene::setCamera(FlyCamera* cam)
{
    camera = cam;
}

void LightingScene::drawCurrent()
{
    if (camera == nullptr) {
        return;
    }

    // draw light source
    lightSourceShader.use();
    lightSourceShader.setVec3("lightColor", lightColor);
    lightSourceShader.setMat4("projection", camera->getProjectionMatrix());
    lightSourceShader.setMat4("view", camera->getViewMatrix());

    lightSourceModel = glm::mat4(1.0f);
    lightSourceModel = glm::translate(lightSourceModel, lightPos);
    lightSourceModel = glm::scale(lightSourceModel, glm::vec3(0.2f));
    lightSourceModel = getGlobalTransform() * lightSourceModel;     // matrix multiplication ordering: from right to left 
    lightSourceShader.setMat4("model", lightSourceModel);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // draw cube
    lightingShader.use();
    lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    lightingShader.setFloat("material.shininess", 32.0f);

    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    lightingShader.setVec3("light.ambient", ambientColor);
    lightingShader.setVec3("light.diffuse", diffuseColor);
    lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    lightingShader.setMat4("projection", camera->getProjectionMatrix());
    lightingShader.setMat4("view", camera->getViewMatrix());

    // world position for light pos
    auto& matrix = lightSourceModel;
    glm::vec4 pos = matrix * glm::vec4(0, 0, 0, 1.f);
    lightingShader.setVec3("light.position", glm::vec3(pos));

    lightingShader.setVec3("viewPos", camera->getPosition());

    cubeModel = glm::mat4(1.0f);
    //cubeModel = getGlobalTransform() * cubeModel;     // so cube does not rotate
    lightingShader.setMat4("model", cubeModel);

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightingScene::updateCurrent(float dt)
{
    deltaTime = dt;
    elapsedTime += dt;

    lightColor.x = sin(elapsedTime * 2.0f);
    lightColor.y = sin(elapsedTime * 0.7f);
    lightColor.z = sin(elapsedTime * 1.3f);

    currentAngle += dt;
    setRotationQuaternion(glm::angleAxis(currentAngle,
        glm::normalize(glm::vec3(0.5f, 1.0f, 0.3f))));
}
