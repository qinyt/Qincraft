#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <string>
#include <glm/glm.hpp>
#include"glad\glad.h"

class Shader {
  public:
    Shader(const std::string &vertexFile, const std::string &fragmentFile);
    virtual ~Shader();

    void bind() const;

    void loadInt(GLuint location, int value);
    void loadFloat(GLuint location, float value);

    void loadVector2(GLuint location, const glm::vec2 &vect);
    void loadVector3(GLuint location, const glm::vec3 &vect);
    void loadVector4(GLuint location, const glm::vec4 &vect);

    void loadMatrix4(GLuint location, const glm::mat4 &matrix);

  protected:
    virtual void getUniforms() = 0;
    GLuint m_id;
};

#endif // SHADER_H_INCLUDED
