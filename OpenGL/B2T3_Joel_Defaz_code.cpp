#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Defaz Joel - CI: 1724915770", NULL, NULL);
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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    Shader ourShader("shaders/B2T3_Joel_Defaz.vs", "shaders/B2T3_Joel_Defaz.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    //Cara Trasera
    -0.5f, -0.5f, -0.5f,  0.33f, 0.5f, 
     0.5f, -0.5f, -0.5f,  0.16f, 0.5f, 
     0.5f,  0.5f, -0.5f,  0.16f, 0.35f,

     0.5f,  0.5f, -0.5f,  0.16f, 0.35f,
    -0.5f,  0.5f, -0.5f,  0.33f, 0.35f,
    -0.5f, -0.5f, -0.5f,  0.33f, 0.5f, 

    //Cara Delantera
    -0.5f, -0.5f,  0.5f,  0.55f, 0.5f,  
     0.5f, -0.5f,  0.5f,  0.72f, 0.5f,
     0.5f,  0.5f,  0.5f,  0.72f, 0.33f,

     0.5f,  0.5f,  0.5f,  0.72f, 0.33f,
    -0.5f,  0.5f,  0.5f,  0.55f, 0.33f,
    -0.5f, -0.5f,  0.5f,  0.55f, 0.5f,

    //Cara Lateral Izquierda
    -0.5f,  0.5f,  0.5f,  0.535f, 0.33f,  
    -0.5f,  0.5f, -0.5f,  0.34f, 0.33f,  
    -0.5f, -0.5f, -0.5f,  0.34f, 0.5f, 

    -0.5f, -0.5f, -0.5f,  0.34f, 0.5f, 
    -0.5f, -0.5f,  0.5f,  0.535f, 0.5f,  
    -0.5f,  0.5f,  0.5f,  0.535f, 0.33f,  

    //Cara Lateral Derecho
     0.5f,  0.5f,  0.5f,  0.73f, 0.33f,
     0.5f,  0.5f, -0.5f,  0.92f, 0.33f,
     0.5f, -0.5f, -0.5f,  0.92f, 0.5f,

     0.5f, -0.5f, -0.5f,  0.92f, 0.5f,
     0.5f, -0.5f,  0.5f,  0.73f, 0.5f,
     0.5f,  0.5f,  0.5f,  0.73f, 0.5f,

     //Cara Debajo
    -0.5f, -0.5f, -0.5f,  0.55f, 0.73f, 
     0.5f, -0.5f, -0.5f,  0.72f, 0.73f,  
     0.5f, -0.5f,  0.5f,  0.72f, 0.5f,  
     
     0.5f, -0.5f,  0.5f,  0.72f, 0.5f,  
    -0.5f, -0.5f,  0.5f,  0.55f, 0.5f,  
    -0.5f, -0.5f, -0.5f,  0.55f, 0.73f, 

    //Cara Encima 
    -0.5f,  0.5f, -0.5f,  0.55f, 0.08f,  
     0.5f,  0.5f, -0.5f,  0.72f, 0.08f,  
     0.5f,  0.5f,  0.5f,  0.72f, 0.32f,  

     0.5f,  0.5f,  0.5f,  0.72f, 0.32f,  
    -0.5f,  0.5f,  0.5f,  0.55f, 0.32f,  
    -0.5f,  0.5f, -0.5f,  0.55f, 0.08f   
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(2.5f, 2.0f, -2.5f),
        glm::vec3(-2.5f,  2.0f, 2.5f),
        glm::vec3(0.0f,  -2.5f, -1.5f),
        glm::vec3(1.0f,  0.0f,  -8.0f),
        glm::vec3(2.6f,  2.0f, 3.0f),
        glm::vec3(1.3f, -3.6f, 3.9f),
        glm::vec3(-6.2f, 6.4f, 2.8f),
        glm::vec3(-1.8f, 9.3f, -6.1f),
        glm::vec3(-2.8f, -0.8f, 5.0f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
 
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2, texture3;
    // texture 1
    // -----------------------------------------------------------------------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("textures/texture1.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // -----------------------------------------------------------------------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 3
// -----------------------------------------------------------------------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    data = stbi_load("textures/texture3.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture3"), 2);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        // activate shader
        ourShader.use();
		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		
		 // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        // render boxes
        ourShader.setFloat("num_text", 1);
        glBindVertexArray(VAO);
        float tiempo1 = sin(glfwGetTime()) / 0.5f;
        float tiempo2 = glfwGetTime();
        for (unsigned int i = 0; i < 4; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::rotate(model, tiempo2, glm::vec3(0.0f, 0.5f, 0.0f));
            model = glm::translate(model, cubePositions[i]);
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        ourShader.setFloat("num_text", 2);
        glBindVertexArray(VAO);
        for (unsigned int i = 4; i < 8; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, tiempo1, glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        ourShader.setFloat("num_text", 3);
        glBindVertexArray(VAO);
        for (unsigned int i = 8; i < 12; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::translate(model, cubePositions[i]);
            model = glm::scale(model, glm::vec3(tiempo1 / 2 + 0.5, tiempo1 / 2 + 0.5, tiempo1 / 2 + 0.5));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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