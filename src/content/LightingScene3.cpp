#include "LightingScene3.h"

void LightingScene3::init()
{
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    // positions all containers
    cubePositions = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    GLuint VBO;
    glGenVertexArrays(1, &cubesVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubesVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // light cube source
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    texture.load("resources/textures/container2.png");
    specularMap.load("resources/textures/container2_specular.png");
    emission.load("resources/textures/container2_emission.png");

    lightingShader.load("shaders/texture_lighting.vs.glsl", "shaders/mult_lighting.fs.glsl");
    lightingShader.use();       // need to use before setting up uniforms lel

    // dir light
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setInt("material.emission", 2);

    lightSourceShader.load("shaders/light_source.vs.glsl", "shaders/light_source.fs.glsl");
}

void LightingScene3::setCamera(FlyCamera* cam)
{
	camera = cam;
}

void LightingScene3::drawCurrent()
{
    if (camera == nullptr) {
        return;
    }


    // draw light source
    lightSourceShader.use();
    lightSourceShader.setVec3("lightColor", pointLightColor);
    lightSourceShader.setMat4("projection", camera->getProjectionMatrix());
    lightSourceShader.setMat4("view", camera->getViewMatrix());

    lightSourceModel = glm::mat4(1.0f);
    lightSourceModel = glm::translate(lightSourceModel, lightPos);
    lightSourceModel = glm::scale(lightSourceModel, glm::vec3(0.2f));
    lightSourceModel = getGlobalTransform() * lightSourceModel;     // matrix multiplication ordering: from right to left 
    lightSourceShader.setMat4("model", lightSourceModel);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    lightingShader.use();

    // directional light
    //lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    //lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    //lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    //lightingShader.setVec3("light.direction", lightDir);

    // point light
    //lightingShader.setVec3("pointLight.ambient", 0.2f, 0.2f, 0.2f);
    //lightingShader.setVec3("pointLight.diffuse", 0.5f, 0.5f, 0.5f);
    //lightingShader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setVec3("pointLight.ambient", pointLightColor * 0.1f);
    lightingShader.setVec3("pointLight.diffuse", pointLightColor);
    lightingShader.setVec3("pointLight.specular",  pointLightColor);
    lightingShader.setFloat("pointLight.constant", 1.0f);
    lightingShader.setFloat("pointLight.linear", 0.09f);
    lightingShader.setFloat("pointlight.quadratic", 0.032f);

    lightingShader.setVec3("pointLight.position", lightPos);
    lightingShader.setVec3("viewPos", camera->getPosition());
    
    lightingShader.setFloat("material.shininess", 32.0f);
    
    lightingShader.setMat4("projection", camera->getProjectionMatrix());
    lightingShader.setMat4("view", camera->getViewMatrix());


    // spot light(coming out of camera)
    lightingShader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("spotLight.constant", 1.0f);
    lightingShader.setFloat("spotLight.linear", 0.09f);
    lightingShader.setFloat("spotLight.quadratic", 0.032f);

    lightingShader.setVec3("spotLight.position", camera->getPosition());
    lightingShader.setVec3("spotLight.direction", camera->getDirection());
    lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

    lightingShader.setVec3("viewPos", camera->getPosition());

    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("projection", camera->getProjectionMatrix());
    lightingShader.setMat4("view", camera->getViewMatrix());


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getID());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap.getID());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, emission.getID());

    glBindVertexArray(cubesVAO);
    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        lightingShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void LightingScene3::updateCurrent(float dt)
{
}
