#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include <iostream>
#include "mesh.h"
#include "camera.h"
#include "cylinder.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
void CreateDesk();
void CreateMonitor();
void CreateScreen();
void CreateSpeakerBase();
void CreateSpeaker();
void CreateKeyboard();
void CreateKeys();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(-2.0f, 1.2f, -0.5f);

// VAOs & VBOs
unsigned int VBO, VBO2, VBO3, VBO4;
unsigned int VAO, VAO2, VAO3, VAO4;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("shaderfiles/6.multiple_lights.vs", "shaderfiles/6.multiple_lights.fs");
    Shader lightCubeShader("shaderfiles/6.light_cube.vs", "shaderfiles/6.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

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
    glm::vec3 cubePositions[] = {
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
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(-1.5f, 0.5f, -0.5f),
        glm::vec3(-1.0f, 0.3f,  1.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);



    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    unsigned int deskMap = loadTexture("images/desk.jpg");
    unsigned int computerMap = loadTexture("images/base.jpg");
    unsigned int screenMap = loadTexture("images/computer.jpg");
    unsigned int lampMap = loadTexture("images/lamp.jpg");
    unsigned int lampBaseMap = loadTexture("images/lamp2.jpg");
    unsigned int speakerMap = loadTexture("images/speaker.jpg");
    unsigned int speakerBaseMap = loadTexture("images/speakerbase.jpg");
    unsigned int keyboardMap = loadTexture("images/keyboard.jpg");
    unsigned int keysMap = loadTexture("images/keys.jpg");


    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("desk.text", 0);
    lightingShader.setInt("computer.text", 1);
    lightingShader.setInt("lamp.text", 2);
    lightingShader.setInt("lampBase.text", 3);
    lightingShader.setInt("screen.text", 3);
    lightingShader.setInt("speakerBase.text", 3);
    lightingShader.setInt("speaker.text", 3);
    lightingShader.setInt("keyboard.text", 3);
    lightingShader.setInt("keys.text", 3);




    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.09);
        lightingShader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[1].constant", 0.1f);
        lightingShader.setFloat("pointLights[1].linear", 0.09);
        lightingShader.setFloat("pointLights[1].quadratic", 0.064);
        // point light 3
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.09);
        lightingShader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.09);
        lightingShader.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        lightingShader.setVec3("spotLight.position", -10.0f, 10.0f, 10.0f);
        lightingShader.setVec3("spotLight.direction", camera.Front);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.0);
        lightingShader.setFloat("spotLight.quadratic", 0.0);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deskMap);


        // render containers
        glBindVertexArray(VAO);

        CreateDesk();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, lampMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(-2.0f, 0.75f, -0.5f));
        lightingShader.setMat4("model", model);

        static_meshes_3D::Cylinder C(0.45, 100, 1.0, true, true, true);
        C.render();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, lampBaseMap);
        glBindVertexArray(VAO2);

        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -0.5f));
        lightingShader.setMat4("model", model);

        static_meshes_3D::Cylinder lamp(0.05, 100, 1.0, true, true, true);
        lamp.render();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, lampBaseMap);
        glBindVertexArray(VAO2);

        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(-2.0f, -0.45f, -0.5f));
        lightingShader.setMat4("model", model);

        static_meshes_3D::Cylinder lamp2(0.5, 100, 0.1, true, true, true);
        lamp2.render();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, computerMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        lightingShader.setMat4("model", model);

        CreateMonitor();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, screenMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.005f));
        lightingShader.setMat4("model", model);

        CreateScreen();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, speakerBaseMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(1.25f, -0.5f, 0.25f));
        lightingShader.setMat4("model", model);

        CreateSpeakerBase();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, speakerBaseMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(-1.25f, -0.5f, 0.25f));
        lightingShader.setMat4("model", model);

        CreateSpeakerBase();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, speakerBaseMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(1.25f, -0.35f, 0.25f));
        model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setMat4("model", model);

        static_meshes_3D::Cylinder speaker(0.05, 100, 0.1, true, true, true);
        speaker.render();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, speakerMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(1.25f, -0.5f, 0.255f));
        lightingShader.setMat4("model", model);

        CreateSpeaker();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, speakerMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(-1.25f, -0.5f, 0.255f));
        lightingShader.setMat4("model", model);

        CreateSpeaker();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, keyboardMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0f, -0.4f, 1.0f));
        lightingShader.setMat4("model", model);

        CreateKeyboard();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, keysMap);
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0f, -0.395f, 1.0f));
        lightingShader.setMat4("model", model);

        CreateKeys();

        // also draw the lamp object(s)
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightCubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void CreateDesk() {
    float vertices[] = {
        //DESK [6]
        -3.0f, -0.5f, -2.0f, 0.0f, 0.0f,
         3.0f, -0.5f, -2.0f, 1.0f, 0.0f,
         3.0f, -0.5f, 2.0f,  1.0f, 1.0f,
         3.0f, -0.5f, 2.0f,  1.0f, 1.0f,
        -3.0f, -0.5f, 2.0f,  0.0f, 1.0f,
        -3.0f, -0.5f, -2.0f, 0.0f, 0.0f,

        //FRONT [6]
        -3.0f, -0.55f, 2.0f, 0.0f, 0.0f,
         3.0f, -0.55f, 2.0f, 1.0f, 0.0f,
         3.0f, -0.5f, 2.0f,  1.0f, 1.0f,
         3.0f, -0.5f, 2.0f,  1.0f, 1.0f,
        -3.0f, -0.5f, 2.0f,  0.0f, 1.0f,
        -3.0f, -0.55f, 2.0f, 0.0f, 0.0f,

        //BACK [6]
        -3.0f, -0.55f, -2.0f, 0.0f, 0.0f,
         3.0f, -0.55f, -2.0f, 1.0f, 0.0f,
         3.0f, -0.5f, -2.0f,  1.0f, 1.0f,
         3.0f, -0.5f, -2.0f,  1.0f, 1.0f,
        -3.0f, -0.5f, -2.0f,  0.0f, 1.0f,
        -3.0f, -0.55f, -2.0f, 0.0f, 0.0f,


        //SIDE ONE [6]
        3.0f, -0.5f, 2.0f,   0.0f, 0.0f,
        3.0f, -0.5f, -2.0f,  1.0f, 0.0f,
        3.0f, -0.55f, -2.0f, 1.0f, 1.0f,
        3.0f, -0.55f, -2.0f, 1.0f, 1.0f,
        3.0f, -0.55f, 2.0f,  0.0f, 1.0f,
        3.0f, -0.5f, 2.0f,   0.0f, 0.0f,

        //SIDE TWO [6]
        -3.0f, -0.5f, 2.0f,   0.0f, 0.0f,
        -3.0f, -0.5f, -2.0f,  1.0f, 0.0f,
        -3.0f, -0.55f, -2.0f, 1.0f, 1.0f,
        -3.0f, -0.55f, -2.0f, 1.0f, 1.0f,
        -3.0f, -0.55f, 2.0f,  0.0f, 1.0f,
        -3.0f, -0.5f, 2.0f,   0.0f, 0.0f,

        //BOTTOM
       -3.0f, -0.55f, -2.0f, 1.0f, 1.0f,
        3.0f, -0.55f, -2.0f, 0.0f, 1.0f,
        3.0f, -0.55f, 2.0f,  0.0f, 0.0f,
        3.0f, -0.55f, 2.0f,  1.0f, 1.0f,
       -3.0f, -0.55f, 2.0f,  0.0f, 1.0f,
       -3.0f, -0.55f, -2.0f, 0.0f, 0.0f,
    };
    unsigned int VBO4, VAO4;


    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);

    glBindVertexArray(VAO4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
void CreateMonitor() {
    float vertices[] = {

        //BASE OF MONITOR [18]
       -0.5f, -0.5f, 0.0f,   1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f,
       -0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,

       -0.5f, -0.5f, -0.3f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.3f,   1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,     1.0f, 1.0f,

       -0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,     1.0f, 1.0f,

       -0.5f, -0.5f, -0.3f,   0.0f, 1.0f,
       -0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,     0.0f, 1.0f,

        0.5f, -0.5f, -0.3f,   0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,     0.0f, 1.0f,

        //SCREEN

        //FRONT [6]
        -1.0f, -0.25f, 0.05f, 0.0f, 0.0f,
         1.0f, -0.25f, 0.05f, 1.0f, 0.0f,
         1.0f, 1.0f, 0.05f,   1.0f, 1.0f,
         1.0f, 1.0f, 0.05f,   1.0f, 1.0f,
        -1.0f, 1.0f, 0.05f,   0.0f, 1.0f,
        -1.0f, -0.25f, 0.05f, 0.0f, 0.0f,

        //BACK [6]
       -1.0f, -0.25f, -0.05f, 0.0f, 0.0f,
        1.0f, -0.25f, -0.05f, 1.0f, 0.0f,
        1.0f, 1.0f, -0.05f,   1.0f, 1.0f,
        1.0f, 1.0f, -0.05f,   1.0f, 1.0f,
       -1.0f, 1.0f, -0.05f,   0.0f, 1.0f,
       -1.0f, -0.25f, -0.05f, 0.0f, 0.0f,

       //TOP [6]
       -1.0f, 1.0f, -0.05f,   0.0f, 0.0f,
        1.0f, 1.0f, -0.05f,   0.0f, 1.0f,
        1.0f, 1.0f, 0.05f,    1.0f, 1.0f,
        1.0f, 1.0f, 0.05f,    1.0f, 1.0f,
       -1.0f, 1.0f, 0.05f,    0.0f, 1.0f,
       -1.0f, 1.0f, -0.05f,   0.0f, 0.0f,

       //BOTTOM [6]
       -1.0f, -0.25f, -0.05f, 0.0f, 0.0f,
        1.0f, -0.25f, -0.05f, 0.0f, 1.0f,
        1.0f, -0.25f, 0.05f,  1.0f, 1.0f,
        1.0f, -0.25f, 0.05f,  1.0f, 1.0f,
       -1.0f, -0.25f, 0.05f,  0.0f, 1.0f,
       -1.0f, -0.25f, -0.05f, 0.0f, 0.0f,

       //SIDE ONE [6]
        1.0f, 1.0f, 0.05f,    0.0f, 0.0f,
        1.0f, 1.0f, -0.05f,   1.0f, 0.0f,
        1.0f, -0.25f, -0.05f, 1.0f, 1.0f,
        1.0f, -0.25f, -0.05f, 1.0f, 1.0f,
        1.0f, -0.25f, 0.05f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.05f,    0.0f, 0.0f,

        //SIDE TWO [6]
        -1.0f, 1.0f, 0.05f,    0.0f, 0.0f,
        -1.0f, 1.0f, -0.05f,   1.0f, 0.0f,
        -1.0f, -0.25f, -0.05f, 1.0f, 1.0f,
        -1.0f, -0.25f, -0.05f, 1.0f, 1.0f,
        -1.0f, -0.25f, 0.05f,  0.0f, 1.0f,
        -1.0f, 1.0f, 0.05f,    0.0f, 0.0f,
    };


    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render boxes
    glBindVertexArray(VAO3);
    // calculate the model matrix for each object and pass it to shader before drawing

    glDrawArrays(GL_TRIANGLES, 0, 54);
}

void CreateScreen() {

    float vertices[] = {
        //SCREEN

            //FRONT [6]
           -1.0f, -0.25f, 0.05f, 0.0f, 0.0f,
            1.0f, -0.25f, 0.05f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.05f,   1.0f, 1.0f,
            1.0f, 1.0f, 0.05f,   1.0f, 1.0f,
           -1.0f, 1.0f, 0.05f,   0.0f, 1.0f,
           -1.0f, -0.25f, 0.05f, 0.0f, 0.0f,

    };


    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render boxes
    glBindVertexArray(VAO3);
    // calculate the model matrix for each object and pass it to shader before drawing

    glDrawArrays(GL_TRIANGLES, 0, 6);
}


void CreateSpeakerBase() {
    float vertices[] = {

        //FRONT [6]
        -0.25f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.25f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.25f, 1.0f, 0.0f,   1.0f, 1.0f,
         0.25f, 1.0f, 0.0f,   1.0f, 1.0f,
        -0.25f, 1.0f, 0.0f,   0.0f, 1.0f,
        -0.25f, 0.0f, 0.0f, 0.0f, 0.0f,

        //BACK [6]
        -0.25f, 0.0f, -0.6f, 0.0f, 0.0f,
         0.25f, 0.0f, -0.6f, 1.0f, 0.0f,
         0.25f, 0.85f, -0.6f,   1.0f, 1.0f,
         0.25f, 0.85f, -0.6f,   1.0f, 1.0f,
        -0.25f, 0.85f, -0.6f,   0.0f, 1.0f,
        -0.25f, 0.0f, -0.6f, 0.0f, 0.0f,

        //TOP [6]
        -0.25f, 0.85f, -0.6f,   0.0f, 0.0f,
         0.25f, 0.85f, -0.6f,   0.0f, 1.0f,
         0.25f, 1.0f, 0.0f,    1.0f, 1.0f,
         0.25f, 1.0f, 0.0f,    1.0f, 1.0f,
        -0.25f, 1.0f, 0.0f,    0.0f, 1.0f,
        -0.25f, 0.85f, -0.6f,   0.0f, 0.0f,

        //BOTTOM [6]
        -0.25f, 0.0f, -0.6f,   0.0f, 0.0f,
         0.25f, 0.0f, -0.6f,   0.0f, 1.0f,
         0.25f, 0.0f, 0.0f,    1.0f, 1.0f,
         0.25f, 0.0f, 0.0f,    1.0f, 1.0f,
        -0.25f, 0.0f, 0.0f,    0.0f, 1.0f,
        -0.25f, 0.0f, -0.6f,   0.0f, 0.0f,

        //SIDE ONE [6]
         0.25f, 1.0f, 0.0f,   0.0f, 0.0f,
         0.25f, 0.85f, -0.6f, 1.0f, 0.0f,
         0.25f, 0.0f, -0.6f,  1.0f, 1.0f,
         0.25f, 0.0f, -0.6f,  1.0f, 1.0f,
         0.25f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.25f, 1.0f, 0.0f,   0.0f, 0.0f,

         //SIDE TWO [6]
         -0.25f, 1.0f, 0.0f,   0.0f, 0.0f,
         -0.25f, 0.85f, -0.6f, 1.0f, 0.0f,
         -0.25f, 0.0f, -0.6f,  1.0f, 1.0f,
         -0.25f, 0.0f, -0.6f,  1.0f, 1.0f,
         -0.25f, 0.0f, 0.0f,   0.0f, 1.0f,
         -0.25f, 1.0f, 0.0f,   0.0f, 0.0f,
    };


    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render boxes
    glBindVertexArray(VAO3);
    // calculate the model matrix for each object and pass it to shader before drawing

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CreateSpeaker() {
    float vertices[] = {

        //FRONT [6]
        -0.25f, 0.3f, 0.0f,  0.0f, 0.0f,
         0.25f, 0.3f, 0.0f,  1.0f, 0.0f,
         0.25f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.25f, 1.0f, 0.0f,  1.0f, 1.0f,
        -0.25f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.25f, 0.3f, 0.0f,  0.0f, 0.0f,

        //BACK [6]
        -0.25f, 0.3f, -0.05f,  0.0f, 0.0f,
         0.25f, 0.3f, -0.05f,  1.0f, 0.0f,
         0.25f, 0.85f, -0.05f, 1.0f, 1.0f,
         0.25f, 0.85f, -0.05f, 1.0f, 1.0f,
        -0.25f, 0.85f, -0.05f, 0.0f, 1.0f,
        -0.25f, 0.3f, -0.05f,  0.0f, 0.0f,

        //TOP [6]
        -0.25f, 0.85f, -0.05f,  0.0f, 0.0f,
         0.25f, 0.85f, -0.05f,  0.0f, 1.0f,
         0.25f, 1.0f, 0.0f,     1.0f, 1.0f,
         0.25f, 1.0f, 0.0f,     1.0f, 1.0f,
        -0.25f, 1.0f, 0.0f,     0.0f, 1.0f,
        -0.25f, 0.85f, -0.05f,  0.0f, 0.0f,

        //BOTTOM [6]
        -0.25f, 0.0f, -0.05f,  0.0f, 0.0f,
         0.25f, 0.0f, -0.05f,  0.0f, 1.0f,
         0.25f, 0.0f, 0.0f,    1.0f, 1.0f,
         0.25f, 0.0f, 0.0f,    1.0f, 1.0f,
        -0.25f, 0.0f, 0.0f,    0.0f, 1.0f,
        -0.25f, 0.0f, -0.05f,  0.0f, 0.0f,

        //SIDE ONE [6]
         0.25f, 1.0f, 0.0f,    0.0f, 0.0f,
         0.25f, 0.85f, -0.05f, 1.0f, 0.0f,
         0.25f, 0.0f, -0.05f,  1.0f, 1.0f,
         0.25f, 0.0f, -0.05f,  1.0f, 1.0f,
         0.25f, 0.0f, 0.0f,    0.0f, 1.0f,
         0.25f, 1.0f, 0.0f,    0.0f, 0.0f,

         //SIDE TWO [6]
         -0.25f, 1.0f, 0.0f,    0.0f, 0.0f,
         -0.25f, 0.85f, -0.05f, 1.0f, 0.0f,
         -0.25f, 0.0f, -0.05f,  1.0f, 1.0f,
         -0.25f, 0.0f, -0.05f,  1.0f, 1.0f,
         -0.25f, 0.0f, 0.0f,    0.0f, 1.0f,
         -0.25f, 1.0f, 0.0f,    0.0f, 0.0f,
    };


    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render boxes
    glBindVertexArray(VAO3);
    // calculate the model matrix for each object and pass it to shader before drawing

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CreateKeyboard() {
    float vertices[] = {
        //DESK [6]
        //TOP
        -0.5f, 0.0f, -0.25f,   0.0f, 0.0f,
         0.5f, 0.0f, -0.25f,   1.0f, 0.0f,
         0.5f, -0.025f, 0.25f, 1.0f, 1.0f,
         0.5f, -0.025f, 0.25f, 1.0f, 1.0f,
        -0.5f, -0.025f, 0.25f, 0.0f, 1.0f,
        -0.5f, 0.0f, -0.25f,   0.0f, 0.0f,

        //BOTTOM
        -0.5f, -0.05f, -0.25f, 0.0f, 0.0f,
         0.5f, -0.05f, -0.25f, 1.0f, 0.0f,
         0.5f, -0.05f, 0.25f,  1.0f, 1.0f,
         0.5f, -0.05f, 0.25f,  1.0f, 1.0f,
        -0.5f, -0.05f, 0.25f,  0.0f, 1.0f,
        -0.5f, -0.05f, -0.25f, 0.0f, 0.0f,

        //FRONT [6]
        -0.5f, -0.05f, 0.25f,   0.0f, 0.0f,
         0.5f, -0.05f, 0.25f,   1.0f, 0.0f,
         0.5f,  -0.025f, 0.25f, 1.0f, 1.0f,
         0.5f,  -0.025f, 0.25f, 1.0f, 1.0f,
        -0.5f,  -0.025f, 0.25f, 0.0f, 1.0f,
        -0.5f, -0.05f, 0.25f,   0.0f, 0.0f,

        //BACK [6]
        -0.5f, -0.05f, -0.25f, 0.0f, 0.0f,
         0.5f, -0.05f, -0.25f, 1.0f, 0.0f,
         0.5f,  0.0f, -0.25f,  1.0f, 1.0f,
         0.5f,  0.0f, -0.25f,  1.0f, 1.0f,
        -0.5f,  0.0f, -0.25f,  0.0f, 1.0f,
        -0.5f, -0.05f, -0.25f, 0.0f, 0.0f,


        //SIDE ONE [6]
        0.5f,  -0.025f, 0.25f, 0.0f, 0.0f,
        0.5f,  0.0f, -0.25f,   1.0f, 0.0f,
        0.5f, -0.05f, -0.25f,  1.0f, 1.0f,
        0.5f, -0.05f, -0.25f,  1.0f, 1.0f,
        0.5f, -0.05f, 0.25f,   0.0f, 1.0f,
        0.5f,  -0.025f, 0.25f, 0.0f, 0.0f,

        //SIDE TWO [6]
        -0.5f, -0.025f, 0.25f,  0.0f, 0.0f,
        -0.5f,  0.0f, -0.25f,   1.0f, 0.0f,
        -0.5f, -0.05f, -0.25f,  1.0f, 1.0f,
        -0.5f, -0.05f, -0.25f,  1.0f, 1.0f,
        -0.5f, -0.025f, 0.25f,  0.0f, 1.0f,
        -0.5f,  -0.025f, 0.25f, 0.0f, 0.0f,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render boxes
    glBindVertexArray(VAO3);
    // calculate the model matrix for each object and pass it to shader before drawing

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CreateKeys() {
    float vertices[] = {
        //DESK [6]
        //TOP
        -0.5f, 0.0f, -0.25f,   1.0f, 1.0f,
         0.5f, 0.0f, -0.25f,   0.0f, 1.0f,
         0.5f, -0.025f, 0.25f, 0.0f, 0.0f,
         0.5f, -0.025f, 0.25f, 0.0f, 0.0f,
        -0.5f, -0.025f, 0.25f, 1.0f, 0.0f,
        -0.5f, 0.0f, -0.25f,   1.0f, 1.0f,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render boxes
    glBindVertexArray(VAO3);
    // calculate the model matrix for each object and pass it to shader before drawing

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
